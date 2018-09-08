#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 3e3 + 7, M = 1e4 + 7;
const double eps = 1e-7;

int n, m, tot = 0, st[N], to[M], nx[M];
double l, r, mid, ans, len[M], dis[N];

inline void add(int u, int v, double w) { to[++tot] = v, nx[tot] = st[u], len[tot] = w, st[u] = tot; }

int flag, vis[N];
void dfs(int u)
{
	if (flag) return;
	vis[u] = 1;
	for (int i = st[u]; i; i = nx[i])
	{
		int v = to[i];
		if (dis[u] + len[i] - mid < dis[v])
		{
			dis[v] = dis[u] + len[i] - mid;
			if (vis[v]) { flag = 1; return; }
			else dfs(v);
		}
	}
	vis[u] = 0;
}
int check()
{
	flag = 0;
	memset(vis, 0, sizeof(vis));
	memset(dis, 0, sizeof(dis));
	for (int i = 1; i <= n; i++) dfs(i);
	return !flag;
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++)
	{
		int a, b; double c;
		scanf("%d%d%lf", &a, &b, &c);
		add(a, b, c);
	}
	l = -1e5, r = 1e5;
	while (r - l > eps)
	{
		mid = (l + r) / 2;
		if (check()) l = mid;
		else r = mid, ans = mid;
	}
	printf("%.6lf\n", ans);
	return 0;
}
