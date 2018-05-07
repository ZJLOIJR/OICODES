#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;

typedef long long ll;
inline ll min(ll a, ll b) { return a < b ? a : b; }

int n;
ll s[11], b[11], ans = 0x3f3f3f3f3f3f3f3f;

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%lld%lld", s + i, b + i);
	for (int S = 1; S <= (1 << n) - 1; S++)
	{
		int cnt = 1, tmp = S; ll sums = 1, sumb = 0;
		while (tmp)
		{
			if (tmp & 1) sums *= s[cnt], sumb += b[cnt];
			tmp >>= 1, cnt++;
		}
		ans = min(ans, abs(sums - sumb));
	}
	printf("%lld\n", ans);
	return 0;
}
