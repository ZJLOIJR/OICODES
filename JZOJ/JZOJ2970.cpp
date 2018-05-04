#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 1e2 + 3, A = 3e3 + 3;

int n, ans;
int a[N], f[N * A], tmp[N * A];

int main()
{
	scanf("%d", &n);
	f[0] = 1;
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", a + i);
		for (int j = N * A; j >= a[i]; j--) f[j] += f[j - a[i]];
	}
	for (int i = 1; i <= n; i++)
	{
		memcpy(tmp, f, sizeof(f));
		for (int j = a[i]; j <= N * A; j++) tmp[j] -= tmp[j - a[i]];
		ans = 0;
		for (int j = 1; j <= N * A; j++) if (tmp[j]) ans++;
		printf("%d\n", ans);
	}
	return 0;
}
