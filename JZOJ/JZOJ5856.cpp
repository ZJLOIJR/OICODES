#include <cstdio>
#include <cstring>
#include <cstdlib>

typedef long long ll;
const int M = 1e6 + 7, P = 1e9 + 7;

int a, c, k, m, n, f[M][21], g[M][21], b[M][21], pow[1050007], ans;
char str[M];

int val(int z) { return z >= m / 2; }
int check(int z)
{
	int now = 1;
	for (int i = 20; i >= 0; i--)
		if (now + (1 << i) < n)
		{
			if (g[z][i] != b[now][i]) return 0;
			now = now + (1 << i), z = f[z][i];
		}
	if (g[z][0] != b[now][0]) return 0;
	return 1;
}

int main()
{
	freopen("zero.in", "r", stdin);
	freopen("zero.out", "w", stdout);
	
	pow[0] = 1; for (int i = 1; i <= 1050000; i++) pow[i] = pow[i - 1] * 233LL % P;
	scanf("%d%d%d%d%d%s", &a, &c, &k, &m, &n, str + 1);
	for (int i = 0; i < m; i++) f[i][0] = ((1LL * a * i + c) / k) % m, g[i][0] = val(f[i][0]);
	for (int j = 1; j <= 20; j++)
		for (int i = 0; i < m; i++)
		{
			f[i][j] = f[f[i][j - 1]][j - 1];
			g[i][j] = (1LL * g[i][j - 1] * pow[(1 << (j - 1))] % P + g[f[i][j - 1]][j - 1]) % P;
		}
	for (int i = 1; i <= n; i++) b[i][0] = str[i] - '0';
	for (int j = 1; j <= 20; j++)
		for (int i = 1; i <= n; i++)
			b[i][j] = (1LL * b[i][j - 1] * pow[(1 << (j - 1))] % P + b[i + (1 << (j - 1))][j - 1]) % P;
	for (int i = 0; i < m; i++) ans += check(i);
	printf("%d\n", ans);

	fclose(stdin);
	fclose(stdout);
	return 0;
}
