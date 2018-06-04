#include <cstdio>

const int M = 12887;
inline int max(int a, int b) { return a > b ? a : b; }

int n, m, w, d;
int f[M];

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d%d", &w, &d);
		for (int j = m; j >= w; j--) f[j] = max(f[j], f[j - w] + d);
	}
	printf("%d\n", f[m]);
	return 0;
}
