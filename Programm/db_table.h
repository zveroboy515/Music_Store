#pragma once
#include "common.h"
//#include "cntx.h"

class plate
{
	std::string keys;
	//std::vector<std::string> values;
	std::string values;
	//static int pNum;
	bool is_date(std::string &date);//�� �����������
public:
	plate(int pNum);
	std::vector<std::string>generic_args();
};

class person //�� �����������
{
	

};

class ansamble
{
	std::string keys;
	std::string values;
public:
	ansamble();
	std::vector<std::string>generic_args();
};