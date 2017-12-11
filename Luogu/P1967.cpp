#include <cstdio>
#include <algorithm>
using namespace std;

const int N = 10007, M = 50007;

int n, m, u, v, w, q, tot = 0;

int fa[N];
struct edg { int from, to, l; } e[M];

int st[N], to[N << 1], nx[N << 1], len[N << 1];
int jum[N][32], mi[N][32], dep[N], lg[N];

void add(int u, int v, int l)
{
	to[++tot] = v;
	nx[tot] = st[u];
	len[tot] = l;
	st[u] = tot;
}
////////////////input and sort part
void init()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++)
		scanf("%d%d%d", &e[i].from, &e[i].to, &e[i].l);

	sort(e + 1, e + m + 1, [](edg x, edg y)
			{
				return x.l < y.l;
			});

	for (int i = 1; i <= n; i++)
		fa[i] = i;
}
////////////////mst part
int getfa(int x)
{
	return fa[x] == x ? x : fa[x] = getfa(fa[x]);
}

void mst()
{
	int cnt = 0;
	for (int i = 1; i <= m; i++)
	{
		int u = getfa(e[i].from), v = getfa(e[i].to);
		if (u != v)
		{
			fa[v] = u;
			add(e[i].from, e[i].to, e[i].l);
			add(e[i].to, e[i].from, e[i].l);
			cnt++;
		}
		if (cnt == n - 1)
			return;
	}
}
///////////////solve part
inline int min(int a, int b) { return a < b ? a : b; }

void dfs(int u, int from)
{
	for (int i = st[u]; i; i = nx[i])
	{
		int v = to[i];
		if (v != from)
		{
			jum[v][0] = u;
			mi[v][0] = len[i];
			dep[v] = dep[u] + 1;
			dfs(v, u);
		}
	}
}
void LCA_PRE()
{
	lg[1] = 0;
	for (int i = 2; i <= n; i++)
		lg[i] = lg[i >> 1] + 1;

	dep[1] = 1;
	dfs(1, 0);
	for (int j = 1; j <= lg[n]; j++)
		for (int i = 1; i <= n; i++)
		{
			jum[i][j] = jum[jum[i][j - 1]][j - 1];
			mi[i][j] = min(mi[i][j - 1], mi[jum[i][j - 1]][j - 1]);
		}
}

void solve()
{
	LCA_PRE();
	scanf("%d", &q);
	while (q--)
	{
		scanf("%d%d", &u, &v);
		
		if (dep[u] < dep[v])
		{
			int t = u;
			u = v;
			v = t;
		}
		int f = dep[u] - dep[v], cnt = 0;
		int ans = 2147483647;
		while (f)
		{
			if (f & 1)
			{
				ans = min(ans, mi[u][cnt]);
				u = jum[u][cnt];
			}
			cnt++;
			f >>= 1;
		}
		if (u != v)
		{
			for (int i = lg[n]; i >= 0; i--)
				if (jum[u][i] != jum[v][i])
				{
					ans = min(ans, min(mi[u][i], mi[v][i]));
					u = jum[u][i], v = jum[v][i];
				}
			ans = min(ans, mi[u][0]);
		}

		printf("%d\n", ans);
	}
}

int main()
{
	init();
	mst();
	solve();
	return 0;
}
