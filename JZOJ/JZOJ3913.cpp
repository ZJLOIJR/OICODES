#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 1e5 + 7;
inline int max(int a, int b) { return a > b ? a : b; }
inline int min(int a, int b) { return a < b ? a : b; }

int n, ans, sum = 0, buc[N * 3];

int main()
{
	memset(buc, -1, sizeof(buc));
	scanf("%d", &n);
	buc[N] = 0;
	for (int i = 1, a; i <= n; i++)
	{
		scanf("%d", &a);
		if (a == 0) sum--; else sum++;
		if (buc[sum + N] != -1) ans = max(ans, i - buc[sum + N]);
		else buc[sum + N] = i;
	}
	printf("%d\n", ans);
	return 0;
}
