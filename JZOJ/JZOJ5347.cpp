#include <cstdio>
#include <cstring>
#include <cstdlib>

typedef long long ll;
const int N = 2e4 + 7, K = 1e2 + 7;

int n, k, x[N], y[N];
int head, tail, que[N];
ll ans, f[N][K];

double slope(int j, int k, int m) { return (f[j][m] - f[k][m]) * 1.0 / (j - k); }

int main()
{
	freopen("pyramid.in", "r", stdin);
	freopen("pyramid.out", "w", stdout);

	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; i++) scanf("%d%d", x + i, y + i);
	for (int j = 1; j <= k; j++)
	{
		head = 1, que[tail = 1] = 0;
		for (int i = 1; i <= n; i++)
		{
			while (head < tail && slope(que[head], que[head + 1], j - 1) > y[i] - x[i] + 1) head++;
			f[i][j] = f[que[head]][j - 1] + (i - que[head]) * (y[i] - x[i] + 1LL);
			while (head < tail && slope(que[tail - 1], que[tail], j - 1) < slope(que[tail], i, j - 1)) tail--;
			que[++tail] = i;
		}
	}
	for (int i = 1; i <= n; i++) if (f[i][k] > ans) ans = f[i][k];
	printf("%lld\n", ans);

	fclose(stdin);
	fclose(stdout);
	return 0;
}
