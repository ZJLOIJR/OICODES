#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

typedef long long ll;
const int N = 65537;

ll n, ans = 0, rt;

ll calcphi(ll x)
{
	ll ret = x, root = sqrt(x);
	for (ll i = 2; i <= root; i++)
		if (x % i == 0)
		{
			ret = ret / i * (i - 1);
			while (x % i == 0) x /= i;
		}
	if (x > 1) ret = ret / x * (x - 1);
	return ret;
}

int main()
{
	scanf("%lld", &n);
	rt = sqrt(n);
	for (int i = 1; i <= rt; i++)
		if (n % i == 0)
		{
			ans += calcphi(n / i) * i;
			if (n / i != i) ans += calcphi(i) * (n / i);
		}
	printf("%lld\n", ans);
	return 0;
}
