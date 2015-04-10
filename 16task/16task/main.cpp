#include<iostream>
#include<thread>
#include<mutex>
#include<chrono>
using namespace std;

mutex mu;

void Sover(unsigned long long& num, long long i, int numthreads, unsigned long long& sum)
{
	unsigned long long end = num / 2;
	unique_lock<mutex> lock(mu, defer_lock);
	for (; i <= end; i += numthreads)
		if (num%i == 0)
			sum += i;
}

int main()
{
	int numthreads;
	cout << "Number of threads:" << endl;
	cin >> numthreads;
	unsigned long long num;
	cout << "Number to check:" << endl;
	cin >> num;
	thread* t = new thread [numthreads+1];
	unsigned long long sum = 0;
	auto start_time = chrono::system_clock::now();
	for (int i = 1; i <= numthreads; i++)
		t[i] = thread(Sover, ref(num), i, numthreads,ref(sum));
	for(long long i = 1; i <= numthreads; i++)
		t[i].join();
	auto end_time = std::chrono::system_clock::now();
	auto dif = end_time - start_time;
	delete[] t;
	cout <<"Time:"<< chrono::duration_cast<std::chrono::milliseconds>(dif).count() << endl;
	cout << boolalpha << (sum == num) << endl;
	return 0;
}