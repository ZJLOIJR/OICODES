#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 23, INF = 0x3f3f3f3f;

int n, m, d, S, T, ans, tot = 1;
int st[N * N * 100], to[N * N * 100], nx[N * N * 100], len[N * N * 100];
int map[N][N];
char ch;

inline int check(int x, int y) { return x > 0 && x <= n && y > 0 && y <= m; }
inline int min(int a, int b) { return a < b ? a : b; }
inline double sqr(double x) { return x * x; }
inline double dis(double x_1, double y_1, double x_2, double y_2) { return sqrt(sqr(x_1 - x_2) + sqr(y_1 - y_2)); }
inline void add(int u, int v, int w)
{
	to[++tot] = v, nx[tot] = st[u], len[tot] = w, st[u] = tot;
	to[++tot] = u, nx[tot] = st[v], len[tot] = 0, st[v] = tot;
}
inline int id(int x, int y, int k) { return (x - 1) * m + y + n * m * k; }

int head, tail, dep[N * N * 100], que[N * N * 100];
int bfs()
{
	memset(dep, 0, sizeof(dep));
	head = 1, tail = 0;
	que[++tail] = S, dep[S] = 1;
	while (head <= tail)
	{
		int u = que[head++];
		for (int i = st[u]; i; i = nx[i])
			if (!dep[to[i]] && len[i] > 0)
			{
				dep[to[i]] = dep[u] + 1, que[++tail] = to[i];
				if (to[i] == T) return 1;
			}
	}
	return 0;
}

int dinic(int u, int flow)
{
	if (u == T) return flow;
	int ret = flow, tmp;
	for (int i = st[u]; i; i = nx[i])
		if (dep[to[i]] == dep[u] + 1 && len[i] > 0)
		{
			tmp = dinic(to[i], min(ret, len[i]));
			if (!tmp) dep[to[i]] = 0;
			len[i] -= tmp, len[i ^ 1] += tmp;
			ret -= tmp;
		}
	return flow - ret;
}

int main()
{
	scanf("%d%d%d", &n, &m, &d);
	S = 0, T = n * m * 2 + 1;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
		{
			scanf(" %c", &ch);
			map[i][j] = ch - '0';
			if (map[i][j]) add(id(i, j, 0), id(i, j, 1), map[i][j]);
		}
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
		{
			scanf(" %c", &ch);
			if (ch == 'L') add(S, id(i, j, 0), 1), ans++;
			if (i - d <= 0 || i + d > n || j - d <= 0 || j + d > m) add(id(i, j, 1), T, INF);
		}
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
		{
			if (!map[i][j]) continue;
			for (int k = 1; k <= n; k++)
				for (int l = 1; l <= m; l++)
				{
					if (i == k && j == l) continue;
					if (map[k][l] && dis(i, j, k, l) <= d) add(id(i, j, 1), id(k, l, 0), INF);
				}
		}
	while (bfs())
	{
		int tmp = 0;
		while (tmp = dinic(S, INF)) ans -= tmp;
	}
	printf("%d\n", ans);
	return 0;
}
