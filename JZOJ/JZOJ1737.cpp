#include <cstdio>
#include <cstring>
#include <cstdlib>

inline int read()
{
	int x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + (c ^ '0');
	return f ? -x : x;
}
inline int max(int a, int b) { return a > b ? a : b; }

const int N = 1e5 + 7;

int n, u, v, w, tot = 0, ans = 0;
int st[N], to[N << 1], nx[N << 1], len[N << 1];
int f[N], dis[N][3][2], g[N][2][2];

inline void add(int u, int v, int w) { to[++tot] = v, nx[tot] = st[u], len[tot] = w, st[u] = tot; }

void dfs(int u, int from)
{
	for (int i = st[u]; i; i = nx[i])
		if (to[i] != from)
		{
			int v = to[i];
			dfs(v, u);
			if (dis[v][0][0] + len[i] > dis[u][0][0])
			{
				dis[u][2][0] = dis[u][1][0], dis[u][2][1] = dis[v][1][1];
				dis[u][1][0] = dis[u][0][0], dis[u][1][1] = dis[u][0][1];
				dis[u][0][0] = dis[v][0][0] + len[i], dis[u][0][1] = v;
			}
			if (dis[v][0][0] + len[i] < dis[u][0][0] && dis[v][0][0] + len[i] > dis[u][1][0])
			{
				dis[u][2][0] = dis[u][1][0], dis[u][2][1] = dis[u][1][1];
				dis[u][1][0] = dis[v][0][0] + len[i], dis[u][1][1] = v;
			}
			if (dis[v][0][0] + len[i] < dis[u][1][0] && dis[v][0][0] + len[i] > dis[u][2][0])
			{
				dis[u][2][0] = dis[v][0][0] + len[i], dis[u][2][1] = v;
			}
			if (f[v] > g[u][0][0])
			{
				g[u][1][0] = g[u][0][0], g[u][1][1] = g[u][0][1];
				g[u][0][0] = f[v], g[u][0][1] = v;
			}
			if (f[v] < g[u][0][0] && f[v] > g[u][1][0])
			{
				g[u][1][0] = f[v], g[u][1][1] = v;
			}
		}
	f[u] = max(g[u][0][0], dis[u][0][0] + dis[u][1][0]);
}

void getans(int u, int from, int mx, int sum)
{
	for (int i = st[u]; i; i = nx[i])
		if (to[i] != from)
		{
			int v = to[i];
			ans = max(ans, f[v] + mx); //situation a
			ans = max(ans, f[v] + sum + (dis[u][0][1] == v ? dis[u][1][0] : dis[u][0][0])); //situation b
			int tmp;
			if (dis[u][0][1] == v) tmp = dis[u][1][0] + dis[u][2][0];
			else
			{
				if (dis[u][1][1] == v) tmp = dis[u][0][0] + dis[u][2][0];
				else tmp = dis[u][0][0] + dis[u][1][0];
			}
			ans = max(ans, f[v] + tmp); //situation c
			ans = max(ans, f[v] + (g[u][0][1] == v ? g[u][1][0] : g[u][0][0])); //situation d
			getans(v, u, max(mx, (g[u][0][1] == v ? g[u][1][0] : g[u][0][0])), max(sum, (dis[u][0][1] == v ? dis[u][1][0] : dis[u][0][0])) + len[i]);
		}
}

int main()
{
	n = read();
	for (int i = 1; i < n; i++) u = read(), v = read(), w = read(), add(u, v, w), add(v, u, w);
	dfs(1, 0);
	getans(1, 0, 0, 0);
	printf("%d\n", ans);
	return 0;
}
