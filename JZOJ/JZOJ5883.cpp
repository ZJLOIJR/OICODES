#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int N = 1e5 + 7;
inline int read()
{
	int x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + (c ^ '0');
	return f ? -x : x;
}

int n, m, q;
int qu[N], qv[N], typ[N];

int fa[N];
int getfa(int x) { return fa[x] == x ? x : fa[x] = getfa(fa[x]); }

int tot, st[N], to[N << 1], nx[N << 1], anc[N][18], dep[N];
void add(int u, int v) { to[++tot] = v, nx[tot] = st[u], st[u] = tot; }

void dfs(int u)
{
	for (int i = st[u]; i; i = nx[i])
		if (to[i] != anc[u][0])
			dep[to[i]] = dep[u] + 1, anc[to[i]][0] = u, dfs(to[i]);
}

int getlca(int u, int v)
{
	if (dep[u] < dep[v]) swap(u, v);
	for (int i = 17; i >= 0; i--) if (dep[anc[u][i]] >= dep[v]) u = anc[u][i];
	if (u == v) return u;
	for (int i = 17; i >= 0; i--) if (anc[u][i] != anc[v][i]) u = anc[u][i], v = anc[v][i];
	return anc[u][0];
}

int main()
{
	//freopen("arrival.in", "r", stdin);
	//freopen("arrival.out", "w", stdout);

	n = read(), m = read();
	for (int i = 1; i <= n; i++) fa[i] = i;
	for (int i = 1, r; i <= m; i++) r = read();
	for (int i = 1, u, v; i <= n - m; i++) u = read(), v = read(), fa[getfa(u)] = getfa(v), add(u, v), add(v, u);
	q = read();
	for (int i = 1; i <= q; i++)
	{
		typ[i] = read(), qu[i] = read(), qv[i] = read();
		if (typ[i] == 1)
		{
			qu[i] = getfa(qu[i]), qv[i] = getfa(qv[i]);
			fa[qv[i]] = qu[i], add(qu[i], qv[i]), add(qv[i], qu[i]);
		}
	}
	for (int i = 1; i <= n; i++) if (!dep[i]) dep[i] = 1, dfs(i);
	for (int j = 1; j <= 17; j++)
		for (int i = 1; i <= n; i++)
			anc[i][j] = anc[anc[i][j - 1]][j - 1];
	for (int i = 1; i <= n; i++) fa[i] = i;
	for (int i = 1; i <= q; i++)
	{
		if (typ[i] == 1) fa[getfa(qv[i])] = getfa(qu[i]);
		else
		{
			if (getfa(qu[i]) != getfa(qv[i])) printf("orzorz\n");
			else
			{
				int root = getfa(qu[i]), mxdep = 0, x, ans;
				ans = getlca(qu[i], qv[i]), mxdep = dep[ans];
				x = getlca(qu[i], root);
				if (dep[x] > mxdep) mxdep = dep[x], ans = x;
				x = getlca(qv[i], root);
				if (dep[x] > mxdep) mxdep = dep[x], ans = x;
				printf("%d\n", x);
			}
		}
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
