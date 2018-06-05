#include <queue>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;

const int N = 5e2 + 7;
const int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

int n, m, fx, fy, tx, ty, l, r, mid, ans;
char map[N][N];
int dis[N][N], d[N][N];
struct note { int x, y; };
queue<note> que;

inline int out(int x, int y) { return x < 1 || x > n || y < 1 || y > m; }

int check(int m)
{
	if (d[fx][fy] < m) return 0;
	memset(dis, 0, sizeof(dis));
	que = queue<note>();
	dis[fx][fy] = 1, que.push((note){fx, fy});
	while (!que.empty())
	{
		note now = que.front(); que.pop();
		for (int i = 0; i < 4; i++)
		{
			int dx = now.x + dir[i][0], dy = now.y + dir[i][1];
			if (out(dx, dy) || d[dx][dy] < m) continue;
			if (!dis[dx][dy]) dis[dx][dy] = 1, que.push((note){dx, dy});
		}
	}
	return dis[tx][ty];
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
		{
			scanf(" %c", &map[i][j]);
			if (map[i][j] == 'V') fx = i, fy = j;
			if (map[i][j] == 'J') tx = i, ty = j;
			if (map[i][j] == '+') que.push((note){i, j});
		}
	while (!que.empty())
	{
		note now = que.front(); que.pop();
		for (int i = 0; i < 4; i++)
		{
			int dx = now.x + dir[i][0], dy = now.y + dir[i][1];
			if (out(dx, dy) || map[dx][dy] == '+') continue;
			if (!d[dx][dy]) d[dx][dy] = d[now.x][now.y] + 1, que.push((note){dx, dy});
		}
	}
	l = 0, r = 1100;
	while (l <= r)
	{
		mid = l + r >> 1;
		if (check(mid)) l = mid + 1, ans = mid;
		else r = mid - 1;
	}
	printf("%d\n", ans);
	return 0;
}
