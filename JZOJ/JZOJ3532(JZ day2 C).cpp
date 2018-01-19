#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

typedef long long ll;

ll n, m, k, x, ans;

ll power(ll a, ll b)
{
	ll ret = 1;
	while (b)
	{
		if (b & 1)
			ret = ret * a % n;
		a = a * a % n;
		b >>= 1;
	}
	return ret;
}

int main()
{
	scanf("%lld%lld%lld%lld", &n, &m, &k, &x);
	ans = (x + power(10, k) * m % n) % n;
	printf("%lld\n", ans);
	return 0;
}
