#include <cstdio>
#include <cstring>
#include <cstdlib>

inline int read()
{
	int x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + (c ^ '0');
	return f ? -x : x;
}
inline int min(int a, int b) { return a < b ? a : b; }

const int N = 5e3 + 7, M = 5e4 + 7;

int n, m, s, t, tot = 1;
int st[N], to[N << 1], nx[N << 1], cost[N << 1], len[N << 1];

inline void add(int u, int v, int l, int c)
{
	to[++tot] = v, nx[tot] = st[u], st[u] = tot, len[tot] = l, cost[tot] = c;
	to[++tot] = u, nx[tot] = st[v], st[v] = tot, len[tot] = 0, cost[tot] = -c;
}

int head, tail, que[N * 20], dis[N], pre[N], vis[N], minflow[N];
int bfs()
{
	head = 1, tail = 0;
	memset(dis, 0x3f, sizeof(dis));
	memset(pre, 0, sizeof(pre));
	memset(vis, 0, sizeof(vis));
	memset(minflow, 0, sizeof(minflow));
	que[++tail] = s, dis[s] = 0, vis[s] = 1, minflow[s] = 0x3f3f3f3f, pre[s] = 0;
	while (head <= tail)
	{
		int u = que[head++];
		vis[u] = 0;
		for (int i = st[u]; i; i = nx[i])
		{
			int v = to[i];
			if (min(minflow[u], len[i]) > minflow[v] || (min(minflow[u], len[i]) == minflow[v] && dis[u] + cost[i] < dis[v]))
			{
				minflow[v] = min(minflow[u], len[i]), dis[v] = dis[u] + cost[i], pre[v] = i;
				if (!vis[v]) que[++tail] = v, vis[v] = 1;
			}
		}
	}
	return minflow[t];
}

int upd(int f)
{
	int now = t;
	while (now != s) len[pre[now]] -= f, len[pre[now] ^ 1] += f, now = to[pre[now] ^ 1];
	return f * dis[t];
}

int main()
{
	n = read(), m = read(), s = read(), t = read();
	for (int i = 1; i <= m; i++) add(read(), read(), read(), read());
	int ans = 0, flow, ret = 0;
	while (flow = bfs()) ans += upd(flow), ret += flow;
	printf("%d %d\n", ret, ans);
	return 0;
}
