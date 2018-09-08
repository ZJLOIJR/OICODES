#include <map>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;

typedef long long ll;
const ll MAX = 100000000000000LL;
int n, ans;
ll w;

map<ll, int> buc;

int check(ll a)
{
	ll rt = sqrt(a);
	if (a < 2 || rt < 2) return 0;
	if (rt * rt == a) return 1;
	if (buc[a]) return 1;
	return 0;
}

int main()
{
	freopen("bread.in", "r", stdin);
	freopen("bread.out", "w", stdout);
	
	for (ll i = 2; i <= 46000; i++)
	{
		ll ret = i * i;
		while (ret * i <= MAX) ret *= i, buc[ret] = 1;
	}
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%lld", &w), ans += check(w);
	printf("%d\n", ans);

	fclose(stdin);
	fclose(stdout);
	return 0;
}
