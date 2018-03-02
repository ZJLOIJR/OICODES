#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 50007;

int n, t, l, r, mid, ans, ret;
int a[N], f[N], que[N], head, tail;

inline int read()
{
	int x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + c - '0';
	return f ? -x : x;
}

inline int min(int a, int b) { return a < b ? a : b; }

int check(int middle)
{
	memset(f, 0x3f, sizeof(f));
	memset(que, 0, sizeof(que));
	f[0] = 0, head = 1, tail = 0;
	for (int i = 1; i <= n; i++)
	{
		while (head <= tail && f[i - 1] <= f[que[tail]]) tail--;
		que[++tail] = i - 1;
		while (head <= tail && que[head] < i - middle) head++;
		f[i] = f[que[head]] + a[i];
	}
	for (int i = n - middle + 1; i <= n; i++) if (f[i] <= t) return 1;
	return 0;
}

int main()
{
	n = read(), t = read();
	for (int i = 1; i <= n; i++) *(a + i) = read();
	l = 0, r = n;
	while (l <= r)
	{
		mid = l + r >> 1;
		if (check(mid + 1)) r = mid - 1, ans = mid;
		else l = mid + 1;
	}
	printf("%d\n", ans);
	return 0;
}
