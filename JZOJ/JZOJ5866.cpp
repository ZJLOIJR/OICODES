#include <set>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int N = 1e5 + 7;

int n, ans;
struct point { int x, y; } a[N], b[N];
multiset<int> s;

int cmp(point p, point q) { return p.x == q.x ? p.y < q.y : p.x < q.x; }

int main()
{
	freopen("guide.in", "r", stdin);
	freopen("guide.out", "w", stdout);

	scanf("%*d%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d%d", &a[i].x, &a[i].y);
	for (int i = 1; i <= n; i++) scanf("%d%d", &b[i].x, &b[i].y);
	sort(a + 1, a + n + 1, cmp);
	sort(b + 1, b + n + 1, cmp);
	for (int i = 1, j = 1; i <= n; i++)
	{
		while (a[j].x <= b[i].x && j <= n) s.insert(a[j].y), j++;
		multiset<int>::iterator tp = s.upper_bound(b[i].y);
		if (tp != s.begin())
		{
			tp--;
			s.erase(tp);
			ans++;
		}
	}
	printf("%d\n", ans);

	fclose(stdin);
	fclose(stdout);
	return 0;
}
