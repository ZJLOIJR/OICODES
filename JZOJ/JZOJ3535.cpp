#include <cstdio>

int n, las = 0, x;
long long ans = 0;

int main()
{
	scanf("%d", &n);
	while (n--)
	{
		scanf("%d", &x);
		if (x > las) ans += x - las;
		las = x;
	}
	printf("%lld\n", ans);
	return 0;
}
