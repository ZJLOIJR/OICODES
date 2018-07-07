#include <cstdio>
#include <cstring>
#include <cstdlib>
inline int read()
{
	int x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + (c ^ '0');
	return f ? -x : x;
}

typedef long long ll;
const int N = 1e5 + 7;

int tot = 0, st[N], to[N << 1], nx[N << 1];
ll sum[N], a[N], len[N << 1], mi = 0;
int n, ans;

inline void add(int u, int v, int w) { to[++tot] = v, nx[tot] = st[u], len[tot] = (ll)w, st[u] = tot; }
void dfs(int u, int from)
{
	sum[u] = a[u];
	for (int i = st[u]; i; i = nx[i]) if (to[i] != from) dfs(to[i], u), sum[u] += sum[to[i]], mi += sum[to[i]] * len[i];
}
void getans(int u, int from, ll ret)
{
	if (ret < mi) mi = ret, ans = u;
	for (int i = st[u]; i; i = nx[i])
		if (to[i] != from)
			getans(to[i], u, ret - sum[to[i]] * len[i] + (sum[1] - sum[to[i]]) * len[i]);
}

int main()
{
	n = read();
	for (int i = 1; i <= n; i++) a[i] = (ll)read();
	for (int i = 1, u, v, w; i < n; i++) u = read(), v = read(), w = read(), add(u, v, w), add(v, u, w);
	dfs(1, 0);
	ans = 1;
	getans(1, 0, mi);
	printf("%d\n%lld\n", ans, mi);
	return 0;
}
