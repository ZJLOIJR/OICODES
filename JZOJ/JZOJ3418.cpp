#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#define max(a, b) ((a) > (b) ? (a) : (b))

const int N = 1e3 + 7;

int n, m, fa, cnt = 0, tot = 0, ans = 0, mxi, mxj;
int st[N], to[N << 1], nx[N << 1], dfn[N], siz[N], w[N];
int f[N][N], pre[N][N][2];

inline void add(int u, int v) { to[++tot] = v, nx[tot] = st[u], st[u] = tot; }
void dfs(int u, int from)
{
	dfn[++cnt] = u, siz[u] = 1;
	for (int i = st[u]; i; i = nx[i])
		if (to[i] != from) dfs(to[i], u), siz[u] += siz[to[i]];
}

void print(int i, int j)
{
	if (i == 1 || i == 0) return;
	print(pre[i][j][0], pre[i][j][1]);
	if (i != cnt + 1) printf("%d\n", i);
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d%d", &fa, w + i + 1);
		if (i != fa)
		{
			if (fa) add(i + 1, fa + 1), add(fa + 1, i + 1);
			else add(1, i + 1), add(i + 1, 1);
		}
	}
	dfs(1, 0);
	memset(f, -0x3f, sizeof(f));
	f[1][0] = 0;
	for (int i = 1; i <= cnt; i++)
	{
		int x = dfn[i];
		for (int j = 0; j <= m; j++)
		{
			if (f[i][j] < 0) continue;
			if (x == 1)
				if (f[i][j] > f[i + 1][j])
				{
					f[i + 1][j] = f[i][j];
					pre[i + 1][j][0] = i, pre[i + 1][j][1] = j;
				}
			if (j + 1 <= m)
				if (f[i][j] + w[x] > f[i + 1][j + 1])
				{
					f[i + 1][j + 1] = f[i][j] + w[x];
					pre[i + 1][j + 1][0] = i, pre[i + 1][j + 1][1] = j;
				}
			if (f[i][j] > f[i + siz[x]][j])
			{
				f[i + siz[x]][j] = f[i][j];
				pre[i + siz[x]][j][0] = i, pre[i + siz[x]][j][1] = j;
			}
			if (f[i][j] > ans) ans = f[i][j], mxi = i, mxj = j;
		}
	}
	for (int i = 0; i <= m; i++)
		if (f[cnt + 1][i] > ans) ans = f[cnt + 1][i], mxi = cnt + 1, mxj = i;
	printf("%d\n", ans);
	print(mxi, mxj);
	return 0;
}
