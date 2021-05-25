#include "bairstowMethod.h"

std::vector<long double> floatingBairstow(int n, std::vector<long double> a_in, int max_it, long double mincorr, long double zerodet) {
	long double r = 0.1;
	long double s = 0.1;
	std::vector<long double> a = a_in;
	std::vector<long double> b(n + 1);
	std::vector<long double> c(n + 1);
	std::vector<long double> ret(2 * n + 1);
	int ret_pos = 0;
	bool stop = false;
	while (!stop) {
		if (n < 1 || max_it < 1 || mincorr <= 0 || zerodet <= 0) break;
		if (n >= 3) {
			
			int it_count = 0;
			while (true) {
				for (int i = n; i >= 0; i--) {
					if (i == n) {
						b[i] = a[i];
						c[i] = b[i];
					}
					else if (i == n - 1) {
						b[i] = a[i] + r * b[i + 1];
						c[i] = b[i] + r * c[i + 1];
					}
					else {
						b[i] = a[i] + r * b[i + 1] + s * b[i + 2];
						c[i] = b[i] + r * c[i + 1] + s * c[i + 2];
					}
				}
				long double dr = (b[0] * c[3] - b[1] * c[2]) / (c[2] * c[2] - c[1] * c[3]);
				long double ds = (b[1] * c[1] - b[0] * c[2]) / (c[2] * c[2] - c[1] * c[3]);
				r += dr;
				s += ds;
				it_count++;
                if (std::abs(dr / r) <= mincorr || std::abs(ds / s) <= mincorr || it_count == max_it) {
					long double d = r * r + 4 * s;
					if (d >= zerodet) {
						ret[ret_pos++] = (r + sqrt(d)) / 2;
						ret[ret_pos++] = 0;
						ret[ret_pos++] = (r - sqrt(d)) / 2;
						ret[ret_pos++] = 0;
					}
					else {
						ret[ret_pos++] = r / 2;
                        ret[ret_pos++] = sqrt(std::abs(d)) / 2;
						ret[ret_pos++] = r / 2;
                        ret[ret_pos++] = -sqrt(std::abs(d)) / 2;
					}
					a.clear();
					for (int i = 2; i <= n; i++) {
						a.push_back(b[i]);
					}
					n -= 2;
					break;
				}
			
			}
		}
		else if (n == 2) {
			long double d = a[1]*a[1] - 4*a[2]*a[0];
			if (d >= zerodet) {
				ret[ret_pos++] = (-a[1] + sqrt(d)) / 2 * a[2];
				ret[ret_pos++] = 0;
				ret[ret_pos++] = (-a[1] - sqrt(d)) / 2 * a[2];
				ret[ret_pos++] = 0;
			}
			else {
				ret[ret_pos++] = -a[1] / 2 * a[2];
                ret[ret_pos++] = sqrt(std::abs(d)) / 2 * a[2];
				ret[ret_pos++] = -a[1] / 2 * a[2];
                ret[ret_pos++] = -sqrt(std::abs(d)) / 2 * a[2];
			}
			n -= 2;
		}
		else if (n == 1) {
			ret[ret_pos++] = -a[0] / a[1];
			n -= 1;
		}
		else {
			stop = true;
		}
		
	}
	
	return ret;
	
}
