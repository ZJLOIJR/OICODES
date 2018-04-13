#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

const int dir[4][2] = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
const int N = 23, INF = 0x3f3f3f3f;

int n, m, d, s, t, ans, tot = 1, sum = 0;
int st[N * N * 20], to[N * N * 20], nx[N * N * 20], len[N * N * 20];
char map[N][N];

inline int check(int x, int y) { return x > 0 && x <= n && y > 0 && y <= m; }
inline int min(int a, int b) { return a < b ? a : b; }
inline double sqr(double x) { return x * x; }
inline double dis(double x_1, double y_1, double x_2, double y_2) { return sqrt(sqr(x_1 - x_2) + sqr(y_1 - y_2)); }
inline void add(int u, int v, int w)
{
	to[++tot] = v, nx[tot] = st[u], len[tot] = w, st[u] = tot;
	to[++tot] = u, nx[tot] = st[v], len[tot] = 0, st[v] = tot;
}

int head, tail, dep[N * N * 20], que[N * N * 20];
int bfs()
{
	memset(dep, 0, sizeof(dep));
	head = 1, tail = 0;
	que[++tail] = s, dep[s] = 1;
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
			len[i] -= tmp, len[i ^ 1] += tmp;
			ret -= tmp;
		}
	return flow - ret;
}

int main()
{
	scanf("%d%d%d", &n, &m, &d);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
		{
			scanf(" %c", &map[i][j]);
			if (map[i][j] - '0' > 0) add((i - 1) * m + j, (i - 1) * m + j + n * m, map[i][j] - '0');
		}
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
		{
			if (map[i][j] - '0' == 0) continue;
			for (int k = 1; k <= n; k++)
				for (int l = 1; k <= m; l++)
				{
					if (i == k && j == l) continue;
					if ()
				}
		}
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
		{
			char ch;
			scanf(" %c", &ch);
			if (ch == 'L') add(s, (i - 1) * m + j, 1), sum++;
		}
	s = 0, t = n * m * 2 + 1;
	while (bfs())
	{
		int tmp;
		while (tmp = dinic(s, INF)) ans += tmp;
	}
	printf("%d\n", sum - ans);
	return 0;
}
