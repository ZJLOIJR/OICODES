#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

typedef long long ll;

ll n, f[1010];

int main()
{
	scanf("%lld", &n);
	f[0] = 1;
	for (ll i = 1; i <= 1004; i++)
	{
		if (i * i / 2008 == (i - 1) * (i - 1) / 2008) f[i] = f[i - 1];
		else f[i] = f[i - 1] + 1;
	}
	if (n <= 1004) printf("%lld\n", f[n]);
	else printf("%lld\n", f[1004] + n - 1004);
	return 0;
}
