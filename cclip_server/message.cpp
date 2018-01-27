#include "message.h"

void clear_buffer(vector<char> &buffer);
void log_sql(sql::SQLException &e, ofstream &lerr, mutex &mtx_errorlog);
void client_loop(SSL *ssl, ofstream &lerr, mutex &mtx_errorlog, 
	const string &uname, vector<char> &buffer, 
	vector<auto_ptr<sql::PreparedStatement>>& stmts);
int dt_to_buffer(auto_ptr<istream> &dt, vector<char> &buffer, int pstart);

int client_login(SOCKET client, SSL *ssl, ofstream &lerr, mutex &mtx_errorlog)
{
	vector<char> buffer(BUFFER_SIZE);
	int receive_len = 0;

	auto_ptr<sql::Connection> con;
	vector<auto_ptr<sql::PreparedStatement>> stmts(NUM_STMT);
	try {
		db_initialize(con, stmts);
	}
	catch (sql::SQLException &e) {
		log_sql(e, lerr, mtx_errorlog);
		close_client(client, ssl);
		return EXIT_FAILURE;
	}

	string username;
	string password;
	int match_pass = 0;

	receive_len = SSL_read(ssl, &(buffer[0]), BUFFER_SIZE);
	if (receive_len < BUFFER_SIZE) {
		switch (buffer[0]) {
		case H_LOG_IN:
		{
			username = &(buffer[LEN_HEADER]);
			password = &(buffer[LEN_HEADER + LEN_UNAME]);
			if (username.length() < LEN_UNAME && password.length() < LEN_UPASS) {
				try {
					match_pass = db_check_pass(stmts, username, password);
				}
				catch (sql::SQLException &e) {
					log_sql(e, lerr, mtx_errorlog);
					close_client(client, ssl);
					return EXIT_FAILURE;
				}
				if (match_pass == 1) {
					SSL_write(ssl, &M_ACCEPTED, sizeof(M_ACCEPTED));
					client_loop(ssl, lerr, mtx_errorlog, username, buffer, stmts);
					close_client(client, ssl);
					return EXIT_SUCCESS;
				}
			}
			break;
		}
		case H_NEW_USER:
		{
			username = &(buffer[LEN_HEADER]);
			password = &(buffer[LEN_HEADER + LEN_UNAME]);
			if (username.length() < LEN_UNAME && password.length() < LEN_UPASS) {
				try {
					db_new_user(stmts, username, password);
				}
				catch (sql::SQLException &e) {
					log_sql(e, lerr, mtx_errorlog);
					close_client(client, ssl);
					return EXIT_FAILURE;
				}
				SSL_write(ssl, &M_ACCEPTED, sizeof(M_ACCEPTED));
				close_client(client, ssl);
				return EXIT_SUCCESS;
			}
			break;
		}
		default:
			close_client(client, ssl);
			return EXIT_FAILURE;
		}
	}
}

void clear_buffer(vector<char> &buffer)
{
	memset(&(buffer[0]), 0, buffer.size());
}

void log_sql(sql::SQLException &e, ofstream &lerr, mutex &mtx_errorlog)
{
	/*
	MySQL Connector/C++ throws three different exceptions:

	- sql::MethodNotImplementedException (derived from sql::SQLException)
	- sql::InvalidArgumentException (derived from sql::SQLException)
	- sql::SQLException (derived from std::runtime_error)
	*/
	stringstream err;
	err << "# ERR: SQLException in " << __FILE__
		<< "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
	/* what() (derived from std::runtime_error) fetches error message */
	err << "# ERR: " << e.what()
		<< " (MySQL error code: " << e.getErrorCode()
		<< ", SQLState: " << e.getSQLState() << " )";
	write_errorlog(lerr, mtx_errorlog, err.str());
}

void client_loop(SSL *ssl, ofstream &lerr, mutex &mtx_errorlog,
	const string &uname, vector<char> &buffer,
	vector<auto_ptr<sql::PreparedStatement>>& stmts)
{
	int receive_len = 0;
	while (true) {
		clear_buffer(buffer);
		receive_len = SSL_read(ssl, &(buffer[0]), BUFFER_SIZE);

		if (receive_len >= BUFFER_SIZE) return;

		switch (buffer[0]) {
		case H_CHANGE_PASS:
		{
			string password = &(buffer[LEN_HEADER]);
			if (password.length() >= LEN_UPASS)
				return;
			try {
				db_change_pass(stmts, uname, password);
			}
			catch (sql::SQLException &e) {
				log_sql(e, lerr, mtx_errorlog);
				return;
			}
			SSL_write(ssl, &M_ACCEPTED, sizeof(M_ACCEPTED));
			return;
		}
		case H_SYNC_RNUM:
		{
			int rnum = -1;
			try {
				rnum = db_get_rnum(stmts, uname);
			}
			catch (sql::SQLException &e) {
				log_sql(e, lerr, mtx_errorlog);
				return;
			}
			if (rnum == -1)
				return;
			clear_buffer(buffer);
			buffer[0] = H_RECORD_NUM;
			memcpy_s(&(buffer[LEN_HEADER]), LEN_RNUM, &rnum, sizeof(int));
			SSL_write(ssl, &(buffer[0]), LEN_HEADER + LEN_RNUM);
			break;
		}
		case H_RECORD_NUM:
		{
			int rnum = -1;
			memcpy_s(&rnum, sizeof(int), &(buffer[LEN_HEADER]), LEN_RNUM);
			if (rnum < 0)
				return;
			string dname;
			auto_ptr<istream> dt;
			try {
				db_get_data(stmts, uname, rnum, dname, dt);
			}
			catch (sql::SQLException &e) {
				log_sql(e, lerr, mtx_errorlog);
				return;
			}
			clear_buffer(buffer);
			buffer[0] = H_RECORD;
			memcpy_s(&(buffer[LEN_HEADER]), LEN_DNAME, dname.c_str(), dname.length());
			int send_len = dt_to_buffer(dt, buffer, LEN_HEADER + LEN_DNAME);
			SSL_write(ssl, &(buffer[0]), send_len);
			break;
		}
		case H_RECORD:
		{
			string dname = &(buffer[LEN_HEADER]);
			stringstream dt;
			int rnum = -1;
			if (dname.length() >= LEN_DNAME)
				return;
			dt.write(&(buffer[LEN_HEADER + LEN_DNAME]), receive_len - LEN_HEADER - LEN_DNAME);
			try {
				rnum = db_new_data(stmts, uname, dname, &dt);
			}
			catch (sql::SQLException &e) {
				log_sql(e, lerr, mtx_errorlog);
				return;
			}
			if (rnum == -1)
				return;
			clear_buffer(buffer);
			buffer[0] = H_RECORD_NUM;
			memcpy_s(&(buffer[LEN_HEADER]), LEN_RNUM, &rnum, sizeof(rnum));
			SSL_write(ssl, &(buffer[0]), LEN_HEADER + LEN_RNUM);
			break;
		}
		default:
		{
			return;
		}
		}
	}
}

/* return message length */
int dt_to_buffer(auto_ptr<istream> &dt, vector<char> &buffer, int pstart)
{
	while (dt->get(buffer[pstart]))
		pstart++;
	return pstart;
}