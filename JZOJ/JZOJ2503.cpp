#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 5e5 + 3;

int n, k, l, r, mid, ans;
char str[N];

int check(int x)
{
	int cnt = 0;
	for (int i = 1; i <= n; i++)
		if (str[i] == '1')
			i += x - 1, cnt++;
	return cnt <= k;
}

int main()
{
	scanf("%d%d%s", &n, &k, str + 1);
	l = 0, r = n;
	while (l <= r)
	{
		mid = l + r >> 1;
		if (check(mid)) r = mid - 1, ans = mid;
		else l = mid + 1;
	}
	printf("%d\n", ans);
	return 0;
}
