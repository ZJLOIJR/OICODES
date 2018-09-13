#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

typedef long long ll;
const ll P = 998244353;
const int N = 1e5 + 7;

int n, K, rk[N];
ll fac[N], inv[N], ans[N];
struct note { int val, id; } a[N];
int cmp(note a, note b) { return a.val < b.val; }

ll C(ll n, ll m)
{
	if (!m) return 1;
	return m > n ? 0 : fac[n] * inv[m] % P * inv[n - m] % P;
}

int main()
{
	scanf("%d%d", &n, &K);
	fac[0] = 1;
	for (int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i % P;
	inv[0] = inv[1] = 1;
	for (int i = 2; i <= n; i++) inv[i] = inv[P % i] * (P - P / i) % P;
	for (int i = 2; i <= n; i++) inv[i] *= inv[i - 1];
	for (int i = 1; i <= n; i++) scanf("%d", &a[i].val), a[i].id = i;
	sort(a + 1, a + n + 1, cmp);
	for (int i = 1, j = 0, k = 0; i <= n; i++)
	{
		while (a[j + 1].val * 2 < a[i].val && j < n) j++;
		while (a[k + 1].val <= a[i].val * 2 && k < n) k++;
		printf("%d %d %d\n", i, j, k);
		ans[a[i].id] += C(j + n - k + 1, K) + C(n - j, k - i) * C(j + n - k + 1, K - 1 - (k - i));
	}
	for (int i = 1; i <= n; i++) printf("%lld\n", ans[i]);
	return 0;
}
