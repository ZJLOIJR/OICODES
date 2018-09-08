#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 1e5 + 7, L = 1e3 + 7, A = 700;
const double eps = 1e-3;

int n;
char str[N][L];

int tot = 0, st[A], to[N], nx[N], len[N];
double l, r, mid, ans = -1, dis[A];

inline void add(int u, int v, int w) { to[++tot] = v, nx[tot] = st[u], len[tot] = w, st[u] = tot; }

int flag, vis[A];
void dfs(int u)
{
	if (flag) return;
	vis[u] = 1;
	for (int i = st[u]; i; i = nx[i])
	{
		int v = to[i];
		if (dis[u] + mid - len[i] < dis[v])
		{
			dis[v] = dis[u] + mid - len[i];
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
	for (int i = 1; i <= 675; i++) dfs(i);
	return flag;
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%s", str[i] + 1);
		int length = strlen(str[i] + 1);
		int u = (str[i][1] - 'a') * 26 + str[i][2] - 'a', v = (str[i][length - 1] - 'a') * 26 + str[i][length] - 'a', w = length;
		add(u, v, w);
	}
	l = 0.0, r = 1e3;
	while (r - l > eps)
	{
		mid = (l + r) / 2;
		if (check()) l = mid, ans = mid;
		else r = mid;
	}
	if (ans == -1) printf("No solution\n");
	else printf("%.2lf\n", ans);
	return 0;
}
