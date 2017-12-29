#include <cstdio>
#include <cstring>

const int N = 200007;

int n, q, u, x, y, cnt, nowans;
int f[N][20], dep[N];

int getdis(int u, int v)
{
	int lca, tmpu = u, tmpv = v;
	if (dep[v] > dep[u])
	{
		int t = u;
		u = v;
		v = t;
	}
	for (int i = 20; i >= 0; i--)
		if (dep[f[u][i]] >= dep[v])
			u = f[u][i];
	if (u == v)
		return dep[tmpu] - dep[u] + dep[tmpv] - dep[u];
	for (int i = 20; i >= 0; i--)
		if (f[u][i] != f[v][i])
			u = f[u][i], v = f[v][i];
	lca = f[u][0];
	return dep[tmpu] - dep[lca] + dep[tmpv] - dep[lca];
}

void add(int fa, int u)
{
	dep[u] = dep[fa] + 1;
	f[u][0] = fa;
	for (int i = 1; i <= 20; i++)
		f[u][i] = f[f[u][i - 1]][i - 1];
}

void solve()
{
	int len = getdis(x, cnt);
	if (len > nowans)
	{
		nowans = len, y = cnt;
		return;
	}
	len = getdis(cnt, y);
	if (len > nowans)
	{
		nowans = len, x = cnt;
		return;
	}
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
