#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 2007, V = 307;

int n, m, v, e, from, to, len;
int dis[V][V], c[N], d[N];
double k[N], f[N][N][2], ans = 2333333333.0;

inline int read()
{
	int x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + c - '0';
	return f ? -x : x;
}

inline double min(double a, double b) { return a < b ? a : b; }

void init()
{
	n = read(), m = read(), v = read(), e = read();
	for (int i = 1; i <= n; i++) *(c + i) = read();
	for (int i = 1; i <= n; i++) *(d + i) = read();
	for (int i = 1; i <= n; i++) scanf("%lf", k + i); k[0] = 1;
	memset(dis, 0x3f, sizeof(dis));
	for (int i = 1; i <= e; i++)
	{
		from = read(), to = read(), len = read();
		if (from == to) continue; //important!!!!!
		if (len < dis[from][to]) dis[from][to] = dis[to][from] = len;
	}
	for (int i = 1; i <= v; i++) dis[i][i] = 0, dis[0][i] = 0;
	for (int k = 1; k <= v; k++)
		for (int i = 1; i <= v; i++)
			for (int j = 1; j <= v; j++)
				dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
}

void solve()
{
	for (int i = 1; i <= n; i++)
		for (int j = 0; j <= m; j++)
			f[i][j][0] = f[i][j][1] = 2333333333.0;
	f[1][0][0] = 0;
	for (int i = 1; i <= n; i++)
		for (int j = 0; j <= i; j++)
		{
			if (j < i)
				f[i][j][0] = min(
					f[i - 1][j][0] + dis[c[i - 1]][c[i]],
					f[i - 1][j][1] + dis[d[i - 1]][c[i]] * k[i - 1] + dis[c[i - 1]][c[i]] * (1 - k[i - 1]));
			if (j > 0)
				if (j > 1)
					f[i][j][1] = min(
						f[i - 1][j - 1][0] + dis[c[i - 1]][d[i]] * k[i] + dis[c[i - 1]][c[i]] * (1 - k[i]),
						f[i - 1][j - 1][1] +
						dis[d[i - 1]][d[i]] * k[i - 1] * k[i] +
						dis[d[i - 1]][c[i]] * k[i - 1] * (1 - k[i]) +
						dis[c[i - 1]][d[i]] * (1 - k[i - 1]) * k[i] +
						dis[c[i - 1]][c[i]] * (1 - k[i - 1]) * (1 - k[i]));
				else
					f[i][j][1] = f[i - 1][j - 1][0] + dis[c[i - 1]][d[i]] * k[i] + dis[c[i - 1]][c[i]] * (1 - k[i]);
		}
	for (int i = 0; i <= m; i++) ans = min(ans, min(f[n][i][0], f[n][i][1]));
	printf("%.2lf\n", ans);
}

int main()
{
	freopen("classroom.in", "r", stdin);
	freopen("classroom.out", "w", stdout);

	init();
	solve();

	fclose(stdin);
	fclose(stdout);
	return 0;
}