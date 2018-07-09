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

const int N = 5e4 + 7;

int n, m, a, b, x, ans = 0;
int fa[N], d[N];

int getfa(int x)
{
	if (fa[x] == x) return x;
	int father = getfa(fa[x]);
	d[x] = (d[x] + d[fa[x]]) % 300;
	return fa[x] = father;
}

int main()
{
	n = read(), m = read();
	for (int i = 1; i <= n; i++) fa[i] = i, d[i] = 0;
	while (m--)
	{
		a = read(), b = read(), x = read();
		int u = getfa(a), v = getfa(b);
		if (u != v)
		{
			if ((x + d[b]) % 300 > d[a]) fa[u] = v, d[u] = ((x + d[b]) % 300 - d[a]);
			else if ((x + d[b]) % 300 < d[a]) fa[v] = u, d[v] = (d[a] - (x + d[b]) % 300);
			else if ((x + d[b]) % 300 == d[a]) fa[u] = v, d[u] = 0;
		}
		else
		{
			if (d[a] > d[b] && x != d[a] - d[b]) ans++;
			else if (d[a] < d[b] && x != 300 - (d[b] - d[a])) ans++;
			else if (d[a] == d[b] && x != 0) ans++;
		}
	}
	printf("%d\n", ans);
	return 0;
}
