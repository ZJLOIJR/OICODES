#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

int n, a, sum;

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a);
		if (n > 1 && a == 0) { printf("Impossible\n"); return 0; }
		sum += a;
	}
	if (sum == 2 * n - 2) printf("Possible\n");
	else printf("Impossible\n");
	return 0;
}
