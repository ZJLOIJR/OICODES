#include <vector>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int N = 3e5 + 7;
inline int read()
{
	int x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + (c ^ '0');
	return f ? -x : x;
}

int n, m, w[N];

int tot, st[N], to[N << 1], nx[N << 1], dep[N], anc[N][19];
void add(int u, int v) { to[++tot] = v, nx[tot] = st[u], st[u] = tot; }
void dfs(int u)
{
	for (int i = st[u]; i; i = nx[i])
		if (to[i] != anc[u][0])
			dep[to[i]] = dep[u] + 1, anc[to[i]][0] = u, dfs(to[i]);
}
int findlca(int u, int v)
{
	if (dep[u] < dep[v]) swap(u, v);
	for (int i = 18; i >= 0; i--) if (dep[anc[u][i]] >= dep[v]) u = anc[u][i];
	if (u == v) return u;
	for (int i = 18; i >= 0; i--) if (anc[u][i] != anc[v][i]) u = anc[u][i], v = anc[v][i];
	return anc[u][0];
}

struct note { int typ, d, val; };
vector<note> notes[N];
int ans[N], buc1[N], buc2[N << 1];

void init()
{
	n = read(), m = read();
	for (int i = 1, u, v; i < n; i++) u = read(), v = read(), add(u, v), add(v, u);
	dep[1] = 1, dfs(1);
	for (int j = 1; j <= 18; j++)
		for (int i = 1; i <= n; i++)
			anc[i][j] = anc[anc[i][j - 1]][j - 1];
	for (int i = 1; i <= n; i++) w[i] = read();
	for (int i = 1, u, v, lca; i <= m; i++)
	{
		u = read(), v = read(), lca = findlca(u, v);
		notes[u].push_back((note){1, dep[u], 1});
		notes[v].push_back((note){2, dep[u] - 2 * dep[lca], 1});
		notes[lca].push_back((note){1, dep[u], -1});
		notes[anc[lca][0]].push_back((note){2, dep[u] - 2 * dep[lca], -1});
	}
}

void getans(int u)
{
	int siz = notes[u].size(), a = buc1[w[u] + dep[u]], b = buc2[w[u] - dep[u] + N];
	for (int i = 0; i < siz; i++)
	{
		if (notes[u][i].typ == 1) buc1[notes[u][i].d] += notes[u][i].val;
		else buc2[notes[u][i].d + N] += notes[u][i].val;
	}
	for (int i = st[u]; i; i = nx[i])
		if (to[i] != anc[u][0])
			getans(to[i]);
	ans[u] = buc1[w[u] + dep[u]] - a + buc2[w[u] - dep[u] + N] - b;
}

void solve()
{
	getans(1);
	for (int i = 1; i <= n; i++) printf("%d ", ans[i]);
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
