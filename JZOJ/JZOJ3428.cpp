#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 1e3 + 7;
const int dir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

int n, m, a[N][N];
int l, r, mid, ans;

inline int check(int x, int y) { return x > 0 && x <= n && y > 0 && y <= m; }

int head, tail, que[N * N], vis[N * N];
int ok(int now)
{
	head = 1, tail = 0, memset(vis, 0, sizeof(vis));
	for (int i = 1; i <= m; i++) vis[i] = 1, que[++tail] = i;
	while (head <= tail)
	{
		int res = que[head++], x = res / m + 1, y = (res - 1) % m + 1;
		for (int i = 0, dx, dy, s; i < 4; i++)
		{
			dx = x + dir[i][0], dy = y + dir[i][1], s = (dx - 1) * m + dy;
			if (check(dx, dy) && a[dx][dy] <= now && !vis[s]) que[++tail] = s, vis[s] = 1;
		}
	}
	for (int i = 1; i <= m; i++) if (!vis[(n - 1) * m + i]) return 0;
	return 1;
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			scanf("%d", &a[i][j]);
	l = 0, r = N - 7;
	while (l <= r)
	{
		mid = l + r >> 1;
		if (ok(mid)) r = mid - 1, ans = mid;
		else l = mid + 1;
	}
	printf("%d\n", ans);
	return 0;
}
