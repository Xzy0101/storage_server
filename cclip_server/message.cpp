#include "message.h"
#include "pbkdf2_pass_hash.h"

#define PASS_SALT_LEN 32
#define PASS_HASH_LEN 32

void clear_buffer(vector<char> &buffer);
void log_sql(sql::SQLException &e, ofstream &lerr, mutex &mtx_errorlog);
void client_loop(SSL *ssl, ofstream &lerr, mutex &mtx_errorlog, 
	const string &uname, vector<char> &buffer, auto_ptr<DBEngine>& db);
int dt_to_buffer(auto_ptr<istream> &dt, vector<char> &buffer, int pstart);

int client_login(SOCKET client, SSL *ssl, ofstream &lerr, mutex &mtx_errorlog)
{
	vector<char> buffer(BUFFER_SIZE);
	int receive_len = 0;

	auto_ptr<DBEngine> db;
	try {
		db.reset(new DBEngine());
	}
	catch (sql::SQLException &e) {
		log_sql(e, lerr, mtx_errorlog);
		close_client(client, ssl);
		return EXIT_FAILURE;
	}

	string username;
	string password;
	unsigned char salt[PASS_SALT_LEN];
	unsigned char passHash[PASS_HASH_LEN];
	unsigned char storedPassHash[PASS_HASH_LEN];
	bool match_pass = false;

	receive_len = SSL_read(ssl, &(buffer[0]), BUFFER_SIZE);
	if (receive_len < BUFFER_SIZE) {
		switch (buffer[0]) {
		case H_LOG_IN:
		{
			username = &(buffer[LEN_HEADER]);
			password = &(buffer[LEN_HEADER + LEN_UNAME]);
			auto_ptr<istream> saltStream;
			auto_ptr<istream> passHashStream;
			if (username.length() < LEN_UNAME && password.length() < LEN_UPASS) {
				try {
					db->get_pass(username, passHashStream, saltStream);
				}
				catch (sql::SQLException &e) {
					log_sql(e, lerr, mtx_errorlog);
					close_client(client, ssl);
					return EXIT_FAILURE;
				}
				saltStream->flags(ios::binary);
				passHashStream->flags(ios::binary);
				saltStream->read((char *)salt, PASS_SALT_LEN);
				passHashStream->read((char *)storedPassHash, PASS_HASH_LEN);
				hash_pass(password.c_str(), salt, PASS_SALT_LEN, passHash, PASS_HASH_LEN);
				match_pass = 0 == memcmp(passHash, storedPassHash, PASS_HASH_LEN);
				if (match_pass) {
					SSL_write(ssl, &M_ACCEPTED, sizeof(M_ACCEPTED));
					client_loop(ssl, lerr, mtx_errorlog, username, buffer, db);
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
			if (username.length() < LEN_UNAME && username.length()>0
				&& password.length() < LEN_UPASS && password.length()>0) {
				hash_new_pass(password.c_str(), salt, PASS_SALT_LEN, passHash, PASS_HASH_LEN);
				stringstream saltStream;
				stringstream passHashStream;
				saltStream.write((const char *)salt, PASS_SALT_LEN);
				passHashStream.write((const char *)passHash, PASS_HASH_LEN);
				try {
					db->new_user(username, &passHashStream, &saltStream);
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
	close_client(client, ssl);
	return EXIT_FAILURE;
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
	const string &uname, vector<char> &buffer, auto_ptr<DBEngine>& db)
{
	int receive_len = 0;
	while (true) {
		clear_buffer(buffer);
		receive_len = SSL_read(ssl, &(buffer[0]), BUFFER_SIZE);

		if (receive_len >= BUFFER_SIZE && receive_len == 0) return;

		switch (buffer[0]) {
		case H_CHANGE_PASS:
		{
			string password = &(buffer[LEN_HEADER]);
			if (password.length() >= LEN_UPASS)
				return;
			stringstream saltStream;
			stringstream passHashStream;
			unsigned char salt[PASS_SALT_LEN];
			unsigned char passHash[PASS_HASH_LEN];
			hash_new_pass(password.c_str(), salt, PASS_SALT_LEN, passHash, PASS_HASH_LEN);
			saltStream.write((const char *)salt, PASS_SALT_LEN);
			passHashStream.write((const char *)passHash, PASS_HASH_LEN);
			try {
				db->change_pass(uname, &passHashStream,&saltStream);
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
				rnum = db->get_rnum(uname);
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
				db->get_data(uname, rnum, dname, dt);
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
				rnum = db->new_data(uname, dname, &dt);
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
	while (!dt->eof()) {
		dt->get(buffer[pstart]);
		pstart++;
	}
	return pstart;
}