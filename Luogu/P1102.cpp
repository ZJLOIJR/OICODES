#include <map>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;

const int N = 200007;
typedef long long ll;

map<ll, ll> buc;

int n;
ll c, ans = 0, a[N];

int main()
{
	scanf("%d%lld", &n, &c);
	for (int i = 1; i <= n; i++)
	{
		scanf("%lld", a + i);
		buc[a[i]]++;
	}
	for (int i = 1; i <= n; i++)
		ans += buc[a[i] - c];
	printf("%lld\n", ans);
	return 0;
}