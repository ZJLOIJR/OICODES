#include <cstdio>
#include <cstring>
#include <cstdlib>

typedef long long ll;
const ll P = 1e6 + 7;
int T;
ll n, m, k, p, ans, fac[P];

ll pow(ll a, ll b)
{
	ll ret = 1;
	while (b)
	{
		if (b & 1) ret = ret * a % p;
		a = a * a % p, b >>= 1;
	}
	return ret;
}

ll C(ll n, ll m)
{
	if (n < m) return 0;
	return fac[n] * pow(fac[m] * fac[n - m] % p, p - 2) % p;
}
ll Lucas(ll n, ll m)
{
	if (n < p && m < p) return C(n, m);
	return Lucas(n % p, m % p) * Lucas(n / p, m / p);
}

int main()
{
	freopen("luckye.in", "r", stdin);
	freopen("luckye.out", "w", stdout);

	scanf("%d", &T);
	fac[0] = 1;
	while (T--)
	{
		scanf("%lld%lld%lld%lld", &n, &m, &k, &p);
		for (int i = 1; i <= p; i++) fac[i] = fac[i - 1] * i % p;
		ans = 0;
		for (int i = 0, x; i <= n; i++)
		{
			if ((k - i) & 1) continue;
			ans = (ans + Lucas(n, i) * Lucas(n + m + ((k - i) / 2) - 1, n + m - 1) % p) % p;
		}
		printf("%lld\n", ans);
	}

	fclose(stdin);
	fclose(stdout);
	return 0;
}
