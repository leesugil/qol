// the current version is not optimized for performance, such as constructing/destructing engine objects per each function call.
// use the standard library functions for distributable work.

#ifndef RANDOM_H
#define RANDOM_H

#include <iostream>
#include <random>
#include <functional>
#include <chrono>
#include <vector>
#include <optional>

// global random engine with optional seed argument
std::default_random_engine& engine(std::optional<unsigned int> seed = std::nullopt)
{
	static std::default_random_engine engine(std::chrono::system_clock::now().time_since_epoch().count());
	if (seed) engine.seed(seed.value());
	return engine;
}

// integer in uniform distribution in [min, max)
auto uniformdi(int min, int max)
{
	return [min, max]() {
		std::uniform_int_distribution<int> dist(min, max);
		return dist(engine());
	};
}

// integer in uniform distribution in [min, max)
int randint(int min, int max)
{
	if (max<min) std::swap(min, max);
	else if (min==max) return min;
	auto dist = uniformdi(min, max);
	return dist();
}

// integer in uniform distribution in [0, max)
int randint(int max) { return randint(0, max); }

// integer vector in uniform distribution in [min, max)
void randivec(std::vector<int>& v, int min, int max) { for (auto& e : v) e = randint(min, max); }

// integer vector in uniform distribution in [0, max)
void randivec(std::vector<int>& v, int max) { for (auto& e : v) e = randint(max); }

// double in uniform distribution in [min, max)
double randdouble(double min, double max)
{
	if (max<min) std::swap(min, max);
	else if (min==max) return min;
	return std::uniform_real_distribution<>{min, max}(engine());
}

// double in uniform distribution in [0.0, 1.0)
double randdouble() { return randdouble(0.0, 1.0); }

// double vector in uniform distribution in [min, max)
void randdvec(std::vector<double>& v, double min, double max) { for (auto& e : v) e = randdouble(min, max); }

// double vector in uniform distribution in [0.0, 1.0)
void randdvec(std::vector<double>& v) { for (auto& e : v) e = randdouble(); }

// double in normal distribution N(mean, std)
auto normald(double mean, double std)
{
	return [mean, std]() mutable {
		std::normal_distribution<double> dist(mean, std);
		return dist(engine());
	};
}

// double in normal distribution N(0.0, 1.0)
auto normald()
{
	return normald(0.0, 1.0);
}

// integer in binomial distribution B(n, p)
auto binomiald(int n, double p)
{
	return [n, p]() mutable {
		std::binomial_distribution<int> dist(n, p);
		return dist(engine());
	};
}


#endif	// RANDOM_H
