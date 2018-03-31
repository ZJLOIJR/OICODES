#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

typedef long long ll;
const int N = 1e6 + 3;

int T, n, tot = 0;
int prime[75003], check[N], phi[N];
ll sum[N], f[N];

int main()
{
	scanf("%d", &T);
	phi[1] = 1;
	for (int i = 2; i <= N - 3; i++)
	{
		if (!check[i]) phi[i] = i - 1, prime[++tot] = i;
		for (int j = 1; j <= tot; j++)
		{
			if (i * prime[j] > N - 3) break;
			check[i * prime[j]] = 1;
			if (i % prime[j] == 0) phi[i * prime[j]] = phi[i] * prime[j];
			else phi[i * prime[j]] = phi[i] * (prime[j] - 1);
		}
	}
	for (int i = 1; i <= N - 3; i++)
		for (int j = i + i; j <= N - 3; j += i)
			f[j] += 1LL * i * phi[j / i];
	for (int i = 2; i <= N - 3; i++) sum[i] = sum[i - 1] + f[i];
	while (T--)
	{
		scanf("%d", &n);
		printf("%lld\n", sum[n]);
	}
	return 0;
}
