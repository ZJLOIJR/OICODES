#include <cstdio>
#include <cstring>
#include <cstdlib>

int T, n, mid;

int gcd(int x, int y) { return y ? gcd(y, x % y) : x; }

int main()
{
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d", &n);
		if (n == 2) { printf("1\n"); continue; }
		if (n & 1) printf("%lld\n", 1LL * (n / 2) * (n / 2 + 1));
		else
		{
			if (gcd(n / 2 + 1, n / 2 - 1) == 1) printf("%lld\n", 1LL * (n / 2 - 1) * (n / 2 + 1));
			else printf("%lld\n", 1LL * (n / 2 - 2) * (n / 2 + 2));
		}
	}
	return 0;
}
