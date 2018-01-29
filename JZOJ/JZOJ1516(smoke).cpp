#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

int main()
{
	int n, k;
	scanf("%d%d", &n, &k);
	printf("%d\n", (n - 1) / (k - 1) + n);
	return 0;
}