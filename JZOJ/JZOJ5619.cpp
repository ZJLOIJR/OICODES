#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int N = 1e5 + 3;

int n, c, d, tot1 = 0, tot2 = 0;
int a[N], b[N];
struct note { int a, b, id; } arr1[N], arr2[N];

int cmp1(note x, note y)
{ return x.a == y.a ? x.b > y.b : x.a < y.a; }

int cmp2(note x, note y)
{ return x.b == y.b ? x.a < y.a : x.b > y.b; }

int main()
{
	//freopen("resist.in", "r", stdin);
	//freopen("resist.out", "w", stdout);

	scanf("%d%d%d%*d", &n, &c, &d);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d%d", a + i, b + i);
		if (b[i] - a[i] >= 0)
			arr1[++tot1].a = a[i], arr1[tot1].b = b[i], arr1[tot1].id = i;
		else
			arr2[++tot2].a = a[i], arr2[tot2].b = b[i], arr2[tot2].id = i;
	}
	sort(arr1 + 1, arr1 + tot1 + 1, cmp1);
	sort(arr2 + 1, arr2 + tot2 + 1, cmp2);
	for (int i = 1; i <= tot1; i++)
	{
		if (c - arr1[i].a < d) { printf("NO\n"); return 0; }
		c = c - arr1[i].a + arr1[i].b;
	}
	for (int i = 1; i <= tot2; i++)
	{
		if (c - arr2[i].a < d) { printf("NO\n"); return 0; }
		c = c - arr2[i].a + arr2[i].b;
	}
	printf("YES\n");
	for (int i = 1; i <= tot1; i++) printf("%d ", arr1[i].id);
	for (int i = 1; i <= tot2; i++) printf("%d ", arr2[i].id);

	fclose(stdin);
	fclose(stdout);
	return 0;
}
