#include <queue>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

typedef long long ll;
inline int read()
{
	int x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + (c ^ '0');
	return f ? -x : x;
}
const int N = 5e5 + 7, M = 2e6 + 7;

int n, m, S, T, ans1;
ll len[M], ans2;
int lene, tot, st[N], to[M], nx[M], temp[M];
struct edge { int from, to, len; } E[M >> 1];
int cmp(edge a, edge b) { return a.len < b.len; }
int fa[N];
int getfa(int x) { return fa[x] == x ? x : fa[x] = getfa(fa[x]); }

void add(int u, int v, int t, ll c)
{
	to[++tot] = v, nx[tot] = st[u], temp[tot] = t, len[tot] = t * c, st[u] = tot;
}

void init()
{
	n = read(), m = read();
	for (int i = 1, a, b, t, c; i <= m; i++)
		a = read(), b = read(), t = read(), c = read(), add(a, b, t, c), add(b, a, t, c), E[++lene] = (edge){a, b, t};
	S = read(), T = read();
}

int tot1, st1[N], nx1[N << 1], to1[N << 1], len1[N << 1];
void add1(int u, int v, int w) { to1[++tot1] = v, nx1[tot1] = st1[u], len1[tot1] = w, st1[u] = tot1; }
struct note { int id; ll val; };
int operator<(note a, note b) { return a.val > b.val; }
priority_queue<note> heap;
int vis[N]; ll dis[N];
void Dijkstra()
{
	memset(vis, 0, sizeof(vis));
	memset(dis, 0x3f, sizeof(dis));
	dis[S] = 0, heap.push((note){S, 0});
	while (!heap.empty())
	{
		note x = heap.top(); heap.pop();
		int u = x.id;
		if (vis[u]) continue;
		vis[u] = 1;
		for (int i = st[u]; i; i = nx[i])
			if (temp[i] <= ans1)
				if (dis[u] + len[i] < dis[to[i]])
					dis[to[i]] = dis[u] + len[i], heap.push((note){to[i], dis[to[i]]});
	}
	ans2 = dis[T];
}

void solve()
{
	sort(E + 1, E + lene + 1, cmp);
	for (int i = 1; i <= n; i++) fa[i] = i;
	for (int i = 1, cnt = 0, u, v; i <= m; i++)
	{
		u = getfa(E[i].from), v = getfa(E[i].to);
		if (u != v) fa[v] = u, cnt++, add1(E[i].from, E[i].to, E[i].len), add1(E[i].to, E[i].from, E[i].len);
		if (getfa(S) == getfa(T)) { ans1 = E[i].len; break; }
		if (cnt == n - 1) break;
	}
	Dijkstra();
	printf("%d %lld\n", ans1, ans2);
}

int main()
{
	freopen("running.in", "r", stdin);
	freopen("running.out", "w", stdout);
	init();
	solve();
	fclose(stdin);
	fclose(stdout);
	return 0;
}
