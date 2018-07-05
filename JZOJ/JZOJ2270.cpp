#include <map>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;

typedef long long ll;

int T, k;
ll y, z, p;

ll pow(ll a, ll b, ll mo)
{
	ll ret = 1;
	while (b)
	{
		if (b & 1) ret = ret * a % mo;
		a = a * a % mo, b >>= 1;
	}
	return ret;
}

ll bsgs(ll a, ll b, ll p)
{
	map<ll, ll> hash;
	ll rt = ceil(sqrt(p));
	f
}

int main()
{
	scanf("%d%d", &T, &k);
	while (T--)
	{
		scanf("%lld%lld%lld", &y, &z, &p);
		if (k == 1) printf("%lld\n", pow(y, z, p));
		else if (k == 2)
		{
			if (y % p == 0) printf("Orz, I cannot find x!\n");
			else printf("%lld\n", pow(y, p - 2, p) * z % p);
		}
		else printf("%lld\n", bsgs(y, z, p));
	}
	return 0;
}
