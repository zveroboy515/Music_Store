#include "cntx.h"
#include "db_table.h"
#include <sstream>

enum DB_cmd {
	CMD_CHANGE,
	CMD_ADD,
	CMD_GET,
};

std::string DB_cmd_desc[]{
	"UPDATE `%s`.`%s` SET %s WHERE(%s)\0",
	"INSERT INTO `%s`.`%s` (%s) VALUES(%s)\0",
	"SELECT %s FROM %s \0",
};

DB_cntx::DB_cntx() {
	initDB();
	//add_cmd("test", &DB_cntx::test_func);
	add_cmd("get", &DB_cntx::get_obj);
	add_cmd("add", &DB_cntx::add_obj);
	add_cmd("change", &DB_cntx::change_obj);
}

bool DB_cntx::initDB() {
	std::string host, username, pwd;
	int port = 0;
	std::string unix_socket;
	int clientflag = 0;

	// Получаем дескриптор соединения
	DB_conn = mysql_init(NULL);
	if (DB_conn == NULL)
	{
		fprintf(stderr, "Error: can'tcreate MySQL-descriptor\n");
		return false;
	}

	std::cout << "Введите данные для подключения к БД (host логин пароль название_ДБ)" << std::endl;
	std::cin >> host;
	//Заглушка для отладки
	if (host == "def") { 
		!mysql_real_connect(DB_conn, "localhost", "german", "12345678", "musicstore", 3306, NULL, 0);
		db_name = "musicstore";
		goto cont;
	}
	else std::cin >> username >> pwd >> db_name;
	if (!mysql_real_connect(DB_conn, host.c_str(), username.c_str(), pwd.c_str(), db_name.c_str(), port, unix_socket.c_str(), clientflag))
	//для проверки
	//if (!mysql_real_connect(DB_conn, "localhost", "german", "12345678", "musicstore", 3306, NULL, 0))
	{
		// Если нет возможности установить соединение с сервером
		// базы данных выводим сообщение об ошибке
		fprintf(stderr, "Error: can't connect to database %s\n", mysql_error(DB_conn));
		return false;
	}
	else
	{
		// Если соединение успешно установлено выводим фразу - "Success!"
		fprintf(stdout, "Connection to database success!\n");
	}
cont:
	mysql_set_character_set(DB_conn, "cp1251");
	//Смотрим изменилась ли кодировка на нужную, по умалчанию идёт latin1
	std::cout << "connectioncharacterset: " << mysql_character_set_name(DB_conn) << std::endl;

	return true;
}

bool DB_cntx::add_cmd(std::string cmd, bool((DB_cntx::*func)(std::string&))) {
	cmd_list.insert(std::pair<std::string, bool((DB_cntx::*)(std::string&))>(cmd, func));
	return true;
}

bool DB_cntx::read_command(std::string &cmd) {
	std::stringstream ss{ cmd };
	std::string str;

	ss >> str;
	//std::cout << "input command :(" << str << ")" << std::endl;
	if (cmd_list.find(str) == cmd_list.end()) {
		std::cout << "Неверная комманда" << std::endl;
		return false;
	}

	return (*this.*(cmd_list[str]))(cmd);
}

bool DB_cntx::new_obj(std::string table, std::string key) {
	std::string cmd;

	cmd = "get force SELECT `" + key + "` FROM `" + db_name +"`.`" + table + "` WHERE ()";
	return !(*this).get_obj(cmd);
}

