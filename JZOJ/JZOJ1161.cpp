#include <cstdio>
#include <cstring>
#include <cstdlib>

typedef long long ll;
const int N = 1e3 + 7;
const ll P = 10000;

int n;
ll ans1, ans2, ret = 1, p[N], e[N], f[N];

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
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%lld%lld", p + i, e + i);
		ret = ret * pow(p[i], e[i], P) % P;
	}
	f[0] = 1;
	ll tmp = (p[1] == 2) ? 2 : 1;
	for (int i = tmp; i <= n; i++)
		for (int j = i; j >= 1; j--)
			f[j] = (f[j] + f[j - 1] * (p[i] - 1) % P) % P;
	ans1 = ans2 = 0;
	for (int i = 1; i <= n; i++)
		if (i & 1) ans2 = (ans2 + f[i]) % P;
		else ans1 = (ans1 + f[i]) % P;
	printf("%lld\n%lld\n%lld\n", ans1, ans2, (ret - ans1 + P - ans2 + P - 1 + P) % P);
	return 0;
}
