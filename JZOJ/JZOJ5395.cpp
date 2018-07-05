#include <cstdio>
#include <cstring>
#include <cstdlib>

typedef long long ll;
const int K = 1e6 + 10;
const ll P = 998244353LL;

ll l, r, k, f[K], fac[K];

ll pow(ll a, ll b)
{
	a %= P;
	ll ret = 1;
	while (b)
	{
		if (b & 1) ret = ret * a % P;
		a = a * a % P, b >>= 1;
	}
	return ret;
}

ll pre[K], suf[K];
ll solve(ll n)
{
	if (n == 0) return 0;
	if (n <= k + 2) return ((f[n] + pow(2, k)) % P - 1 + P) % P;
	ll ret = 0, cur = 1, up, down;
	for (int i = 1; i <= k + 2; i++) cur = cur * (n - i) % P;
	for (int i = 1; i <= k + 2; i++)
	{
		int flag = ((k + 2 - i) & 1) ? -1 : 1;
		up = cur * pow(n - i, P - 2) % P, down = (flag * fac[i - 1] + P) % P * fac[k + 2 - i] % P;
		ret = (ret + f[i] * up % P * pow(down, P - 2) % P) % P;
	}
	return ((ret + pow(2, k)) % P - 1 + P) % P;
}

int main()
{
	freopen("count.in", "r", stdin);
	freopen("count.out", "w", stdout);

	scanf("%lld%lld%lld", &l, &r, &k);
	f[1] = 1;
	for (int i = 2; i <= k + 2; i++) f[i] = (f[i - 1] + pow(i, k)) % P;
	fac[0] = 1;
	for (int i = 1; i <= k + 2; i++) fac[i] = fac[i - 1] * i % P;
	printf("%lld\n", (solve(r) - solve(l - 1) + P) % P);

	fclose(stdin);
	fclose(stdout);
	return 0;
}
