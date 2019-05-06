#include <iostream>
#include <chrono>
#include <vector>
#include <numeric>
#include <execution>
#include <omp.h>

int main() {

	auto t1 = std::chrono::high_resolution_clock::now();
	std::vector<double> v(500'000'137,0.5);
	auto t2 = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> ms = t2 - t1;
	std::cout << std::fixed << "Time taken to initialize array: " << ms.count() << " ms\n";

	{
		auto t1 = std::chrono::high_resolution_clock::now();
		double result = std::accumulate(v.begin(), v.end(), 0.0);
		auto t2 = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double, std::milli> ms = t2 - t1;
		std::cout << std::fixed << "std::accumulate result " << result
				<< " took " << ms.count() << " ms\n";
	}

	{
		auto t1 = std::chrono::high_resolution_clock::now();
		double result = std::reduce(std::execution::par_unseq, v.begin(),
				v.end());
		auto t2 = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double, std::milli> ms = t2 - t1;
		std::cout << "parallel::reduce result " << result << " took "
				<< ms.count() << " ms\n";
	}

	{
		auto t1 = std::chrono::high_resolution_clock::now();
		double result = 0;
#pragma omp parallel for shared(v) reduction(+: result)
		for (auto val : v) {
			result += val;
		}
		auto t2 = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double, std::milli> ms = t2 - t1;
		std::cout << "OpenMP result " << result << " took " << ms.count()
				<< " ms\n";
	}
}
