#include<iostream>
#include"Stack.h"

using namespace std;
int main()
{
	Stack<int> st;
	st.push(-23);
	st.push(2455);
	st.push(-456);
	st.push(-345);
	st.push(-3556);
	cout << "Top: " << st.top() << endl;
	cout <<"Min: "<< st.min() << endl;
	st.pop();
	cout << "Min: " << st.min() << endl;
	st.pop(); 
	cout << "Min: " << st.min() << endl;
	st.pop();
	cout << "Min: " << st.min() << endl;
	st.pop();
	cout << "Min: " << st.min() << endl;
	cout << "Top: " << st.top() << endl;
	return 0;
}