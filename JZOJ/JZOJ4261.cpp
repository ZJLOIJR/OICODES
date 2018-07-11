#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

typedef long long ll;
const int N = 1e5 + 7, M = 2e5 + 7;

inline ll read()
{
	ll x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + (c ^ '0');
	return f ? -x : x;
}

int n, m;
int tot = 0, col[N], st[N], to[M << 2], nx[M << 2];
ll len[M << 2];

inline void add(int u, int v, ll w) { to[++tot] = v, nx[tot] = st[u], len[tot] = w, st[u] = tot; }

void init()
{
	n = read(), m = read();
	for (int i = 1; i <= n; i++)
	{
		col[i] = read();
		if (col[i]) add(n + 1, i, 0), add(i, n + 1, 0);
	}
	for (int i = 1, u, v, w; i <= m; i++) u = read(), v = read(), w = read(), add(u, v, w), add(v, u, w);
}

int head, tail, que[N * 20], vis[N];
ll dis[N];
void spfa()
{
	head = 1, tail = 0;
	memset(dis, 0x3f, sizeof(dis));
	memset(vis, 0, sizeof(vis));
	que[++tail] = n + 1, dis[n + 1] = 0, vis[n + 1] = 1;
	while (head <= tail)
	{
		int u = que[head++];
		vis[u] = 0;
		for (int i = st[u]; i; i = nx[i])
		{
			int v = to[i];
			if (dis[u] + len[i] < dis[v])
			{
				dis[v] = dis[u] + len[i];
				if (!vis[v]) que[++tail] = v, vis[v] = 1;
			}
		}
	}
}

struct edge { int from, to, len; } e[M];
int cnt = 0, fa[N];
inline int getfa(int x) { return fa[x] == x ? x : fa[x] = getfa(fa[x]); }
void build_graph()
{
	for (int u = 1; u <= n; u++)
		for (int i = st[u]; i; i = nx[i])
			if (dis[u] + len[i] == dis[to[i]])
				e[++cnt] = (edge){u, to[i], len[i]};
}

int cmp(edge p, edge q) { return p.len < q.len; }
void kruskal()
{
	sort(e + 1, e + cnt + 1, cmp);
	int count = 0;
	ll ans = 0;
	for (int i = 1; i <= n + 1; i++) fa[i] = i;
	for (int i = 1; i <= cnt; i++)
	{
		int u = getfa(e[i].from), v = getfa(e[i].to);
		if (u != v) fa[v] = u, count++, ans += e[i].len;
		if (count == n) break;
	}
	if (count < n) printf("impossible\n");
	else printf("%lld\n", ans);
}

int main()
{
	init();
	spfa();
	build_graph();
	kruskal();
	return 0;
}
