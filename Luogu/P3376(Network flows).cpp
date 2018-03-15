#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 1e4 + 3, M = 2e5 + 3;

int n, m, s, t, u, v, w, tot = 0;
int st[N], to[M], nx[M], cost[M];

inline int opp(int x) { return ((x + 1) ^ 1) - 1; }
inline void add(int u, int v, int c) { to[++tot] = v, nx[tot] = st[u], cost[tot] = c, st[u] = tot; }
inline int min(int a, int b) { return a < b ? a : b; }
inline int read()
{
	int x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + (c ^ '0');
	return f ? -x : x;
}

void init()
{
	n = read(), m = read(), s = read(), t = read();
	for (int i = 1; i <= m; i++)
		u = read(), v = read(), w = read(), add(u, v, w), add(v, u, 0);
}

int head = 1, tail = 0;
int pre[N][2], minflow[N], que[N * 20], dep[N];

int bfs()
{
	head = 1, tail = 0;
	for (int i = 1; i <= n; i++) pre[i][0] = -1;
	pre[s][0] = 0, minflow[N] = 0x3f3f3f3f, que[++tail] = s;
	memset(dep, -1, sizeof(dep));
	while (head <= tail)
	{
		int u = que[head++];
		if (u == t) break;
		for (int i = st[u]; i; i = nx[i])
		{
			int v = to[i];
			if (cost[i] > 0 && dep[v] == -1)
			{
				dep[v] = dep[u] + 1;
				pre[v][0] = u, pre[v][1] = i;
				minflow[v] = min(cost[i], minflow[u]);
				que[++tail] = v;
			}
		}
	}
	if (pre[t][0] == -1) return -1;
	else return minflow[t];
}

void solve()
{
	int ans = 0, flow;
	while (flow = bfs() != -1)
	{
		ans += flow;
		int now = t;
		while (now != s)
		{
			cost[pre[now][1]] -= flow;
			cost[opp(pre[now][1])] += flow;
			now = pre[now][0];
		}
	}
	printf("%d\n", ans);
}

int main()
{
	init();
	solve();
	return 0;
}
