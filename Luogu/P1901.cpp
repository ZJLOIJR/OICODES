#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>

const int N = 1000007, INF = 23333333;

int n;
int lef[N], rig[N], valu[N], h[N], v[N];
int sta[N], top;

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
	n = read();
	for (int i = 1; i <= n; i++)
		*(h + i) = read(), *(v + i) = read();
	h[0] = INF, h[n + 1] = INF;
	sta[top = 1] = 0;
	for (int i = 1; i <= n; i++)
	{
		while (top > 0 && h[i] >= h[sta[top]]) top--;
		lef[i] = sta[top];
		sta[++top] = i;
	}
	sta[top = 1] = n + 1;
	for (int i = n; i >= 1; i--)
	{
		while (top > 0 && h[i] >= h[sta[top]]) top--;
		rig[i] = sta[top];
		sta[++top] = i;
	}
}

void solve()
{
	int ans = 0;
	for (int i = 1; i <= n; i++)
		valu[lef[i]] += v[i], valu[rig[i]] += v[i];
	for (int i = 1; i <= n; i++)
		ans = valu[i] > ans ? valu[i] : ans;
	printf("%d\n", ans);
}

int main()
{
	init();
	solve();
	return 0;
}
