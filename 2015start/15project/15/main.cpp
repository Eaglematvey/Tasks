#include"Transport.h"
#include"Transport.cpp"
#include<iostream>
using namespace std;

int main()
{
	list<string> stops;
	stops.push_back("a");
	stops.push_back("c");
	list<string> stops2;
	stops2.push_back("c");
	stops2.push_back("d");
	list<string> stops3;
	stops2.push_back("e");
	stops2.push_back("b");
	Transport<int> transport;
	transport.addType("Bus", 1, stops.begin(), stops.end());	
	transport.addRoute(10, "Bus", stops2.begin(), stops2.end());
	transport.addType("Trolleybus", 5, stops3.begin(), stops3.end());
	transport.delStop("a");
	transport.addStop("x");
	cout << "Number of routes:" << transport.count_routes() << endl;
	cout <<"Number of stops:"<<transport.count_stops() << endl;
	pair<list<int>::iterator, list<int>::iterator> pr = transport.routes_of_stop("c");
	list<int> routes(pr.first, pr.second);
	cout << "Routes of stop c:" << endl;
	for (int t : routes)
	    cout << t << endl;
	routes.clear();
	pr = transport.routes_X_Y("Bus", 0, 4);
	list<int> rout(pr.first, pr.second);
	cout << "Routes beteen 0 and 4 of Bus:" << endl;
	for (int t : rout)
		cout << t << endl;
	pair<list<string>::iterator, list<string>::iterator> pr2 = transport.stops_no_routes();
	list<string> routes2(pr2.first, pr2.second);
	cout << "Stops without routs:" << endl;
	for (string t : routes2)
		cout << t << endl;;
	cout << "Stop with maximum routs:" <<endl<< transport.stop_max_routes() << endl;
	return 0;
}