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

inline double slope(int k, int j) { return (g[k] - g[j]) * 1.0 / (sum[k] - sum[j]); }
inline ll sqr(ll x) { return x * x; }

int main()
{
	n = read(), a = read(), b = read(), c = read();
	for (int i = 1; i <= n; i++) x[i] = read(), sum[i] = sum[i - 1] + x[i];
	f[0] = 0, head = 1, que[tail = 1] = 0;
	for (int i = 1; i <= n; i++)
	{
		while (head < tail && slope(que[head], que[head + 1]) >= 2.0 * a * sum[i]) head++;
		f[i] = f[que[head]] + a * sqr(sum[i] - sum[que[head]]) + b * (sum[i] - sum[que[head]]) + c;
		g[i] = f[i] + a * sqr(sum[i]) - b * sum[i];
		while (head < tail && slope(i, que[tail]) > slope(que[tail], que[tail - 1])) tail--;
		que[++tail] = i;
	}
	printf("%lld\n", f[n]);
	return 0;
}
