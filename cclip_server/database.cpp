#include "database.h"

void db_initialize(std::auto_ptr<sql::Connection> &con, 
	std::vector<std::auto_ptr<sql::PreparedStatement>> &stmts)
{
	sql::Driver* driver = get_driver_instance();
	con.reset(driver->connect(DB_HOST, DB_USER, DB_PASS));
	con->setSchema(DB_SCHEMA);
	stmts[STMT_NEW_USER].reset(con->prepareStatement("CALL new_user(?,?)"));
	stmts[STMT_NEW_DATA].reset(con->prepareStatement("CALL new_data(?,?,?)"));
	stmts[STMT_CHECK_PASS].reset(con->prepareStatement("CALL check_pass(?,?)"));
	stmts[STMT_CHANGE_PASS].reset(con->prepareStatement("CALL change_pass(?,?)"));
	stmts[STMT_GET_RNUM].reset(con->prepareStatement("CALL get_rnum(?)"));
	stmts[STMT_GET_DATA].reset(con->prepareStatement("CALL get_data(?,?)"));
}

int db_new_user(std::vector<std::auto_ptr<sql::PreparedStatement>> &stmts, 
	const std::string& username, 
	const std::string& password)
{
	stmts[STMT_NEW_USER]->setString(1, username);
	stmts[STMT_NEW_USER]->setString(2, password);

	return stmts[STMT_NEW_USER]->execute();
}

int db_new_data(std::vector<std::auto_ptr<sql::PreparedStatement>> &stmts,
	const std::string& username,
	const std::string& devicename, 
	std::istream* dt)
{
	std::auto_ptr<sql::ResultSet> res;

	stmts[STMT_NEW_DATA]->setString(1, username);
	stmts[STMT_NEW_DATA]->setString(2, devicename);
	stmts[STMT_NEW_DATA]->setBlob(3, dt);
	stmts[STMT_NEW_DATA]->execute();
	do {
		res.reset(stmts[STMT_NEW_DATA]->getResultSet());
		while (res->next()) {
			return res->getInt("record_number");
		}
	} while (stmts[STMT_GET_RNUM]->getMoreResults());

	return -1;
}

int db_check_pass(std::vector<std::auto_ptr<sql::PreparedStatement>> &stmts,
	const std::string& username,
	const std::string& password)
{
	std::auto_ptr<sql::ResultSet> res;

	stmts[STMT_CHECK_PASS]->setString(1, username);
	stmts[STMT_CHECK_PASS]->setString(2, password);
	stmts[STMT_CHECK_PASS]->execute();
	do {
		res.reset(stmts[STMT_CHECK_PASS]->getResultSet());
		while (res->next()) {
			return res->getBoolean("name_pass_match");
		}
	} while (stmts[STMT_CHECK_PASS]->getMoreResults());

	return -1;
}

int db_change_pass(std::vector<std::auto_ptr<sql::PreparedStatement>> &stmts,
	const std::string& username,
	const std::string& newpass)
{
	stmts[STMT_CHANGE_PASS]->setString(1, username);
	stmts[STMT_CHANGE_PASS]->setString(2, newpass);

	return stmts[STMT_CHANGE_PASS]->executeUpdate();
}

int db_get_rnum(std::vector<std::auto_ptr<sql::PreparedStatement>> &stmts,
	const std::string& username)
{
	std::auto_ptr<sql::ResultSet> res;

	stmts[STMT_GET_RNUM]->setString(1, username);
	stmts[STMT_GET_RNUM]->execute();
	do {
		res.reset(stmts[STMT_GET_RNUM]->getResultSet());
		while (res->next()) {
			return res->getInt("record_number");
		}
	} while (stmts[STMT_GET_RNUM]->getMoreResults());

	return -1;
}

void db_get_data(std::vector<std::auto_ptr<sql::PreparedStatement>> &stmts,
	const std::string& username,
	int record_number,
	std::string& devicename,
	std::auto_ptr<std::istream> &dt)
{
	std::auto_ptr<sql::ResultSet> res;

	stmts[STMT_GET_DATA]->setString(1, username);
	stmts[STMT_GET_DATA]->setInt(2, record_number);
	stmts[STMT_GET_DATA]->execute();
	do {
		res.reset(stmts[STMT_GET_DATA]->getResultSet());
		while (res->next()) {
			devicename = res->getString("device_name");
			dt.reset(res->getBlob("data"));
		}
	} while (stmts[STMT_GET_DATA]->getMoreResults());
}