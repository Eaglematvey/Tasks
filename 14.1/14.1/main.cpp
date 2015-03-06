#include<iostream>
#include<vector>
#include<algorithm>
#include<functional>
#include<string>

using namespace std;

int main(int argc, char * argv[])
{
	vector<string> v;
	string str;
	cout << "Enter a number of files:" << endl;
	int numFiles;
	cin >> numFiles;
	cout << "Enter names of files:" << endl;
	for (int i = 0; i < numFiles;i++)
	{
		cin >> str;
		v.push_back(str);
	}
	sort(v.begin(), v.end(), 
		[](const string& str1, const string& str2)->bool const
	{
		int i = str1.length() - 1,
			j = str2.length() - 1;
		for (i; isdigit(str1[i - 1]); i--);
		for (j; isdigit(str2[j - 1]); j--);
		if (i != j)
			return (i < j);
		long long num1 = stoll(str1.substr(i)),
			      num2 = stoll(str2.substr(j));
		return (num1 < num2);
	});
	cout << "Result:" << endl;
	for (string str : v)
	{
		cout << str << ' ';
	}
	cout << endl;
	return 0;
}
