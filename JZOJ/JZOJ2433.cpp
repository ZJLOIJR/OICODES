#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 1e2 + 3;

int n, m, u, v, q;
int dis[N][N];

int main()
{
	memset(dis, 0x3f, sizeof(dis));
	scanf("%d%d", &n, &m);
	while (m--)
	{
		scanf("%d%d", &u, &v);
		dis[u][v] = dis[v][u] = 1;
	}
	for (int i = 1; i <= n; i++) dis[i][i] = 0;
	for (int k = 1; k <= n; k++)
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				if (dis[i][k] + dis[k][j] < dis[i][j])
					dis[i][j] = dis[i][k] + dis[k][j];
	scanf("%d", &q);
	while (q--)
	{
		scanf("%d%d", &u, &v);
		int ans = 0;
		for (int i = 1; i <= n; i++)
			ans += (dis[u][i] + dis[i][v] == dis[u][v]);
		printf("%d\n", ans);
	}
	return 0;
}
