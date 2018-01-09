#include <cmath>
#include <cstdio>
#include <cstring>

long long n, l, r, ret, mid;

int main()
{
	scanf("%lld", &n);
	l = 1, r = 2e9;
	while (l <= r)
	{
		mid = (l + r) >> 1;
		if (mid * log(mid) / log(10) + 1 >= n)
			ret = mid, r = mid - 1;
		else
			l = mid + 1;
	}
	printf("%lld\n", ret);
	return 0;
}
