#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 4e5 + 3;

int n, tot = 0, ans = 0, check[N], prime[N / 10], phi[N];

int main()
{
	scanf("%d", &n);
	phi[1] = 1;
	for (int i = 2; i <= n; i++)
	{
		if (!check[i]) prime[++tot] = i, phi[i] = i - 1;
		for (int j = 1; j <= tot; j++)
		{
			if (prime[j] * i > n) break;
			check[prime[j] * i] = 1;
			if (i % prime[j] == 0) { phi[prime[j] * i] = phi[i] * prime[j]; break; }
			else phi[prime[j] * i] = (prime[j] - 1) * phi[i];
		}
	}
	for (int i = 1; i <= n - 1; i++) ans += phi[i];
	printf("%d\n", 2 * ans + 1);
	return 0;
}
