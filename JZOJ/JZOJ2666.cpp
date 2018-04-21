#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

typedef long long ll;
const int N = 1e2 + 3, M = 12;

int n, m;
ll ans, f[N][M];

int main()
{
	scanf("%d%d", &n, &m);
	f[0][0] = f[1][1] = 1;
	for (int i = 2; i <= n; i++)
		for (int j = 1; j <= m && j <= i; j++)
			for (int k = 0; k <= i - 2; k++) f[i][j] += f[k][j - 1];
	for (int i = 1; i <= n; i++) ans += f[i][m];
	printf("%lld\n", ans);
	return 0;
}
