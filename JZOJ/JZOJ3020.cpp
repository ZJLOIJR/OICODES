#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

typedef long long ll;

const int prime[16] = {0, 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47};
const int tot = 15;

int maxd = 0;
ll n, ans;

void dfs(int dep, int upper, ll now, int sum)
{
	if (now > n) return;
	if (sum > maxd) maxd = sum, ans = now;
	if (sum == maxd && now < ans) ans = now;
	if (dep > tot) return;
	ll d = 1LL;
	for (int i = 0; now * d <= n && i <= upper; i++)
	{
		dfs(dep + 1, i, now * d, sum * (i + 1));
		d = d * prime[dep];
	}
}

int main()
{
	scanf("%lld", &n);
	ans = n;
	dfs(1, 30, 1, 1);
	printf("%lld\n", ans);
	return 0;
}
