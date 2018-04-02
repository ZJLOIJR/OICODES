#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

long long n, m, ans, tmp;

int main()
{
	scanf("%lld", &n);
	m = sqrt(n), ans = n, tmp = n;
	for (long long i = 2; i <= m; i++)
		if (n % i == 0)
		{
			ans = ans / i * (i - 1);
			while (n % i == 0) n /= i;
		}
	if (n > 1) ans = ans / n * (n - 1);
	printf("%lld\n", tmp * ans / 2);
	return 0;
}
