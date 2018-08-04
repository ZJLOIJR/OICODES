#include <cstdio>
#include <cstring>
#include <cstdlib>

typedef long long ll;
const ll P = 1000000007LL;

ll n, m;

ll solve(ll a)
{
	ll ret = 0;
	for (ll l = 1, r; l <= a; l = r + 1)
		r = a / (a / l), ret = (ret + (a / l) * (l + r) % P * (r - l + 1) % P * 500000004LL % P) % P;
	return (a * a % P - ret + P) % P;
}

int main()
{
	scanf("%lld%lld", &n, &m);
	printf("%lld\n", solve(n) * solve(m) % P);
	return 0;
}
