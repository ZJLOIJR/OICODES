#include <cstdio>
#include <cstring>
#include <cstdlib>

typedef long long ll;
const int N = 1e6 + 7;

int n, m, ans;
int tot, check[N], prime[N / 10];

void dfs(int now, ll mtp)
{
	if (now > tot) { ans++; return; }
	if (mtp * prime[now] * prime[now] > n)
	{
		int l = now, r = tot, ret = -1;
		while (l <= r)
		{
			int mid = l + r >> 1;
			if (mtp * prime[mid] <= n) l = mid + 1, ret = mid;
			else r = mid - 1;
		}
		if (ret != -1) ans += ret - now + 1;
		ans++;
		return;
	}
	dfs(now + 1, mtp);
	ll s = prime[now];
	while (1)
	{
		if (mtp * s <= n) dfs(now + 1, mtp * s);
		else break;
		s *= 1LL * prime[now] * prime[now];
	}
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 2; i <= m; i++)
	{
		if (!check[i]) prime[++tot] = i;
		for (int j = 1; j <= tot; j++)
		{
			if (i * prime[j] > m) break;
			check[i * prime[j]] = 1;
			if (i % prime[j] == 0) break;
		}
	}
	dfs(1, 1);
	printf("%d\n", ans);
	return 0;
}
