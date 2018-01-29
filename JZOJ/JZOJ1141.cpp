#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 107;

int n, m, q, u, v, w;
int dis[N][N];

inline int read()
{
	int x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + c - '0';
	return f ? -x : x;
}
inline int min(int a, int b) { return a < b ? a : b; }
inline int max(int a, int b) { return a > b ? a : b; }

int main()
{
	memset(dis, 0x3f, sizeof(dis));
	n = read(), m = read();
	for (int i = 1; i <= m; i++)
		u = read(), v = read(), w = read(), dis[u][v] = dis[v][u] = w;
	for (int k = 1; k <= n; k++)
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				dis[i][j] = max(dis[i][j], min(dis[i][k], dis[k][j]));
	q = read();
	while (q--)
	{
		u = read(), v = read();
		if (dis[u][v] >= 0x3f3f3f3f) printf("-1\n");
		else printf("%d\n", dis[u][v]);
	}
	return 0;
}