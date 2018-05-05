#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#define max(a, b) ((a) > (b) ? (a) : (b))

typedef long long ll;
const int N = 1e5 + 3;

inline ll read()
{
	ll x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + (c ^ '0');
	return f ? -x : x;
}

int n, top, l[N], r[N], sta[N];
ll ans = 0, sum[N], a[N];

int main()
{
	n = read();
	for (int i = 1; i <= n; i++) a[i] = read(), sum[i] = sum[i - 1] + a[i];
	sta[top = 1] = 0;
	for (int i = 1; i <= n; i++)
	{
		while (top && a[i] <= a[sta[top]]) top--;
		l[i] = sta[top] + 1, sta[++top] = i;
	}
	sta[top = 1] = n + 1;
	for (int i = n; i >= 1; i--)
	{
		while (top && a[i] <= a[sta[top]]) top--;
		r[i] = sta[top] - 1, sta[++top] = i;
	}
	for (int i = 1; i <= n; i++) ans = max(ans, a[i] * (sum[r[i]] - sum[l[i] - 1]));
	printf("%lld\n", ans);
	return 0;
}
