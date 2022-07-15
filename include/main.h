#pragma once
#include "mysql_connection.h"

#include <string>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/prepared_statement.h>
using namespace std;

sql::Driver* driver;
sql::Connection* con;

// READ PASSWORD FROM FILE
string read_pass() {
	ifstream file;
	string pass = "";

	// for security purposes I'm opening a local .env file to read database password
	file.open("C:\\Users\\Administrator\\Documents\\Visual Studio 2022\\C++ Projects\\school system\\.env", ios::in);

	if (file.is_open()) {
		getline(file, pass);
		file.close();
	}

	return pass;
}

const string server = "localhost";
const string username = "root";
const string password = read_pass(); // read password from .env and assign it to string

// CONNECT TO DATABASE
void connect_db() {
	try {
		driver = get_driver_instance();
		con = driver->connect(server, username, password);
	}
	catch (sql::SQLException e) {
		cout << "Error connecting to DB Server: " << e.what() << endl;
		system("pause");
		exit(1);
	}

	con->setSchema("school_system");
}