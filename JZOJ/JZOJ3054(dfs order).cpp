#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 4e4 + 3;

int n, u, v, q, root, tot = 0, cnt = 0;
int st[N], to[N << 1], nx[N << 1], tid[N], siz[N];

inline int read()
{
	int x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + (c ^ '0');
	return f ? -x : x;
}
inline void add(int u, int v) { to[++tot] = v, nx[tot] = st[u], st[u] = tot; }

void dfs(int u, int from)
{
	tid[u] = ++cnt, siz[u] = 1;
	for (int i = st[u]; i; i = nx[i])
	{
		int v = to[i];
		if (v != from)
		{
			dfs(v, u);
			siz[u] += siz[v];
		}
	}
}

void init()
{
	n = read();
	for (int i = 1; i <= n; i++)
	{
		u = read(), v = read();
		if (v == -1) root = u;
		else add(u, v), add(v, u);
	}
	dfs(root, 0);
}

void solve()
{
	q = read();
	while (q--)
	{
		u = read(), v = read();
		if (tid[u] <= tid[v] && tid[v] <= tid[u] + siz[u] - 1) printf("1\n");
		else if (tid[v] <= tid[u] && tid[u] <= tid[v] + siz[v] - 1) printf("2\n");
		else printf("0\n");
	}
}

int main()
{
	init();
	solve();
	return 0;
}
