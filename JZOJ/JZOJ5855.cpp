#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

typedef __int128 ll;

int t;
ll a, b, c, x, y, ans;

ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
void exgcd(ll a, ll b, ll &x, ll &y)
{
	if (!b) { x = 1, y = 0; return; }
	exgcd(b, a % b, y, x);
	y -= (a / b) * x;
}

int main()
{
	freopen("cake.in", "r", stdin);
	freopen("cake.out", "w", stdout);
	
	scanf("%d", &t);
	while (t--)
	{
		scanf("%lld%lld%lld", &a, &b, &c);
		ll g = gcd(a, b);
		if (c % g) printf("0\n");
		else
		{
			a /= g, b /= g, c /= g, g = 1;
			exgcd(a, b, x, y);
			x *= c, y *= c;
			if (x < 0) ans = y / a - (-x - 1) / b;
			else if (y < 0) ans = x / b - (-y - 1) / a;
			else ans = x / b + y / a + 1;
			printf("%lld\n", (long long)ans);
		}
	}

	fclose(stdin);
	fclose(stdout);
	return 0;
}
