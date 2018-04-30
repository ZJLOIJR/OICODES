#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

typedef long long ll;
const int N = 2e2 + 3, INF = 0x3f3f3f3f;

int n, m, s, t, sum;
int ths[N], mx[N];
int tot, st[N * 2], to[N * N * 10], nx[N * N * 10], len[N * N * 10];
ll l, r, mid, ans = -1, w, dis[N][N];

inline int min(int a, int b) { return a < b ? a : b; }
inline void add(int u, int v, int w)
{
	to[++tot] = v, nx[tot] = st[u], len[tot] = w, st[u] = tot;
	to[++tot] = u, nx[tot] = st[v], len[tot] = 0, st[v] = tot;
}

void init()
{
	memset(dis, 0x3f, sizeof(dis));
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%d%d", ths + i, mx + i), sum += ths[i], dis[i][i] = 0LL;
	for (int i = 1, u, v; i <= m; i++)
	{
		scanf("%d%d%lld", &u, &v, &w);
		dis[u][v] = dis[v][u] = w, r += w;
	}
	for (int k = 1; k <= n; k++)
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
}

int head, tail, que[N * N * 50], dep[N * 2];
int bfs()
{
	memset(dep, 0, sizeof(dep));
	head = 1, dep[s] = 1, que[tail = 1] = s;
	while (head <= tail)
	{
		int u = que[head++];
		for (int i = st[u]; i; i = nx[i])
			if (!dep[to[i]] && len[i] > 0)
			{
				dep[to[i]] = dep[u] + 1, que[++tail] = to[i];
				if (to[i] == t) return 1;
			}
	}
	return 0;
}

int dinic(int u, int flow)
{
	if (u == t) return flow;
	int rest = flow, tmp;
	for (int i = st[u]; i; i = nx[i])
		if (dep[to[i]] == dep[u] + 1 && len[i] > 0)
		{
			tmp = dinic(to[i], min(rest, len[i]));
			if (!tmp) dep[to[i]] = 0;
			len[i] -= tmp, len[i ^ 1] += tmp, rest -= tmp;
		}
	return flow - rest;
}

void makegraph()
{
	tot = 1;
	memset(st, 0, sizeof(st));
	memset(nx, 0, sizeof(nx));
	for (int i = 1; i <= n; i++) add(s, i, ths[i]), add(i + n, t, mx[i]);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			if (dis[i][j] <= mid) add(i, j + n, INF);
}

int check()
{
	int total = 0;
	s = 0, t = n * 2 + 1;
	makegraph();
	while (bfs())
		while (int f = dinic(s, INF))
			total += f;
	return total == sum;
}

void solve()
{
	l = 0;
	while (l <= r)
	{
		mid = l + r >> 1;
		if (check()) r = mid - 1, ans = mid;
		else l = mid + 1;
	}
	printf("%lld\n", ans);
}

int main()
{
	init();
	solve();
	return 0;
}
