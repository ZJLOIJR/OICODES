#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

int st[1200010], to[1200010], nx[1200010], val[1200010];
int m, k, l, n, tot = 0, cnt = 1;
char str[51], ch[1200010];
int f[1200010][51];

inline void add(int u, int v) { to[++tot] = v, nx[tot] = st[u], st[u] = tot; }
inline int max(int a, int b) { return a > b ? a : b; }

void dfs(int x)
{
	f[x][0] = 0;
	for (int i = st[x]; i; i = nx[i])
	{
		int v = to[i];
		dfs(v);
		for (int j = n; j >= 0; j--)
			for (int k = 0; k <= j; k++)
				f[x][j] = max(f[x][j], f[x][j - k] + f[v][k]);
	}
	for (int i = 1; i <= n; i++)
		f[x][i] += val[x];
}

int main()
{
	scanf("%d%d%d%d", &m, &k, &l, &n);
	for (int i = 1; i <= m; i++)
	{
		scanf("%s", str);
		int now = 1; char *s = str;
		while (*s != '\0')
		{
			int p = 0;
			for (int i = st[now]; i; i = nx[i])
				if (*s == ch[to[i]]) { p = 1, now = to[i]; break; }
			if (!p)
			{
				add(now, ++cnt);
				now = cnt, ch[cnt] = *s;
			}
			s++;
		}
		val[now] = 1;
	}
	dfs(1);
	printf("%d\n", f[1][n]);
	return 0;
}
