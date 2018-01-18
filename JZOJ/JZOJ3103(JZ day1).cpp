#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 1000007, INF = 0x7fffffff;
typedef long long ll;

int n, q, l, r, mid, ans = 0;
int lef[N], rig[N];
ll a[N], c[N], w[N];

int check(int m)
{
	for (int i = 1; i <= n; i++) c[i] = a[i] - a[i - 1];
	ll sum = 0;
	for (int i = 1; i <= m; i++)
		c[lef[i]] += w[i], c[rig[i] + 1] -= w[i];
	for (int i = 1; i <= n; i++)
	{
		sum += c[i];
		if (sum < 0) return 0;
	}
	return 1;
}

inline ll read()
{
	ll x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + c - '0';
	return f ? -x : x;
}

int main()
{
	n = read(), q = read();
	for (int i = 1; i <= n; i++)
		*(a + i) = read(),
		c[i] = a[i] - a[i - 1];
	for (int i = 1; i <= q; i++)
		*(w + i) = read(), *(lef + i) = read(), *(rig + i) = read(),
		w[i] = -w[i];
	l = 1, r = q;
	while (l <= r)
	{
		mid = l + r >> 1;
		if (check(mid)) l = mid + 1, ans = mid;
		else r = mid - 1;
	}
	if (ans + 1 > q) printf("0\n");
	else printf("-1\n%d\n", ans + 1);
	return 0;
}
