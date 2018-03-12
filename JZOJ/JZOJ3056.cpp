#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

typedef long long ll;
const int N = 1e3 + 3;
const ll P = 999983;

int n, len;
ll anssum = 0, anseven = 0, ansodd = 0, f[N][N * 9];
char str[15];
int num[15];

int main()
{
	scanf("%d%s", &n, str + 1);
	len = strlen(str + 1);
	for (int i = 1; i <= len; i++) num[i] = str[i] - '0';
	f[0][0] = 1;
	for (int i = 1; i <= n; i++)
		for (int j = 0; j <= n * 9; j++)
			for (int k = 1; k <= len; k++)
				if (j - num[k] >= 0)
					f[i][j] = (f[i][j] + f[i - 1][j - num[k]]) % P;
	for (int i = 0; i <= n * 9; i++)
		anssum = (anssum + 2 * f[n][i] % P * f[n][i]) % P;
	int len1 = (n + 1) / 2, len2 = n / 2;
	for (int i = 0; i <= len1 * 9; i++)
		anseven = (anseven + f[len1][i] % P * f[len1][i]) % P;
	for (int i = 0; i <= len2 * 9; i++)
		ansodd = (ansodd + f[len2][i] % P * f[len2][i]) % P;
	printf("%lld\n", (anssum - anseven * ansodd % P + P) % P);
	return 0;
}
