#include "cntx.h"

global_cntx::global_cntx() {
	add_cmd("sort", &global_cntx::sort);
	add_cmd("filter", &global_cntx::filter);
	add_cmd("db", &global_cntx::db_process);
}

bool global_cntx::add_cmd(std::string cmd, bool((global_cntx::*func)(std::string&, DB_cntx&))) {
	cmd_list.insert(std::pair<std::string, bool((global_cntx::*)(std::string&, DB_cntx&))>(cmd, func));
	return true;
}

bool global_cntx::read_command(std::string &cmd, DB_cntx &cur_db) {
	std::stringstream ss{ cmd };
	std::string str;

	ss >> str;
	//std::cout << "input command :(" << str << ")" << std::endl;
	if (cmd_list.find(cmd) == cmd_list.end()) {
		std::cout << "�������� ��������" << std::endl;
		return false;
	}

	return (*this.*(cmd_list[str]))(cmd, cur_db);
}

bool global_cntx::sort(std::string &cmd, DB_cntx &cur_db) {
	std::string sql_cmd;
	//�������� ������� ������ �������� ����, �� ���� ��������
		//������� - ������, ������� ���� ����� �������� � ������� ����;
	std::cout << "������� ������/��������� �� ���-�� ��������� � ���� ����" << std::endl;
	//SELECT PLName FROM musicstore.platestat order by ~SellLastYear
	sql_cmd = "get force SELECT PLName FROM musicstore.platestat order by ~SellLastYear";
	return cur_db.read_command(sql_cmd);
}

bool global_cntx::filter(std::string &cmd, DB_cntx &cur_db)
{
	std::string str;
	std::cout << "�� �����������" << std::endl;
	//1) �������� ���������� ����������� ������������ ��������� ��������;
	//SELECT * FROM musicstore WHERE ansamble = ''
	//2) �������� �������� ���� �������-������ ��������� ��������;
	//SELECT PLName FROM musicstore.plate WHERE ansamble = ''
	return true;
}

bool global_cntx::db_process(std::string &cmd, DB_cntx &cur_db)
{
	std::string str;

	while (1) {
		std::cout << "������� ��������: " <<
			"\nchange - ��������� ��������� � �� �������" <<
			"\nadd - ���������� ����� ������� � ��" <<
			"\nstop - ��� �������� � ������� ����" << std::endl;
		std::cin >> str;
		if (str == "stop") return false;
		if(cur_db.read_command(str)) break;
		/*if (str == "change" || str == "add") { 
			cmd = str + " ";
			break;
		}
		else if (str == "stop") return false;
		std::cout << "����������� ��������, ��������� ����" << std::endl;*/
	}
	
	/*while (1) {
		std::cout << " ������� ������� � ������� ���������� ��������: " <<
			"\nansamble - ������� ���������" <<
			"\nplate - ������� ������/���������" <<
			"\nstop - ��� �������� � ������� ����" << std::endl;
		std::cin >> str;
		if (str == "ansamble" || str == "plate") cmd = str + " ";
		else if (str == "stop") return false;
		std::cout << "����������� ��������, ��������� ����" << std::endl;
	}*/

	return true;
}
