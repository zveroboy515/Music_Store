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
	//показать лидеров продаж текущего года, то есть названия
		//компакт - дисков, которые чаще всего покупали в текущем году;
	std::cout << "Рейтинг дисков/пластинок по кол-ву проданных в этом году" << std::endl;
}

bool global_cntx::filter(std::string &cmd, DB_cntx &cur_db)
{
	return true;
}

bool global_cntx::db_process(std::string &cmd, DB_cntx &cur_db)
{
	return true;
}
