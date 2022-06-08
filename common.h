#pragma once
#include <iostream>
#include <string>
#include <mysql.h>
#include <vector>

//#define CLASS_PT  

#define DBG std::cout << __FILE__<< ":" <<__LINE__ << std::endl;
#define ErrExit(num) fprintf(stderr, "in func(%s) заданное кол-во аргументов не реализовано(%d)\n", __func__, num);
#define MAX_SQL_REQ 255
std::vector<std::string> ParsInArgs(std::string &str);