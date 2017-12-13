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
	ll tmp;

	while (y != 0)
	{
		tmp = y;
		y = x % y;
		x = tmp;
	}

	return x;
}

inline ll read()
{
	ll sum = 0, f = 1;

	char c = getchar();
	while (c > '9' || c < '0')
	{
		if (c == '-')
			f = -1;
		c = getchar();
	}

	while (c >= '0' && c <= '9')
	{
		sum = (sum << 1) + (sum << 3) + c - '0';
		c = getchar();
	}
	
	return sum * f;
}

void init()
{
	n = (int)read();

	for (register int i = 1; i <= n; i++)
		a[i] = read();

	for (register int i = 1; i <= n; i++)
		nx[i] = i + 1, pr[i] = i - 1, g[i] = a[i];
}

void solve()
{
	ll ans = 0;
	for (register int r = 1; r <= n; r++)
		for (register int l = 1; l <= r; l = nx[l])
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
	T = (int)read();
	
	while (T--)
	{
		init();
		solve();
	}

	return 0;
}
