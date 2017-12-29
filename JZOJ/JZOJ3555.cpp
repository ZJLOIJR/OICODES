#pragma GCC optimize(3)
#include <cstdio>
#include <cstring>

const int N = 200007;

int n, q, u, x, y, cnt, nowans;
int f[N][21], dep[N];

void swap(int &a, int &b) { int t = a; a = b, b = t; }

int getlca(int u, int v)
{
	if (dep[v] > dep[u])
		swap(u, v);
	for (int i = 20; i >= 0; i--)
		if (dep[f[u][i]] >= dep[v])
			u = f[u][i];
	if (u == v)
		return u;
	for (int i = 20; i >= 0; i--)
		if (f[u][i] != f[v][i])
			u = f[u][i], v = f[v][i];
	return f[u][0];
}

void add(int fa, int tmp)
{
	f[tmp][0] = fa;
	dep[tmp] = dep[fa] + 1;
	for (int i = 1; i <= 20; i++)
		f[tmp][i] = f[f[tmp][i - 1]][i - 1];
}

void solve()
{
	int lca = getlca(x, cnt), len = dep[cnt] + dep[x] - 2 * dep[lca];
	if (len > nowans)
		nowans = len, y = cnt;
	lca = getlca(cnt, y), len = dep[cnt] + dep[y] - 2 * dep[lca];
	if (len > nowans)
		nowans = len, x = cnt;
}

int main()
{
	dep[2] = dep[3] = dep[4] = 1;
	f[2][0] = f[3][0] = f[4][0] = 1;
	x = 2, y = 3, cnt = 4, nowans = 2;
	scanf("%d", &q);
	while (q--)
	{
		scanf("%d", &u);
		add(u, ++cnt);
		add(u, ++cnt);
		solve();
		printf("%d\n", nowans);
	}
	return 0;
}
