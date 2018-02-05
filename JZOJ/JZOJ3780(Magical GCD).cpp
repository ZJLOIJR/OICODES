#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>

const int N = 100007;
typedef long long ll;

int T, n;
ll a[N], g[N];
int nx[N], pr[N];

ll gcd(ll x, ll y)
{
	return y ? gcd(y, x % y) : x;
}

inline ll read()
{
	ll x = 0, f = 0;
	char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) if (ch == '-') f = 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) x = (x << 1) + (x << 3) + c - '0';
	return f ? -x : x;
}

void init()
{
	n = read();
	for (int i = 1; i <= n; i++)
		a[i] = read();
	for (int i = 1; i <= n; i++)
		nx[i] = i + 1, pr[i] = i - 1, g[i] = a[i];
}

void solve()
{
	ll ans = 0;
	for (int r = 1; r <= n; r++)
		for (int l = 1; l <= r; l = nx[l])
		{
			g[l] = gcd(g[l], a[r]);
			if (g[l] * (r - l + 1) > ans)
				ans = g[l] * (r - l + 1);
			if (g[l] == g[pr[l]])
			{
				nx[pr[l]] = nx[l];
				pr[nx[l]] = pr[l];
			}
		}

	printf("%lld\n", ans);
}

int main()
{
	T = read();
	while (T--)
	{
		init();
		solve();
	}
	return 0;
}
