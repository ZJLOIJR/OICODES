#include <cstdio>
#include <cstring>
#include <cstdlib>
inline int min(int a, int b) { return a < b ? a : b; }

const int N = 5e4 - 7;

int T, a, b, c, d, k;
int tot = 0, check[N], prime[N / 10], mu[N], sum[N];

void init()
{
	mu[1] = sum[1] = 1;
	for (int i = 2; i <= N - 7; i++)
	{
		if (!check[i]) prime[++tot] = i, mu[i] = -1;
		sum[i] = sum[i - 1] + mu[i];
		for (int j = 1; j <= tot; j++)
		{
			if (prime[j] * i > N - 7) break;
			check[prime[j] * i] = 1;
			if (i % prime[j]) mu[prime[j] * i] = -mu[i];
			else { mu[prime[j] * i] = 0; break; }
		}
	}
}

int solve(int n, int m)
{
	n /= k, m /= k;
	if (n > m) n ^= m ^= n ^= m;
	int ret = 0;
	for (int d = 1, r; d <= n; d = r + 1)
	{
		r = min(n / (n / d), m / (m / d));
		ret += (sum[r] - sum[d - 1]) * (n / d) * (m / d);
	}
	return ret;
}

int main()
{
	init();
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d%d%d%d%d", &a, &b, &c, &d, &k);
		printf("%d\n", solve(b, d) - solve(b, c - 1) - solve(a - 1, d) + solve(a - 1, c - 1));
	}
	return 0;
}
