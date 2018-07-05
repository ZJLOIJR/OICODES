#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

typedef long long ll;
const ll P1 = 2000000011LL, P2 = 2000000063LL;

ll a, b, ans, temp, rt;

ll pow(ll a, ll b, ll mo)
{
	a %= mo;
	ll ret = 1;
	while (b)
	{
		if (b & 1) ret = ret * a % mo;
		a = a * a % mo, b >>= 1;
	}
	return ret;
}

int main()
{
	scanf("%lld%lld", &a, &b);
	if (b == 0) { printf("1 1\n"); return 0; }
	temp = a, ans = a, rt = sqrt(a);
	for (ll i = 2; i <= rt; i++)
		if (a % i == 0)
		{
			ans = ans / i * (i - 1);
			while (a % i == 0) a /= i;
		}
	if (a > 1) ans = ans / a * (a - 1);
	a = temp;
	printf("%lld %lld\n", ans % P1 * pow(a, b - 1, P1) % P1, ans % P2 * pow(a, b - 1, P2) % P2);
	return 0;
}
