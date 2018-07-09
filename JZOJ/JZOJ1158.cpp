#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;

typedef long long ll;
const int N = 20;

int n, mx, c[N], p[N], l[N];

ll exgcd(ll a, ll b, ll &x, ll &y)
{
	if (!b)
	{
		x = 1, y = 0;
		return a;
	}
	ll ret = exgcd(b, a % b, y, x);
	y -= a / b * x;
	return ret;
}

int check(ll m)
{
	for (int i = 1; i <= n - 1; i++)
		for (int j = i + 1; j <= n; j++)
		{
			ll a = p[i] - p[j], b = -m, C = c[j] - c[i], x, y, g = exgcd(a, b, x, y);
			if (C % g == 0)
			{
				x = x * C / g;
				x %= (b / g);
				ll t = 0;
				while (x + t * abs(b / g) < 0) t++;
				x = x + t * abs(b / g);
				if (x <= l[i] && x <= l[j]) return 0;
			}
		}
	return 1;
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d%d%d", c + i, p + i, l + i);
		if (c[i] > mx) mx = c[i];
		c[i]--;
	}
	for (int i = mx; i <= 1000000; i++)
		if (check(i))
		{
			printf("%d\n", i);
			return 0;
		}
	return 0;
}
