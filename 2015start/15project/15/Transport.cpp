#pragma once
#include"Transport.h"
template<class T>
void Transport<T>::addType(std::string type_name, T No, std::list<std::string>::iterator beg, std::list<std::string>::iterator en)
{
	Type typ;
	typ.type_name = type_name;
	std::list<std::string> st(beg, en);
	for (std::string ststr : st)
		addStop(ststr);
	typ.Routes.insert(make_pair(No, st));
	types.push_back(typ);
}

template<class T>
void Transport<T>::addRoute(T No, std::string type_name, std::list<std::string>::iterator beg, std::list<std::string>::iterator en)
{
	auto it = find_if(types.begin(), types.end(), [type_name](Type t)
	{return (type_name == t.type_name); });
	std::list<std::string> st(beg, en);
	for (std::string ststr : st)
		addStop(ststr);
	if (it != types.end())
		it->Routes.insert(make_pair(No, st));
}

template<class T>
void Transport<T>::delRoute(T No, std::string type_name)
{

	if (it != types.end())
		typ.Routes.erase(No);
}

template<class T>
void Transport<T>::addStop(std::string str)
{
	trstops.insert(str);
}

template<class T>
void Transport<T>::delStop(std::string stop_name)
{
	trstops.erase(stop_name);
	for (Type typ : types)
     	for (auto rit = typ.Routes.begin(); rit != typ.Routes.end(); rit++)
	        if (find(rit->second.begin(), rit->second.end(), stop_name) != rit->second.end())
	        {
	        	if (rit->second.size() == 1)
		        	typ.Routes.erase(rit);
           	}
	        else rit->second.remove(stop_name);
}

template<class T>
int Transport<T>::count_routes()
{
	int num = 0;
	for_each(types.begin(), types.end(), [&num](Type t)
	{num += t.Routes.size(); });
	return num;
}

template<class T>
int Transport<T>::count_stops()
{
	return trstops.size();
}

template<class T>
std::pair<typename std::list<T>::iterator, typename std::list<T>::iterator>
Transport<T>::routes_of_stop(std::string stop_name)
{
	Tlist.clear();
	for (Type typ : types)
	    for (auto route : typ.Routes)
	        if (find(route.second.begin(), route.second.end(), stop_name) != route.second.end())
	         	Tlist.push_back(route.first);
	return std::make_pair(Tlist.begin(), Tlist.end());
}

template<class T>
std::pair<typename std::list<T>::iterator, typename std::list<T>::iterator>
Transport<T>::routes_X_Y(std::string type_name, T X, T Y)
{
	Tlist.clear();
	std::list<Type>::iterator it = find_if(types.begin(), types.end(), [type_name](Type t)
	{return (type_name == t.type_name); });
	if (it != types.end())
	    for (auto route : it->Routes)
	         if (X <= route.first && route.first < Y)
	        	Tlist.push_back(route.first);
	return std::make_pair(Tlist.begin(), Tlist.end());
}

template<class T>
std::pair<typename std::list<std::string>::iterator, typename std::list<std::string>::iterator>
Transport<T>::stops_no_routes()
{
	strlist.clear();
	for (std::string trs : trstops)
	{
		bool b = true;
        for (Type typ : types)
	        for (auto route : typ.Routes)
	    	      if (find(route.second.begin(),route.second.end(),trs) != route.second.end())
			     	 b = false;
		if (b) strlist.push_back(trs);
	}
	return std::make_pair(strlist.begin(), strlist.end());
}

template<class T>
std::string Transport<T>::stop_max_routes()
{
	if (trstops.empty())
		return NULL;
	std::map<int, std::string> maxstr;
	int maxint = 0;
	for (std::string trs : trstops)
	{
		int i = 0;
		for (Type typ : types)
		    for (auto route : typ.Routes)
			    for (std::string str : route.second)
				    if (str == trs) i++;
		if (i >= maxint)
		{
			maxint = i;
			maxstr.insert(make_pair(i, trs));
		}
	}
	return (maxstr.find(maxint))->second;
}