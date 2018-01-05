#include <cstdio>
#include <cstring>

const int N = 50007, M = 500007;

int n, m, u, v, tot = 0;
int st[N], to[M << 1], nx[M << 1], vis[N], col[N];

inline int read()
{
	int x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + c - '0';
	return f ? -x : x;
}

void add(int u, int v) { to[++tot] = v, nx[tot] = st[u], st[u] = tot; }

int dfs(int u)
{
	for (int i = st[u]; i; i = nx[i])
	{
		int v = to[i];
		if (~col[v] && col[v] != col[u] ^ 1)
			return 0;
		if (~col[v])
			continue;
		col[v] = col[u] ^ 1;
		if (!dfs(v))
			return 0;
	}
	return 1;
}

int main()
{
	memset(vis, 0, sizeof(vis));
	memset(col, 0xff, sizeof(col));
	n = read(), m = read();
	while (m--)
	{
		u = read(), v = read();
		add(u, v), add(v, u);
	}
	for (int i = 1; i <= n; i++)
		if (~col[i])
			continue;
		else
		{
			col[i] = 1;
			if (!dfs(i))
			{
				printf("IMPOSSIBLE\n");
				return 0;
			}
		}
	for (int i = 1; i <= n; i++)
		if (col[i] || col[i] == -1)
			printf("%d ", i);
	putchar('\n');
	for (int i = 1; i <= n; i++)
		if (!col[i])
			printf("%d ", i);
	return 0;
}
