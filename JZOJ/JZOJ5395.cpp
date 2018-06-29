#include <cstdio>
#include <cstring>
#include <cstdlib>

typedef long long ll;
const int K = 1e6 + 7;
const ll P = 998244353;

ll l, r, k, f[K], fac[K], inv[K];

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

ll solve(ll n)
{
	if (n <= k + 2) return f[n];
	ll ret = 0;
	for (int i = 1; i <= k + 2; i++)
	{
		ll up
		ret = (ret + f[i] *  % P) % P;
	}
}

int main()
{
	//freopen("count.in", "r", stdin);
	//freopen("count.out", "w", stdout);

	scanf("%lld%lld%lld", &l, &r, &k);
	f[1] = 2, fac[0] = fac[1] = inv[0] = inv[1] = 1;
	for (int i = 2; i <= k + 2; i++)
	{
		f[i] = (f[i - 1] + pow(i, k, P)) % P;
		fac[i] =  fac[i - 1] * i % P, inv[i] = pow(fac[i], P - 2, P);
	}
	printf("%lld\n", (solve(r) - solve(l - 1) + P) % P);

	fclose(stdin);
	fclose(stdout);
	return 0;
}
