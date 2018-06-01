#include <cstdio>

typedef long long ll;
const ll P = 1e9 + 7;

ll a, b;

ll quickpow(ll a, ll b, ll mo)
{
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
	freopen("dream.in", "r", stdin);
	freopen("dream.out", "w", stdout);

	scanf("%lld%lld", &a, &b);
	printf("%lld\n", quickpow(a, quickpow(a, b - 1, P - 1), P));

	fclose(stdin);
	fclose(stdout);
	return 0;
}
