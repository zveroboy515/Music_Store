#include "cntx.h"


bool DB_cntx::initDB() {
	std::string host, username, pwd, db_name;
	int port = 0;
	std::string unix_socket;
	int clientflag = 0;
	//static MYSQL *conn;

	// �������� ���������� ����������
	DB_conn = mysql_init(NULL);
	if (DB_conn == NULL)
	{
		// ���� ���������� �� ������� � ������� ��������� �� ������
		fprintf(stderr, "Error: can'tcreate MySQL-descriptor\n");
		//exit(1); //���� ������������ ������� ����������
		return false;
	}

	std::cout << "������� ������ ��� ����������� � �� (host username pwd db_name)" << std::endl;
	std::cin >> host >> username >> pwd >> db_name;
	//����������
	//if (!mysql_real_connect(conn, host.c_str(), username.c_str(), pwd.c_str(), db_name.c_str(), port, unix_socket.c_str(), clientflag))
	if (!mysql_real_connect(DB_conn, "localhost", "german", "12345678", "musicstore", 3306, NULL, 0))
	{
		// ���� ��� ����������� ���������� ���������� � ��������
		// ���� ������ ������� ��������� �� ������
		fprintf(stderr, "Error: can't connect to database %s\n", mysql_error(DB_conn));
		return false;
	}
	else
	{
		// ���� ���������� ������� ����������� ������� ����� - "Success!"
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

	// ������������ � �������
	//if (!initDB()) return 0;
	//initDB();
	mysql_set_character_set(DB_conn, "cp1251");
	//������� ���������� �� ��������� �� ������, �� ��������� ��� latin1
	std::cout << "connectioncharacterset: " << mysql_character_set_name(DB_conn) << std::endl;
	//mysql_query(conn, "UPDATE `musicstore`.`ansamble` SET `name` = '�����' WHERE(`AName` = '�������')");
					  //"INSERT INTO `musicstore`.`person` (`Profession`, `AName`, `PName`) VALUES('we', 'jgf', 'sdc')"
	mysql_query(DB_conn, "INSERT INTO `musicstore`.`person` (`Profession`, `AName`, `PName`) VALUES('�����������', '�������', '����')");
	mysql_query(DB_conn, "INSERT INTO `musicstore`.`person` (`Profession`, `AName`, `PName`) VALUES('�����������', '�������', '����')");
	mysql_query(DB_conn, "INSERT INTO `musicstore`.`person` (`Profession`, `AName`, `PName`) VALUES('�����������', 'Skilet', '����')");
	//mysql_query(conn, "INSERT INTO `musicstore`.`ansamble` (`name`, `AName`) VALUES('����', '�������')");
	std::cout << "�������� ������� ���������" << std::endl;
	mysql_query(DB_conn, "SELECT * FROM ansamble"); //������ ������ � ������� �� ����� ��� =)

	if (res = mysql_store_result(DB_conn)) {
		while (row = mysql_fetch_row(res)) {
			if (mysql_num_fields(res) <= 0) std::cout << "DB empty" << std::endl;
			for (i = 0; i < mysql_num_fields(res); i++) {
				std::cout << row[i] << "\n"; //������� ��� ��� ���� � ���� ����� ����
			}
		}
	}
	else { 
		fprintf(stderr, "%s\n", mysql_error(DB_conn)); 
		return false;
	}

	std::cout << "�������� ������� �����" << std::endl;
	mysql_query(DB_conn, "SELECT * FROM Person");
	if (res = mysql_store_result(DB_conn)) {
		while (row = mysql_fetch_row(res)) {
			if (mysql_num_fields(res) <= 0) std::cout << "DB empty" << std::endl;
			for (i = 0; i < mysql_num_fields(res); i++) {
				std::cout << row[i] << "\n"; //������� ��� ��� ���� � ���� ����� ����
			}
		}
	}
	else { fprintf(stderr, "%s\n", mysql_error(DB_conn));
		return false;
	}

	// ��������� ���������� � �������� ���� ������
	mysql_close(DB_conn);

	//system("Pause");

	return true;
}