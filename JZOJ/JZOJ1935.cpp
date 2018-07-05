#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#define max(a, b) ((a) > (b) ? (a) : (b))

const int N = 1e7 + 3;

int n, x, y, z, a[N];
double ans = 0.0;

int main()
{
	scanf("%d%d%d%d%d", &n, &x, &y, &z, a + 1);
	for (int i = 2; i <= n; i++) a[i] = ((long long)a[i - 1] * x + y) % 100000001;
	for (int i = 1; i <= n; i++) a[i] = a[i] % z + 1;
	for (int i = 1; i <= n; i++) ans += 1.0 / max(a[i], a[i % n + 1]);
	printf("%.3lf\n", ans);
	return 0;
}
