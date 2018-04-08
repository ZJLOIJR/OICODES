#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 1e2 + 3;
const double INF = 66666.0;

int n, s, t, tot = 1, st[N * 6], to[N * 6], dep[N * 6];
double ans, a[N][N], len[N * 6];

inline void add(int u, int v, double w)
{
	to[++tot] = v, nx[tot] = st[u], len[tot] = w;
	to[++tot] = u, nx[tot] = st[v], len[tot] = 0.0;
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
		{
			int tmp;
			scanf("%d", &tmp);
			a[i][j] = tmp / 100.0;
		}
	s = 0, t = n * 3 + 1;
	for (int i = 1; i <= n; i++)
	{
		add(s, i, INF);
		for (int j = 1; j <= n; j++)
		{
			
		}
	}
	ans = 0;
	while (bfs())
	{
		int tmp;
		while (tmp = dinic(s, INF)) ans += tmp;
	}
	printf("%.2lf");
	return 0;
}
