#include <cmath>
#include <vector>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;

const int N = 300000;

int n, m, u, v, tot = 0;
int st[N], to[N << 1], nx[N << 1], f[N][30], dep[N];
int w[N], s[N], t[N], ans[N], lca[N], start[N];
int bucket[N << 1];
vector<int> V1[N], V2[N], V3[N];

inline int read()
{
	int x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + c - '0';
	return f ? -x : x;
}
inline void add(int u, int v) { to[++tot] = v, nx[tot] = st[u], st[u] = tot; }
inline void swap(int& a, int& b) { int t = a; a = b, b = t; }

void dfs_pre(int u)
{
	for (int i = st[u]; i; i = nx[i])
	{
		int v = to[i];
		if (v != f[u][0]) dep[v] = dep[u] + 1, f[v][0] = u, dfs_pre(v);
	}
}

void LCA_pre()
{
	for (int j = 1; j <= 20; j++)
		for (int i = 1; i <= n; i++)
			f[i][j] = f[f[i][j - 1]][j - 1];
}

int LCA(int u, int v)
{
	if (dep[u] < dep[v]) swap(u, v);
	for (int i = 20; i >= 0; i--) if (dep[f[u][i]] >= dep[v]) u = f[u][i];
	if (u == v) return u;
	for (int i = 20; i >= 0; i--) if (f[u][i] != f[v][i]) u = f[u][i], v = f[v][i];
	return f[u][0];
}

int getson(int u, int v)
{
	if (dep[u] < dep[v]) swap(u, v);
	for (int i = 20; i >= 0; i--) if (dep[f[u][i]] > dep[v]) u = f[u][i];
	return u;
}

void init()
{
	n = read(), m = read();
	for (int i = 1; i <= n - 1; i++) u = read(), v = read(), add(u, v), add(v, u);
	dep[1] = 1, f[1][0] = 0, dfs_pre(1); LCA_pre();
	for (int i = 1; i <= n; i++) *(w + i) = read();
	for (int i = 1; i <= m; i++)
	{
		*(s + i) = read(), *(t + i) = read(), lca[i] = LCA(s[i], t[i]);
		start[s[i]]++;
		V1[lca[i]].push_back(s[i]);
		V2[t[i]].push_back(dep[s[i]] - (dep[lca[i]] << 1));
		V3[lca[i]].push_back(dep[s[i]] - (dep[lca[i]] << 1));
	}
}

void dfs1(int u)
{
	int pre = bucket[dep[u] + w[u] + N];
	for (int i = st[u]; i; i = nx[i]) if (to[i] != f[u][0]) dfs1(to[i]);
	bucket[dep[u] + N] += start[u];
	ans[u] += bucket[dep[u] + w[u] + N] - pre;
	int l = V1[u].size();
	for (int i = 0; i < l; i++) bucket[dep[V1[u][i]]]--;
}

void dfs2(int u)
{
	int pre = bucket[w[u] - dep[u] + N];
	for (int i = st[u]; i; i = nx[i]) if (to[i] != f[u][0]) dfs2(to[i]);
	int l = V2[u].size();
	for (int i = 0; i < l; i++) bucket[V2[u][i] + N]++;
	ans[u] += bucket[w[u] - dep[u] + N] - pre;
	l = V3[u].size();
	for (int i = 0; i < l; i++) bucket[V3[u][i] + N]--;
}

void solve()
{
	dfs1(1);
	dfs2(1);
	for (int i = 1; i <= m; i++) if (dep[s[i]] == dep[lca[i]] + w[lca[i]]) ans[lca[i]]--;
	for (int i = 1; i <= n; i++) printf("%d ", ans[i]);
	printf("\n");
}

int main()
{
	freopen("running.in", "r", stdin);
	//freopen("running.out", "w", stdout);

	init();
	solve();

	fclose(stdin);
	fclose(stdout);
	return 0;
}