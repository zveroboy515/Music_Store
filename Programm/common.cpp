#include "common.h"
#include <sstream>


std::vector<std::string> ParsInArgs(std::string &str) {
	std::stringstream ss{ str };
	std::string cur_arg;
	std::vector <std::string> out_vec;

	while (!ss.eof()) {
		ss >> cur_arg;
		out_vec.push_back(cur_arg);
		cur_arg.clear();
	}

	return out_vec;
}