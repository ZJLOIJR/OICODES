#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
inline int min(int a, int b) { return a < b ? a : b; }

typedef long long ll;
const int N = 1e5 + 7;

int n, m, tot = 0, check[N], prime[N / 10], mu[N], sum[N];

ll solve(int n, int m)
{
	ll ret = 0;
	for (int d = 1, r; d <= n; d = r + 1)
	{
		r = min(n / (n / d), m / (m / d));
		ret += (sum[r] - sum[d - 1]) * 1LL * (n / d) * (m / d);
	}
	return ret;
}

int main()
{
	scanf("%d%d", &n, &m);
	if (n > m) n ^= m ^= n ^= m;
	mu[1] = sum[1] = 1;
	for (int i = 2; i <= n; i++)
	{
		if (!check[i]) prime[++tot] = i, mu[i] = -1;
		sum[i] = sum[i - 1] + mu[i];
		for (int j = 1; j <= tot; j++)
		{
			if (prime[j] * i > n) break;
			check[prime[j] * i] = 1;
			if (i % prime[j]) mu[prime[j] * i] = -mu[i];
			else { mu[prime[j] * i] = 0; break; }
		}
	}
	ll ans = 0;
	for (int g = 1, r; g <= n; g = r + 1)
	{
		r = min(n / (n / g), m / (m / g));
		ans += (r - g + 1LL) * (g + r) / 2 * solve(n / g, m / g);
	}
	printf("%lld\n", 2 * ans - (ll)n * (ll)m);
	return 0;
}
