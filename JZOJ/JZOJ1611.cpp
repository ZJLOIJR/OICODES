#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 1e2 + 3, INF = 0x3f3f3f3f;

int n, f, d, s, t, tot = 1;
int st[N * 10], to[N * N * 20], nx[N * N * 20], len[N * N * 20];

inline int read()
{
	int x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + (c ^ '0');
	return f ? -x : x;
}
inline void add(int u, int v, int w) { to[++tot] = v, nx[tot] = st[u], len[tot] = w, st[u] = tot; }
inline int min(int a, int b) { return a < b ? a : b; }

int head, tail, dep[N * 10], que[N * N * 20];
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
	n = read(), f = read(), d = read();
	s = 0, t = f + 2 * n + d + 1;
	for (int i = 1; i <= f; i++) add(s, i, 1), add(i, s, 0);
	for (int i = 1; i <= d; i++) add(i + f + 2 * n, t, 1), add(t, i + f + 2 * n, 0);
	for (int i = 1; i <= n; i++)
	{
		add(i + f, i + f + n, 1), add(i + f + n, i + f, 0);
		int F = read(), D = read(), tmp;
		for (int j = 1; j <= F; j++)
			tmp = read(), add(tmp, i + f, 1), add(i + f, tmp, 0);
		for (int j = 1; j <= D; j++)
			tmp = read(), add(i + f + n, tmp + f + 2 * n, 1), add(tmp + f + 2 * n, i + f + n, 0);
	}
	int ans = 0, tmp;
	while (bfs())
		while (tmp = dinic(s, INF))
			ans += tmp;
	printf("%d\n", ans);
	return 0;
}
