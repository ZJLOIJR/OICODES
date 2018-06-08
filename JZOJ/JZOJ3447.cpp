#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 37;

int n, m, ans = 0, w[N][N];
int S, T, tot = 1, st[N * 4], to[N * N * 16], nx[N * N * 16], len[N * N * 16], cost[N * N * 16];

inline void add(int u, int v, int l, int c)
{
	to[++tot] = v, nx[tot] = st[u], st[u] = tot, len[tot] = l, cost[tot] = c;
	to[++tot] = u, nx[tot] = st[v], st[v] = tot, len[tot] = 0, cost[tot] = -c;
}
inline int min(int a, int b) { return a < b ? a : b; }

int head, tail, que[N * 80], vis[N * 4], dis[N * 4], minflow[N * 4], pre[N * 4];
int bfs()
{
	head = 1, tail = 0;
	memset(dis, 0, sizeof(dis));
	memset(vis, 0, sizeof(vis));
	memset(minflow, 0, sizeof(minflow));
	memset(pre, 0, sizeof(pre));
	que[++tail] = S, dis[S] = 0, vis[S] = 1, minflow[S] = 0x3f3f3f3f;
	while (head <= tail)
	{
		int u = que[head++];
		vis[u] = 0;
		for (int i = st[u]; i; i = nx[i])
		{
			int v = to[i];
			if (min(minflow[u], len[i]) > minflow[v] || (min(minflow[u], len[i]) == minflow[v] && dis[u] + cost[i] > dis[v]))
			{
				minflow[v] = min(minflow[u], len[i]), dis[v] = dis[u] + cost[i], pre[v] = i;
				if (!vis[v]) que[++tail] = v, vis[v] = 1;
			}
		}
	}
	return minflow[T] && dis[T] > 0;
}

void upd()
{
	int now = T;
	while (now != S) len[pre[now]] -= minflow[T], len[pre[now] ^ 1] += minflow[T], now = to[pre[now] ^ 1];
	ans += minflow[T] * dis[T];
}

int main()
{
	freopen("pick.in", "r", stdin);
	freopen("pick.out", "w", stdout);
	
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			scanf("%d", &w[i][j]);
	S = 1, T = n + m + 2;
	for (int i = 1; i <= n; i++) add(S, i + 1, 2, 0);
	for (int i = 1; i <= m; i++) add(i + n + 1, T, 2, 0);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			add(i + 1, j + n + 1, 1, w[i][j]);
	while (bfs()) upd();
	printf("%d\n", ans);

	fclose(stdin);
	fclose(stdout);
	return 0;
}
