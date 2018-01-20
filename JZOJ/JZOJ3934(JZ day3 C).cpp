#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 10007, M = 200007;

int n, m, u, v, s, t;
int g[N];

struct Graph
{
	int tot, st[N], to[M], nx[M];
	void init() { tot = 0; }
	void add_edge(int u, int v)
	{ to[++tot] = v, nx[tot] = st[u], st[u] = tot; }
} graph1, graph2;

inline int read()
{
	int x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + c - '0';
	return f ? -x : x;
}

void init()
{
	graph1.init(), graph2.init();
	n = read(), m = read();
	for (int i = 1; i <= m; i++)
	{
		u = read(), v = read();
		graph1.add_edge(u, v);
		graph2.add_edge(v, u);
	}
	s = read(), t = read();
}

void dfs(int x)
{
	g[x] = 1;
	for (int i = graph2.st[x]; i; i = graph2.nx[i])
	{
		int v = graph2.to[i];
		if (!g[v]) dfs(v);
	}
}

int dis[N], vis[N], que[N * 20], head, tail;
void spfa()
{
	memset(dis, 0x3f, sizeof(dis));
	memset(vis, 0, sizeof(vis));
	head = 1, tail = 0;
	que[++tail] = s, vis[s] = 1, dis[s] = 0;
	while (head <= tail)
	{
		int u = que[head++], p = 1;
		vis[u] = 0;
		for (int i = graph1.st[u]; i; i = graph1.nx[i]) if (!g[graph1.to[i]]) { p = 0; break; }
		if (!p) continue;
		for (int i = graph1.st[u]; i; i = graph1.nx[i])
		{
			int v = graph1.to[i];
			if (dis[u] + 1 < dis[v])
			{
				dis[v] = dis[u] + 1;
				if (!vis[v])
					que[++tail] = v, vis[v] = 1;
			}
		}
	}
	if (dis[t] == 0x3f3f3f3f) printf("-1\n");
	else printf("%d\n", dis[t]);
}

int main()
{
	init();
	dfs(t);
	spfa();
	return 0;
}
