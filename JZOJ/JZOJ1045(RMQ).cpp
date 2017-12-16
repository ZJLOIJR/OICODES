#include <cstdio>
#include <cstdlib>
#include <cstring>

const int N = 30007;

int mi[N][20], mx[N][20], a[N], lg[N];

int n, k;

inline int min(int x, int y) { return x < y ? x : y; }
inline int max(int x, int y) { return x > y ? x : y; }

void init()
{
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", a + i);
		mi[i][0] = mx[i][0] = a[i];
	}
}

void RMQ()
{
	lg[1] = 0;
	for (int i = 2; i <= n; i++)
		lg[i] = lg[i >> 1] + 1;
	
	for (int j = 1; (1 << j) <= n; j++)
		for (int i = 1; i + (1 << j) - 1 <= n; i++)
		{
			mi[i][j] = min(mi[i][j - 1], mi[i + (1 << (j - 1))][j - 1]);
			mx[i][j] = max(mx[i][j - 1], mx[i + (1 << (j - 1))][j - 1]);
		}
}

inline int qry_min(int l, int r)
{
	int len = r - l + 1;
	return min(mi[l][lg[len]], mi[r - (1 << lg[len]) + 1][lg[len]]);
}

inline int qry_max(int l, int r)
{
	int len = r - l + 1;
	return max(mx[l][lg[len]], mx[r - (1 << lg[len]) + 1][lg[len]]);
}

int check(int m)
{
	for (int i = 1; i <= n - m + 1; i++)
		if (qry_max(i, i + m - 1) - qry_min(i, i + m - 1) <= k)
			return 1;
	return 0;
}

void solve()
{
	RMQ();

	int l = 1, r = n, ans;
	while (l <= r)
	{
		int mid = (l + r) >> 1;
		if (check(mid))
			l = mid + 1, ans = mid;
		else
			r = mid - 1;
	}

	printf("%d\n", ans);
}

int main()
{
	init();
	solve();
	return 0;
}
