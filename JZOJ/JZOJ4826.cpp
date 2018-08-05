#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 2e3 + 7, M = 2e4 + 7;
const double eps = 1e-4;

int n, m, u, v, w, tot = 0, st[N], to[M], nx[M], len[M];
double l, r, mid, ans, dis[N];

int top = 0, sta[N], arr[N], rd[N];

inline void add(int u, int v, int w) { to[++tot] = v, nx[tot] = st[u], len[tot] = w, st[u] = tot; }

int check()
{
	memset(dis, 127, sizeof(dis));
	dis[n] = 0;
	for (int i = arr[0]; i; i--)
	{
		int u = arr[i];
		if (u == n) continue;
		double res = 23333333.0;
		for (int j = st[u]; j; j = nx[j])
			if (dis[to[j]] + len[j] - mid < res)
				res = dis[to[j]] + len[j] - mid;
		dis[u] = res;
	}
	return dis[1] <= 0;
}

int main()
{
	freopen("input", "r", stdin);
	//freopen("calabash.in", "r", stdin);
	//freopen("calabash.out", "w", stdout);
	
	scanf("%d%d", &n, &m);
	for (int i = 1, u, v, w; i <= m; i++) scanf("%d%d%d", &u, &v, &w), add(u, v, w), rd[v]++;
	for (int i = 1; i <= n; i++) if (!rd[i]) sta[++top] = i;
	while (top)
	{
		int x = sta[top--];
		arr[++arr[0]] = x;
		for (int i = st[x]; i; i = nx[i])
		{
			int v = to[i];
			rd[v]--;
			if (!rd[v]) sta[++top] = v;
		}
	}
	l = 0.0, r = 1e3;
	while (r - l > eps)
	{
		mid = (l + r) / 2;
		if (check()) r = mid, ans = mid;
		else l = mid;
	}
	printf("%.3lf\n", ans);

	fclose(stdin);
	fclose(stdout);
	return 0;
}
