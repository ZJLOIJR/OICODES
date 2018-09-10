#include <cstdio>
#include <cstring>
#include <cstdlib>

inline int min(int a, int b) { return a < b ? a : b; }
const int N = 2e2 + 7, M = N * N, INF = 0x3f3f3f3f;

int n, m;
int f[N][N];

int S, T;
int tot = 1, st[N], nx[M], to[M], len[M];
void add(int u, int v)
{
	to[++tot] = v, nx[tot] = st[u], len[tot] = 1, st[u] = tot;
	to[++tot] = u, nx[tot] = st[v], len[tot] = 0, st[v] = tot;
}

int head, tail, que[N * 20], dep[N];
int bfs()
{
	head = 1, que[tail = 1] = S, dep[S] = 1;
	while (head <= tail)
	{
		int u = que[head++];
		for (int i = st[u]; i; i = nx[i])
			if (len[i] > 0 && !dep[to[i]])
				dep[to[i]] = dep[u] + 1, que[++tail] = to[i];
	}
	return dep[T];
}

int dinic(int u, int flow)
{
	int rest = flow, tmp;
	for (int i = st[u]; i; i = nx[i])
		if (len[i] > 0 && dep[u] + 1 == dep[to[i]])
		{
			tmp = dinic(to[i], min(rest, len[i]));
			if (!tmp) dep[to[i]] = 0;
			rest -= tmp, len[i] -= tmp, len[i ^ 1] += tmp;
		}
	return flow - rest;
}

int main()
{
	//freopen("dance.in", "r", stdin);
	//freopen("dance.out", "w", stdout);

	scanf("%d%d", &n, &m);
	for (int i = 1, x, y; i <= m; i++) scanf("%d%d", &x, &y), f[x][y] = 1;
	for (int i = 1; i <= n; i++) f[i][i] = 1;
	for (int k = 1; k <= n; k++)
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				f[i][j] |= (f[i][k] & f[k][j]);
	S = 0, T = 2 * n + 1;
	for (int i = 1; i <= n; i++) add(S, i), add(i + n, T), add(i, i + n);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			if (i != j && f[i][j])
				add(i, j + n);
	int ret = 0;
	while (bfs())
		while (int flow = dinic(S, INF))
			ret += flow;
	printf("%d\n", n - ret);

	fclose(stdin);
	fclose(stdout);
	return 0;
}
