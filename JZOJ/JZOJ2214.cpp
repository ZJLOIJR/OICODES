#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 1e5 + 3;

int n, u, v, tot = 0, ret = 0;
int st[N], to[N << 1], nx[N << 1];

inline void add(int u, int v) { to[++tot] = v, nx[tot] = st[u], st[u] = tot; }

inline void read(int& num)
{
	int x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + c - '0';
	num = f ? -x : x;
}

void dfs(int now, int from, int len)
{
	if (len > ret) u = now, ret = len;
	for (int i = st[now]; i; i = nx[i])
	{
		v = to[i];
		if (v != from)
			dfs(v, now, len + 1);
	}
}

int main()
{
	read(n);
	for (int i = 1; i <= n; i++)
	{
		read(u), read(v);
		if (u) add(i, u), add(u, i);
		if (v) add(i, v), add(v, i);
	}
	ret = 0;
	dfs(1, 0, 0);
	ret = 0;
	dfs(u, 0, 0);
	printf("%d\n", ret);
	return 0;
}