bool DB_cntx::add_obj(std::string &cmd) {//добавление информации об ансамбле в БД
	std::vector<std::string> args;
	std::string ans;

	args = ParsInArgs(cmd);
	if (args.size() > 1 && args[1] == "force") {
		mysql_query(DB_conn, cmd.substr(cmd.find("force") + strlen("force")).c_str());
	}
	else if (args.size() == 4 ) {
		if (MAX_SQL_REQ <= sizeof(args) + strlen(DB_cmd_desc[CMD_ADD].c_str()) + strlen(db_name.c_str()))
			std::cout << "sql запрос может быть обрезан" << std::endl;
		char sql_cmd[MAX_SQL_REQ];
		sprintf_s(sql_cmd, DB_cmd_desc[CMD_ADD].c_str(), db_name.c_str(), args[1].c_str(), args[2].c_str(),
			args[3].c_str());
		mysql_query(DB_conn, sql_cmd);
	}else{
		char sql_cmd[MAX_SQL_REQ];
		//old function
		/*if (!generic_SQLrequest(CMD_ADD, sql_cmd))
			return false;*/

		while (1) { 
			std::cout << "Введите название таблицы:" <<
				"\nplate - добавить данные о новой пластинке/диске" <<
				"\nansamble - добавить данные о новом ансамбле" <<
				"\nstop - отмена добавления" << std::endl;
			std::cin >> ans;
			if (ans == "stop") return false;
			else if (ans == "plate") {
				std::cout << "Введите id пластинки" << std::endl;
				std::cin >> Pid;
				plate new_pl(Pid);
				args = new_pl.generic_args();
			
				if (new_obj("PlateStat", "id")) {
					
					if (MAX_SQL_REQ <= sizeof(args) + strlen(DB_cmd_desc[CMD_ADD].c_str()) + strlen(db_name.c_str()))
						std::cout << "sql запрос может быть обрезан" << std::endl;
					sprintf_s(sql_cmd, DB_cmd_desc[CMD_ADD].c_str(), db_name.c_str(), ans.c_str(), args[0].c_str(),
						args[1].c_str());
					std::cout << "sql_cmd = " << sql_cmd << std::endl;
					mysql_query(DB_conn, sql_cmd);
					
					ans = "PlateStat";
					new_pl.pl_trigger(Pid);
					args = new_pl.generic_args();
				}
				break;
			}
			else if (ans == "ansamble") {
				ansamble new_ans;
				args = new_ans.generic_args();
				break;
			}
		}

		if (MAX_SQL_REQ <= sizeof(args) + strlen(DB_cmd_desc[CMD_ADD].c_str()) + strlen(db_name.c_str()))
			std::cout << "sql запрос может быть обрезан" << std::endl;
		sprintf_s(sql_cmd, DB_cmd_desc[CMD_ADD].c_str(), db_name.c_str(), ans.c_str(), args[0].c_str(),
			args[1].c_str());
		std::cout <<"sql_cmd = " << sql_cmd << std::endl;
		mysql_query(DB_conn, sql_cmd);

		//ErrExit(args.size());

//		return false;
	}
	return true;
}

bool DB_cntx::change_obj(std::string &cmd) {
	std::vector<std::string> args;
	std::string tmp;

	args = ParsInArgs(cmd);

	if (args.size() > 1 && args[1] == "force") {
		mysql_query(DB_conn, cmd.substr(cmd.find("force") + strlen("force")).c_str());
	//Старая версия
		/*}
	else if (args.size() == 6) { 
		if (MAX_SQL_REQ <= sizeof(args) + strlen(DB_cmd_desc[CMD_CHANGE].c_str()) + strlen(db_name.c_str()))
			std::cout << "sql запрос может быть обрезан" << std::endl;
		char sql_cmd[MAX_SQL_REQ]; //255
		//динамично, но опасно
		 //const int len = sizeof(args) + strlen(DB_cmds[0].c_str()) + strlen(db_name.c_str());
		 //char sql_cmd[len];
		sprintf_s(sql_cmd, DB_cmd_desc[CMD_CHANGE].c_str(), db_name.c_str(), args[1].c_str(), args[2].c_str(),
			args[3].c_str(), args[4].c_str(), args[5].c_str());
		mysql_query(DB_conn, sql_cmd);*/
	}else{
		/*ErrExit(args.size());
		return false;*/
		std::cout << "Реализовано изменение информации только о дисках/пластинках(по ТЗ)" << std::endl;
		tmp = "get id plate";
		if (!(*this).get_obj(tmp)) {
			std::cout << "В ДБ нет добавленных пластинок" << std::endl;
			return false;
		}
		
		args = plate::change_plate();
		if (MAX_SQL_REQ <= sizeof(args) + strlen(DB_cmd_desc[CMD_CHANGE].c_str()) + strlen(db_name.c_str()))
			std::cout << "sql запрос может быть обрезан" << std::endl;
		char sql_cmd[MAX_SQL_REQ]; //255
		
		sprintf_s(sql_cmd, DB_cmd_desc[CMD_CHANGE].c_str(), db_name.c_str(),
			"plate", args[0].c_str(), args[1].c_str());
		//std::cout << sql_cmd << std::endl;
		mysql_query(DB_conn, sql_cmd);
	}

	//стабильно но может обрезаться
	
	return true;
}

