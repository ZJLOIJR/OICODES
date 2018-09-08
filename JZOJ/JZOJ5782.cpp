#include <cstdio>
#include <cstring>
#include <cstdlib>

inline int read()
{
	int x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + (c ^ '0');
	return f ? -x : x;
}
inline int max(int a, int b) { return a > b ? a : b; }
const int N = 1e5 + 7;

int n, m, q, u, v, tmp;
int fa[N], size[N], val[N], vis[N], mx[N];

int getfa(int x) { return fa[x] == x ? x : getfa(fa[x]); }
void link(int p, int q, int v)
{
	p = getfa(p), q = getfa(q);
	if (p == q) return;
	if (size[p] < size[q]) fa[p] = q, val[p] = v, size[q] += size[p];
	else fa[q] = p, val[q] = v, size[p] += size[q];
}

int main()
{
	freopen("pictionary.in", "r", stdin);
	freopen("pictionary.out", "w", stdout);
	
	n = read(), m = read(), q = read();
	for (int i = 1; i <= n; i++) fa[i] = i, size[i] = 1;
	for (int i = 1; i <= m; i++)
	{
		int t = m - i + 1;
		for (int j = t + t; j <= n; j += t) link(t, j, i);
	}
	while (q--)
	{
		u = read(), v = read(), tmp = u;
		vis[u] = 1;
		while (fa[u] != u) vis[fa[u]] = 1, mx[fa[u]] = max(mx[u], val[u]), u = fa[u];
		int ans = 0;
		while (!vis[v]) ans = max(ans, val[v]), v = fa[v];
		printf("%d\n", max(ans, mx[v]));
		vis[tmp] = 0;
		while (fa[tmp] != tmp) vis[fa[tmp]] = mx[fa[tmp]] = 0, tmp = fa[tmp];
	}
	
	fclose(stdin);
	fclose(stdout);
	return 0;
}
