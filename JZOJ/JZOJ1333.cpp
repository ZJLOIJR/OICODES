#include <cstdio>

typedef long long ll;
const int N = 1e5 + 3;

int n, m, ans[N];
ll a[N], b[N], c[N], d[N];

ll pow(ll a, ll b, ll mod)
{
	ll ret = 1;
	while (b)
	{
		if (b & 1) ret = ret * a % mod;
		a = a * a % mod, b >>= 1;
	}
	return ret;
}

void solve(int l, int r, int lower, int upper)
{
	if (l > r) return;
	int mid = l + r >> 1; ll min = 2147483647LL;
	int base = a[mid] * pow(b[mid], lower, d[mid]) % d[mid];
	for (int i = lower; i <= upper; i++, base = base * b[mid] % d[mid])
		if ((base + c[mid]) % d[mid] < min)
			ans[mid] = i, min = (base + c[mid]) % d[mid];
	solve(l, mid - 1, lower, ans[mid]);
	solve(mid + 1, r, ans[mid], upper);
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%lld%lld%lld%lld", a + i, b + i, c + i, d + i);
	solve(1, n, 1, m);
	for (int i = 1; i <= n; i++) printf("%d\n", ans[i]);
	return 0;
}
