#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 80;
const int dir[4][2] = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};

int n, m, anscow = 0, ansroom = 0;
char map[N][N];
int head, tail, que[N * N * 10][2], vis[N][N];

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			scanf(" %c", &map[i][j]);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			if (map[i][j] == '#' && !vis[i][j])
			{
				int cnt = 0, mxx = 0, mxy = 0, mix = N, miy = N;
				head = 1, tail = 0;
				que[++tail][0] = i, que[tail][1] = j, vis[i][j] = 1;
				while (head <= tail)
				{
					int x = que[head][0], y = que[head][1];
					if (x > mxx) mxx = x;
					if (y > mxy) mxy = y;
					if (x < mix) mix = x;
					if (y < miy) miy = y;
					head++, cnt++;
					for (int i = 0; i < 4; i++)
					{
						int dx = x + dir[i][0], dy = y + dir[i][1];
						if (dx > 0 && dx <= n && dy > 0 && dy <= m)
							if (!vis[dx][dy] && map[dx][dy] == '#')
							{
								que[++tail][0] = dx, que[tail][1] = dy;
								vis[dx][dy] = 1;
							}
					}
				}
				if (cnt == (mxx - mix + 1) * (mxy - miy + 1)) ansroom++;
				else anscow++;
			}
	printf("%d\n%d\n", ansroom, anscow);
	return 0;
}
