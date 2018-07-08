#include <cstdio>
#include <cstring>
#include <cstdlib>

typedef long long ll;
const int N = 1e5 + 7;

ll ans = 0;
int n, tot = 0, check[N], prime[N / 10], phi[N];

int main()
{
	scanf("%d", &n);
	if (n == 1) { printf("0\n"); return 0; }
	phi[1] = 1;
	for (int i = 2; i <= n; i++)
	{
		if (!check[i]) prime[++tot] = i, phi[i] = i - 1;
		for (int j = 1; j <= tot ;j++)
		{
			if (prime[j] * i > n) break;
			check[prime[j] * i] = 1;
			if (i % prime[j] == 0) phi[prime[j] * i] = prime[j] * phi[i];
			else phi[prime[j] * i] = (prime[j] - 1) * phi[i];
		}
	}
	for (int i = 1; i <= n - 1; i++) ans += phi[i];
	printf("%lld\n", ans * 2 + 1);
	return 0;
}
