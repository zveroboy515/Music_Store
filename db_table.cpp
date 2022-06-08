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
	std::cout << "Введите дату выпуска пластнки/диска(формат ДД.ММ.ГГГГ)" << std::endl;
	std::cin >> ans;
	while (!is_date(ans)) {
		std::cout << "Дата некорректна повторите ввод" << std::endl;
		std::cin >> ans;
	}
	values += ",'" + ans + "'";
	std::cout << "Введите адрес производства" << std::endl;
	std::cin >> ans;
	values += ",'" + ans + "'";
	std::cout << "Введите название организации-производителя" << std::endl;
	std::cin >> ans;
	values += ",'" + ans + "'";
	
	//values.push_back(ans)
}

std::vector<std::string> plate::generic_args()
{
	return std::vector<std::string>{keys, values};
}

std::vector<std::string> plate::change_plate() {
	std::vector<std::string> fields_name{"дата производства", "адрес оптовой фирмы", "название выпустившей компании" };
	std::vector<std::string> fields_key{ "Date", "MAddress", "MName" };
	std::string ans;
	std::vector<std::string> res{"",""};
	//res.resize(2);
	/*вызов списка пластинок в DB_cntxt*/

	std::cout << "Введите id пластинки, которую хотите изменить '" << std::endl;
	std::cin >> ans;
	res[1] = "`id` = '" + ans + "'";
	//for (auto &it : fields_name) {
	for (int i = 0; i < fields_name.size(); i++) {
		std::cout << "Хотите изменить поле '" << fields_name[i] << "' ?(yes/no)" << std::endl;
		std::cin >> ans;
		std::cin.ignore();
		if (ans == "yes") {
			if (res[0] != "") res[0] += ',';
			res[0] += "`" + fields_key[i] +"` = ";
			std::cout << "Введите значение поля '" << fields_name[i] << "'" << std::endl;
			//std::cin >> ans;
			//std::cin.ignore();
			getline(std::cin, ans);
			res[0] += "'" + ans + "'";
		}
	}
	//std::cout << res[1] << std::endl;
	return res;
	//std::cout<<
}

ansamble::ansamble() {
	std::string ans;

	keys = "`Aname`";
	std::cout << "Введите названиы нового ансамбля" << std::endl;
	std::cin >> ans;
	values = "'" + ans + "'";

}

std::vector<std::string> ansamble::generic_args()
{
	return std::vector<std::string>{keys, values};
}
