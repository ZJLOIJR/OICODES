#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 1e5 + 7;

int n, q, sum[N], a[N];
int tot, prime[N / 10], check[N], mu[N];

int main()
{
	scanf("%d%d", &n, &q);
	for (int i = 1; i <= n; i++) scanf("%d", a + i);
	for (int i = 1; i <= n; i++)
		for (int j = i; j <= n; j += i)
			sum[i] += a[j];
	mu[1] = 1;
	for (int i = 2; i <= n; i++)
	{
		if (!check[i]) prime[++tot] = i, mu[i] = -1;
		for (int j = 1; j <= tot; j++)
		{
			if (prime[j] * i > n) break;
			check[prime[j] * i] = 1;
			if (i % prime[j]) mu[prime[j] * i] = -mu[i];
			else { mu[prime[j] * i] = 0; break; }
		}
	}
	while (q--)
	{
		int opt, x, b, rt;
		scanf("%d", &opt);
		if (opt == 1)
		{
			scanf("%d%d", &x, &b);
			rt = sqrt(x);
			for (int i = 1; i <= rt; i++)
				if (x % i == 0)
				{
					sum[i] -= a[x], sum[i] += b;
					if (x / i != i) sum[x / i] -= a[x], sum[x / i] += b;
				}
			a[x] = b;
		}
		else
		{
			scanf("%d", &x);
			int ans = 0;
			rt = sqrt(x);
			for (int i = 1; i <= rt; i++)
				if (x % i == 0)
				{
					ans += mu[i] * sum[i];
					if (x / i != i) ans += mu[x / i] * sum[x / i];
				}
			printf("%d\n", ans);
		}
	}
	return 0;
}
