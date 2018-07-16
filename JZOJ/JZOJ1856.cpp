#include <cstdio>
#include <cstring>
#include <cstdlib>

typedef long long ll;
const int N = 2e5 + 7;

int n, tot = 0, st[N], to[N << 1], nx[N << 1], siz[N];
ll ans = 0, sum = 0, len[N << 1];

inline void add(int u, int v, ll w) { to[++tot] = v, nx[tot] = st[u], len[tot] = w, st[u] = tot; }

void dfs(int u, int from)
{
	siz[u] = 1;
	for (int i = st[u]; i; i = nx[i])
		if (to[i] != from)
		{
			dfs(to[i], u), siz[u] += siz[to[i]];
			sum += siz[to[i]] * len[i];
		}
}
void getsum(int u, int from, ll now)
{
	ans += now;
	for (int i = st[u]; i; i = nx[i])
		if (to[i] != from)
			getsum(to[i], u, now - siz[to[i]] * len[i] + (siz[1] - siz[to[i]]) * len[i]);
}

int main()
{
	scanf("%d", &n);
	for (int i = 1, u, v, w; i < n; i++) scanf("%d%d%d", &u, &v, &w), add(u, v, w), add(v, u, w);
	dfs(1, 0);
	getsum(1, 0, sum);
	printf("%.2lf\n", ans * 1.0 / (n * 1LL * n - n));
	return 0;
}
