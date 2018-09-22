#include <cstdio>
#include <cstring>
#include <cstdlib>

typedef long long ll;
const int N = 2e6 + 7;

int n, s[N];
ll sum, ans = 233333333, c[N], a[N];

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
			add(0, i - 1, s[i] - i, 1);
			add(i, i + n - s[i], n - s[i], -1);
			add(i + n - s[i], n, 0, 1);
		}
		if (s[i] < i)
		{
			add(i, n, n - s[i], -1);
			add(0, i - s[i], i - s[i], -1);
			add(i - s[i], i - 1, 0, 1);
		}
		if (s[i] == i)
		{
			add(0, i - 1, 0, 1);
			add(i, n, n - s[i], -1);
		}
	}
	sum = 0;
	for (int i = 0; i <= n; i++) sum += c[i], a[i] = sum;
	sum = 0;
	for (int i = 0; i <= n; i++)
	{
		sum += a[i];
		if (sum < ans) ans = sum;
		printf("%d ", sum);
	}
	printf("%lld\n", ans);
	return 0;
}
