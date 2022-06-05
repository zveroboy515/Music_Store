#include "cntx.h"


bool DB_cntx::initDB() {
	std::string host, username, pwd, db_name;
	int port = 0;
	std::string unix_socket;
	int clientflag = 0;
	//static MYSQL *conn;

	// Получаем дескриптор соединения
	DB_conn = mysql_init(NULL);
	if (DB_conn == NULL)
	{
		// Если дескриптор не получен – выводим сообщение об ошибке
		fprintf(stderr, "Error: can'tcreate MySQL-descriptor\n");
		//exit(1); //Если используется оконное приложение
		return false;
	}

	std::cout << "Введите данные для подключения к БД (host username pwd db_name)" << std::endl;
	std::cin >> host >> username >> pwd >> db_name;
	//правильный
	//if (!mysql_real_connect(conn, host.c_str(), username.c_str(), pwd.c_str(), db_name.c_str(), port, unix_socket.c_str(), clientflag))
	if (!mysql_real_connect(DB_conn, "localhost", "german", "12345678", "musicstore", 3306, NULL, 0))
	{
		// Если нет возможности установить соединение с сервером
		// базы данных выводим сообщение об ошибке
		fprintf(stderr, "Error: can't connect to database %s\n", mysql_error(DB_conn));
		return false;
	}
	else
	{
		// Если соединение успешно установлено выводим фразу - "Success!"
		fprintf(stdout, "Success!\n");
	}

	return true;
}

bool DB_cntx::add_cmd(std::string command) {
	
	cmd_list.insert(std::pair<std::string, bool((DB_cntx::*)(std::string&))>(command, &DB_cntx::test_func));
	return true;
}

bool DB_cntx::read_command(std::string &command) {
	
	return (*this.*(cmd_list[command]))(command);
	//cmd_list(command).second
}

bool DB_cntx::test_func(std::string &cmd) {
	int i = 0;

	// Подключаемся к серверу
	//if (!initDB()) return 0;
	//initDB();
	mysql_set_character_set(DB_conn, "cp1251");
	//Смотрим изменилась ли кодировка на нужную, по умалчанию идёт latin1
	std::cout << "connectioncharacterset: " << mysql_character_set_name(DB_conn) << std::endl;
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