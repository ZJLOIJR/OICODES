#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 5e3 + 3, M = 1e5 + 3;

inline int read()
{
	int x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + (c ^ '0');
	return f ? -x : x;
}

int n, m, u, v, w, head, tail, tot = 0;
int st[N], to[M << 1], nx[M << 1], len[M << 1], dis[N][2], que[N * 20], vis[N];

inline void add(int u, int v, int w) { to[++tot] = v, nx[tot] = st[u], len[tot] = w, st[u] = tot; }

int main()
{
	freopen("block.in", "r", stdin);
	freopen("block.out", "w", stdout);

	memset(dis, 0x3f, sizeof(dis));
	memset(vis, 0, sizeof(vis));
	n = read(), m = read();
	for (int i = 1; i <= m; i++) u = read(), v = read(), w = read(), add(u, v, w), add(v, u, w);
	head = 1, tail = 0;
	que[++tail] = 1, vis[1] = 1, dis[1][0] = 0;
	while (head <= tail)
	{
		int u = que[head++];
		vis[u] = 0;
		for (int i = st[u]; i; i = nx[i])
		{
			int v = to[i];
			if (dis[u][0] + len[i] < dis[v][0])
			{
				dis[v][0] = dis[u][0] + len[i];
				if (!vis[v]) que[++tail] = v, vis[v] = 1;
			}
			if (dis[u][0] + len[i] > dis[v][0] && dis[u][0] + len[i] < dis[v][1]) dis[v][1] = dis[u][0] + len[i];
		}
	}
	printf("%d\n", dis[n][1]);

	fclose(stdin);
	fclose(stdout);
	return 0;
}
