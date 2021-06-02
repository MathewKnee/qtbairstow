#pragma once
#include <vector>

#include <Interval.h>
std::vector<long double> floatingBairstow(int n, std::vector<long double> a_in, int max_it, long double mincorr, long double zerodet);
std::vector<interval_arithmetic::Interval<long double>> intervalBairstow(int n, std::vector<interval_arithmetic::Interval<long double>> a_in, int max_it, long double mincorr, long double zerodet);
std::vector<std::vector<long double>> floatingPointBairstow(int n, std::vector<long double> a, int max_it, long double mincorr, long double zerodet);
std::vector<std::vector<interval_arithmetic::Interval<long double>>> intervalABairstow(int n, std::vector<interval_arithmetic::Interval<long double>> a, int max_it, long double mincorr, long double zerodet);
