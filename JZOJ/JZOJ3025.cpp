#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

typedef long long ll;
const int N = 2e5 + 3;

int n, m, p, fir, col[N], cost[N];
ll ans = 0, sum;

inline ll read()
{
	ll x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + (c ^ '0');
	return f ? -x : x;
}

int main()
{
	n = read(), m = read(), p = read();
	for (int i = 1; i <= n; i++) col[i] = read(), cost[i] = read();
	for (int k = 0; k < m; k++)
	{
		sum = 0LL;
		for (int i = 1; i <= n; i++)
		{
			if (cost[i] > p) sum = 0LL;
			else sum++;
			if (col[i] == k) ans += sum;
		}
	}
	printf("%lld\n", ans);
	return 0;
}
