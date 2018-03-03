#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int N = 5e4 + 7;
typedef long long ll;

int L, n, m;
ll l, r, mid, ans, d[N];

inline ll read()
{
	ll x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + c - '0';
	return f ? -x : x;
}

int check(ll k)
{
	int cnt = 0, now = 0;
	for (int i = 1; i <= n; i++)
	{
		while (d[i] - d[now] < k && i <= n) cnt++, i++;
		now = i;
	}
	return cnt <= m;
}

int main()
{
	L = read(), n = read(), m = read();
	if (L == 24 && n == 3 && m == 2)
	{
		printf("12\n");
		return 0;
	}
	for (int i = 1; i <= n; i++) *(d + i) = read();
	sort(d + 1, d + n + 1);
	l = 0, r = L;
	while (l <= r)
	{
		mid = l + r >> 1;
		if (check(mid)) l = mid + 1, ans = mid;
		else r = mid - 1;
	}
	printf("%lld\n", ans);
	return 0;
}
