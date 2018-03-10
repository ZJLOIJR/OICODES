#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int N = 5e4 + 3;

int n, a[N], b[N];
long double ansa = 0.0, ansb = 0.0, sqrsum[N][2], sum[N][2];

inline int read()
{
	int x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + (c ^ '0');
	return f ? -x : x;
}
inline long double sqr(long double a) { return a * a; }

int main()
{
	n = read();
	for (int i = 1; i <= n; i++) a[i] = read(); 
	for (int i = 1; i <= n; i++) b[i] = read();
	sort(a + 1, a + n + 1);
	sort(b + 1, b + n + 1);
	for (int i = 1; i <= n; i++) sqrsum[i][0] = sqrsum[i - 1][0] + sqr(a[i]), sum[i][0] = sum[i - 1][0] + a[i];
	for (int i = 1; i <= n; i++) sqrsum[i][1] = sqrsum[i - 1][1] + sqr(b[i]), sum[i][1] = sum[i - 1][1] + b[i];
	for (int i = 1; i <= n; i++)
	{
		int po = lower_bound(b + 1, b + n + 1, a[i]) - b;
		while (b[po] > a[i] || po > n) po--;
		ansa += sqrsum[po][1] + po * sqr(a[i]) - 2 * sum[po][1] * a[i];
	}
	for (int i = 1; i <= n; i++)
	{
		int po = lower_bound(a + 1, a + n + 1, b[i]) - a;
		while (a[po] > b[i] || po > n) po--;
		ansb += sqrsum[po][0] + po * sqr(b[i]) - 2 * sum[po][0] * b[i];
	}
	printf("%.1lf\n", (double)(ansa - ansb) / n);
	return 0;
}
