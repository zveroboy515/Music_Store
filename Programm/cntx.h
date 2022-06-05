#pragma once
#include <map>
#include <sstream>
#include "common.h"

class cntx
{

public:
	virtual bool read_command(std::string &cmd) { return true; };
	//virtual bool add_cmd(std::string command,...) { return true; };
};

class DB_cntx :
	public cntx
{
	std::map <std::string, bool( (DB_cntx::*)(std::string&))> cmd_list;
	std::string db_name;
	MYSQL *DB_conn;
	MYSQL_RES *res;
	MYSQL_ROW row;

	bool initDB();
	bool test_func(std::string &cmd);
	bool get_obj(std::string &cmd);
	bool add_obj(std::string &cmd);
	bool change_obj(std::string &cmd);
	std::vector<std::string>  add_plate();
	bool generic_SQLrequest(int flag, char *sql_res);
public:
	bool add_cmd(std::string cmd, bool((DB_cntx::*func)(std::string&)));
	bool read_command(std::string &cmd) override;
	DB_cntx();
};

class global_cntx :
	public cntx
{
	std::map <std::string, bool((global_cntx::*)(std::string&, DB_cntx&))> cmd_list;
	//int change_cntx(std::string &cmd);
	bool sort(std::string &cmd, DB_cntx &cur_db);
	bool filter(std::string &cmd, DB_cntx &cur_db);
	bool db_process(std::string &cmd, DB_cntx &cur_db);
public:
	global_cntx();
	bool add_cmd(std::string cmd, bool((global_cntx::*func)(std::string&, DB_cntx&)));
	bool read_command(std::string &cmd, DB_cntx &cur_db) ;

};
