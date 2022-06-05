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
	std::cout << "input command :(" << str << ")" << std::endl;
	return (*this.*(cmd_list[str]))(cmd, cur_db);
}

bool global_cntx::sort(std::string &cmd, DB_cntx &cur_db) {
	std::string cmd;
	//показать лидеров продаж текущего года, то есть названия
		//компакт - дисков, которые чаще всего покупали в текущем году;
	std::cout << "Рейтинг дисков/пластинок по кол-ву проданных в этом году" << std::endl;
	//SELECT PLName FROM musicstore.platestat order by ~SellLastYear
	cmd = "get force SELECT PLName FROM musicstore.platestat order by ~SellLastYear";
	return cur_db.read_command(cmd);
}

bool global_cntx::filter(std::string &cmd, DB_cntx &cur_db)
{
	std::string str;
	//1) получить количество музыкальных произведений заданного ансамбля;
	//SELECT * FROM musicstore WHERE ansamble = ''
	//2) выводить название всех компакт-дисков заданного ансамбля;
	//SELECT PLName FROM musicstore.plate WHERE ansamble = ''
	return true;
}

bool global_cntx::db_process(std::string &cmd, DB_cntx &cur_db)
{
	std::string str;

	while (1) {
		std::cout << " Введите операцию: " <<
			"\nchange - изменение имеющихся в БД записей" <<
			"\nadd - добавление новых записей в БД" <<
			"\nstop - для возврата в главное меню" << std::endl;
		std::cin >> str;

		if (str == "change" || str == "add") cmd = str + " ";
		else if (str == "stop") return false;
		std::cout << "Неизвестная комманда, повторите ввод" << std::endl;
	}
	cur_db.read_command(str);
	/*while (1) {
		std::cout << " Введите таблицу с которой собираетеь работать: " <<
			"\nansamble - таблица ансамблей" <<
			"\nplate - таблица дисков/пластинок" <<
			"\nstop - для возврата в главное меню" << std::endl;
		std::cin >> str;
		if (str == "ansamble" || str == "plate") cmd = str + " ";
		else if (str == "stop") return false;
		std::cout << "Неизвестная комманда, повторите ввод" << std::endl;
	}*/

	return true;
}
