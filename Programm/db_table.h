#pragma once
#include "common.h"
//#include "cntx.h"

class plate
{
	std::string keys;
	//std::vector<std::string> values;
	std::string values;
	static int pNum;
	bool is_date(std::string &date) { //�� �����������
		if (date.size() > 10) return false;
		return true;
	}
public:
	plate() {
		std::string ans;
		keys = "`id`,`Date`,`MName`,`MAddress`";
		//values.push_back(std::string(std::to_string(pNum)));
		values = "`" + std::to_string(pNum) +"`";
		std::cout << "������� ���� ������� ��������/�����(������ ��.��.����)"<< std::endl;
		std::cin >> ans;
		while (!is_date(ans)) {
			std::cout << "���� ����������� ��������� ����" << std::endl;
			std::cin >> ans;
		}
		values += ",`" + ans + "`";
		std::cout << "������� �������� �����������-�������������" << std::endl;
		std::cin >> ans;
		values += ",`" + ans + "`";
		std::cout << "������� ����� ������������" << std::endl;
		std::cin >> ans;
		values += ",`" + ans + "`";
		//values.push_back(ans)
	}
	std::vector<std::string>generic_args();
	
};

class person 
{
	

};

class ansamble
{
	

};