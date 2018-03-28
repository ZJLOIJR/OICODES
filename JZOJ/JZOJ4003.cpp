#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 1e2 + 3, INF = 0x3f3f3f3f;
const int dir[8][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

int T, n, m, tot = 1, s, t;
char matrix[N][N], str[N * N * 40], nxchar[256];
int cnt[N][N];
int st[N * N * 40], to[N * N * 40], nx[N * N * 40], len[N * N * 40];

inline void add(int u, int v, int w) { to[++tot] = v, nx[tot] = st[u], len[tot] = w, st[u] = tot; }
inline int id(int x, int y, int k) { return (x - 1) * m + y + k * n * m + 1; }
inline int check(int x, int y) { return x > 0 && x <= n && y > 0 && y <= m; }
inline int min(int a, int b) { return a < b ? a : b; }

inline void init()
{
	memset(st, 0, sizeof(st)); memset(to, 0, sizeof(to)); memset(nx, 0, sizeof(nx)); memset(len, 0, sizeof(len));
	tot = 1;
	scanf("%d%d", &n, &m);
	s = 1, t = n * m * 2 + 2;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			scanf(" %c", &matrix[i][j]);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			scanf("%d", &cnt[i][j]);
	scanf("%s", str + 1);
	int le = strlen(str + 1);
	for (int i = 1; i <= le - 1; i++) nxchar[str[i]] = str[i + 1];
	nxchar[str[le]] = '$';
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
		{
			if (matrix[i][j] == str[1])
				add(s, id(i, j, 0), INF),
				add(id(i, j, 0), s, 0);
			if (matrix[i][j] == str[le])
				add(id(i, j, 1), t, INF),
				add(t, id(i, j, 1), 0);
			if (nxchar[matrix[i][j]])
			{
				add(id(i, j, 0), id(i, j, 1), cnt[i][j]);
				add(id(i, j, 1), id(i, j, 0), 0);
				for (int k = 0; k < 8; k++)
				{
					int dx = i + dir[k][0], dy = j + dir[k][1];
					if (check(dx, dy) && matrix[dx][dy] == nxchar[matrix[i][j]])
						add(id(i, j, 1), id(dx, dy, 0), INF),
						add(id(dx, dy, 0), id(i, j, 1), 0);
				}
			}
		}
}

int head, tail, dep[N * N * 40], que[N * N * 40];
int bfs()
{
	memset(dep, 0, sizeof(dep));
	head = 1, tail = 0;
	dep[s] = 1, que[++tail] = s;
	while (head <= tail)
	{
		int u = que[head++];
		for (int i = st[u]; i; i = nx[i])
			if (!dep[to[i]] && len[i] > 0)
			{
				dep[to[i]] = dep[u] + 1, que[++tail] = to[i];
				if (to[i] == t) return 1;
			}
	}
	return 0;
}

int dinic(int u, int flow)
{
	if (u == t) return flow;
	int ret = flow, tmp;
	for (int i = st[u]; i; i = nx[i])
		if (dep[to[i]] == dep[u] + 1 && len[i] > 0)
		{
			tmp = dinic(to[i], min(ret, len[i]));
			len[i] -= tmp;
			len[i ^ 1] += tmp;
			ret -= tmp;
			if (!ret) break;
		}
	if (!tmp) dep[u] = 0;
	return flow - ret;
}

void solve()
{
	long long ans = 0;
	while (bfs())
	{
		int tmp;
		while (tmp = dinic(s, INF))
			ans += tmp;
	}
	printf("%lld\n", ans);
}

int main()
{
	scanf("%d", &T);
	for (int i = 1; i <= T; i++)
	{
		init();
		printf("Case #%d: ", i);
		solve();
	}
	return 0;
}
