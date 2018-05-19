#include <cstdio>
#include <cstring>

int n, cost[11], f[2001];

int main()
{
	for (int i = 1; i <= 10; i++) scanf("%d", cost + i);
	scanf("%d", &n);
	memset(f, 0x3f, sizeof(f));
	f[0] = 0;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= i && j <= 10; j++)
			if (f[i - j] + cost[j] < f[i])
				f[i] = f[i - j] + cost[j];
	printf("%d\n", f[n]);
	return 0;
}
