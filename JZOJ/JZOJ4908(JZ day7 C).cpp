#pragma GCC optimize(3)
#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;

const int N = 18, FULL = 1 << N;

int T, n, m;
int dp[FULL], f[N + 7][N + 7];
double x[N + 7], y[N + 7];

inline int bit(int x) { return 1 << (x - 1); }
inline int equal(double a, double b) { return abs(a - b) <= 1e-8; }
inline int min(int a, int b) { return a < b ? a : b; }

int main()
{
	freopen("angrybirds.in", "r", stdin);
	freopen("angrybirds.out", "w", stdout);

	scanf("%d", &T);
	while (T--)
	{
		memset(f, 0, sizeof(f)), memset(dp, 0x3f, sizeof(dp)), dp[0] = 0;
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; i++) scanf("%lf%lf", x + i, y + i);
		for (int i = 1; i <= n - 1; i++)
			for (int j = i + 1; j <= n; j++)
			{
				if (x[i] == x[j]) continue;
				double a = (y[i] * x[j] - y[j] * x[i]) / (x[i] * x[i] * x[j] - x[j] * x[j] * x[i]),
					   b = (y[i] - a * x[i] * x[i]) / x[i];
				if (a >= 0) continue;
				for (int k = 1; k <= n; k++)
					if (equal(a * x[k] * x[k] + b * x[k], y[k])) f[i][j] |= bit(k);
			}
		for (int i = 0; i <= (1 << n) - 1; i++)
		{
			for (int j = 1; j <= n - 1; j++)
				for (int k = j + 1; k <= n; k++)
					dp[i | f[j][k]] = min(dp[i | f[j][k]], dp[i] + 1);
			for (int j = 1; j <= n; j++)
				dp[i | bit(j)] = min(dp[i | bit(j)], dp[i] + 1);
		}
		printf("%d\n", dp[(1 << n) - 1]);
	}

	fclose(stdin);
	fclose(stdout);
	return 0;
}