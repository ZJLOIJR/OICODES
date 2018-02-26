#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 1e5 + 3;

int n, cnt = 0;
int a[25], f[N];

inline int min(int a, int b) { return a < b ? a : b; }

int main()
{
	memset(f, 0x3f, sizeof(f));
	f[0] = 0;
	scanf("%d", &n);
	for (int i = 1; i * i * i * i <= n; i++)
		a[++cnt] = i * i * i * i;
	for (int i = 1; i <= cnt; i++)
		for (int j = a[i]; j <= n; j++)
			f[j] = min(f[j], f[j - a[i]] + 1);
	printf("%d\n", f[n]);
	return 0;
}
