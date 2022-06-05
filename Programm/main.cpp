// Programm.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
/* Standard C++ includes */

/*
  Include directly the different
  headers from cppconn/ and mysql_driver.h + mysql_util.h
  (and mysql_connection.h). This will reduce your build time!
*/

/*#include <jdbc.h>

//using namespace std;

int main(void)
{
	std::cout << std::endl;
	std::cout << "Running 'SELECT 'Hello World!' »  AS _message'..." << std::endl;
	
		try {
		sql::Driver *driver;
		sql::Connection *con;
		sql::Statement *stmt;
		sql::ResultSet *res;

		// Create a connection 
		driver = get_driver_instance();
		con = driver->connect("tcp://127.0.0.1:3306", "root", "12345678");
		// Connect to the MySQL test database 
		con->setSchema("test");

		stmt = con->createStatement();
		res = stmt->executeQuery("SELECT 'Hello World!' AS _message"); // replace with your statement
		while (res->next()) {
			std::cout << "\t... MySQL replies: ";
			// Access column data by alias or column name 
			std::cout << res->getString("_message") << std::endl;
			std::cout << "\t... MySQL says it again: ";
			// Access column fata by numeric offset, 1 is the first column 
			std::cout << res->getString(1) << std::endl;
		}
		delete res;
		delete stmt;
		delete con;

	}
	catch (sql::SQLException &e) {
		std::cout << "# ERR: SQLException in " << __FILE__;
		std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
		std::cout << "# ERR: " << e.what();
		std::cout << " (MySQL error code: " << e.getErrorCode();
		std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
	}

	std::cout << std::endl;

	return EXIT_SUCCESS;
}



*/


#include<iostream>
#include<conio.h>
#include<stdlib.h>
#include<stdio.h>
#include <string>

#include "cntx.h"

using namespace std;

int main(int argc, char argv[])
{
	std::string cur_cmd;
	system("cls");

	setlocale(0, "");
	DB_cntx new_DB;

	cur_cmd = "test";
	new_DB.read_command(cur_cmd);
	return 0;
}


/*
#include<cctype>

#include "common.h"

#include "out_iface.h"
#include "plate.h"

void print_menu(){ 
	std::cout << " Введите операцию(1 - 4 или stop):"
			  << "\n1 - получить количество музыкальных произведений заданного ансамбля"
			  << "\n2 - вывести название всех компакт-дисков заданного ансамбля"
			  << "\n3 - вывести лидеров продаж текущего года"
			  << "\n4 - добавление/изменение данных"
			  << "\nstop - завершение работы программы" << std::endl;
}


int main()
{
	//out_iface *ui;
	//plate pl_1;
	std::string command;
	bool end_fl = false;

	setlocale(0, "");
	//ui = &pl_1;
	//ui->add_obj_on_db();
 //   std::cout << "hello world!\n";

	while (1) {
		print_menu();
		//std::cin.ignore();
		//if (!getline(std::cin, command)) continue;
		std::cin >> command;
		if (command == "stop") break;
		
		///Продумать систему комманд(слова которые мапятся на ф-ции или цифры)!!!!!!
		if (stoi(command) <= 0 ) {
			std::cout << "Неверная комманда" << std::endl;
			continue;
		}
		switch (stoi(command))
		{
		case 1:
			DBG
			break;
		case 2:
			DBG
			break;
		case 3:
			DBG
			break;
		case 4:
			DBG
			break;
		default:
			std::cout << "Неверная комманда" << std::endl;
			break;
		}
	}
}
*/
// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
