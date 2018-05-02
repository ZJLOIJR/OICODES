#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int N = 1e5 + 3;

int n, x, cnt, ans, tot, a[N], arr[N];
char str[20];

int main()
{
	freopen("seq.in", "r", stdin);
	freopen("seq.out", "w", stdout);

	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%s", str);
		if (str[0] == 'N') cnt++;
		else scanf("%d", &x), a[++tot] = x - cnt;
	}
	memset(arr, 0x3f, sizeof(arr));
	for (int i = 1; i <= tot; i++)
	{
		int po = lower_bound(arr + 1, arr + n + 1, a[i]) - arr;
		arr[po] = a[i], ans = max(ans, po);
	}
	printf("%d\n", ans + cnt);

	fclose(stdin);
	fclose(stdout);
	return 0;
}
