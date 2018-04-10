#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

typedef long long ll;
const int N = 1e5 + 3;

int n, tot1 = 0, tot2 = 0, tot = 0;
ll c, d, a[N], b[N];
int ord[N];
struct note { ll a, b; int id; } arr1[N], arr2[N];

int cmp1(note x, note y) { return x.a < y.a; }
int cmp2(note x, note y) { return x.b > y.b; }

int main()
{
	//freopen("resist.in", "r", stdin);
	//freopen("resist.out", "w", stdout);

	scanf("%lld%lld%lld%*d", &n, &c, &d);
	for (int i = 1; i <= n; i++)
	{
		scanf("%lld%lld", a + i, b + i);
		if (b[i] - a[i] >= 0)
			arr1[++tot1].a = a[i], arr1[tot1].b = b[i], arr1[tot1].id = i;
		else
			arr2[++tot2].a = a[i], arr2[tot2].b = b[i], arr2[tot2].id = i;
	}
	sort(arr1 + 1, arr1 + tot1 + 1, cmp1);
	sort(arr2 + 1, arr2 + tot2 + 1, cmp2);
	for (int i = 1; i <= tot1; i++)
		if (arr1[i].id && c - arr1[i].a > d)
		{
			c = c - arr1[i].a + arr1[i].b;
			ord[++tot] = arr1[i].id;
		}
		else { printf("NO\n"); return 0; }
	for (int i = 1; i <= tot2; i++)
		if (arr2[i].id && c - arr2[i].a > d)
		{
			c = c - arr2[i].a + arr2[i].b;
			ord[++tot] = arr2[i].id;
		}
		else { printf("NO\n"); return 0; }
	printf("YES\n");
	for (int i = 1; i <= tot; i++) printf("%d ", ord[i]);

	fclose(stdin);
	fclose(stdout);
	return 0;
}
