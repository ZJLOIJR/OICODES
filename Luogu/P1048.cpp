#include <cstdio>

const int V = 1007, N = 107;

int v, n, a, b;

int f[V];

inline int max(int x, int y) { return x > y ? x : y; }

int main()
{
	scanf("%d%d", &v, &n);
	while (n--)
	{
		scanf("%d%d", &a, &b);
		for (int i = v; i >= a; i--)
			f[i] = max(f[i], f[i - a] + b);
	}
	printf("%d\n", f[v]);
	return 0;
}
