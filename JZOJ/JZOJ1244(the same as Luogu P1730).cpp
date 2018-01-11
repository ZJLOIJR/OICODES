#pragma GCC optimize(2)
#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 57, INF = 10000000;

int n, m, u, v, w, q;
double ans;
int dis[N][N][N];

inline double min(double a, double b) { return a < b ? a : b; }

void init()
{
	scanf("%d%d", &n, &m);
	for (int i = 0; i <= n; i++)
		for (int j = 0; j <= n; j++)
			for (int k = 0; k <= n; k++)
				dis[i][j][k] = INF;
	for (int i = 1; i <= m; i++)
	{
		scanf("%d%d%d", &u, &v, &w);
		if (w < dis[u][v][1]) dis[u][v][1] = w;
	}
	for (int i = 1; i <= n; i++) dis[i][i][0] = 0;
	for (register int l = 1; l <= n; l++)
		for (register int k = 1; k <= n; k++)
			for (register int i = 1; i <= n; i++)
				for (register int j = 1; j <= n; j++)
					dis[i][j][l] = min(dis[i][j][l], dis[i][k][l - 1] + dis[k][j][1]);
}

void solve()
{
	scanf("%d", &q);
	while (q--)
	{
		scanf("%d%d", &u, &v);
		ans = INF;
		for (int i = 1; i <= n; i++)
			if (dis[u][v][i] < INF)
				ans = min(ans, dis[u][v][i] * 1.0 / i);
		if (ans >= INF)
			printf("OMG!\n");
		else
			printf("%.3lf\n", ans);
	}
}

int main()
{
	init();
	solve();
	return 0;
}
