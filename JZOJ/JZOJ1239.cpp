#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;

const int N = 1e2 + 7;
const double eps = 1e-9;

inline int min(int a, int b) { return a < b ? a : b; }

int n;
double a[N][N];

int S, T, tot = 1;
int st[N * 4], to[N * N * 16], nx[N * N * 16], len[N * N * 16];
double ans = 0, cost[N * N * 16];

inline void add(int u, int v, int l, double c)
{
	to[++tot] = v, nx[tot] = st[u], st[u] = tot, len[tot] = l, cost[tot] = c;
	to[++tot] = u, nx[tot] = st[v], st[v] = tot, len[tot] = 0, cost[tot] = -c;
}

double dis[N * 4];
int head, tail, vis[N * 4], pre[N * 4], maxflow[N * 4], que[N * 80];
int bfs()
{
	head = 1, tail = 0;
	memset(dis, 127, sizeof(dis));
	memset(vis, 0, sizeof(vis));
	memset(pre, 0, sizeof(pre));
	memset(maxflow, 0, sizeof(maxflow));
	que[++tail] = S, vis[S] = 1, maxflow[S] = 0x3f3f3f3f;
	while (head <= tail)
	{
		int u = que[head++]; vis[u] = 0;
		for (int i = st[u]; i; i = nx[i])
		{
			int v = to[i];
			if (min(maxflow[u], len[i]) > maxflow[v] || (min(maxflow[u], len[i]) == maxflow[v] && dis[u] + cost[i] - dis[v] > eps))
			{
				maxflow[v] = min(maxflow[u], len[i]), dis[v] = dis[u] + cost[i], pre[v] = i;
				if (!vis[v]) que[++tail] = v, vis[v] = 1;
			}
		}
	}
	return maxflow[T];
}

void upd()
{
	int now = T;
	while (now != S) len[pre[now]] -= maxflow[T], len[pre[now] ^ 1] += maxflow[T], now = to[pre[now] ^ 1];
	ans += maxflow[T] * dis[T];
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			scanf("%lf", &a[i][j]), a[i][j] /= 100.0;
	S = 1, T = n * 2 + 2;
	for (int i = 1; i <= n; i++) add(S, i + 1, 1, 0), add(i + n + 1, T, 1, 0);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			add(i + 1, j + n + 1, 1, log(a[i][j]));
	while (bfs()) upd();
	printf("%.6lf\n", exp(ans) * 100.0);
	return 0;
}
