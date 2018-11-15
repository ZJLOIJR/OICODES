#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

const double eps = 1e-8;
const int N = 2557, M = N * 130, INF = 0x3f3f3f3f;
int min(int a, int b) { return a < b ? a : b; }

int n, m;
double t1, t2, v, X1[N], Y1[N], X2[N], Y2[N], dis[N][N];
double l, r, mid, ans;

int cnt, S, T, ind[57];
int tot, st[N], to[M], nx[M], len[M];
void add(int u, int v, int w)
{
	to[++tot] = v, nx[tot] = st[u], len[tot] = w, st[u] = tot;
	to[++tot] = u, nx[tot] = st[v], len[tot] = 0, st[v] = tot;
}
int head, tail, que[N], dep[N];
int bfs()
{
	memset(dep, 0, sizeof(dep));
	head = 1, que[tail = 1] = S, dep[S] = 1;
	while (head <= tail)
	{
		int u = que[head++];
		for (int i = st[u]; i; i = nx[i])
			if (!dep[to[i]] && len[i] > 0)
				dep[to[i]] = dep[u] + 1, que[++tail] = to[i];
	}
	return dep[T];
}
int dinic(int u, int flow)
{
	if (u == T) return flow;
	int rest = flow, tmp;
	for (int i = st[u]; i; i = nx[i])
		if (dep[to[i]] == dep[u] + 1 && len[i] > 0)
		{
			tmp = dinic(to[i], min(rest, len[i]));
			if (!tmp) dep[to[i]] = 0;
			len[i] -= tmp, len[i ^ 1] += tmp, rest -= tmp;
		}
	return flow - rest;
}
int check()
{
	cnt = 0, tot = 1;
	memset(st, 0, sizeof(st));
	memset(nx, 0, sizeof(nx));
	memset(to, 0, sizeof(to));
	memset(len, 0, sizeof(len));
	S = ++cnt, T = ++cnt;
	for (int i = 1; i <= m; i++) ind[i] = ++cnt, add(ind[i], T, 1);
	for (int i = 1; i <= n; i++)
	{
		double tim = 0;
		for (int j = 1; j <= m; j++)
		{
			int ths = ++cnt;
			tim += t1;
			if (tim <= mid) add(S, ths, 1);
			for (int k = 1; k <= m; k++)
				if (tim + dis[i][k] <= mid)
					add(ths, ind[k], 1);
			tim += t2;
		}
	}
	int ret = 0;
	while (bfs()) ret += dinic(S, INF);
	return ret >= m;
}

int main()
{
	scanf("%d%d%lf%lf%lf", &n, &m, &t1, &t2, &v);
	t1 /= 60.0;
	for (int i = 1; i <= m; i++) scanf("%lf%lf", X2 + i, Y2 + i);
	for (int i = 1; i <= n; i++) scanf("%lf%lf", X1 + i, Y1 + i);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			dis[i][j] = sqrt((X1[i] - X2[j]) * (X1[i] - X2[j]) + (Y1[i] - Y2[j]) * (Y1[i] - Y2[j])) / v;
	l = 0, r = 1e6;
	while (r - l > eps)
	{
		mid = (l + r) / 2;
		if (check()) r = mid, ans = mid;
		else l = mid;
	}
	printf("%.6lf\n", ans);
	return 0;
}
