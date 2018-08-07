#include <queue>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;

typedef long long ll;
const int N = 5e4 + 7;

int n, k, ans, used[N];
ll m, p[N][2];

struct note { int id, typ; };
int operator<(note a, note b) { return p[a.id][a.typ] == p[b.id][b.typ] ? a.typ > b.typ : p[a.id][a.typ] > p[b.id][b.typ]; }
priority_queue<note> heap;

int main()
{
	freopen("shopping.in", "r", stdin);
	freopen("shopping.out", "w", stdout);

	scanf("%d%d%lld", &n, &k, &m);
	for (int i = 1; i <= n; i++)
	{
		scanf("%lld%lld", &p[i][0], &p[i][1]);
		heap.push((note){i, 0});
		heap.push((note){i, 1});
	}
	while (1)
	{
		if (heap.empty()) break;
		note x = heap.top(); heap.pop();
		if (used[x.id]) continue;
		if (x.typ && !k) continue;
		if (m - p[x.id][x.typ] >= 0)
		{
			ans++, m -= p[x.id][x.typ], used[x.id] = 1;
			if (x.typ) k--;
		}
		else break;
	}
	printf("%d\n", ans);

	fclose(stdin);
	fclose(stdout);
	return 0;
}
