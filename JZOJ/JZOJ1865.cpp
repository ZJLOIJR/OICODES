#pragma GCC optimize(2)
#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#define min(a, b) ((a) < (b) ? (a) : (b))

const int N = 5e2 + 3;

int n, m, ans = N, map[N][N], f[N], seg[N][2];
bool arr[N], vis[N][N];
inline int check(int x, int y) { return x > 0 && x <= n && y > 0 && y <= m; }

void dfs(int x, int y, int now)
{
	vis[x][y] = 1;
	if (x == n)
	{
		arr[y] = 1;
		if (y < seg[now][0]) seg[now][0] = y;
		if (y > seg[now][1]) seg[now][1] = y;
	}
	if (map[x + 1][y] < map[x][y] && x != n && !vis[x + 1][y]) dfs(x + 1,y,now);
	if (map[x - 1][y] < map[x][y] && x != 1 && !vis[x - 1][y]) dfs(x - 1,y,now);
	if (map[x][y + 1] < map[x][y] && y != m && !vis[x][y + 1]) dfs(x,y + 1,now);
	if (map[x][y - 1] < map[x][y] && y != 1 && !vis[x][y - 1]) dfs(x,y - 1,now);
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			scanf("%d", &map[i][j]);
	for (int i = 1; i <= m; i++)
	{
		memset(vis, 0, sizeof(vis));
		seg[i][0] = m + 1, seg[i][1] = 0, dfs(1, i, i);
	}
	int cnt = 0;
	for (int i = 1; i <= m; i++) if (!arr[i]) cnt++;
	if (cnt) { printf("0\n%d\n", cnt); return 0; }
	memset(f, 0x3f, sizeof(f));
	f[0] = 0;
	for (int i = 1; i <= m; i++)
		for (int j = 1; j <= m; j++)
			if (seg[j][0] <= i && i <= seg[j][1])
				f[i] = min(f[i], f[seg[j][0] - 1] + 1);
	printf("1\n%d\n", f[m]);
	return 0;
}
