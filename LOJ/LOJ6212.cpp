#include <cstdio>
#include <cstring>
#include <cstdlib>

typedef long long ll;

int T;
ll n, l;

int main()
{
	scanf("%d", &T);
	while (T--)
	{
		scanf("%lld%lld", &n, &l);
		if (l >= n) printf("%lld\n", n);
		else if (2 * l >= n) printf("%lld\n", l);
		else printf("%lld\n", n % 2 ? n / 2 + 1 : n / 2);
	}
	return 0;
}
