#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#define bit(x) (1 << ((x) - 1))

const int N = 1e2 + 3;

int n, k;
int a[N], f[N][N][1 << 8][9];

int main()
{
	while (1)
	{
		scanf("%d%d", &n, &k);
		if (n == 0 && k == 0) break;
		memset(f, 0x3f, sizeof(f));
		for (int i = 1; i <= n; i++)
		{
			scanf("%d", a + i);
			a[i] -= 24;
		}
	}
	return 0;
}
// 3853
