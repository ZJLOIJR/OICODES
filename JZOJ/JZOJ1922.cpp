#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 5e2 + 3, INF = 0x3f3f3f3f;

int n, m, s, t, u, v, tot = 1, ans = 0;
int st[N * 20], to[N * 20], nx[N * 20], len[N * 20];

inline int read()
{
	int x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 3) + (x << 1) + (c ^ '0');
	return f ? -x : x;
}
inline void add(int u, int v, int w)
{
	to[++tot] = v, nx[tot] = st[u], len[tot] = w, st[u] = tot;
	to[++tot] = u, nx[tot] = st[v], len[tot] = 0, st[v] = tot;
}
inline int min(int a, int b) { return a < b ? a : b; }

int head, tail, dep[N * 20], que[N * 20];
int bfs()
{
	memset(dep, 0, sizeof(dep));
	head = 1, tail = 0, dep[s] = 1, que[++tail] = s;
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
	int ret = flow, tmp;
	for (int i = st[u]; i; i = nx[i])
		if (dep[to[i]] == dep[u] + 1 && len[i] > 0)
		{
			tmp = dinic(to[i], min(ret, len[i]));
			if (!tmp) dep[to[i]] = 0;
			len[i] -= tmp;
			len[i ^ 1] += tmp;
			ret -= tmp;
		}
	return flow - ret;
}

int main()
{
	n = read(), m = read();
	s = 0, t = n * 2 + 1;
	for (int i = 1; i <= m; i++) u = read(), v = read(), add(u, v + n, INF);
	for (int i = 1; i <= n; i++) add(s, i, 1), add(i + n, t, 1);
	while (bfs())
	{
		int tmp;
		while (tmp = dinic(s, INF)) ans += tmp;
	}
	printf("%d\n", ans);
	return 0;
}
