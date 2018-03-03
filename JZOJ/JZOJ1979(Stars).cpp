#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int N = 6e4 + 3, Y = 3e4 + 2e3 + 3;

int n;
struct point { int x, y, id; } a[N];
int ans[N];

inline int read()
{
	int x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + (c ^ '0');
	return f ? -x : x;
}

int c[N];
inline int lowbit(int x) { return x & (-x); }

inline void add(int po)
{ for (; po <= Y; po += lowbit(po)) c[po]++; }
inline int get(int po)
{ int sum = 0; for (; po; po -= lowbit(po)) sum += c[po]; return sum; }

int main()
{
	n = read();
	for (int i = 1; i <= n; i++) a[i].x = read(), a[i].y = read(), a[i].id = i;
	sort(a + 1, a + n + 1, [](point u, point v){ return u.x == v.x ? u.y < v.y : u.x < v.x; });
	for (int i = 1; i <= n; i++)
	{
		ans[a[i].id] = get(a[i].y + 1);
		add(a[i].y + 1);
	}
	for (int i = 1; i <= n; i++)
		printf("%d\n", ans[i]);
	return 0;
}
