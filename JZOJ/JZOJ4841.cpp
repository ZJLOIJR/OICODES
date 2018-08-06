#include <map>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;

const int N = 22;

int n, mid, full, ans, a[N];
map<int, int> buc;

int main()
{
	//freopen("subset.in", "r", stdin);
	//freopen("subset.out", "w", stdout);

	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", a + i);
	mid = (1 + n) / 2;
	full = 1; for (int i = 1; i <= mid; i++) full *= 3; full--;
	for (int s = 0; s <= full; s++)
	{
		int tmp = s, ret = 0, now = 1;
		while (tmp)
		{
			if (tmp % 3 == 1) ret += a[now];
			else if (tmp % 3 == 2) ret -= a[now];
			tmp /= 3, now++;
		}
		buc[ret]++;
	}
	full = 1; for (int i = mid + 1; i <= n; i++) full *= 3; full--;
	for (int s = 0; s <= full; s++)
	{
		int tmp = s, ret = 0, now = mid + 1;
		while (tmp)
		{
			if (tmp % 3 == 1) ret += a[now];
			else if (tmp % 3 == 2) ret -= a[now];
			tmp /= 3, now++;
		}
		ans += buc[ret];
	}
	printf("%d\n", (ans - 1) / 2);

	fclose(stdin);
	fclose(stdout);
	return 0;
}
