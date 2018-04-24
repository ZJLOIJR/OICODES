#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#define min(a, b) ((a) < (b) ? (a) : (b))
using namespace std;

const int N = 20;

int n, m, r, c, ans = 0x3f3f3f3f, a[N][N], f[N][N];
int ord[N], used[N], res[N][N], ths[N];

void upd()
{
	memset(res, 0, sizeof(res)); memset(ths, 0, sizeof(ths));
	for (int i = 1; i <= m; i++)
		for (int j = 1; j <= i - 1; j++)
			for (int k = 1; k <= r; k++)
				res[i][j] += abs(a[ord[k]][i] - a[ord[k]][j]);
	for (int i = 1; i <= m; i++)
		for (int j = 1; j < r; j++)
			ths[i] += abs(a[ord[j]][i] - a[ord[j + 1]][i]);
	memset(f, 0x3f, sizeof(f));
	f[0][0] = 0;
	for (int i = 1; i <= m; i++)
		for (int j = 1; j <= c && j <= i; j++)
			for (int k = 0; k <= i - 1; k++)
				f[i][j] = min(f[i][j], f[k][j - 1] + ths[i] + res[i][k]);
	int minsum = 0x3f3f3f3f;
	for (int i = c; i <= m; i++) minsum = min(minsum, f[i][c]);
	ans = min(ans, minsum);
}

void dfs(int now, int cnt)
{
	if (cnt == r) { upd(); return; }
	if (now > n) return;
	for (int i = now; i <= n; i++)
	{
		ord[cnt + 1] = i;
		dfs(i + 1, cnt + 1);
	}
}

int main()
{
	scanf("%d%d%d%d", &n, &m, &r, &c);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			scanf("%d", &a[i][j]);
	dfs(1, 0);
	printf("%d\n", ans);
	return 0;
}
