#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 1e7 + 7;

int q, l, r, tot = 0, check[N], prime[N / 10], mark[N], sum[N];

int main()
{
	for (int i = 2; i <= N - 7; i++)
	{
		if (!check[i]) prime[++tot] = i, mark[i] = 1;
		sum[i] = sum[i - 1] + mark[i];
		for (int j = 1; j <= tot; j++)
		{
			if (prime[j] * i > N - 7) break;
			check[prime[j] * i] = 1;
			if (!check[i]) mark[prime[j] * i] = 1;
			if (i % prime[j] == 0) break;
		}
	}
	scanf("%d", &q);
	while (q--)
	{
		scanf("%d%d", &l, &r);
		printf("%d\n", sum[r] - sum[l - 1]);
	}
	return 0;
}
