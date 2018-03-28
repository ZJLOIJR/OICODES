#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 1e2 + 3, INF = 0x3f3f3f3f;
const int dir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {-1, 0}};

inline int read()
{
	int x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + (c ^ '0');
	return f ? -x : x;
}

int n, m, s, t, ans = 0, tot = 1;
int st[N * N], to[N * N * 10], nx[N * N * 10], len[N * N * 10];

inline void add(int u, int v, int w) { to[++tot] = v, nx[tot] = st[u], len[tot] = w, st[u] = tot; }
inline int id(int x, int y) { return (x - 1) * m + y; }
inline int check(int x, int y) { return x > 0 && x <= n && y > 0 && y <= m; }
inline int min(int a, int b) { return a < b ? a : b; }

int head, tail, dep[N * N], que[N * N * 40];
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
	s = 0, t = n * m + 1;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
		{
			int tmp = read();
			if (tmp == 1) add(s, id(i, j), INF), add(id(i, j), s, 0);
			if (tmp == 2) add(id(i, j), t, INF), add(t, id(i, j), 0);
			if (tmp == 0 || tmp == 1)
				for (int k = 0; k < 4; k++)
				{
					int dx = i + dir[k][0], dy = j + dir[k][1];
					if (check(dx, dy)) add(id(i, j), id(dx, dy), 1), add(id(dx, dy), id(i, j), 0);
				}
		}
	while (bfs())
	{
		int tmp;
		while (tmp = dinic(s, INF))
			ans += tmp;
	}
	printf("%d\n", ans);
	return 0;
}
