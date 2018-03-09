#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int N = 1e4 + 3;

int n, ans = 0;
int arr[N], arr1[N], arr2[N], po[N], vis[N];

inline int read()
{
	int x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + (c ^ '0');
	return f ? -x : x;
}
inline int min(int a, int b) { return a < b ? a : b; }

int main()
{
	freopen("csort.in", "r", stdin);
	freopen("csort.out", "w", stdout);

	n = read();
	for (int i = 1; i <= n; i++) arr1[i] = read();
	memcpy(arr2, arr1, sizeof(arr1));
	sort(arr2 + 1, arr2 + n + 1);
	for (int i = 1; i <= n; i++)
		po[i] = lower_bound(arr2 + 1, arr2 + n + 1, arr1[i]) - arr2;
	for (int i = 1; i <= n; i++)
	{
		if (po[i] == i || vis[i]) { vis[i] = 1; continue; }
		int sum = 0, minn = 66666666, now = i, cnt = 0;
		while (!vis[now])
		{
			cnt++;
			vis[now] = 1;
			minn = min(minn, arr1[now]);
			sum += arr1[now];
			now = po[now];
		}
		ans += min(sum + minn * (cnt - 2), sum + minn + (cnt + 1) * arr2[1]);
	}
	printf("%d\n", ans);

	fclose(stdin);
	fclose(stdout);
	return 0;
}
