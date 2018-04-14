#include <queue>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#define min(a, b) ((a) < (b) ? (a) : (b))
#define check(x, y) ((x) > 0 && (x) <= n && (y) > 0 && (y) <= m)
#define id(x, y) (((x) - 1) * m + (y))
using namespace std;

const int N = 20, P = 245;
const int dir[5][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}, {0, 0}};

int n, m, k, st1, st2, st3, en1, en2, en3, tot = 0;
int st[P * 5], to[P * 5], nx[P * 5], dis[P][P][P];
char map[N][N];

inline void add(int u, int v) { to[++tot] = v, nx[tot] = st[u], st[u] = tot; }

struct note { int a_, b_, c_; };
queue<note> que;
void bfs()
{
	memset(dis, -1, sizeof(dis));
	while (!que.empty()) que.pop();
	dis[st1][st2][st3] = 0, que.push((note){st1, st2, st3});
	while (!que.empty())
	{
		note u = que.front();
		que.pop();
		int a = u.a_, b = u.b_, c = u.c_;
		if (a == en1 && b == en2 && c == en3) return;
		for (int i = st[a]; i; i = nx[i])
			for (int j = st[b]; j; j = nx[j])
				for (int k = st[c]; k; k = nx[k])
				{
					int toa = to[i], tob = to[j], toc = to[k];
					if (toa == tob || tob == toc || toa == toc) continue;
					if ((toa == b && tob == a) || (tob == c && toc == b) || (toa == c && toc == a)) continue;
					if (dis[toa][tob][toc] == -1)
					{
						dis[toa][tob][toc] = dis[a][b][c] + 1;
						que.push((note){toa, tob, toc});
					}
				}
	}
}

int main()
{
	while (1)
	{
		scanf("%d%d%d", &m, &n, &k);
		if (n == 0 && m == 0) break;
		memset(st, 0, sizeof(st));
		st1 = st2 = st3 = en1 = en2 = en3 = tot = 0;
		getchar();
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= m; j++)
			{
				map[i][j] = getchar();
				if (map[i][j] == 'a') st1 = id(i, j);
				if (map[i][j] == 'b') st2 = id(i, j);
				if (map[i][j] == 'c') st3 = id(i, j);
				if (map[i][j] == 'A') en1 = id(i, j);
				if (map[i][j] == 'B') en2 = id(i, j);
				if (map[i][j] == 'C') en3 = id(i, j);
			}
			getchar();
		}
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++)
				if (map[i][j] != '#')
					for (int k = 0; k < 5; k++)
					{
						int dx = i + dir[k][0], dy = j + dir[k][1];
						if (check(dx, dy) && map[dx][dy] != '#') add(id(i, j), id(dx, dy));
					}
		if (k <= 2)
		{
			add(n * m + 1, n * m + 1);
			st3 = en3 = n * m + 1;
		}
		if (k <= 1)
		{
			add(n * m + 2, n * m + 2);
			st2 = en2 = n * m + 2;
		}
		bfs();
		printf("%d\n", dis[en1][en2][en3]);
	}
	return 0;
}
