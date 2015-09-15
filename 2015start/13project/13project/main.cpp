#include<iostream> //ѕроверить, €вл€етс€ ли контейнер палиндромом.
#include<fstream>
#include<vector>
#include<list>
using namespace std;

template<class T>
bool isPolyndrom(const T& v) 
{
	if (v.empty()) return true;
	T::const_iterator it = v.begin();
	T::const_iterator rit = v.end();
	rit--;
	for (it, rit;it<rit ; ++it,--rit)
		if ((*it) != (*rit))
			return false;			
	return true;
} 

int main()
{
	ifstream fin("file.txt");
	vector<int> container1;
	int cont1_num;
	while (fin >> cont1_num)
		container1.push_back(cont1_num);
	bool b = isPolyndrom(container1);
	cout << boolalpha << b << endl;
	return 0;
}