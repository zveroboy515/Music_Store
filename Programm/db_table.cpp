#include "db_table.h"

bool plate::is_date(std::string &date) {
	if (date.size() > 10) return false;
	return true;
}

plate::plate(int pNum) {
	std::string ans;
	keys = "`id`,`Date`,`MAddress`,`MName`";
	//values.push_back(std::string(std::to_string(pNum)));
	values = "'" + std::to_string(pNum) + "'";
	std::cout << "������� ���� ������� ��������/�����(������ ��.��.����)" << std::endl;
	std::cin >> ans;
	while (!is_date(ans)) {
		std::cout << "���� ����������� ��������� ����" << std::endl;
		std::cin >> ans;
	}
	values += ",'" + ans + "'";
	std::cout << "������� ����� ������������" << std::endl;
	std::cin >> ans;
	values += ",'" + ans + "'";
	std::cout << "������� �������� �����������-�������������" << std::endl;
	std::cin >> ans;
	values += ",'" + ans + "'";
	
	//values.push_back(ans)
}

std::vector<std::string> plate::generic_args()
{
	return std::vector<std::string>{keys, values};
}

std::vector<std::string> plate::change_plate() {
	std::string fields[3]{"���� ������������", "�������� ����������� ��������" ,"����� ������� �����"};
	std::string ans, res = "";
	/*����� ������ ��������� � DB_cntxt*/
	std::cout << "������� id ���������, ������� ������ �������� '" << std::endl;
	for (auto &it : fields) {
		std::cout << "������ �������� ���� '" << it << "' ?(�� - ����, ������ ������� -���)" << std::endl;
		std::cin >> ans;
		if (ans == "��") {
			std::cout << "������� �������� ���� '" << it << "'" << std::endl;
			std::cin.ignore();
			getline(std::cin, ans);
			if (res != "") res += ',';
			res += "'" + ans + "'";
		}
	}
	//std::cout<<
}

ansamble::ansamble() {
	std::string ans;

	keys = "`Aname`";
	std::cout << "������� �������� ������ ��������" << std::endl;
	std::cin >> ans;
	values = "'" + ans + "'";

}

std::vector<std::string> ansamble::generic_args()
{
	return std::vector<std::string>{keys, values};
}
