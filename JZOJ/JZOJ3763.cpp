#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 1e3 + 7, K = 17;
int sqr(int x) { return x * x; }
int min(int a, int b) { return a < b ? a : b; }
int bit(int x) { return (1 << (x - 1)); }

int n, m, k, sx, sy, tx, ty;
int cnt, id[N][N], h[N];
int tot, st[N], to[N * 4], nx[N * 4], len[N * 4];

int x[K + 7], y[K + 7], g[K + 7], w[K + 7][K + 7];
int f[K + 7][1 << K];

int head, tail, que[N * 50], dis[N], vis[N];

void add(int u, int v, int w) { to[++tot] = v, nx[tot] = st[u], len[tot] = w, st[u] = tot; }

int main()
{
	scanf("%d%d%d%d%d%d%d", &n, &m, &k, &sx, &sy, &tx, &ty);
	for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) id[i][j] = ++cnt;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			scanf("%d", &h[id[i][j]]);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
		{
			if (i + 1 <= n) add(id[i][j], id[i + 1][j], sqr(h[id[i][j]] - h[id[i + 1][j]]));
			if (i - 1 >= 1) add(id[i][j], id[i - 1][j], sqr(h[id[i][j]] - h[id[i - 1][j]]));
			if (j + 1 <= m) add(id[i][j], id[i][j + 1], sqr(h[id[i][j]] - h[id[i][j + 1]]));
			if (j - 1 >= 1) add(id[i][j], id[i][j - 1], sqr(h[id[i][j]] - h[id[i][j - 1]]));
		}
	x[1] = sx, y[1] = sy, g[1] = 0;
	for (int i = 2; i <= k + 1; i++) scanf("%d%d%d", x + i, y + i, g + i);
	x[k + 2] = tx, y[k + 2] = ty, g[k + 2] = 0;
	k += 2;
	for (int i = 1; i <= k; i++)
	{
		memset(dis, 0x3f, sizeof(dis));
		memset(vis, 0, sizeof(vis));
		head = 1, que[tail = 1] = id[x[i]][y[i]], dis[id[x[i]][y[i]]] = 0, vis[id[x[i]][y[i]]] = 1;
		while (head <= tail)
		{
			int u = que[head++];
			vis[u] = 0;
			for (int j = st[u]; j; j = nx[j])
				if (dis[u] + len[j] < dis[to[j]])
				{
					dis[to[j]] = dis[u] + len[j];
					if (!vis[to[j]]) que[++tail] = to[j], vis[to[j]] = 1;
				}
		}
		for (int j = 1; j <= k; j++) w[i][j] = dis[id[x[j]][y[j]]];
	}
	int full = (1 << k) - 1;
	memset(f, 0x3f, sizeof(f));
	f[1][1] = 0;
	for (int s = 1; s <= full; s++)
		for (int i = 1; i <= k; i++)
			if (bit(i) & s)
				for (int j = 1; j <= k; j++)
				{
					int tmp = (s & bit(j)) ? 0 : g[j];
					f[j][s | bit(j)] = min(f[j][s | bit(j)], f[i][s] + w[i][j] - tmp);
				}
	int ans = 0x3f3f3f3f;
	for (int s = 1; s <= full; s++) if (f[k][s] < ans) ans = f[k][s];
	printf("%d\n", ans);
	return 0;
}
