#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 407, INF = 0x3f3f3f3f;
inline int min(int a, int b) { return a < b ? a : b; }

int n, m, S, T;
int tot = 1, st[N], to[N * N * 5], nx[N * N * 5], len[N * N * 5];

inline void add(int u, int v, int w)
{
	to[++tot] = v, nx[tot] = st[u], len[tot] = w, st[u] = tot;
	to[++tot] = u, nx[tot] = st[v], len[tot] = 0, st[v] = tot;
}

int head, tail, que[N], dep[N];
int bfs()
{
	head = 1, tail = 0;
	memset(dep, 0, sizeof(dep));
	que[++tail] = S, dep[S] = 1;
	while (head <= tail)
	{
		int u = que[head++];
		for (int i = st[u]; i; i = nx[i])
			if (!dep[to[i]] && len[i] > 0)
				dep[to[i]] = dep[u] + 1, que[++tail] = to[i];
	}
	return dep[T];
}
int dinic(int u, int flow)
{
	if (u == T) return flow;
	int ret = flow;
	for (int i = st[u]; i; i = nx[i])
		if (dep[to[i]] == dep[u] + 1 && len[i] > 0)
		{
			int tmp = dinic(to[i], min(ret, len[i]));
			if (!tmp) dep[to[i]] = 0;
			len[i] -= tmp, len[i ^ 1] += tmp, ret -= tmp;
		}
	return flow - ret;
}

int x[N];
int main()
{
	scanf("%d", &n);
	S = 0, T = 2 * n + 1;
	for (int i = 1; i <= n; i++) add(S, i, 1);
	for (int i = 1; i <= n; i++) add(i + n, T, 1);
	for (int i = 1; i <= n; i++) scanf("%d%*d", x + i);
	scanf("%d", &m);
	for (int i = 1, u, v; i <= m; i++)
	{
		scanf("%d%d", &u, &v);
		if (x[u] < x[v]) add(u, v + n, 1);
		else if (x[v] < x[u]) add(v, u + n, 1);
	}
	int ans = 0;
	while (bfs())
		while (int flow = dinic(S, INF))
			ans += flow;
	printf("%d\n", n - ans);
	return 0;
}
