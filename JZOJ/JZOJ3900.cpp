#include <cstdio>
#include <algorithm>
using namespace std;

int T, n, m, x, cnt, x1, y1, x2, y2;

int main()
{
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d%d%d%d%d%d%d%d", &n, &m, &x, &cnt, &x1, &y1, &x2, &y2);
		long long tmp = 1LL * (x2 - x1) * (y2 - y1) * (cnt + 1);
		if (x * 2 > n) x = n - x;
		tmp += 1LL * (y2 - y1) * max(0, min(x, x2) - x1) * (cnt + 1);
		printf("%lld\n", (long long)n * (long long)m - tmp);
	}
	return 0;
}
