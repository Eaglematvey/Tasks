#pragma once
#include<string>
#include<set>
#include<map>
#include<vector>
#include<list>
#include<algorithm>

template <typename T = int> 
class Transport
{
private:
	struct Type
	{
		std::string type_name;
		std::map<T, std::list<std::string>> Routes;
	};
	std::list<Type> types;
	std::set<std::string> trstops;
	std::list<T> Tlist;
	std::list<std::string> strlist;
public:
	Transport(){};
	Transport(const Transport& transp){};
	~Transport(){};
	void addType(std::string type_name, T No, std::list<std::string>::iterator beg, std::list<std::string>::iterator en);
	void addRoute(T No, std::string type_name, std::list<std::string>::iterator beg, std::list<std::string>::iterator en);
	void delRoute(T No, std::string type_name);
	void addStop(std::string str);
	void delStop(std::string stop_name);
	int count_routes();
	int count_stops();
	std::pair<typename std::list<T>::iterator, typename std::list<T>::iterator>
		routes_of_stop(std::string stop_name);
	std::pair<typename std::list<T>::iterator, typename std::list<T>::iterator>
		routes_X_Y(std::string type_name, T X, T Y);
	std::pair<typename std::list<std::string>::iterator, typename std::list<std::string>::iterator>
		stops_no_routes();
	std::string stop_max_routes();
};