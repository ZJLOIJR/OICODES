#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 250007, INF = 0x3f3f3f3f;
inline int read()
{
	int x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + (c ^ '0');
	return f ? -x : x;
}
int min(int a, int b) { return a < b ? a : b; }
void swap(int &a, int &b) { int t = a; a = b, b = t; }

int n, q, k;

struct Tree
{
	int tot, st[N], to[N << 1], nx[N << 1], len[N << 1];
	void add(int u, int v, int w) { to[++tot] = v, nx[tot] = st[u], len[tot] = w, st[u] = tot; }
} T1, T2;

int tid, dfn[N], dep[N], anc[N][19], mi[N][19];
void dfs(int u)
{
	dfn[u] = ++tid;
	for (int i = T1.st[u], v; i; i = T1.nx[i])
	{
		v = T1.to[i];
		if (v != anc[u][0]) dep[v] = dep[u] + 1, anc[v][0] = u, mi[v][0] = T1.len[i], dfs(v);
	}
}

void getlca(int u, int v, int &lca, int &minv)
{
	if (dep[u] < dep[v]) swap(u, v);
	minv = INF;
	for (int i = 20; i >= 0; i--) if (dep[anc[u][i]] >= dep[v]) minv = min(minv, mi[u][i]), u = anc[u][i];
	if (u == v) { lca = u; return; }
	for (int i = 20; i >= 0; i--) if (anc[u][i] != anc[v][i]) minv = min(minv, min(mi[u][i], mi[v][i])), u = anc[u][i], v = anc[v][i];
	minv = min(minv, mi[u][0]), lca = anc[u][0];
}

int 
void dp(int u)
{
}

int top, k, arr[N], vis[N], stk[N];
int cmp(int a, int b) { return dfn[a] < dfn[b]; }
void doit()
{
	sort(arr + 1, arr + k + 1, cmp);
	for (int i = 1; i <= k; i++) vis[arr[i]] = 1;
	top = 0;
	for (int i = 1, lca, minv, tmp; i <= k; i++)
	{
		if (!top) { stk[++top] = arr[i]; continue; }
		getlca(arr[i], stk[top], lca, minv);
		while (dfn[lca] < dfn[stk[top]])
		{
			if (dfn[lca] >= dfn[stk[top - 1]])
			{
				getlca(lca, stk[top], tmp, minv);
				T2.add(lca, stk[top], minv);
				if (stk[--top] != lca) stk[++top] = lca;
				break;
			}
			getlca(lca, stk[top], tmp, minv);
			T2.add(stk[top - 1], stk[top], minv);
			top--;
		}
		stk[++top] = arr[i];
	}
	dp();
	for (int i = 1; i <= k; i++) vis[arr[i]] = 0;
	T2.tot = 0;
}

int main()
{
	T1.tot = 0;
	n = read();
	for (int i = 1, u, v, w; i < n; i++) u = read(), v = read(), w = read(), T1.add(u, v, w), T1.add(v, u, w);
	dfs(1);
	for (int j = 1; j <= 18; j++)
		for (int i = 1; i <= n; i++)
			anc[i][j] = anc[anc[i][j - 1]][j - 1], mi[i][j] = min(mi[i][j - 1], mi[anc[i][j - 1]][j - 1]);
	q = read();
	while (q--)
	{
		k = read();
		for (int i = 1; i <= k; i++) arr[i] = read();
		doit();
	}
	return 0;
}
