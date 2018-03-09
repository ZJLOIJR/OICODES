#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int N = 1e3 + 5;
const int DIRE[8][2] = {{1, 2}, {-1, 2}, {1, -2}, {-1, -2}, {2, 1}, {-2, 1}, {2, -1}, {-2, -1}};

int n, m, xfrom, yfrom, xto, yto, tot = 0, cnt = 0, head, tail;
int st[N], to[N * 500], nx[N * 500], len[N * 500];
int map[35][35], vis[N * 500], vis2[N * 500], arr[N * 500], dis[N * 500], que[N * 500];
long long f[N * 500];
int used[N][N];

inline void add(int u, int v, int w) { to[++tot] = v, len[tot] = w, nx[tot] = st[u], st[u] = tot; }
inline int check(int x, int y) { return 1 <= x && x <= n && 1 <= y && y <= m && map[x][y] != 2; }

void dfs(int x, int y)
{
	for (int i = 0; i < 8; i++)
	{
		int dx = x + DIRE[i][0], dy = y + DIRE[i][1];
		if (check(dx, dy))
		{
			if (!map[dx][dy] && !vis2[dx * m + dy])
			{
				vis2[dx * m + dy] = 1;
				arr[++cnt] = dx * m + dy;
			}
			if (map[dx][dy] == 1 && !vis[dx * m + dy])
			{
				vis[dx * m + dy] = 1;
				dfs(dx, dy);
			}
		}
	}
}

void init()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
		{
			scanf("%d", &map[i][j]);
			if (map[i][j] == 3)
				xfrom = i, yfrom = j, map[i][j] = 0;
			if (map[i][j] == 4)
				xto = i, yto = j, map[i][j] = 0;
		}
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			if (!map[i][j])
				for (int k = 0; k < 8; k++)
				{
					int dx = i + DIRE[k][0], dy = j + DIRE[k][1];
					if (check(dx, dy) && !map[dx][dy])
						add(i * m + j, dx * m + dy, 1);
				}
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			if (map[i][j] == 1 && !vis[i * m + j])
			{
				cnt = 0; memset(vis2, 0, sizeof(vis2));
				vis[i * j + 1] = 1;
				dfs(i, j);
				for (int k = 1; k <= cnt; k++)
					for (int l = 1; l <= cnt; l++)
					{
						if (!used[arr[k]][arr[l]])
						{
							used[arr[k]][arr[l]] = used[arr[l]][arr[k]] = 1;
							add(arr[k], arr[l], 1);
							add(arr[l], arr[k], 1);
						}
					}
			}
}

void solve()
{
	memset(vis, 0, sizeof(vis));
	memset(dis, 0x3f, sizeof(dis));
	head = 1, tail = 0;
	que[++tail] = xfrom * m + yfrom, vis[xfrom * m + yfrom] = 1, f[xfrom * m + yfrom] = 1, dis[xfrom * m + yfrom] = 0;
	while (head <= tail)
	{
		int u = que[head++];
		vis[u] = 0;
		for (int i = st[u]; i; i = nx[i])
		{
			int v = to[i];
			if (dis[u] + len[i] == dis[v])
				f[v] += f[u];
			if (dis[u] + len[i] < dis[v])
			{
				dis[v] = dis[u] + len[i];
				f[v] = f[u];
				if (!vis[v] && v != xto * m + yto)
				{
					vis[v] = 1;
					que[++tail] = v;
				}
			}
		}
	}
	if (dis[xto * m + yto] >= 0x3f3f3f3f) printf("-1\n");
	else printf("%d\n%lld\n", dis[xto * m + yto] - 1, f[xto * m + yto]);
}

int main()
{
	freopen("lilypad.in", "r", stdin);
	freopen("lilypad.out", "w", stdout);

	init();
	solve();

	fclose(stdin);
	fclose(stdout);
	return 0;
}
