#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int N = 500007, R = 10007, C = 10007;

inline int read()
{
	int x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + c - '0';
	return f ? -x : x;
}

int left, right, mid, ans, n, r, c, a[N];

void init()
{
	n = read(), r = read(), c = read();
	for (int i = 1; i <= n; i++) *(a + i) = read();
	sort(a + 1, a + n + 1);
}

int check(int m)
{
	int cnt = 0, i = 1;
	while (i <= n - c + 1)
	{
		if (a[i + c - 1] - a[i] <= m) i = i + c, cnt++;
		else i++;
	}
	return cnt >= r;
}

void solve()
{
	left = 0, right = 1e9;
	while (left <= right)
	{
		mid = left + right >> 1;
		if (check(mid)) right = mid - 1, ans = mid;
		else left = mid + 1;
	}
	printf("%d\n", ans);
}

int main()
{
	init();
	solve();
	return 0;
}
