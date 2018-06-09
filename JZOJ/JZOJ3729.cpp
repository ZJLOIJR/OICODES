#include <cstdio>

typedef long long ll;

ll n, ans;

int main()
{
	freopen("exp.in", "r", stdin);
	freopen("exp.out", "w", stdout);
	scanf("%lld", &n), ans = n * n;
	for (ll l = 1, r; l <= n; l = r + 1) r = n / (n / l), ans -= (l + r) * (r - l + 1) / 2 * (n / l);
	printf("%lld\n", ans);
	return 0;
}
