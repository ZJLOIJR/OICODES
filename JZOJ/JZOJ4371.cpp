#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
inline int read()
{
	int x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + (c ^ '0');
	return f ? -x : x;
}
inline int min(int a, int b) { return a < b ? a : b; }
inline int max(int a, int b) { return a > b ? a : b; }

typedef long long ll;
const int N = 2e2 + 7, INF = 0x3f3f3f3f;

struct edge { int to, dist; } c[N][N];
int cnt[N], edgepre[N];
int cmp(edge p, edge q) { return p.dist < q.dist; }

int n, m, a[N], b[N];
int tot = 1, st[N * 20], to[N * N * 20], nx[N * N * 20], len[N * N * 20];
ll ans, cost[N * N * 20];

inline void add(int u, int v, int w, int c)
{
	to[++tot] = v, nx[tot] = st[u], len[tot] = w, cost[tot] = c, st[u] = tot;
	to[++tot] = u, nx[tot] = st[v], len[tot] = 0, cost[tot] = -c, st[v] = tot;
}

ll dis[N * 20];
int head, tail, que[N * 10000], vis[N * 20], maxflow[N * 20], pre[N * 20], S, T;
int bfs()
{
	head = 1, tail = 0;
	memset(dis, 0x3f, sizeof(dis));
	memset(vis, 0, sizeof(vis));
	memset(pre, 0, sizeof(pre));
	memset(maxflow, 0, sizeof(maxflow));
	dis[S] = 0, que[++tail] = S, vis[S] = 1, maxflow[S] = INF;
	while (head <= tail)
	{
		int u = que[head++];
		vis[u] = 0;
		for (int i = st[u]; i; i = nx[i])
		{
			int v = to[i];
			if (len[i] > 0 && dis[u] + cost[i] < dis[v])
			{
				maxflow[v] = min(maxflow[u], len[i]), dis[v] = dis[u] + cost[i], pre[v] = i;
				if (!vis[v]) que[++tail] = v, vis[v] = 1;
			}
		}
	}
	return maxflow[T];
}

void solve()
{
	while (bfs())
	{
		int now = T;
		while (now) len[pre[now]] -= maxflow[T], len[pre[now] ^ 1] += maxflow[T], now = to[pre[now] ^ 1];
		for (int i = 1; i <= n; i++)
			while (!len[edgepre[c[i][cnt[i]].to]] && cnt[i] < m)
				cnt[i]++, add(i, c[i][cnt[i]].to + n, INF, c[i][cnt[i]].dist);
		ans += maxflow[T] * dis[T];
	}
	printf("%lld\n", ans);
}

void make_graph()
{
	S = 0, T = n + m + 1;
	for (int i = 1; i <= n; i++) add(S, i, a[i], 0);
	for (int i = 1; i <= m; i++) add(i + n, T, b[i], 0), edgepre[i] = tot - 1;
	for (int i = 1; i <= n; i++)
	{
		sort(c[i] + 1, c[i] + m + 1, cmp);
		add(i, c[i][1].to + n, INF, c[i][1].dist);
		cnt[i] = 1;
	}
}

void init()
{
	n = read(), m = read();
	for (int i = 1; i <= n; i++) a[i] = read();
	for (int i = 1; i <= m; i++) b[i] = read();
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			c[i][j].dist = read(), c[i][j].to = j;
}

int main()
{
	init();
	make_graph();
	solve();
	return 0;
}
