#include <cstdio>
#include <cstring>
#include <cstdlib>

typedef long long ll;
const int N = 2e6 + 7;

int n, s[N], c[N], a[N];
ll sum, ans = 233333333;

void rplus(int l, int r, int val) { c[l] += val, c[r + 1] -= val; }

void add(int fir, int las, int val, int inc)
{
	rplus(fir, fir, val), rplus(fir + 1, las, inc), rplus(las + 1, las + 1, -(val + (fir - las) * inc));
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", s + i);
		if (s[i] > i)
		{
			add(i + 1, n, n - s[i], -1);
			add();
		}
	}
	sum = 0;
	for (int i = 1; i <= n; i++) sum += c[i], a[i] = sum;
	sum = 0;
	for (int i = 1; i <= n; i++)
	{
		sum += a[i];
		if (sum < ans) ans = sum;
	}
	printf("%lld\n", ans);
	return 0;
}
