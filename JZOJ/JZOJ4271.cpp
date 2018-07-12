#include <cstdio>
#include <cstring>
#include <cstdlib>

typedef long long ll;
const int N = 2e2 + 7;
const ll P = 1e9 + 7;

const int dt1[10] = {12, 9, 6, 6, 6, 3, 0, 3, 0, 0};
const int dt2[10] = {4, 2, 1, 1, 0, 0, 0, 0, 0, 0};
const int flag[10][10] = {
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
	{1, 1, 0, 0, 0, 0, 0, 0, 0, 0}, 
	{1, 0, 1, 0, 0, 0, 0, 0, 0, 0}, 
	{1, 2, 0, 1, 0, 0, 0, 0, 0, 0}, 
	{1, 2, 0, 0, 1, 0, 0, 0, 0, 0}, 
	{1, 1, 1, 0, 0, 1, 0, 0, 0, 0}, 
	{1, 0, 2, 0, 0, 0, 1, 0, 0, 0}, 
	{1, 3, 0, 2, 1, 0, 0, 1, 0, 0}, 
	{1, 2, 1, 1, 0, 2, 0, 0, 1, 0}, 
	{1, 4, 0, 4, 2, 0, 0, 4, 0, 1}, 
};

int n, k;
ll f[N][N][10];
ll C[20][20];

int main()
{
	freopen("magic.in", "r", stdin);
	freopen("magic.out", "w", stdout);
	
	scanf("%d%d", &n, &k);
	for (int i = 0; i <= 15; i++) C[i][0] = 1;
	for (int i = 1; i <= 15; i++)
		for (int j = 1; j <= i; j++)
			C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % P;
	f[0][0][0] = 1;
	f[0][1][1] = 4, f[0][1][2] = 4;
	f[0][2][3] = 4, f[0][2][4] = 2, f[0][2][5] = 8, f[0][2][6] = 2;
	f[0][3][7] = 4, f[0][3][8] = 4;
	f[0][4][9] = 1;
	for (int i = 0; i < n; i++)
		for (int s = 0; s < 10; s++)
			for (int j = 0; j <= k; j++)
			{
				if (!f[i][j][s]) continue;
				for (int l = 0; l < 10; l++)
				{
					if (!flag[s][l]) continue;
					for (int p = 0; j + p <= k && p <= dt2[l]; p++)
						for (int q = 0; j + p + q <= k && 2 * p + q <= dt1[l]; q++)
							f[i + 1][j + p + q][l] = (f[i + 1][j + p + q][l] + f[i][j][s] * C[dt2[l]][p] % P * C[dt1[l] - 2 * p][q] * flag[s][l] % P) % P;
				}
			}
	ll ans = 0;
	for (int i = 0; i < 10; i++) ans = (ans + f[n][k][i]) % P;
	for (int i = 1; i <= k; i++) ans = ans * i % P;
	printf("%lld\n", ans);

	fclose(stdin);
	fclose(stdout);
	return 0;
}
