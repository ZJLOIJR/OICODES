#pragma GCC optimize(3)
#include <cmath>
#include <cstdio>
#include <cstring>

const int N = 500007;

int n, q, len, tot, opt;
int a[N], b[N], lef[N / 100], rig[N / 100], sum[N / 100];

inline int max(int a, int b) { return a > b ? a : b; }
inline int min(int a, int b) { return a < b ? a : b; }

inline int read()
{
    int x = 0, f = 0;
    char c = getchar();
    for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
    for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + c - '0';
    return f ? -x : x;
}

void init()
{
    n = read(), q = read();
    len = sqrt(n);
    tot = n / len;
    if (n % len)
        tot++;
    for (int i = 1; i <= n; i++)
        *(a + i) = read(), b[i] = (i - 1) / len + 1, sum[b[i]] += a[i];
    for (int i = 1; i <= tot; i++)
        lef[i] = (i - 1) * len + 1, rig[i] = i * len;
}

void solve()
{
    int l, r, ans;
    while (q--)
    {
        opt = read(), l = read(), r = read();
		if (opt == 1)
		{
			a[l] += r;
			sum[b[l]] += r;
		}
		else
		{
        	ans = 0;
        	for (int i = l; i <= min(r, rig[b[l]]); i++)
            	ans += a[i];
        	for (int i = r; i >= max(l, lef[b[r]]); i--)
            	ans += a[i];
        	for (int i = b[l] + 1; i <= b[r] - 1; i++)
            	ans += sum[i];
        	printf("%d\n", ans);
		}
    }
}

int main()
{
    init();
    solve();
    return 0;
}
