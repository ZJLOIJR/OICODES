#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

typedef long long ll;
const int N = 1e5 + 7;
const ll INF = (1LL << 62);

int n, m;
ll x1, y1, x2, y2, a[N];

ll myabs(ll a) { return a > 0 ? a : -a; }

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%lld", a + i);
	sort(a + 1, a + n + 1);
	scanf("%d", &m);
	while (m--)
	{
		scanf("%lld%lld%lld%lld", &x1, &y1, &x2, &y2);
		if (y1 * y2 > 0) printf("%lld\n", myabs(x1 - x2) + myabs(y1 - y2));
		else
		{
			int nex, pre; ll ans = INF;
			nex = lower_bound(a + 1, a + n + 1, x1) - a;
			pre = upper_bound(a + 1, a + n + 1, x1) - a - 1;
			if (nex >= 1 && nex <= n) ans = min(ans, myabs(x1 - a[nex]) + myabs(x2 - a[nex]) + myabs(y1 - y2));
			if (pre >= 1 && pre <= n) ans = min(ans, myabs(x1 - a[pre]) + myabs(x2 - a[pre]) + myabs(y1 - y2));
			printf("%lld\n", ans);
		}
	}
	return 0;
}
