#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

typedef long long ll;
const int N = 10007, M = 100007;
const ll P = 1e9;

int n, m, u, v, tot = 0, flag = 0;
int st[N], to[M], nx[M], vis[N], p[N];
ll f[N];

void add(int u, int v) { to[++tot] = v, nx[tot] = st[u], st[u] = tot; }

void print(ll num, int po)
{
	if (po == 0) return;
	print(num / 10, po - 1);
	printf("%d", num % 10);
}

void search(int u)
{
	p[u] = 1;
	for (int i = st[u]; i; i = nx[i])
	{
		int v = to[i];
		if (!p[v]) search(v);
	}
}

ll dfs(int u)
{
	vis[u] = 1;
	if (~f[u]) { vis[u] = 0; return f[u]; }
	f[u] = 0;
	for (int i = st[u]; i; i = nx[i])
	{
		int v = to[i];
		if (vis[v] && p[v])
		{
			printf("inf\n");
			exit(0);
		}
		f[u] = f[u] + dfs(v);
		if (f[u] >= P)
		{
			flag = 1;
			f[u] %= P;
		}
	}
	vis[u] = 0;
	return f[u];
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++)
		scanf("%d%d", &u, &v), add(v, u);
	memset(f, 0xff, sizeof(f));
	search(1);
	f[1] = 1; dfs(2);
	if (flag) print(f[2], 9);
	else printf("%lld\n", f[2]);
	return 0;
}
