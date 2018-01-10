#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 2007, M = 200007;

int n, m, u, v, w, a, b, tot = 0;
int st[N], to[M], nx[M], len[M];
int que[N * 20], vis[N], head, tail;
double dis[N];

inline int read()
{
	int x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + c - '0';
	return f ? -x : x;
}

void add(int u, int v, int l) { to[++tot] = v, len[tot] = l, nx[tot] = st[u], st[u] = tot; }

void init()
{
	n = read(), m = read();
	for (int i = 1; i <= m; i++)
		u = read(), v = read(), w = read(), add(u, v, w), add(v, u, w);
	for (int i = 1; i <= n; i++)
		dis[i] = 0;
}

void solve()
{
	a = read(), b = read();
	memset(vis, 0, sizeof(vis));
	head = 1, tail = 0;
	que[++tail] = a, vis[a] = 1, dis[a] = 1;
	while (head <= tail)
	{
		u = que[head++], vis[u] = 0;
		for (int i = st[u]; i; i = nx[i])
		{
			v = to[i];
			if (dis[u] * (1.0 - len[i] / 100.0) > dis[v])
			{
				dis[v] = dis[u] * (1.0 - len[i] / 100.0);
				if (!vis[v])
					vis[v] = 1, que[++tail] = v;
			}
		}
	}
	printf("%.8lf\n", 100.0 / dis[b]);
}

int main()
{
	init();
	solve();
	return 0;
}
