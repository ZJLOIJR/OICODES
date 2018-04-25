#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

typedef long long ll;
ll n, ans = 0;

int main()
{
	scanf("%lld", &n);
	for (ll l = 1, r; l <= n; l = r + 1)
	{
		r = n / (n / l);
		ans += (r - l + 1) * (n / l);
	}
	ans -= n;
	printf("%lld\n", ans);
	return 0;
}
