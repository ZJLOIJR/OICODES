#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
inline int min(int a, int b) { return a < b ? a : b; }
inline int read()
{
	int x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + (c ^ '0');
	return f ? -x : x;
}

const int N = 1e2 + 3, INF = 0x3f3f3f3f;

int n, q, u, v, w, opt;
int dis[N][N];

int main()
{
	n = read(), q = read();
	memset(dis, 0x3f, sizeof(dis));
	for (int i = 1; i <= n; i++) dis[i][i] = 0;
	while (q--)
	{
		opt = read(), u = read(), v = read();
		if (opt == 0)
		{
			if (dis[u][v] >= INF) printf("-1\n");
			else printf("%d\n", dis[u][v]);
		}
		else
		{
			w = read();
			dis[u][v] = dis[v][u] = min(dis[u][v], w);
			for (int i = 1; i <= n; i++)
				for (int j = 1; j <= n; j++)
				{
					dis[i][j] = min(dis[i][j], dis[i][u] + dis[u][v] + dis[v][j]);
					dis[i][j] = min(dis[i][j], dis[i][v] + dis[v][u] + dis[u][j]);
				}
		}
	}
	return 0;
}
