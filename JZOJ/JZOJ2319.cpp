#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

typedef long long ll;
const int N = 1e6 + 3;

int n, head, tail, que[N];
ll a, b, c, x[N], f[N], g[N], sum[N];

inline ll read()
{
	ll x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + (c - '0');
	return f ? -x : x;
}

int main()
{
	n = read(), a = read(), b = read(), c = read();
	for (int i = 1; i <= n; i++) x[i] = read(), sum[i] = sum[i - 1] + x[i];
	return 0;
}
//f[k]-2*a*sum[i]*sum[k]+a*sum[k]^2-b*sum[k] > f[j]-2*a*sum[i]*sum[j]+a*sum[j]^2-b*sum[j]
