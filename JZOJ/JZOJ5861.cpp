#include <queue>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int N = 1e6 + 7;

int n, m, ans, tmp;
struct seg { int l, r, id; } segm[N];
struct Pair { int r, id; };
int operator<(Pair a, Pair b) { return a.r > b.r; }
priority_queue<Pair> heap;

int cmp(seg a, seg b) { return a.l < b.l; }

int main()
{
	freopen("failure.in", "r", stdin);
	freopen("failure.out", "w", stdout);
	
	scanf("%*d%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%d%d", &segm[i].l, &segm[i].r), segm[i].id = i;
	sort(segm + 1, segm + n + 1, cmp);
	for (int i = 1; i <= n; i++)
	{
		heap.push((Pair){segm[i].r, segm[i].id});
		if (heap.size() == m)
		{
			Pair mx = heap.top(); heap.pop();
			if (mx.r - segm[i].l > ans) ans = mx.r - segm[i].l, tmp = i;
		}
	}
	printf("%d\n", ans);
	if (ans == 0) { for (int i = 1; i <= m; i++) printf("%d ", i); return 0; }
	while (!heap.empty()) heap.pop();
	for (int i = 1; i <= tmp; i++)
	{
		heap.push((Pair){segm[i].r, segm[i].id});
		if (heap.size() == m && i != tmp) heap.pop();
	}
	while (!heap.empty())
	{
		Pair temp = heap.top(); heap.pop();
		printf("%d ", temp.id);
	}

	fclose(stdin);
	fclose(stdout);
	return 0;
}
