// This header aims to make the standard library <random> more simple for non-computer programmers by providing shortcuts to some of the initialization steps.
// By hiding the seeding and library-loading process, we can jump into using known probability distributions and picking samples from them.
// The caveat of hiding the initialization of seed and engine is that this library cannot provide a testing environment with a specific seed.

#ifndef RANDOM_H
#define RANDOM_H

#include <iostream>
#include <random>
#include <functional>
#include <chrono>
#include <vector>
#include <optional>

namespace qol {

// initiating seed and random engine
unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
std::default_random_engine reng(seed);

// uniform distribution - double, int
class uniformd {
	// double [min, max)
	using pdf = std::uniform_real_distribution<double>;
	double min, max;
	pdf dist;
public:
	uniformd() : min{0.0}, max{1.0}, dist{min, max} {}
	uniformd(double a, double b) : min{a}, max{b}, dist{min, max} {}
	void set(double a, double b) { min=a; max=b; dist = pdf{min, max}; }
	double operator()() { return dist(reng); }
};
uniformd standard_uniformd;
double randd() { return standard_uniformd(); }
double uniformsample() { return randd(); }

class uniformdi {
	// int [min, max]
	using pdf = std::uniform_int_distribution<int>;
	int min, max;
	pdf dist;
public:
	uniformdi() : min{0}, max{100}, dist{min, max} {}
	uniformdi(int a, int b) : min{a}, max{b}, dist{min, max} {}
	void set(int a, int b) { min=a; max=b; dist = pdf{min, max}; }
	int operator()() { return dist(reng); }
};
uniformdi standard_uniformdi;
int randint() { return standard_uniformdi(); }

// normal distribution - double
class normald {
	using pdf = std::normal_distribution<double>;
	double mean, stdev;
	pdf dist;
public:
	normald() : mean{0.0}, stdev{1.0}, dist{mean, stdev} {}
	normald(double a, double b) : mean{a}, stdev{b}, dist{mean, stdev} {}
	void set(double a, double b) { mean=a; stdev=b; dist = pdf{mean, stdev}; }
	double operator()() { return dist(reng); }
};
normald standard_normald;
double normalsample() { return standard_normald(); }

// binomial distribution - int
class binomiald {
	using pdf = std::binomial_distribution<int>;
	int n;
	double p;
	pdf dist;
public:
	binomiald() : n{100}, p{0.5}, dist{n, p} {}
	binomiald(int a, double b) : n{a}, p{b}, dist{n, p} {}
	void set(int a, double b) { n=a; p=b; dist = pdf{n, p}; }
	double operator()() { return dist(reng); }
};
binomiald standard_binomiald;
double binomialsample() { return standard_binomiald(); }

// bernoulli distribution

// exponential distribution

// chi-squared distribution

// gamma distribution



}		// namespace qol

#endif	// RANDOM_H
