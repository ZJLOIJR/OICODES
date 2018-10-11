#include <queue>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int N = 1e5 + 7;

int n, m, b[N];
struct range { int l, r; } a[N];
int cmp(range x, range y) { return x.l < y.l; }
priority_queue<int> heap;

int main()
{
	//freopen("ore.in", "r", stdin);
	//freopen("ore.out", "w", stdout);

	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%d%d", &a[i].l, &a[i].r);
	sort(a + 1, a + n + 1, cmp);
	for (int i = 1; i <= m; i++) scanf("%d", b + i);
	sort(b + 1, b + n + 1);
	for (int i = 1; i <= n; i++)
	{
	}

	fclose(stdin);
	fclose(stdout);
	return 0;
}
