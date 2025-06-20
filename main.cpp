#include <vector>
#include <thread>
#include <mutex>
#include <atomic>
#include <random>
#include <iostream>

std::vector<int> a;
std::vector<uint64_t> b;
std::mutex a_mutex; 

uint64_t fib(int n) {
    uint64_t a = 0, b = 1;
    for (int i = 0; i < n; ++i) {
        uint64_t c = a + b;
        a = b;
        b = c;
    }
    return a;
}
void print_fib(int thread_id, size_t start, size_t end)
{
	for (size_t i = start; i < end; ++i) {
        	uint64_t fib_num = fib(a[i]);
        	b[i] = fib_num;
        	{
            		std::lock_guard<std::mutex> lock(a_mutex);
           	 	std::cout << "Thread id: " << thread_id  << " Номер числа фибоначи: " << a[i]  << " Число фибоначи: " << fib_num << "\n";
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
	b.resize(n);
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
	size_t chunk_size = n / p;
    	size_t remainder = n % p;
    	size_t start = 0;
	for (int i = 0; i < p; ++i) {
		size_t end = start + chunk_size + (i < remainder ? 1 : 0);
        	threads.emplace_back(print_fib, i, start, end);
		start = end;
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
