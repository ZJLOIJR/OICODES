#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>

const int N = 100007;

int n, m, l, r, mid, ans;
int a[N];

inline int read()
{
	int x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + c - '0';
	return f ? -x : x;
}

int check(int val)
{
	int ret = 1, sum = 0;
	for (int i = 1; i <= n; i++)
		if (sum + a[i] > val)
			ret++, sum = a[i];
		else
			sum += a[i];
	return ret <= m;
}

int main()
{
	n = read(), m = read();
	for (int i = 1; i <= n; i++)
		*(a + i) = read(), l = l > a[i] ? l : a[i];
	r = 1e9;
	while (l <= r)
	{
		mid = (l + r) >> 1;
		if (check(mid))
			r = mid - 1, ans = mid;
		else
			l = mid + 1;
	}
	printf("%d\n", ans);
	return 0;
}
