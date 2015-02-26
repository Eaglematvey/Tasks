#include<iostream> //ѕроверить, €вл€етс€ ли контейнер палиндромом.
#include<fstream>
#include<vector>

using namespace std;

template<class T>
bool isPolynom(T& v) 
{
	//ѕустое множество считаетс€ палиндромом ?
	//if (v.empty()) return false;    
	T::iterator it = v.begin();
	T::reverse_iterator rit = v.rbegin();
	int halfsize = v.size()/2;
	for (int i = 1; i <= halfsize; i++, ++it, ++rit)
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
	bool b = isPolynom(container1);
	cout << boolalpha << b << endl;
	return 0;
}