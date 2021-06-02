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
                if (abs(dr / r) <= mincorr || abs(ds / s) <= mincorr || it_count == max_it) {
					long double d = r * r + 4 * s;
                    int st;
					if (d >= zerodet) {
                        ret[ret_pos++] = (r + std::sqrt(d)) / 2;
						ret[ret_pos++] = 0;
                        ret[ret_pos++] = (r - std::sqrt(d)) / 2;
						ret[ret_pos++] = 0;
					}
					else {
						ret[ret_pos++] = r / 2;
                        ret[ret_pos++] = std::sqrt(std::abs(d)) / 2;
						ret[ret_pos++] = r / 2;
                        ret[ret_pos++] = -std::sqrt(std::abs(d)) / 2;
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
                ret[ret_pos++] = (-a[1] +std::sqrt(d)) / 2 * a[2];
				ret[ret_pos++] = 0;
                ret[ret_pos++] = (-a[1] - std::sqrt(d)) / 2 * a[2];
				ret[ret_pos++] = 0;
			}
			else {
				ret[ret_pos++] = -a[1] / 2 * a[2];
                ret[ret_pos++] = std::sqrt(std::abs(d)) / 2 * a[2];
				ret[ret_pos++] = -a[1] / 2 * a[2];
                ret[ret_pos++] = -std::sqrt(std::abs(d)) / 2 * a[2];
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
std::vector<interval_arithmetic::Interval<long double>>
intervalBairstow(int n, std::vector<interval_arithmetic::Interval<long double>> a_in,
                 int max_it, long double mincorr,
                 long double zerodet){

    interval_arithmetic::Interval<long double> r(0.1,0.1);
    interval_arithmetic::Interval<long double> s(0.1,0.1);
    std::vector<interval_arithmetic::Interval<long double>> a = a_in;
    std::vector<interval_arithmetic::Interval<long double>> b(n + 1);
    std::vector<interval_arithmetic::Interval<long double>> c(n + 1);
    std::vector<interval_arithmetic::Interval<long double>> ret(2 * n + 1);
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
                interval_arithmetic::Interval<long double> dr = (b[0] * c[3] - b[1] * c[2]) / (c[2] * c[2] - c[1] * c[3]);
                interval_arithmetic::Interval<long double> ds = (b[1] * c[1] - b[0] * c[2]) / (c[2] * c[2] - c[1] * c[3]);
                r = r + dr;
                s = s + ds;
                it_count++;
                if ((interval_arithmetic::IAbs(dr / r).a <= mincorr && interval_arithmetic::IAbs(dr / r).b <= mincorr)  || (interval_arithmetic::IAbs(ds / s).a <= mincorr && interval_arithmetic::IAbs(ds / s).b <= mincorr) || it_count == max_it) {
                    interval_arithmetic::Interval<long double> d = r * r + interval_arithmetic::Interval<long double>(4,4) * s;
                    if (d.a >= zerodet && d.b >=zerodet) {
                        int st;
                        ret[ret_pos++] = (r + interval_arithmetic::ISqrt(d,st)) / interval_arithmetic::Interval<long double>(2,2);
                        ret[ret_pos++] = interval_arithmetic::Interval<long double>(0,0);
                        ret[ret_pos++] = (r - interval_arithmetic::ISqrt(d,st)) / interval_arithmetic::Interval<long double>(2,2);
                        ret[ret_pos++] = interval_arithmetic::Interval<long double>(0,0);
                    }
                    else {
                        int st;
                        ret[ret_pos++] = r / interval_arithmetic::Interval<long double>(2,2);
                        ret[ret_pos++] = interval_arithmetic::ISqrt(interval_arithmetic::IAbs(d),st) / interval_arithmetic::Interval<long double>(2,2);
                        ret[ret_pos++] = r / interval_arithmetic::Interval<long double>(2,2);
                        ret[ret_pos++] = (interval_arithmetic::ISqrt(interval_arithmetic::IAbs(d),st) / interval_arithmetic::Interval<long double>(2,2)).Opposite();
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
            interval_arithmetic::Interval<long double> d = a[1]*a[1] - interval_arithmetic::Interval<long double>(4,4)*a[2]*a[0];
            if (d.a >= zerodet && d.b >=zerodet) {
                int st;
                ret[ret_pos++] = (a[1].Opposite() + interval_arithmetic::ISqrt(d,st)) / interval_arithmetic::Interval<long double>(2,2);
                ret[ret_pos++] = interval_arithmetic::Interval<long double>(0,0);
                ret[ret_pos++] = (a[1].Opposite() - interval_arithmetic::ISqrt(d,st)) / interval_arithmetic::Interval<long double>(2,2);
                ret[ret_pos++] = interval_arithmetic::Interval<long double>(0,0);
            }
            else {
                int st;
                ret[ret_pos++] = a[1].Opposite() / interval_arithmetic::Interval<long double>(2,2) * a[2];
                ret[ret_pos++] = interval_arithmetic::ISqrt(interval_arithmetic::IAbs(d),st) / interval_arithmetic::Interval<long double>(2,2) * a[2];
                ret[ret_pos++] = a[1] / interval_arithmetic::Interval<long double>(2,2) * a[2];
                ret[ret_pos++] =interval_arithmetic::ISqrt(interval_arithmetic::IAbs(d),st).Opposite()/ interval_arithmetic::Interval<long double>(2,2) * a[2];
            }
            n -= 2;
        }
        else if (n == 1) {
            ret[ret_pos++] = a[0].Opposite() / a[1];
            n -= 1;
        }
        else {
            stop = true;
        }

    }

    return ret;
}
std::vector<std::vector<long double>> floatingPointBairstow(int n, std::vector<long double> a, int max_it, long double mincorr, long double zerodet) {
    int i, k, n1, it, st;
    long double m, p, pq0, pq1, q, q0, q1, q2, q3, q4;
    bool cond, endpq;
    std::vector<std::vector<long double>> z, w;
    std::vector<long double> b(n+1);
    if (n < 1 || max_it < 1 || mincorr <= 0 || zerodet <= 0) {
        st = 1;
    }
    else {
        for (i = 0; i <= n; i++) {
            b[n - i] = a[i];
            if(i!=n){
                z.push_back(std::vector<long double>(2, 0));
                w.push_back(std::vector<long double>(2, 0));
            }

        }
        st = 0;
        i = 0;
        p = -1;
        q = -1;
        n1 = n - 1;
        cond = true;
        it = 0;
        do {
            if (n == 1) {
                z[i][0] = -b[1] / b[0];
                z[i][1] = 0;
                cond = false;
            }
            else {
                if (n == 2) {
                    q = b[0];
                    p = b[1] / q;
                    q = b[2] / q;
                    cond = false;
                }
                else {
                    pq0 = 1.0e63;
                    pq1 = pq0;
                    endpq = true;
                    do {
                        it++;
                        q0 = 0;
                        q1 = 0;
                        q2 = b[0];
                        q3 = b[1] - p * q2;
                        for (k = 2; k <= n; k++) {
                            q4 = b[k] - p * q3 - q * q2;
                            q2 = q2 - p * q - q * q0;
                            q0 = q1;
                            q1 = q2;
                            q2 = q3;
                            q3 = q4;
                        }
                        if (abs(q2) + abs(q3) < zerodet) {
                            endpq = false;
                        }
                        else {
                            m = q * q0 + p * q1;
                            q4 = q1 * q1 + m * q0;
                            if (abs(q4) < zerodet) {
                                st = 2;
                            }
                            else {
                                q0 = (q1 * q2 - q0 * q3) / q4;
                                q1 = (m * q2 + q1 * q3) / q4;
                                q2 = abs(q0);
                                q3 = abs(q1);
                                if (q2 > mincorr || q3 > mincorr || (q2 < pq0 && q3 < pq1)) {
                                    p = p + q0;
                                    pq0 = q2;
                                    q = q + q1;
                                    pq1 = q3;
                                }
                                else {
                                    endpq = false;
                                }
                                if (it == max_it && endpq) {
                                    st = 3;
                                }
                            }
                        }
                } while (!(st != 0 || !endpq));
            }
            if (st == 0) {
                m = -p / 2;
                q0 = m * m - q;
                q1 = std::sqrt(abs(q0));
                if (q0 < 0){
                    z[i][0] = m;
                    z[i + 1][0] = m;
                    z[i][1] = q1;
                    z[i + 1][1] = -q1;
                }
                else {
                    if (m > 0) {
                        m += q1;
                    }
                    else {
                        m -= q1;
                    }
                    z[i + 1][0] = m;
                    if (abs(m) < zerodet) {
                        z[i][0] = 0;
                    }
                    else {
                        z[i][0] = q / m;
                    }
                    z[i][1] = 0;
                    z[i + 1][1] = 0;
                }
                if (n > 2) {
                    i = i + 2;
                    n = n - 2;
                    q0 = 0;
                    q1 = b[0];
                    for (k = 1; k <= n; k++) {
                        q2 = b[k] - p * q1 - q * q0;
                        b[k] = q2;
                        q0 = q1;
                        q1 = q2;
                    }
                }
            }
            }
        } while (!(st != 0 || !cond));
        if (st == 0) {
            n = n1 + 1;
            for (i = 0; i < n; i++) {
                p = z[i][0];
                q = z[i][1];
                q1 = a[n];
                if (q == 0) {
                    for (k = n1; k >= 0; k--) {
                        q1 = q1 * p + a[k];
                    }
                    q2 = 0;
                }
                else {
                    q0 = std::sqrt(p * p + q * q);
                    q3 = 2 * atan(q / (p + q0));
                    q4 = n * q3;
                    q2 = q1 * sin(q4);
                    q1 = q1 * cos(q4);
                    for (k = n1; k >= 0; k--) {
                        p = a[k];
                        q4 = k * q3;
                        q1 = q1 * q0 + p * cos(q4);
                        q2 = q2 * q0 + p * sin(q4);
                    }
                }
            }
            w[i-1][0] = q1;
            w[i-1][1] = q2;
        }
    }

    std::vector<std::vector<long double>> ret;
    for(int j =0; j<(int)w.size();j++){
        ret.push_back(z[j]);
    }
    for(int j =0; j<(int)z.size();j++){
        ret.push_back(w[j]);
    }
    std::vector<long double> last_row;
    last_row.push_back(it);
    last_row.push_back(st);
    ret.push_back(last_row);
    return ret;
}
template<typename T>
interval_arithmetic::Interval<T> IArcsin(const interval_arithmetic::Interval<T> &x,int &st){
    bool finished;
    int k;
    interval_arithmetic::Interval<T> d1, d2, d3, s, w, w1, x2;
    if(x.a>x.b){
        st = 1;
    }else if(x.a <=-1 || x.b >=1){
        st = 3;
    }else{
        s = x;
        w = s;
        if(x.a<-0.998) w.a = -M_PI/2;
        else if(x.b >0.998) w.b = M_PI/2;
        x2=interval_arithmetic::ISqr(x,st);
        k=1;
        finished = false;
        st=0;
        do{
            d1.a=k;
            d1.b=d1.a;
            d2.a=k+1;
            d2.b=d2.a;
            d3.a=k+2;
            d3.b=d3.a;
            s = interval_arithmetic::IMul(s, interval_arithmetic::IDiv(interval_arithmetic::IMul(d1,x2),d2));
            w1 = interval_arithmetic::IAdd(w,interval_arithmetic::IDiv(s,d3));
            if(x.a<-0.998) w1.a = -M_PI/2;
            else if(x.b > 0.998) w1.b=M_PI/2;
            if(w.a!=0 && w.b !=0){
                if(abs(w.a-w1.a)/abs(w.a) < 1e-18 && abs(w.b-w1.b)/abs(w.b)<1e-18) finished = true;
            }else if(w.a==0 && w.b !=0){
                if (abs(w.a-w1.a)<1e-18 && abs(w.b-w1.b)/abs(w.b)<1e-18) finished = true;
            }else if(w.a !=0){
                if(abs(w.a-w1.a)/abs(w.a) < 1e-18 && abs(w.b-w1.b) < 1e-18) finished = true;
                else if(abs(w.a-w1.a) < 1e-18 && abs(w.b-w1.b) < 1e-18) finished = true;
            }

            if(finished){
                if(w1.b==M_PI/2 || w1.a == -M_PI/2) st =4;
                return w1;
            }else{
                w = w1;
                k = k +2;
            }
        }while(!(finished || k > INT_MAX/2));
    }
    if(!finished){
        st = 2;
    }
    return w1;
}
template<typename T>
interval_arithmetic::Interval<T> IAtan(const interval_arithmetic::Interval<T> &x,int &st){
    interval_arithmetic::Interval<T> s;

    if(x.a>x.b){
        st = 1;
    }else{
        s.a=1;
        s.b = s.a;
        s=interval_arithmetic::IAdd(s,interval_arithmetic::ISqr(x,st));
        s = interval_arithmetic::ISqrt(s,st);
        s = interval_arithmetic::IDiv(x,s);
        return IArcsin(s,st);
    }
    return s;
}



std::vector<std::vector<interval_arithmetic::Interval<long double>>> intervalABairstow(int n, std::vector<interval_arithmetic::Interval<long double>> a, int max_it, long double mincorr, long double zerodet) {
    int i, k, n1, it, st,rt;
    interval_arithmetic::Interval<long double> m, p, pq0, pq1, q, q0, q1, q2, q3, q4;
    bool cond, endpq;
    std::vector<std::vector<interval_arithmetic::Interval<long double>>> z, w;
    std::vector<interval_arithmetic::Interval<long double>> b(n+1);
    if (n < 1 || max_it < 1 || mincorr <= 0 || zerodet <= 0) {
        st = 1;
    }
    else {
        for (i = 0; i <= n; i++) {
            b[n - i] = a[i];
            if(i!=n){
                z.push_back(std::vector<interval_arithmetic::Interval<long double>>(2, interval_arithmetic::Interval<long double>(0,0)));
                w.push_back(std::vector<interval_arithmetic::Interval<long double>>(2, interval_arithmetic::Interval<long double>(0,0)));
            }
        }
        st = 0;
        i = 0;
        p = interval_arithmetic::Interval<long double>(-1,-1);
        q = interval_arithmetic::Interval<long double>(-1,-1);
        n1 = n - 1;
        cond = true;
        it = 0;
        do {
            if (n == 1) {
                z[i][0] = b[1].Opposite() / b[0];
                z[i][1] = interval_arithmetic::Interval<long double>(0,0);
                cond = false;
            }
            else {
                if (n == 2) {
                    q = b[0];
                    p = b[1] / q;
                    q = b[2] / q;
                    cond = false;
                }
                else {
                    pq0 = interval_arithmetic::Interval<long double>(1.0e63,1.0e63);
                    pq1 = pq0;
                    endpq = true;
                    do {
                        it++;
                        q0 = interval_arithmetic::Interval<long double>(0,0);
                        q1 = interval_arithmetic::Interval<long double>(0,0);
                        q2 = b[0];
                        q3 = b[1] - p * q2;
                        for (k = 2; k <= n; k++) {
                            q4 = b[k] - p * q3 - q * q2;
                            q2 = q2 - p * q - q * q0;
                            q0 = q1;
                            q1 = q2;
                            q2 = q3;
                            q3 = q4;
                        }
                        if ((interval_arithmetic::IAbs(q2) + interval_arithmetic::IAbs(q3)).a < zerodet && (interval_arithmetic::IAbs(q2) + interval_arithmetic::IAbs(q3)).b < zerodet) {
                            endpq = false;
                        }
                        else {
                            m = q * q0 + p * q1;
                            q4 = q1 * q1 + m * q0;
                            if (interval_arithmetic::IAbs(q4).a < zerodet && interval_arithmetic::IAbs(q4).b < zerodet || (q4.a < zerodet && q4.b > zerodet)) {
                                st = 2;
                            }
                            else {
                                q0 = (q1 * q2 - q0 * q3) / q4;
                                q1 = (m * q2 + q1 * q3) / q4;
                                q2 = interval_arithmetic::IAbs(q0);
                                q3 = interval_arithmetic::IAbs(q1);
                                if ((q2.a > mincorr && q2.b > mincorr) || (q3.a > mincorr && q3.b > mincorr) || ((q2.b < pq0.a) && ( q3.b < pq1.a))) {
                                    p = p + q0;
                                    pq0 = q2;
                                    q = q + q1;
                                    pq1 = q3;
                                }
                                else {
                                    endpq = false;
                                }
                                if (it == max_it && endpq) {
                                    st = 3;
                                }
                            }
                        }
                } while (!(st != 0 || !endpq));
            }
            if (st == 0) {
                m = p.Opposite() / interval_arithmetic::Interval<long double>(2,2);
                q0 = m * m - q;
                q1 = interval_arithmetic::ISqrt(interval_arithmetic::IAbs(q0),rt);
                if (q0.a < zerodet && q0.b < zerodet){
                    z[i][0] = m;
                    z[i + 1][0] = m;
                    z[i][1] = q1;
                    z[i + 1][1] = q1.Opposite();
                }
                else {
                    if (m.a > zerodet && m.b >zerodet) {
                        m = m + q1;
                    }
                    else {
                        m = m - q1;
                    }
                    z[i + 1][0] = m;
                    if ((interval_arithmetic::IAbs(m).a < zerodet && interval_arithmetic::IAbs(m).b < zerodet) ||(m.a <= zerodet && m.b >= zerodet)) {
                        z[i][0] = interval_arithmetic::Interval<long double>(0,0);
                    }
                    else {
                        z[i][0] = q / m;
                    }
                    z[i][1] = interval_arithmetic::Interval<long double>(0,0);
                    z[i + 1][1] = interval_arithmetic::Interval<long double>(0,0);
                }
                if (n > 2) {
                    i = i + 2;
                    n = n - 2;
                    q0 = interval_arithmetic::Interval<long double>(0,0);
                    q1 = b[0];
                    for (k = 1; k <= n; k++) {
                        q2 = b[k] - p * q1 - q * q0;
                        b[k] = q2;
                        q0 = q1;
                        q1 = q2;
                    }
                }
            }
            }
        } while (!(st != 0 || !cond));
        if (st == 0) {
            n = n1 + 1;
            for (i = 0; i < n; i++) {
                p = z[i][0];
                q = z[i][1];
                q1 = a[n];
                if ((q.a <= zerodet && q.b >=zerodet) || (abs(q.a)<=zerodet && abs(q.b)<=zerodet)) {
                    for (k = n1; k >= 0; k--) {
                        q1 = q1 * p + a[k];
                    }
                    q2 =interval_arithmetic::Interval<long double>(0,0);
                }
                else {
                    q0 = interval_arithmetic::ISqrt(p * p + q * q,rt);
                    q3 = 2 * interval_arithmetic::Interval<long double>(IAtan((q / (p + q0)),rt));
                    q4 = n * q3;
                    q2 = q1 * interval_arithmetic::ISin(q4);
                    q1 = q1 * interval_arithmetic::ICos(q4);
                    for (k = n1; k >= 0; k--) {
                        p = a[k];
                        q4 = k * q3;
                        q1 = q1 * q0 + p * interval_arithmetic::ICos(q4);
                        q2 = q2 * q0 + p * interval_arithmetic::ISin(q4);
                    }
                }
            }
            w[i-1][0] = q1;
            w[i-1][1] = q2;
        }
    }

    std::vector<std::vector<interval_arithmetic::Interval<long double>>> ret;
    for(int j =0; j<(int)w.size();j++){
        ret.push_back(z[j]);
    }
    for(int j =0; j<(int)z.size();j++){
        ret.push_back(w[j]);
    }
    std::vector<interval_arithmetic::Interval<long double>> last_row;
    last_row.push_back(interval_arithmetic::Interval<long double>(it,it));
    last_row.push_back(interval_arithmetic::Interval<long double>(st,st));
    ret.push_back(last_row);
    return ret;
}
