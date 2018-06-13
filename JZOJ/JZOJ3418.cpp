#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int N = 1e3 + 7;

int cnt = 0, n, m, v[N], arr[N], dfn[N], out[N];
int f[N][N], pre[N][N][2];
int tot = 0, st[N], to[N], nx[N];
inline void add(int u, int v) { to[++tot] = v, nx[tot] = st[u], st[u] = tot; }

void dfs(int x)
{
	dfn[++cnt] = x;
	for (int i = st[x]; i; i = nx[i]) dfs(to[i]);
	out[x] = cnt;
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1, fa; i <= n; i++)
	{
		scanf("%d%d", &fa, v + i);
		if (fa) add(fa, i); else arr[++arr[0]] = i;
	}
	for (int i = 1; i <= arr[0]; i++) dfs(arr[i]);
	memset(f, -0x3f, sizeof(f));
	f[1][0] = 0;
	for (int i = 1; i <= n; i++)
	{
		int x = dfn[i];
		for (int j = 0; j <= m; j++)
		{
			if (f[i][j] + v[x] > f[i + 1][j + 1]) f[i + 1][j + 1] = f[i][j] + v[x], pre[i + 1][j + 1][0] = i, pre[i + 1][j + 1][1] = j;
			if (f[i][j] > f[out[x] + 1][j]) f[out[x] + 1][j] = f[i][j], pre[out[x] + 1][j][0] = i, pre[out[x] + 1][j][1] = j;
			if (f[i][j] + v[x] > f[out[x] + 1][j + 1]) f[out[x] + 1][j + 1] = f[i][j] + v[x], pre[out[x] + 1][j + 1][0] = i, pre[out[x] + 1][j + 1][1] = j;
		}
	}
	printf("%d\n", f[n + 1][m]);
	if (m >= 100) return 0;
	int x = n + 1, y = m;
	memset(arr, 0, sizeof(arr));
	while (pre[x][y][0])
	{
		int nx = pre[x][y][0], ny = pre[x][y][1];
		if (y != ny) arr[++arr[0]] = dfn[nx];
		x = nx, y = ny;
	}
	sort(arr + 1, arr + arr[0] + 1);
	for (int i = 1; i <= arr[0]; i++) printf("%d\n", arr[i]);
	return 0;
}
