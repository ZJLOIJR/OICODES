#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int N = 1e4 + 3;

int n, mindis = 1e9, cnt = 0;
struct point { int x, y; } a[N];

inline int read()
{
	int x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + (c ^ '0');
	return f ? -x : x;
}

int main()
{
	freopen("newbarn.in", "r", stdin);
	freopen("newbarn.out", "w", stdout);

	n = read();
	for (int i = 1; i <= n; i++) a[i].x = read(), a[i].y = read();
	if (n & 1)
	{
		sort(a + 1, a + n + 1, [](point u, point v){ return u.x < v.x; });
		int xx = a[n + 1 >> 1].x;
		sort(a + 1, a + n + 1, [](point u, point v){ return u.y < v.y; });
		int yy = a[n + 1 >> 1].y;
		int flag = 0;
		for (int i = 1; i <= n; i++) if (a[i].x == xx && a[i].y == yy) { flag = 1; break; }
		if (flag)
		{
			int DIR[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
			mindis = 1e9, cnt = 0;
			for (int i = 0; i < 4; i++)
			{
				int dx = xx + DIR[i][0], dy = yy + DIR[i][1], sum = 0;
				for (int j = 1; j <= n; j++)
					sum += abs(dx - a[j].x) + abs(dy - a[j].y);
				if (sum == mindis) cnt++;
				if (sum < mindis) mindis = sum, cnt = 1;
			}
		}
		else
		{
			mindis = 0, cnt = 1;
			for (int i = 1; i <= n; i++)
				mindis += abs(xx - a[i].x) + abs(yy - a[i].y);
		}
		printf("%d %d\n", mindis, cnt);
	}
	else
	{
		sort(a + 1, a + n + 1, [](point u, point v){ return u.x < v.x; });
		int xl = a[(n >> 1)].x, xr = a[(n >> 1) + 1].x;
		sort(a + 1, a + n + 1, [](point u, point v){ return u.y < v.y; });
		int yl = a[(n >> 1)].y, yr = a[(n >> 1) + 1].y;
		mindis = 0, cnt = (xr - xl + 1) * (yr - yl + 1);
		for (int i = 1; i <= n; i++) mindis += abs(xr - a[i].x) + abs(yr - a[i].y);
		for (int i = 1; i <= n; i++)
			if (xl <= a[i].x && a[i].x <= xr &&
				yl <= a[i].y && a[i].y <= yr)
					cnt--;
		printf("%d %d\n", mindis, cnt);
	}

	fclose(stdin);
	fclose(stdout);
	return 0;
}
