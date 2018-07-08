#include "database.h"
DBEngine::DBEngine()
{
	driver = get_driver_instance();
}

int DBEngine::new_user(const std::string& username, 
	std::istream *passHash,
	std::istream *salt)
{
	int res;
	std::auto_ptr<sql::Connection> conn(driver->connect(HOST, USER, PASS));
	conn->setSchema(SCHEMA);
	conn->setAutoCommit(false);
	std::auto_ptr<sql::PreparedStatement>stmt(conn->prepareStatement("CALL new_user(?, ?, ?);"));
	stmt->setString(1, username);
	stmt->setBlob(2, passHash);
	stmt->setBlob(3, salt);
	res = stmt->executeUpdate();
	conn->commit();
	conn->close();
	return res;
}

int DBEngine::new_data(const std::string& username,
	const std::string& devicename, 
	std::istream* dt)
{
	std::auto_ptr<sql::Connection> conn(driver->connect(HOST, USER, PASS));
	conn->setSchema(SCHEMA);
	conn->setAutoCommit(false);
	std::auto_ptr<sql::ResultSet> res;
	std::auto_ptr<sql::PreparedStatement>stmt(conn->prepareStatement("CALL new_data(?, ?, ?);"));
	int rnum = -1;
	stmt->setString(1, username);
	stmt->setString(2, devicename);
	stmt->setBlob(3, dt);
	stmt->execute();
	do {
		res.reset(stmt->getResultSet());
		while (res->next()) {
			rnum = res->getInt("numOfRecords");
		}
	} while (stmt->getMoreResults());

	conn->commit();
	conn->close();
	return rnum;
}

int DBEngine::get_pass(const std::string& username, 
	std::auto_ptr<std::istream>& passHash, 
	std::auto_ptr<std::istream>& salt)
{
	std::auto_ptr<sql::Connection> conn(driver->connect(HOST, USER, PASS));
	conn->setSchema(SCHEMA);
	conn->setAutoCommit(false);
	std::auto_ptr<sql::ResultSet> res;
	std::auto_ptr<sql::PreparedStatement> stmt(conn->prepareStatement("CALL get_pass(?);"));
	int count = 0;

	stmt->setString(1, username);
	stmt->execute();
	do {
		res.reset(stmt->getResultSet());
		while (res->next()) {
			passHash.reset(res->getBlob("passHash"));
			salt.reset(res->getBlob("salt"));
			count++;
		}
	} while (stmt->getMoreResults());

	conn->commit();
	conn->close();
	return count;
}

int DBEngine::change_pass(const std::string& username,
	std::istream *newPassHash,
	std::istream *newSalt)
{
	std::auto_ptr<sql::Connection> conn(driver->connect(HOST, USER, PASS));
	conn->setSchema(SCHEMA);
	conn->setAutoCommit(false);
	int res;
	std::auto_ptr<sql::PreparedStatement> stmt(conn->prepareStatement("CALL change_pass(?, ?, ?);"));
	stmt->setString(1, username);
	stmt->setBlob(2, newPassHash);
	stmt->setBlob(3, newSalt);

	res = stmt->executeUpdate();
	conn->commit();
	conn->close();
	return res;
}

int DBEngine::get_rnum(const std::string& username)
{
	std::auto_ptr<sql::Connection> conn(driver->connect(HOST, USER, PASS));
	conn->setSchema(SCHEMA);
	conn->setAutoCommit(false);
	std::auto_ptr<sql::ResultSet> res;
	std::auto_ptr<sql::PreparedStatement> stmt(conn->prepareStatement("CALL get_rnum(?);"));
	int rnum = -1;

	stmt->setString(1, username);
	stmt->execute();
	do {
		res.reset(stmt->getResultSet());
		while (res->next()) {
			rnum = res->getInt("numOfRecords");
		}
	} while (stmt->getMoreResults());

	conn->commit();
	conn->close();
	return rnum;
}

void DBEngine::get_data(const std::string& username,
	int record_number,
	std::string& devicename,
	std::auto_ptr<std::istream> &dt)
{
	std::auto_ptr<sql::Connection> conn(driver->connect(HOST, USER, PASS));
	conn->setSchema(SCHEMA);
	conn->setAutoCommit(false);
	std::auto_ptr<sql::ResultSet> res;
	std::auto_ptr<sql::PreparedStatement> stmt(conn->prepareStatement("CALL get_data(?, ?);"));

	stmt->setString(1, username);
	stmt->setInt(2, record_number);
	stmt->execute();
	do {
		res.reset(stmt->getResultSet());
		while (res->next()) {
			devicename = res->getString("deviceName");
			dt.reset(res->getBlob("data"));
		}
	} while (stmt->getMoreResults());

	conn->commit();
	conn->close();
}