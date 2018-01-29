#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

typedef long long ll;

ll n, a, b, ans = 0, i, j, k;

inline ll min(ll a, ll b) { return a < b ? a : b; }

int main()
{
	scanf("%lld%lld%lld", &n, &a, &b);
	while (2333)
	{
		ll len = min(a - j, b - k);
		if (i + len > n)
		{
			ans += (n - i) * abs(j - k);
			break;
		}
		ans += len * abs(j - k);
		i += len, j = (j + len) % a, k = (k + len) % b;
	}
	printf("%lld\n", ans);
	return 0;
}