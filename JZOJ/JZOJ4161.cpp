#include <cstdio>
#include <cstring>
#include <cstdlib>
inline int min(int a, int b) { return a < b ? a : b; }
typedef long long ll;
const ll P = 1000000007LL;
const int N = 5e6 + 7;

int n, m, k;
int tot = 0, check[N], prime[N / 10], mu[N], summu[N];
ll ans = 0LL, sumg[N], kpow[N];

ll pow(ll a, ll b)
{
	ll ret = 1;
	while (b)
	{
		if (b & 1) ret = ret * a % P;
		a = a * a % P, b >>= 1; 
	}
	return ret;
}

ll solve(int n_, int m_)
{
	ll ret = 0;
	for (int l = 1, r; l <= n_; l = r + 1)
	{
		r = min(n_ / (n_ / l), m_ / (m_ / l));
		ret = (ret + (summu[r] - summu[l - 1] + P) * (n_ / l) % P * (m_ / l) % P) % P;
	}
	return ret;
}

int main()
{
	scanf("%d%d%d", &n, &m, &k);
	if (n > m) { int t = n; n = m, m = t; }
	mu[1] = summu[1] = sumg[1] = kpow[1] = 1;
	for (int i = 2; i <= n; i++)
	{
		if (!check[i]) prime[++tot] = i, mu[i] = -1, kpow[i] = pow(i, k);
		summu[i] = summu[i - 1] + mu[i], sumg[i] = sumg[i - 1] + kpow[i];
		for (int j = 1; j <= tot; j++)
		{
			if (prime[j] * i > n) break;
			check[prime[j] * i] = 1, kpow[prime[j] * i] = kpow[prime[j]] * kpow[i] % P;
			if (i % prime[j] == 0) { mu[prime[j] * i] = 0; break; }
			else mu[prime[j] * i] = -mu[i];
		}
	}
	for (int g = 1, r; g <= n; g = r + 1)
	{
		r = min(n / (n / g), m / (m / g));
		ans = (ans + (sumg[r] - sumg[g - 1] + P) * solve(n / g, m / g) % P) % P;
	}
	printf("%lld\n", ans);
	return 0;
}
