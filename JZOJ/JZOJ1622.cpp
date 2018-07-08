#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
inline int min(int a, int b) { return a < b ? a : b; }
inline int max(int a, int b) { return a > b ? a : b; }

const int N = 257;

int n, m, k, dis[N][N], ans[N][N];
struct node { int id, c; } a[N];
int cmp(node x, node y) { return x.c < y.c; }

int main()
{
	freopen("toll.in", "r", stdin);
	freopen("toll.out", "w", stdout);
	memset(dis, 0x3f, sizeof(dis));
	memset(ans, 0x3f, sizeof(ans));
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i].c), a[i].id = i;
	for (int i = 1; i <= n; i++) dis[i][i] = 0, ans[i][i] = a[i].c;
	for (int i = 1, u, v, w; i <= m; i++)
	{
		scanf("%d%d%d", &u, &v, &w);
		dis[u][v] = dis[v][u] = min(dis[u][v], w);
		ans[u][v] = ans[v][u] = min(ans[u][v], dis[u][v] + max(a[u].c, a[v].c));
	}
	sort(a + 1, a + n + 1, cmp);
	for (int k = 1; k <= n; k++)
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
			{
				int x = a[i].id, y = a[k].id, z = a[j].id;
				dis[x][z] = min(dis[x][z], dis[x][y] + dis[y][z]);
				ans[x][z] = min(ans[x][z], dis[x][z] + max(max(a[i].c, a[k].c), a[j].c));
			}
	while (k--)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		printf("%d\n", ans[u][v]);
	}
	return 0;
}
