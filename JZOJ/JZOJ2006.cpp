#include <cstdio>

const int N = 1e5 + 7;

int n, m, l, r, mid, ans, sum = 0, p[N];

int check()
{
	int cnt = 1, s = 0;
	for (int i = 1; i <= n; i++)
	{
		if (p[i] > mid) return 0;
		if (s + p[i] > mid) s = p[i], cnt++;
		else s += p[i];
	}
	return cnt <= m;
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%d", p + i), sum += p[i];
	l = 0, r = sum;
	while (l <= r)
	{
		mid = l + r >> 1;
		if (check()) r = mid - 1, ans = mid;
		else l = mid + 1;
	}
	printf("%d\n", ans);
	return 0;
}
