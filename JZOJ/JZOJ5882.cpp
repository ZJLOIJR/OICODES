#include <cstdio>

const int N = 1e6 + 7;

int n, ans, mi, a[N];

int main()
{
	freopen("snowman.in", "r", stdin);
	freopen("snowman.out", "w", stdout);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", a + i);
	mi = a[n];
	for (int i = n - 1; i >= 1; i--)
	{
		if (a[i] > mi) ans++;
		if (a[i] < mi) mi = a[i];
	}
	printf("%d\n", ans);
	return 0;
}