bool DB_cntx::get_obj(std::string &cmd) {
	std::vector<std::string> args;

	args = ParsInArgs(cmd);

	if (args.size() > 1 && args[1] == "force") {
		mysql_query(DB_conn, cmd.substr(cmd.find("force") + strlen("force")).c_str());
	}
	else if (args.size() == 3) {
		if (MAX_SQL_REQ <= sizeof(args) + strlen(DB_cmd_desc[CMD_GET].c_str()) + strlen(db_name.c_str()))
			std::cout << "sql запрос может быть обрезан" << std::endl;
		char sql_cmd[MAX_SQL_REQ];
		sprintf_s(sql_cmd, DB_cmd_desc[CMD_GET].c_str(),
			args[1].c_str(), args[2].c_str());
		mysql_query(DB_conn, sql_cmd);
	}else {
		ErrExit(args.size());
		return false;
	}

	if (res = mysql_store_result(DB_conn)) {
		while (row = mysql_fetch_row(res)) {
			for (int i = 0; i < mysql_num_fields(res); i++) {
				std::cout << row[i] << "\n"; //Выводим все что есть в базе через цикл
			}
		}
	}
	else { 
		//std::cout << "В ДБ нет данных" << std::endl;
		return false;
	}
	//mysql_query(DB_conn, "SELECT * FROM ansamble"); //Делаем запрос к таблице по имени МНУ =)
	return true;
}

//old function
/*bool DB_cntx::generic_SQLrequest(int flag, char *sql_res) {
	//char 
	std::string ans;
	std::vector<std::string> args, adding_arg;

	while (1) {
		switch (flag)
		{
			case CMD_ADD:
				std::cout << "Введите название таблицы:" <<
							 "\nplate - добавить данные о новой пластинке/диске" <<
							 "\nansamble - добавить данные о новом ансамбле" <<
							 "\nstop - отмена добавления"<< std::endl;
				std::cin >> ans;
				if (ans != "stop") return false;
				else if (ans != "plate" && ans != "ansamble") {
					std::cout << "Неверная команда, повторите ввод" << std::endl;
					break;
				}
				args.push_back(ans);
				//adding_arg = (ans == "plate") ? add_plate() : adding_arg; //ЗАТЫЧКА
				//args.insert(args.end(), adding_arg.begin(), adding_arg.end());
				break;
			case CMD_CHANGE:

				break;
			default:
				std::cout << "Некорректный аргумент в ф-ции " << __func__ << std::endl;
				return NULL;
				break;
		}
	}

}*/

//test
/*bool DB_cntx::test_func(std::string &cmd) {
	int i = 0;

	// Подключаемся к серверу
	//if (!initDB()) return 0;
	//initDB();

	//mysql_query(conn, "UPDATE `musicstore`.`ansamble` SET `name` = 'Катян' WHERE(`AName` = 'песняры')");
					  //"INSERT INTO `musicstore`.`person` (`Profession`, `AName`, `PName`) VALUES('we', 'jgf', 'sdc')"
	mysql_query(DB_conn, "INSERT INTO `musicstore`.`person` (`Profession`, `AName`, `PName`) VALUES('Исполнитель', 'песняры', 'Вова')");
	mysql_query(DB_conn, "INSERT INTO `musicstore`.`person` (`Profession`, `AName`, `PName`) VALUES('Исполнитель', 'песняры', 'Петя')");
	mysql_query(DB_conn, "INSERT INTO `musicstore`.`person` (`Profession`, `AName`, `PName`) VALUES('Исполнитель', 'Skilet', 'Катя')");
	//mysql_query(conn, "INSERT INTO `musicstore`.`ansamble` (`name`, `AName`) VALUES('Вова', 'песняры')");
	std::cout << "Получаем таблицу Ансамблей" << std::endl;
	mysql_query(DB_conn, "SELECT * FROM ansamble"); //Делаем запрос к таблице по имени МНУ =)

	if (res = mysql_store_result(DB_conn)) {
		while (row = mysql_fetch_row(res)) {
			if (mysql_num_fields(res) <= 0) std::cout << "DB empty" << std::endl;
			for (i = 0; i < mysql_num_fields(res); i++) {
				std::cout << row[i] << "\n"; //Выводим все что есть в базе через цикл
			}
		}
	}
	else { 
		fprintf(stderr, "%s\n", mysql_error(DB_conn)); 
		return false;
	}

	std::cout << "Получаем таблицу Людей" << std::endl;
	mysql_query(DB_conn, "SELECT * FROM Person");
	if (res = mysql_store_result(DB_conn)) {
		while (row = mysql_fetch_row(res)) {
			if (mysql_num_fields(res) <= 0) std::cout << "DB empty" << std::endl;
			for (i = 0; i < mysql_num_fields(res); i++) {
				std::cout << row[i] << "\n"; //Выводим все что есть в базе через цикл
			}
		}
	}
	else { fprintf(stderr, "%s\n", mysql_error(DB_conn));
		return false;
	}

	// Закрываем соединение с сервером базы данных
	mysql_close(DB_conn);

	//system("Pause");

	return true;
}
*/