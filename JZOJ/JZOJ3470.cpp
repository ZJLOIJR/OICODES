#include <queue>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;

typedef long long ll;
const int N = 5e4 + 7, M = 1e5 + 7, K = 12;
const ll INF = 0x3f3f3f3f3f3f3f3f;
inline int read()
{
	int x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + (c ^ '0');
	return f ? -x : x;
}
inline ll min(int a, int b) { return a < b ? a : b; }

struct note { int x; ll val; };
int operator<(note p, note q) { return p.val > q.val; }
priority_queue<note> heap;
int n, m, k, s, t, tot = 0, st[N], to[M], nx[M], pre[N], vis[N];
ll dis[N], len[M];

inline void add(int u, int v, int w) { to[++tot] = v, nx[tot] = st[u], len[tot] = w, st[u] = tot; }
void Dijkstra(int x)
{
	memset(dis, 0x3f, sizeof(dis));
	memset(pre, 0, sizeof(pre));
	memset(vis, 0, sizeof(vis));
	while (!heap.empty()) heap.pop();
	dis[x] = 0, heap.push((note){x, 0});
	while (!heap.empty())
	{
		note tmp = heap.top();
		heap.pop();
		int u = tmp.x;
		if (vis[u]) continue;
		vis[u] = 1;
		for (int i = st[u]; i; i = nx[i])
		{
			int v = to[i];
			if (dis[u] + len[i] < dis[v]) pre[v] = u, dis[v] = dis[u] + len[i], heap.push((note){v, dis[v]});
		}
	}
}

int full, arr[K + 7];
ll length[K + 7][K + 7], f[1 << K][K + 7];
inline int bit(int n) { return (1 << (n - 1)); }

int main()
{
	n = read(), m = read(), k = read(), s = read(), t = read();
	arr[1] = s, arr[2] = t;
	for (int i = 1, x, y, z; i <= m; i++) x = read(), y = read(), z = read(), add(x, y, z);
	for (int i = 1; i <= k; i++) arr[i + 2] = read();
	k += 2;
	for (int i = 1; i <= k; i++)
	{
		Dijkstra(arr[i]);
		for (int j = 1; j <= k; j++) if (i != j) length[i][j] = dis[arr[j]];
	}
	memset(f, 0x3f, sizeof(f));
	full = (1 << k) - 1;
	f[bit(1)][s] = 0;
	for (int S = 1; S <= full; S++)
		for (int i = 1; i <= k; i++)
			if ((S & bit(i)) && f[S][i] != INF)
				for (int j = 1; j <= k; j++)
				{
					if (i == j) continue;
					f[S | bit(j)][j] = min(f[S | bit(j)][j], f[S][i] + length[i][j]);
				}
	if (f[full][2] == INF) printf("-1\n");
	else printf("%lld\n", f[full][2]);
	return 0;
}
