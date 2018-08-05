#include <cstdio>
#include <cstring>
#include <cstdlib>

inline int min(int a, int b) { return a < b ? a : b; }
const int N = 2e3 + 7, M = 2e4 + 7;

int n, m, u, v, w, tot = 0, st[N], to[M], nx[M], len[M];
int dis[N][N];

int top = 0, sta[N], arr[N], rd[N];

inline void add(int u, int v, int w) { to[++tot] = v, nx[tot] = st[u], len[tot] = w, st[u] = tot; }

int main()
{
	freopen("calabash.in", "r", stdin);
	freopen("calabash.out", "w", stdout);
	
	memset(dis, 0x3f, sizeof(dis));
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
	dis[n][1] = 0;
	for (int i = arr[0]; i; i--)
		for (int j = 2; j <= n; j++)
			for (int k = st[arr[i]]; k; k = nx[k])
				dis[arr[i]][j] = min(dis[arr[i]][j], dis[to[k]][j - 1] + len[k]);
	double ans = 233333333.0;
	for (int i = 2; i <= n; i++) if (dis[1][i] * 1.0 / i < ans) ans = dis[1][i] * 1.0 / i;
	printf("%.3lf\n", ans);

	fclose(stdin);
	fclose(stdout);
	return 0;
}
