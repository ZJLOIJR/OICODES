#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#define max(a, b) ((a) > (b) ? (a) : (b))

const int N = 1e3 + 3, M = 1e5 + 3;

int n, m, x, u, v, w, ans, tot[2] = {0, 0};
int st[N][2], to[M][2], nx[M][2], len[M][2];

inline void add(int u, int v, int w, int k)
{ to[++tot[k]][k] = v, nx[tot[k]][k] = st[u][k], len[tot[k]][k] = w, st[u][k] = tot[k]; }

int head, tail, que[N * 20], dis[M][2], vis[N];
void spfa(int k)
{
	memset(vis, 0, sizeof(vis));
	head = 1, tail = 0;
	que[++tail] = x, vis[x] = 1, dis[x][k] = 0;
	while (head <= tail)
	{
		int u = que[head++];
		vis[u] = 0;
		for (int i = st[u][k]; i; i = nx[i][k])
		{
			int v = to[i][k];
			if (dis[u][k] + len[i][k] < dis[v][k])
			{
				dis[v][k] = dis[u][k] + len[i][k];
				if (!vis[v]) que[++tail] = v, vis[v] = 1;
			}
		}
	}
}

int main()
{
	scanf("%d%d%d", &n, &m, &x);
	for (int i = 1; i <= m; i++)
	{
		scanf("%d%d%d", &u, &v, &w);
		add(u, v, w, 0), add(v, u, w, 1);
	}
	memset(dis, 0x3f, sizeof(dis));
	spfa(0), spfa(1);
	ans = 0;
	for (int i = 1; i <= n; i++) if (i != x) ans = max(ans, dis[i][0] + dis[i][1]);
	printf("%d\n", ans);
	return 0;
}
