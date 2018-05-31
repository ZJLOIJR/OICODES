#include <cstdio>
#include <cstring>
#include <cstdlib>
inline int min(int a, int b) { return a < b ? a : b; }

typedef long long ll;
const int N = 5e4 + 7;

int T, n, m;
int tot = 0, check[N], d[N], prime[N / 10], mu[N], sum[N];
ll ans;

int main()
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
	for (int i = 1; i <= N - 7; i++) for (int j = i; j <= N - 7; j += i) d[j]++;
	for (int i = 1; i <= N - 7; i++) d[i] += d[i - 1];
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d%d", &n, &m);
		if (n > m) n ^= m ^= n ^= m;
		ans = 0;
		for (int l = 1, r; l <= n; l = r + 1)
		{
			r = min(n / (n / l), m / (m / l));
			ans += (sum[r] - sum[l - 1]) * 1LL * d[n / l] * d[m / l];
		}
		printf("%lld\n", ans);
	}
	return 0;
}
