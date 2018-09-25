#include <queue>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;

const int N = 5e4 + 7;
double getdis(double x, double y) { return sqrt(x * x + y * y); }

double ans;
int n, y, u, w[N], v[N];

struct note { int id, len; double m; };
int operator<(note p, note q) { return p.m > q.m; }
priority_queue<note> heap;

int main()
{
	scanf("%d%d%d", &n, &y, &u);
	w[0] = 0, v[0] = u;
	for (int i = 1; i <= n; i++) scanf("%d", w + i);
	for (int i = 1; i <= n; i++) scanf("%d", v + i);
	for (int i = 1; i <= n; i++) ans += w[i] * 1.0 / v[i];
	for (int i = 1; i <= n; i++)
	{
		note t = (note){i, 1, (getdis(w[i], 1) - w[i]) / v[i]};
		heap.push(t);
	}
	heap.push((note){0, 0, 1.0 / u});
	for (int i = 1; i <= y && !heap.empty(); i++)
	{
		note t = heap.top(); heap.pop();
		ans += t.m;
		note p = (note){t.id, t.len + 1, (getdis(w[t.id], t.len + 1) - getdis(w[t.id], t.len)) / v[t.id]};
		heap.push(p);
	}
	printf("%.4lf\n", ans);
	return 0;
}
