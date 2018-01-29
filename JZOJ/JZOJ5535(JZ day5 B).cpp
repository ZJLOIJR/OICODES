#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 1007, K  = 57;

int n, s, k;
int f[N][K], sum[N][N], r[N];

inline int min(int a, int b) { return a < b ? a : b; }

int main()
{
	freopen("board.in", "r", stdin);
	freopen("board.out", "w", stdout);

	memset(f, 0x3f, sizeof(f));
	scanf("%d%d%d", &n, &s, &k);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", r + i);
		for (int j = 1; j < i; j++) if (r[j] < r[i]) sum[r[i]][r[j]]++;
	}
	for (int i = 1; i <= s; i++)
	{
		for (int j = 1; j < i; j++) sum[i][j] += sum[i][j - 1];
		for (int j = 1; j < i; j++) sum[i][j] += sum[i - 1][j];
		sum[i][i] += sum[i][i - 1];
	}
	f[0][0] = 0;
	for (int i = 1; i <= s; i++)
		for (int j = 1; j <= k; j++)
			for (int l = 0; l < i; l++)
				f[i][j] = min(f[i][j], f[l][j - 1] + sum[i][i] - sum[i][l]);
	printf("%d\n", f[s][k]);

	fclose(stdin);
	fclose(stdout);
	return 0;
}