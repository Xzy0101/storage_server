#pragma once

/*
 * MySQL database queries.
 * All stored procedures are called via prepared statements.
 * Needs a vector to store all these statements.
 * This vector must be of size NUM_STMT before db_initialize().
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

#define DB_HOST "localhost"
#define DB_USER "cclip_admin"
#define DB_PASS "asdf123456JKL:"
#define DB_SCHEMA "cclip"

#define NUM_STMT 6
#define STMT_NEW_USER 0
#define STMT_NEW_DATA 1
#define STMT_CHECK_PASS 2
#define STMT_CHANGE_PASS 3
#define STMT_GET_RNUM 4
#define STMT_GET_DATA 5

void db_initialize(std::auto_ptr<sql::Connection> &con,
	std::vector<std::auto_ptr<sql::PreparedStatement>> &stmts);
int db_new_user(std::vector<std::auto_ptr<sql::PreparedStatement>> &stmts,
	const std::string& username,
	const std::string& password);
int db_new_data(std::vector<std::auto_ptr<sql::PreparedStatement>> &stmts,
	const std::string& username,
	const std::string& devicename,
	std::istream* dt);
int db_check_pass(std::vector<std::auto_ptr<sql::PreparedStatement>> &stmts,
	const std::string& username,
	const std::string& password);
int db_change_pass(std::vector<std::auto_ptr<sql::PreparedStatement>> &stmts,
	const std::string& username,
	const std::string& newpass);
int db_get_rnum(std::vector<std::auto_ptr<sql::PreparedStatement>> &stmts,
	const std::string& username);
void db_get_data(std::vector<std::auto_ptr<sql::PreparedStatement>> &stmts,
	const std::string& username,
	int record_number,
	std::string& devicename,
	std::auto_ptr<std::istream> &dt);

#endif