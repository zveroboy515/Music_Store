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
	std::string fields[3]{"дата производства", "название выпустившей компании" ,"адрес оптовой фирмы"};
	std::string ans, res = "";
	/*вызов списка пластинок в DB_cntxt*/
	std::cout << "Введите id пластинки, которую хотите изменить '" << std::endl;
	for (auto &it : fields) {
		std::cout << "Хотите изменить поле '" << it << "' ?(да - хочу, другие символы -нет)" << std::endl;
		std::cin >> ans;
		if (ans == "да") {
			std::cout << "Введите значение поля '" << it << "'" << std::endl;
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
	std::cout << "Введите названиы нового ансамбля" << std::endl;
	std::cin >> ans;
	values = "'" + ans + "'";

}

std::vector<std::string> ansamble::generic_args()
{
	return std::vector<std::string>{keys, values};
}
