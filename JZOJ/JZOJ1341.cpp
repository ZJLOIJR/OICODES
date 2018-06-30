#include <cstdio>
#include <cstring>
#include <cstdlib>

typedef long long ll;
const int N = 2e5 + 7;

ll ans = 0, c[N], r[N];
int n, a[N];

void add(int po)
{ for (; po <= n; po += (po & (-po))) c[po]++; }
ll sum(int po)
{
	ll ret = 0;
	for (; po; po -= (po & (-po))) ret += c[po];
	return ret;
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", a + i);
	for (int i = n; i >= 1; i--)
	{
		r[i] = sum(n) - sum(a[i]);
		ans += r[i] * (r[i] - 1) / 2, add(a[i]);
	}
	memset(c, 0, sizeof(c));
	for (int i = 1; i <= n; i++)
		ans -= sum(a[i] - 1) * r[i], add(a[i]);
	printf("%lld\n", ans);
	return 0;
}
