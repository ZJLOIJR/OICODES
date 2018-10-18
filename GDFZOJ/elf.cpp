#include <vector>
#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 1e5 + 7;
inline int read()
{
	int x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + (c ^ '0');
	return f ? -x : x;
}

int n, q;

int dfn, fa[N], tid[N], son[N], top[N], size[N], dep[N];
int tot, st[N], to[N], nx[N];

struct note { int val, id; };
vector<note>
int ans[N];

void add(int u, int v) { to[++tot] = v, nx[tot] = st[u], st[u] = tot; }
void dfs1(int u)
{
	int mxsiz = 0;
	size[u] = 1;
	for (int i = st[u]; i; i = nx[i])
		if (to[i] != fa[u])
		{
			dep[to[i]] = dep[u] + 1, fa[to[i]] = u, dfs1(to[i]), size[u] += size[to[i]];
			if (size[to[i]] > mxsiz) mxsiz = size[to[i]], son[u] = to[i];
		}
}

void dfs2(int u, int tp)
{
	tid[u] = ++dfn, top[u] = tp;
	if (son[u]) dfs2(son[u], tp);
	for (int i = st[u]; i; i = nx[i])
		if (to[i] != fa[u] && to[i] != son[u])
			dfs2(to[i], to[i]);
}

int main()
{
	n = read(), q = read();
	for (int i = 2, x; i <= n; i++) x = read(), add(x, i);
	dep[1] = 1, dfs1(1);
	dfs2(1, 1);
	for (int i = 1; i <= q; i++)
	return 0;
}
