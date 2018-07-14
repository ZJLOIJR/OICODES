#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 1e4 + 7, M = 5e4 + 7;

inline int min(int a, int b) { return a < b ? a : b; }

int n, m, cnt, ans = 0;
int tot = 0, st[N], to[M], nx[M], col[N];
int val[N], rd[N], sum[N];

inline void add(int u, int v) { to[++tot] = v, nx[tot] = st[u], st[u] = tot; }

int now, dfn[N], low[N], sta[N], vis[N], top;
void tarjan(int u)
{
	dfn[u] = low[u] = ++now, sta[++top] = u, vis[u] = 1;
	for (int i = st[u]; i; i = nx[i])
	{
		int v = to[i];
		if (!dfn[v]) tarjan(v), low[u] = min(low[u], low[v]);
		else if (vis[v]) low[u] = min(low[u], dfn[v]);
	}
	if (low[u] == dfn[u])
	{
		col[u] = ++cnt;
		while (top && sta[top] != u) col[sta[top]] = cnt, vis[sta[top--]] = 0;
		vis[sta[top--]] = 0;
	}
}

int tote = 0, begin[N], getto[M], next[M];
inline void add_edge(int u, int v) { getto[++tote] = v, next[tote] = begin[u], begin[u] = tote; }

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1, u, v; i <= m; i++) scanf("%d%d", &u, &v), add(u, v);
	for (int i = 1; i <= n; i++) if (!dfn[i]) tarjan(i);
	for (int u = 1; u <= n; u++)
	{
		for (int i = st[u]; i; i = nx[i])
			if (col[u] != col[to[i]])
				add_edge(col[u], col[to[i]]), rd[col[to[i]]]++;
		val[col[u]]++, sum[col[u]]++;
	}
	top = 0;
	for (int i = 1; i <= cnt; i++) if (!rd[i]) sta[++top] = i;
	while (top)
	{
		int u = sta[top--];
		for (int i = begin[u]; i; i = next[i])
		{
			sum[getto[i]] += sum[u];
			rd[getto[i]]--;
			if (!rd[getto[i]]) sta[++top] = getto[i];
		}
	}
	for (int i = 1; i <= cnt; i++) if (sum[i] == n) ans += val[i];
	printf("%d\n", ans);
	return 0;
}
