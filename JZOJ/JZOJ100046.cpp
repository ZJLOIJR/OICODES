#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 5e5 + 3;

int n, l, r, mid, ans, kind = 0;
char str[N];
int buc[256];

int check(int len)
{
	memset(buc, 0, sizeof(buc));
	int end = len, cnt = 0;
	for (int i = 1; i <= end; i++)
	{
		if (!buc[str[i]]) cnt++;
		buc[str[i]]++;
	}
	while (end <= n)
	{
		if (cnt == kind) return 1;
		buc[str[end - len + 1]]--;
		if (!buc[str[end - len + 1]]) cnt--;
		if (!buc[str[end + 1]]) cnt++;
		buc[str[end + 1]]++;
		end++;
	}
	return 0;
}

int main()
{
	scanf("%d%s", &n, str + 1);
	for (int i = 1; i <= n; i++)
		if (!buc[str[i]])
			kind++, buc[str[i]]++;
	l = 1, r = n;
	while (l <= r)
	{
		mid = l + r >> 1;
		if (check(mid)) r = mid - 1, ans = mid;
		else l = mid + 1;
	}
	printf("%d\n", ans);
	return 0;
}
