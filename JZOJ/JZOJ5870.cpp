#include <cstdio>
#include <cstring>
#include <cstdlib>

typedef long long ll;
const int N = 2e3 + 7;
const ll P = 998244353;

int n, tot1, tot2;
ll ans1, ans2, f[N][N];

int two(int n) { return n * (n - 1) / 2 % P; }

int main()
{
	freopen("map.in", "r", stdin);
	freopen("map.out", "w", stdout);
	
	scanf("%d", &n);
	for (int i = 1, d; i <= n; i++)
	{
		scanf("%d", &d);
		if (d == 1) tot1++;
		else tot2++;
	}
	if (tot1 & 1) { printf("0\n"); return 0; }
	f[0][0] = 1;
	for (int i = 1; i <= tot2; i++)
		for (int j = 0; j <= i; j++)
		{
			if (j >= 3 && i >= 3) f[i][j] = (f[i][j] + f[i - 3][j - 3] * two(i - 1) % P) % P;
			if (j >= 1) f[i][j] = (f[i][j] + f[i - 1][j - 1] * (j - 1)) % P;
			f[i][j] = (f[i][j] + f[i - 1][j] * (i - j - 1 + tot1 / 2)) % P;
		}
	for (int i = 0; i <= tot2; i++) ans1 = (ans1 + f[tot2][i]) % P;
	ans2 = 1;
	for (int i = 3; i <= tot1; i++) if (i & 1) ans2 = ans2 * i % P;
	printf("%lld\n", ans1 * ans2 % P);

	fclose(stdin);
	fclose(stdout);
	return 0;
}
