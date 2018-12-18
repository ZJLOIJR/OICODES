#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long ll;
const int N = 250007;
const ll INF = (1ll << 60);
inline ll read()
{
	ll x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + (c ^ '0');
	return f ? -x : x;
}
ll min(ll a, ll b) { return a < b ? a : b; }
void swap(int &a, int &b) { int t = a; a = b, b = t; }

int n, q;

struct Tree
{
	int tot, st[N], to[N << 1], nx[N << 1], len[N << 1];
	void add(int u, int v, int w) { to[++tot] = v, nx[tot] = st[u], len[tot] = w, st[u] = tot; }
} T1, T2;

int tid, dfn[N], dep[N], anc[N][19];
ll val[N];
void dfs(int u)
{
	dfn[u] = ++tid;
	for (int i = T1.st[u], v; i; i = T1.nx[i])
	{
		v = T1.to[i];
		if (v != anc[u][0]) dep[v] = dep[u] + 1, anc[v][0] = u, val[v] = min(val[u], T1.len[i]), dfs(v);
	}
}

int getlca(int u, int v)
{
	if (dep[u] < dep[v]) swap(u, v);
	for (int i = 18; i >= 0; i--) if (dep[anc[u][i]] >= dep[v]) u = anc[u][i];
	if (u == v) return u;
	for (int i = 18; i >= 0; i--) if (anc[u][i] != anc[v][i]) u = anc[u][i], v = anc[v][i];
	return anc[u][0];
}

int top, k, arr[N], stk[N];
int cmp(int a, int b) { return dfn[a] < dfn[b]; }
ll dp(int u)
{
	if (!T2.st[u]) return val[u];
	ll sum = 0;
	for (int i = T2.st[u], v; i; i = T2.nx[i]) sum += dp(T2.to[i]);
	T2.st[u] = 0;
	return min(sum, val[u]);
}
void doit()
{
	sort(arr + 1, arr + k + 1, cmp);
	top = 0;
	stk[++top] = 1;
	for (int i = 1, lca; i <= k; i++)
	{
		if (top == 1) { stk[++top] = arr[i]; continue; }
		lca = getlca(arr[i], stk[top]);
		if (lca == stk[top]) continue;
		while (dfn[lca] < dfn[stk[top]])
		{
			if (dfn[lca] >= dfn[stk[top - 1]])
			{
				T2.add(lca, stk[top], 1);
				if (stk[--top] != lca) stk[++top] = lca;
				break;
			}
			T2.add(stk[top - 1], stk[top], 1), top--;
		}
		stk[++top] = arr[i];
	}
	while (top > 1) T2.add(stk[top - 1], stk[top], 1), top--;
	printf("%lld\n", dp(1));
	T2.tot = 0;
}

int main()
{
	T1.tot = 0;
	n = read();
	for (int i = 1, u, v, w; i < n; i++) u = read(), v = read(), w = read(), T1.add(u, v, w), T1.add(v, u, w);
	val[1] = INF, dep[1] = 1, dfs(1);
	for (int j = 1; j <= 18; j++) for (int i = 1; i <= n; i++) anc[i][j] = anc[anc[i][j - 1]][j - 1];
	q = read();
	while (q--)
	{
		k = read();
		for (int i = 1; i <= k; i++) arr[i] = read();
		doit();
	}
	return 0;
}
