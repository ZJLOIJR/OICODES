#include <cstdio>
#include <cstring>
#include <cstdlib>

typedef long long ll;
const int N = 1e6 + 7;

int n, k;
double ans, sum;
char str[N];
double g[N], f[N];

int main()
{
	scanf("%s%d", str + 1, &k);
	n = strlen(str + 1);
	for (int i = 1; i <= n; i++) sum += str[i] - '0';
	g[0] = 1.0;
	for (int i = 1; i <= k; i++) g[i] = g[i - 1] * (n - 2.0) / n + (1 - g[i - 1]) / ((ll)n * (n - 1) / 2);
	for (int i = 1; i <= n; i++) f[i] = i * (n - i + 1.0) / ((ll)n * (n + 1) / 2);
	for (int i = 1; i <= n; i++) ans += f[i] * ((str[i] - '0') * g[k] + (sum - (str[i] - '0')) / (n - 1) * (1 - g[k]));
	printf("%.9lf\n", ans);
	return 0;
}
