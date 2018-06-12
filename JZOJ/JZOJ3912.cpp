#include <cstdio>
#include <cstring>
#include <cstdlib>

typedef long long ll;
inline ll min(ll a, ll b) { return a < b ? a : b; }

ll x, y, z;

int main()
{
	scanf("%lld%lld", &x, &y);
	if (y > x) z += x * (y - x), y = x;
	z += x * y;
	for (ll l = 1, r; l <= y; l = r + 1)
	{
		r = min(x / (x / l), y);
		z -= (x / l) * (r - l + 1) * (r + l) / 2;
	}
	printf("%lld\n", z);
	return 0;
}
