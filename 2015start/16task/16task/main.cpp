#include<iostream>
#include<thread>
#include<mutex>
#include<chrono>
#include<atomic>
using namespace std;

mutex mu;
mutex mu2;

atomic<unsigned long long> sum(0);
atomic<long long> copnum(0);

void Sover(unsigned long long num, long long part)
{
	long long partsum = 0;
	long long end;
	long long start;
	while (copnum > 0)
	{
		unique_lock<mutex> _lock(mu);
		end = copnum;
		copnum -= part;
		start = copnum;
		_lock.unlock();
		if (start < 0)
			start = 0;
		for (long long i = end; i > start; --i)
		if (num%i == 0)
			partsum += i;
	}
	unique_lock<mutex> _lock2(mu2);
	sum += partsum;
	_lock2.unlock();
}

int main()
{
	short numthreads;
	cout << "Number of threads:" << endl;
	cin >> numthreads;
	unsigned long long num;
	cout << "Number to check:" << endl;
	cin >> num;
	long long part = num / 200 + 1;
	thread* t = new thread [numthreads];
	copnum = num/2;
	auto start_time = chrono::system_clock::now();
	for (short i = 0; i < numthreads; i++)
		t[i] = thread(Sover,num, part);
	for(short i = 0; i < numthreads; i++)
		t[i].join();
	auto end_time = std::chrono::system_clock::now();
	auto dif = end_time - start_time;
	delete[] t;
	cout <<"Time:"<< chrono::duration_cast<std::chrono::milliseconds>(dif).count() << endl;
	cout << boolalpha << (sum == num) << endl;
	return 0;
}