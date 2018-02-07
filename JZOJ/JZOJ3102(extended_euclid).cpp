#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

typedef long long ll;

ll a, b, x, y;

ll ext_gcd(ll a, ll b, ll& x, ll& y)
{
	if (!b)
	{
		x = 1, y = 0;
		return a;
	}
	ll ret = ext_gcd(b, a % b, y, x);
	y -= a / b * x;
	return ret;
}

int main()
{
	scanf("%lld%lld", &a, &b, &x, &y);
	ext_gcd(a, b, x, y);
	printf("%lld\n", (x + b) % b);
	return 0;
}
