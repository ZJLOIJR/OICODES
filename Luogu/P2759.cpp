#include <cmath>
#include <cstdio>
#include <cstring>

int log10(long long a)
{
	int ans = 0;
	while (a)
	{
		ans++;
		a /= 10;
	}
	return ans;
}

long long n, l, r, ret, mid;

int main()
{
	scanf("%lld", &n);
	l = 1, r = 2e9;
	while (l <= r)
	{
		mid = (l + r) >> 1;
		if (mid * log10(mid) + 1 >= n)
			ret = mid, r = mid - 1;
		else
			l = mid + 1;
	}
	printf("%lld\n", ret);
	return 0;
}
