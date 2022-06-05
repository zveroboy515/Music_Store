#pragma once
#include <map>
#include "common.h"

class cntx
{

public:
	virtual bool read_command(std::string &cmd) { return true; };
	virtual bool add_cmd(std::string command) { return true; };
};

class DB_cntx :
	public cntx
{
	std::map <std::string, bool( (DB_cntx::*)(std::string&))> cmd_list;
	MYSQL *DB_conn;
	MYSQL_RES *res;
	MYSQL_ROW row;

	bool initDB();
	bool test_func(std::string &cmd);
public:

	bool add_cmd(std::string command) override;
	bool read_command(std::string &cmd) override;
	DB_cntx(){
		initDB();
		add_cmd("test");
	}
};
