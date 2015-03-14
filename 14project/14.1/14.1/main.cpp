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
		for (i; i != -1 && isdigit(str1[i]); i--);
		for (j; j != -1 && isdigit(str2[j]); j--);
		if (i == j)
		{
		if (!isdigit(str1[i + 1]) && isdigit(str2[j + 1])) return true;
		else  if(isdigit(str1[i + 1]) && !isdigit(str2[j + 1])) return false;
		else if (isdigit(str1[i + 1]) && isdigit(str2[j + 1]))
			return(stoll(str1.substr(i + 1)) < stoll(str2.substr(j + 1)));
		}
		return (i < j);
	});
	cout << "Result:" << endl;
	for (string str : v)
	{
		cout << str << ' ';
	}
	cout << endl;
	return 0;
}
