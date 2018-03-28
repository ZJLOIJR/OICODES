#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 1e2 + 3;
const int dir[8][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

int T, n, m, tot = 0;
char matrix[N][N], str[N * N], nxchar[256];
int cnt[N][N];
int st[N * N], to[N * N * 20], nx[N * N * 20], len[N * N * 20];

inline void add(int u, int v, int w) { to[++tot] = v, nx[tot] = st[u], len[tot] = w, st[u] = tot; }
inline int opp(int x) { return ((x + 1) ^ 1) - 1; }
inline int id(int x, int y) { return (x - 1) * m + y + 1; }
inline int check(int x, int y) { return x > 0 && x <= n && y > 0 && y <= m; }

inline void init()
{
	memset(st, 0, sizeof(st)); memset(to, 0, sizeof(to)); memset(nx, 0, sizeof(nx)); memset(len, 0, sizeof(len));
	tot = 0;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			scanf(" %c", &matrix[i][j]);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			scanf("%d", &cnt[i][j]);
	scanf("%s", str + 1);
	int le = strlen(str + 1);
	for (int i = 1; i <= le - 1; i++) nxchar[str[i]] = str[i + 1];
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
		{
			if (matrix[i][j] == str[1])
				add(1, id(i, j), cnt[i][j]),
				add(id(i, j), 1, 0);
			if (matrix[i][j] == str[le])
				add(id(i, j), n * m + 2, cnt[i][j]),
				add(n * m + 2, id(i, j), 0);
			for (int k = 0; k < 8; k++)
			{
				int dx = i + dir[k][0], dy = j + dir[k][1];
				if (check(dx, dy) && matrix[dx][dy] == nxchar[matrix[i][j]])
					add(id(i, j), id(dx, dy), cnt[i][j]),
					add(id(dx, dy), id(i, j), 0);
			}
		}
}

int main()
{
	scanf("%d", &T);
	while (T--)
	{
		init();
		solve();
	}
	return 0;
}
