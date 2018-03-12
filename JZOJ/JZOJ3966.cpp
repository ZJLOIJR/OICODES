#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 1e5 + 3;
const double exp = 1e-12;

int n, a[N];
double l, r, mid, ans;

inline int read()
{
	int x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + (c ^ '0');
	return f ? -x : x;
}

int main()
{
	n = read();
	for (int i = 1; i <= n; i++) a[i] = read();
	l = 0.0, r = 10000.0;
	while (r - l >= exp)
	{
		mid = (l + r) / 2;
		if (check(mid)) r = mid, ans = mid;
		else l = mid;
	}
	printf("%.3lf\n", ans);
	return 0;
}
