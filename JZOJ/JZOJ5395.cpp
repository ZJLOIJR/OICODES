#include <cstdio>
#include <cstring>
#include <cstdlib>

typedef long long ll;
const int K = 1e6 + 7;
const ll P = 998244353LL;

ll l, r, k, f[K], fac[K];

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
	n %= P;
	ll ret = 0, up = 1;
	for (int i = 1; i <= k + 2; i++) up = up * (n - i) % P;
	for (int i = 1; i <= k + 2; i++)
	{
		ret = (ret + ((k + 2 - i) & 1 ? -1 : 1) *
				pow(fac[i - 1] * fac[k + 2 - i] % P, P - 2, P) % P *
				pow(n - i, P - 2, P) % P *
				f[i] % P *
				up % P) % P;
	}
	return (ret + P) % P;
}

int main()
{
	freopen("count.in", "r", stdin);
	freopen("count.out", "w", stdout);

	scanf("%lld%lld%lld", &l, &r, &k);
	f[1] = 2;
	for (int i = 2; i <= k + 2; i++) f[i] = (f[i - 1] + pow(i, k, P)) % P;
	fac[0] = 1;
	for (int i = 1; i <= k + 2; i++) fac[i] = fac[i - 1] * i % P;
	printf("%lld\n", (solve(r) - solve(l - 1) + P) % P);

	fclose(stdin);
	fclose(stdout);
	return 0;
}
