#include <vector>
#include <cstdio>
#include <cstring>
using namespace std;
inline int read()
{
	int x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + (c ^ '0');
	return f ? -x : x;
}

const int N = 3e5 + 7;

int n, m, u, v;
int tot = 0, st[N], to[N << 1], nx[N << 1], anc[N][21], dep[N], w[N], ans[N];
struct note { int type, dir, depth; };
vector<note> ques[N];

inline void add(int u, int v) { to[++tot] = v, nx[tot] = st[u], st[u] = tot; }

void dfs1(int u)
{
	for (int i = st[u]; i; i = nx[i])
		if (to[i] != anc[u][0])
			dep[to[i]] = dep[u] + 1, anc[to[i]][0] = u, dfs1(to[i]);
}
int getlca(int u, int v)
{
	if (dep[u] < dep[v]) u ^= v ^= u ^= v;
	for (int i = 20; i >= 0; i--) if (dep[anc[u][i]] >= dep[v]) u = anc[u][i];
	if (u == v) return u;
	for (int i = 20; i >= 0; i--) if (anc[u][i] != anc[v][i]) u = anc[u][i], v = anc[v][i];
	return anc[u][0];
}
int getson(int u, int v)
{
	for (int i = 20; i >= 0; i--) if (dep[anc[u][i]] > dep[v]) u = anc[u][i];
	return u;
}

int buc1[N << 1], buc2[N << 1];
void dfs2(int u)
{
	int a = buc1[dep[u] + w[u]], b = buc2[dep[u] - w[u] + N];
	int len = ques[u].size();
	for (int i = 0; i < len; i++)
		if (ques[u][i].type == 1)
			if (ques[u][i].dir == 1) buc1[ques[u][i].depth]++; else buc2[ques[u][i].depth]++;
	for (int i = st[u]; i; i = nx[i]) if (to[i] != anc[u][0]) dfs2(to[i]);
	ans[u] = buc1[dep[u] + w[u]] - a + buc2[dep[u] - w[u] + N] - b;
	for (int i = 0; i < len; i++)
		if (ques[u][i].type == -1)
			if (ques[u][i].dir == 1) buc1[ques[u][i].depth]--; else buc2[ques[u][i].depth]--;
}

int main()
{
	freopen("running.in", "r", stdin);
	freopen("running.out", "w", stdout);

	n = read(), m = read();
	for (int i = 1; i < n; i++) u = read(), v = read(), add(u, v), add(v, u);
	dep[1] = 1, dfs1(1); for (int j = 1; j <= 20; j++) for (int i = 1; i <= n; i++) anc[i][j] = anc[anc[i][j - 1]][j - 1];
	for (int i = 1; i <= n; i++) w[i] = read();
	for (int i = 1; i <= m; i++)
	{
		u = read(), v = read();
		int lca = getlca(u, v), son = getson(v, lca);
		ques[u].push_back((note){1, 1, dep[u]}), ques[lca].push_back((note){-1, 1, dep[u]});
		if (v != lca) ques[v].push_back((note){1, 2, 2 * dep[lca] - dep[u] + N}), ques[son].push_back((note){-1, 2, 2 * dep[lca] - dep[u] + N});
	}
	dfs2(1);
	for (int i = 1; i <= n; i++) printf("%d ", ans[i]);

	fclose(stdin);
	fclose(stdout);
	return 0;
}
