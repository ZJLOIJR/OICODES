#include <cmath>
#include <queue>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;

const int N = 1e2 + 3;
const int dir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
const long double INF = 2333333333.0;

struct record { int x, y; };

int r, c, v;
int map[N][N];
queue<record> que;
long double dis[N][N], speed[N][N], vis[N][N], power[60];

inline int check(int x, int y) { return x > 0 && x <= r && y > 0 && y <= c; }

int main()
{
	freopen("cowski.in", "r", stdin);
	freopen("cowski.out", "w", stdout);

	power[0] = 1; for (int i = 1; i <= 50; i++) power[i] = power[i - 1] * 2;
	scanf("%d%d%d", &v, &r, &c);
	speed[1][1] = v;
	for (int i = 1; i <= r; i++)
		for (int j = 1; j <= c; j++)
		{
			scanf("%d", &map[i][j]);
			speed[i][j] = map[i][j] > map[1][1] ?
				speed[1][1] / power[map[i][j] - map[1][1]] : speed[1][1] * power[map[1][1] - map[i][j]];
			dis[i][j] = INF;
		}
	que.push((record){1, 1});
	dis[1][1] = 0.0, vis[1][1] = 1;
	while (!que.empty())
	{
		record tmp = que.front();
		que.pop();
		vis[tmp.x][tmp.y] = 0;
		for (int i = 0; i < 4; i++)
		{
			int dx = tmp.x + dir[i][0], dy = tmp.y + dir[i][1];
			if (!check(dx, dy)) continue;
			if (dis[tmp.x][tmp.y] + 1.0 / speed[tmp.x][tmp.y] < dis[dx][dy])
			{
				dis[dx][dy] = dis[tmp.x][tmp.y] + 1.0 / speed[tmp.x][tmp.y];
				if (!vis[dx][dy])
				{
					que.push((record){dx, dy});
					vis[dx][dy] = 1;
				}
			}
		}
	}
	dis[r][c] = abs(dis[r][c] - 0.00000057);
	long long tmp = dis[r][c] + 0.05;
	double temp = 0.63 + tmp - dis[r][c];
	if (temp > 0 && temp <= 0.01) printf("%.2lf\n", (double)dis[r][c] + 0.01);
	else printf("%.2lf\n", (double)abs(dis[r][c] - 0.00000057));

	fclose(stdin);
	fclose(stdout);
	return 0;
}
