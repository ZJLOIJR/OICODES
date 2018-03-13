#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 1e5 + 3;
const double EXP = 1e-12;

int n;
double l, r, mid, ans = -1.0, a[N];

int check(double x)
{
	double ret = 0, sum = 0.0, maxx = -1e9;
	for (int i = 1; i <= n; i++) ret += a[i] - x;
	for (int i = 2; i <= n - 1; i++)
	{
		if (sum < 0) sum = 0;
		sum += a[i] - x;
		if (sum > maxx) maxx = sum;
	}
	return ret <= maxx;
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%lf", a + i);
	l = 1.0, r = n * 10000.0;
	while (r - l >= EXP)
	{
		mid = (l + r) / 2;
		if (check(mid)) r = mid, ans = mid;
		else l = mid;
	}
	printf("%.3lf\n", ans);
	return 0;
}
