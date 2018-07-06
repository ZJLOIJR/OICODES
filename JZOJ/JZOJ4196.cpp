#include <cstdio>
#include <cstring>
#include <cstdlib>

typedef long long ll;
const int N = 17;
const ll P = 1e9 + 7;

ll m, ans = 0, f[N][N];
int n, full, a[N], ok[1 << N], cnt[1 << N];

int check(int s)
{
	for (int i = 0; i < n - 1; i++)
		if ((1 << i) & s)
			for (int j = i + 1; j < n; j++)
				if ((1 << j) & s)
					if (a[i] == a[j]) return 1;
	return 0;
}
int count(int s)
{
	int ret = 0;
	while (s) ret += (s & 1), s >>= 1;
	return ret;
}

int main()
{
	freopen("bipartite.in", "r", stdin);
	freopen("bipartite.out", "w", stdout);

	scanf("%d%lld", &n, &m);
	if (n == 1) { printf("%lld\n", m - 1); return 0; }
	for (int i = 0; i < n; i++) scanf("%d", a + i);
	full = (1 << n) - 1;
	for (int s = 1; s <= full; s++) ok[s] = check(s), cnt[s] = count(s);
	for (int i = 1; i <= n; i++)
		for (int j = i; j <= n; j++)
		{
			f[i][j] = 1;
			for (int k = i; k <= j; k++) f[i][j] = f[i][j] * (m - k + 1) % P;
		}
	for (int s = 1; s <= full; s++)
	{
		ll fs = f[1][cnt[s]];
		if (cnt[s] > m) continue;
		for (int s1 = s; s1; s1 = ((s1 - 1) & s))
		{
			if (ok[s1]) continue;
			int flag = (cnt[s1] & 1) ? -1 : 1;
			fs = (fs + flag * f[cnt[s1] + 1][cnt[s]] + P) % P;
		}
		ans = (ans + fs * s % P) % P;
	}
	printf("%lld\n", ans);

	fclose(stdin);
	fclose(stdout);
	return 0;
}
