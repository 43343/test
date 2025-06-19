#include <vector>
#include <thread>
#include <mutex>
#include <stdio.h>
#include <random>
#include <iostream>

std::vector<int> a;
std::vector<uint64_t> b;
std::mutex aMutex;

uint64_t fib(int n) {
    uint64_t a = 0, b = 1;
    for (int i = 0; i < n; ++i) {
        uint64_t c = a + b;
        a = b;
        b = c;
    }
    return a;
}
void print_fib(int thread_id)
{
	while(!a.empty())
	{
		{
			std::lock_guard<std::mutex> lock(aMutex);
			if (a.empty()) break;
			int num = a[0];
			a.erase(a.begin());
			uint64_t fib_num = fib(num);
			std::cout << "Thread id: " << thread_id << " Номер числа фибоначи: " << num << " Число фибоначи: " << fib_num << "\n";
			b.push_back(fib_num);
		}
	}
}
int main()
{
	int n, p = 0;
	std::cout << "Введите колличество потоков: ";
	std::cin >> p;
	std::cout << "Введите размер массива: ";
	std::cin >> n;
	//Каждому индексу массива присваивается случайное число от 0 до 92
	std::random_device rd;
    	std::mt19937 gen(rd());
    	std::uniform_int_distribution<> dist(0, 92);
	
	a.resize(n);
	for (int& num : a) {
        	num = dist(gen);
    	}
	//вывод массива а
	std::cout << "Array a: { ";
	for (int num : a)
	{
      		std::cout << num << " ";
	}
	std::cout << " }\n";
	std::vector<std::thread> threads;
	for (int i = 0; i < p; ++i) {
        	threads.emplace_back(print_fib, i);
	}
	for (auto& thread : threads) {
        	thread.join();
    	}
	//Выводим массив b
	std::cout << "Array b: { ";
	for (uint64_t num : b)
	{
      		std::cout << num << " ";
	}
	std::cout << "}\n";

	return 0;
}
