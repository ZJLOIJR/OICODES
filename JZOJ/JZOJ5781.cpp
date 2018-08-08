#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 5e2 + 7;
const int dir[4][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};

int n, m, head, tail, s, t, dis[N * N], vis[N * N];
int shot[N][N][4], que[N * N * 20];
char map[N][N];

int id(int x, int y) { return (x - 1) * m + y; }

int tot = 0, st[N * N], to[N * N * 10], nx[N * N * 10], len[N * N * 10];
void add(int u, int v, int w) { to[++tot] = v, nx[tot] = st[u], len[tot] = w, st[u] = tot; }

int main()
{
	freopen("portal.in", "r", stdin);
	freopen("portal.out", "w", stdout);

	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
		{
			scanf(" %c", &map[i][j]);
			if (map[i][j] == 'C') s = id(i, j);
			if (map[i][j] == 'F') t = id(i, j);
		}
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			if (map[i][j] != '#')
				for (int k = 0; k < 4; k++)
					if (map[i + dir[k][0]][j + dir[k][1]] != '#')
						add(id(i, j), id(i + dir[k][0], j + dir[k][1]), 1);
	for (int i = 2; i <= n - 1; i++)
		for (int j = 1, st, en; j <= m; j = en)
		{
			st = j, en = j + 1;
			while (map[i][en] != '#' && en <= m) en++;
			for (int k = st + 1; k <= en - 1; k++) shot[i][k][0] = st + 1, shot[i][k][1] = en - 1;
		}
	for (int i = 2; i <= m - 1; i++)
		for (int j = 1, st, en; j <= n; j = en)
		{
			st = j, en = j + 1;
			while (map[en][i] != '#' && en <= n) en++;
			for (int k = st + 1; k <= en - 1; k++) shot[k][i][2] = st + 1, shot[k][i][3] = en - 1;
		}
	for (int i = 2; i <= n - 1; i++)
		for (int j = 2; j <= m - 1; j++)
			if (map[i][j] != '#')
			{
				int mi = j - shot[i][j][0], d = 0;
				if (shot[i][j][1] - j < mi) mi = shot[i][j][1] - j, d = 1;
				if (i - shot[i][j][2] < mi) mi = i - shot[i][j][2], d = 2;
				if (shot[i][j][3] - i < mi) mi = shot[i][j][3] - i, d = 3;
				add(id(i, j), id(i, shot[i][j][0]), d == 0 ? mi : mi + 1);
				add(id(i, j), id(i, shot[i][j][1]), d == 1 ? mi : mi + 1);
				add(id(i, j), id(shot[i][j][2], j), d == 2 ? mi : mi + 1);
				add(id(i, j), id(shot[i][j][3], j), d == 3 ? mi : mi + 1);
			}
	memset(dis, 0x3f, sizeof(dis));
	head = 1, que[tail = 1] = s, dis[s] = 0, vis[s] = 1;
	while (head <= tail)
	{
		int now = que[head++];
		vis[now] = 0;
		for (int i = st[now]; i; i = nx[i])
			if (dis[now] + len[i] < dis[to[i]])
			{
				dis[to[i]] = dis[now] + len[i];
				if (!vis[to[i]]) que[++tail] = to[i], vis[to[i]] = 1;
			}
	}
	if (dis[t] >= 0x3f3f3f3f) printf("nemoguce\n");
	else printf("%d\n", dis[t]);

	fclose(stdin);
	fclose(stdout);
	return 0;
}
