#include "Sample.h"
#include <iostream>
#include <iterator>__msvc_all_public_headers.hpp
#include <complex>_dbdao.h
#include <numeric>__msvc_all_public_headers.hpp
#include <vector>activation.h
#include <algorithm>
using namespace std;
using cmplx = complex<double_t>; 

static auto scaler(int32_t min_from, int32_t max_from, double_t min_to,
	double_t max_to) {
	const int32_t w_from{ max_from - min_from };
	const double w_to{ max_to - min_to };
	const int32_t mid_from{ (max_to-min_to ) / 2+ min_to};
	const double mid_to{ (max_to - min_to) / 2.0 + min_to };
	return [=](int from) {
		return double(from - mid_from) / w_from * w_to + mid_to; 
	};
};

template<typename A,typename B>
static auto scaled_cmplx(A scaler_x, B scaler_y) {
	return [=](int x, int y) {
		return cmplx{ scaler_x(x),scaler_y(y) };
	};
};
static auto mandelbrot_iterations(cmplx c) {
	cmplx z{};
	size_t iterations{ 0 };
	const size_t max_iterations{ 1000 };
	while (abs(z) < 2 && iterations < max_iterations) {
		++iterations;
		z = pow(z, 2) + c;
	}
	return  iterations;
}

int main() {
	/*const size_t w{ 100 };
	const size_t h{ 40 };

	auto scale(scaled_cmplx(scaler(0, w, -2.0, 1.0),
		scaler(0, h, -1.0, 1.0)));

	auto i_to_xy([=](int i) {return scale(i % w, i / w); });
	auto to_iteration_count([=](int i) {
		return mandelbrot_iterations(i_to_xy(i)); });

	vector<int> v(w * h);
	iota(begin(v), end(v), 0);
	transform(begin(v), end(v), begin(v), to_iteration_count);

	auto binfunc([w, n{ 0 }](auto output_it, int x)mutable{
		*++output_it = (x > 50 ? '*' : ' ');
		if (++n % w == 0) { ++output_it = '\n' }
		return output_it;
	});

	accumulate(begin(v), end(v), ostream_iterator<char>{cout}, binfunc);*/
	

	/*std::vector<int> q;
	q.push_back(); */
};