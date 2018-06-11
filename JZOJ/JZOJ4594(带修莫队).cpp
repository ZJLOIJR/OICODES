#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int N = 5e4 + 7;

int n, m, block, col[N], b[N], las[N], buc[1000007];
struct query { int l, r, id, tim; } q[N];
struct change { int po, now, old; } c[N];
int tot1 = 0, tot2 = 0, ans[N];
int time, l, r, tmp = 0;

int cmp(query x, query y)
{
	return b[x.l] == b[y.l] ? (b[x.r] == b[y.r] ? x.tim < y.tim : x.r < y.r) : x.l < y.l;
}

void add(int color, int typ)
{
	buc[color] += typ;
	if (typ == 1) tmp += (buc[color] == 1);
	else tmp -= (buc[color] == 0);
}
void changecolor(int pos, int color) { if (l <= pos && pos <= r) add(color, 1), add(col[pos], -1); col[pos] = color; }

int main()
{
	freopen("len.in", "r", stdin);
	freopen("len.out", "w", stdout);

	scanf("%d%d", &n, &m), block = pow(n, 0.66666);
	for (int i = 1; i <= n; i++) scanf("%d", col + i), b[i] = (i - 1) / block + 1, las[i] = col[i];
	for (int i = 1; i <= m; i++)
	{
		char ch; int a, b;
		scanf(" %c %d %d", &ch, &a, &b);
		if (ch == 'Q') q[++tot1] = (query){a + 1, b, tot1, tot2};
		else c[++tot2] = (change){a + 1, b, las[a + 1]}, las[a + 1] = b;
	}
	sort(q + 1, q + tot1 + 1, cmp);
	l = 1, r = 0, time = 0;
	for (int i = 1; i <= tot1; i++)
	{
		while (time < q[i].tim) changecolor(c[time + 1].po, c[time + 1].now), time++;
		while (time > q[i].tim) changecolor(c[time].po, c[time].old), time--;
		while (r < q[i].r) add(col[r + 1], 1), r++;
		while (r > q[i].r) add(col[r], -1), r--;
		while (l < q[i].l) add(col[l], -1), l++;
		while (l > q[i].l) add(col[l - 1], 1), l--;
		ans[q[i].id] = tmp;
	}
	for (int i = 1; i <= tot1; i++) printf("%d\n", ans[i]);

	fclose(stdin);
	fclose(stdout);
	return 0;
}
