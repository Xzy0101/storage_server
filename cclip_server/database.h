#pragma once

/*
 * MySQL database queries.
 */

#ifndef CCLIP_DATABASE_H
#define CCLIP_DATABASE_H

#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>

#include <mysql_connection.h>

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/prepared_statement.h>

class DBEngine {
public:
	DBEngine();
	int new_user(const std::string& username, std::istream *passHash, std::istream *salt);
	int new_data(const std::string& username, const std::string& devicename, std::istream* dt);
	int get_pass(const std::string& username, std::auto_ptr<std::istream>& passHash, std::auto_ptr<std::istream>& salt);
	int change_pass(const std::string& username, std::istream *newPassHash, std::istream *newSalt);
	int get_rnum(const std::string& username);
	void get_data(const std::string& username, int record_number, std::string& devicename, std::auto_ptr<std::istream> &dt);
private:
	sql::Driver *driver;
	const std::string HOST = "localhost";
	const std::string USER = "cclip_admin";
	const std::string PASS = "asdf123456JKL:";
	const std::string SCHEMA = "cclip";
};

#endif