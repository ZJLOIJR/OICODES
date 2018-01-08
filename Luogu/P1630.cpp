#include <cstdio>
#include <cstring>

const long long P = 10000;

int n;
long long a, b, f[P + 1];

long long power(long long x, long long y)
{
	long long ret = 1;
	while (y)
	{
		if (y & 1)
			ret = ret * x % P;
		x = x * x % P;
		y >>= 1;
	}
	return ret;
}

int main()
{
	scanf("%d", &n);
	while (n--)
	{
		scanf("%lld%lld", &a, &b);
		memset(f, 0, sizeof(f));
		for (int i = 1; i <= P; i++)
			f[i] = (f[i - 1] + power(i, b)) % P;
		printf("%lld\n", (a / P * f[P] + f[a % P]) % P);
	}
	return 0;
}
