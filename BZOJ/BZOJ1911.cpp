#include <cstdio>
#include <cstring>
#include <cstdlib>

typedef long long ll;
const int N = 1e6 + 7;

int n, head, tail, que[N];
ll a, b, c, f[N], g[N], s[N];

double slope(int i, int j) { return (g[i] - g[j]) * 1.0 / (s[i] - s[j]); }
ll sqr(ll a) { return a * a; }

int main()
{
	scanf("%d%lld%lld%lld", &n, &a, &b, &c);
	for (int i = 1, x; i <= n; i++) scanf("%d", &x), s[i] = s[i - 1] + x;
	head = 1, que[tail = 1] = 0;
	for (int i = 1; i <= n; i++)
	{
		while (head < tail && slope(que[head], que[head + 1]) >= 2.0 * a * s[i]) head++;
		f[i] = f[que[head]] + a * sqr(s[i] - s[que[head]]) + b * (s[i] - s[que[head]]) + c;
		g[i] = f[i] + a * sqr(s[i]) - b * s[i];
		while (head < tail && slope(que[tail], i) > slope(que[tail], que[tail - 1])) tail--;
		que[++tail] = i;
	}
	printf("%lld\n", f[n]);
	return 0;
}
