#ifndef RANDOM_H
#define RANDOM_H

#include <iostream>
#include <random>
#include <functional>
#include <chrono>
#include <vector>
#include <optional>

// global random engine with optional seed argument
std::default_random_engine& engine(std::optional<unsigned int> opt_s = std::nullopt)
{
	static std::optional<unsigned int> seed;
	if (opt_s) seed = opt_s;
	static std::default_random_engine engine(seed.value_or(std::chrono::system_clock::now().time_since_epoch().count()));
	return engine;
}

// integer in uniform distribution in [min, max)
int randint(int min, int max)
{
	if (max<min) std::swap(min, max);
	else if (min==max) return min;
	return std::uniform_int_distribution<>{min, max}(engine());
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

#endif	// RANDOM_H
