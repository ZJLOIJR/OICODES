#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
inline int min(int a, int b) { return a < b ? a : b; }

typedef long long ll;
const int N = 1e7 + 7;
const ll P = 20101009;

int n, m, tot = 0, check[N], prime[N / 10], mu[N], sum[N];
ll ans = 0;

ll solve(int n, int m)
{
	ll ret = 0;
	for (int l = 1, r; l <= n; l = r + 1)
	{
		r = min(n / (n / l), m / (m / l));
		ret = (ret + (sum[r] - sum[l - 1] + P) % P * (1LL + (n / l)) * (n / l) / 2 % P * (1LL + (m / l)) * (m / l) / 2 % P) % P;
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
		sum[i] = (sum[i - 1] + mu[i] * i % P * i % P) % P;
		for (int j = 1; j <= tot; j++)
		{
			if (prime[j] * i > n) break;
			check[prime[j] * i] = 1;
			if (i % prime[j]) mu[prime[j] * i] = -mu[i];
			else { mu[prime[j] * i] = 0; break; }
		}
	}
	for (int g = 1, r; g <= n; g = r + 1)
	{
		r = min(n / (n / g), m / (m / g));
		ans = (ans + (r - g + 1) * 1LL * (r + g) / 2 % P * solve(n / g, m / g) % P) % P;
	}
	printf("%lld\n", ans);
	return 0;
}
