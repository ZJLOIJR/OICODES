#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int N = 1e5 + 7;

int T;
int n, m, a[N];
double ans;

int main()
{
	freopen("atom.in", "r", stdin);
	freopen("atom.out", "w", stdout);

	scanf("%d", &T);
	while (T--)
	{
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; i++) scanf("%d", a + i);
		sort(a + 1, a + n + 1);
		ans = -1;
		for (int i = 1; i <= n - 2; i++)
		{
			int po = upper_bound(a + 1, a + n + 1, a[i] + m) - a - 1;
			if (po >= i + 2 && po <= n) ans = max(ans, (a[po] - a[i + 1]) * 1.0 / (a[po] - a[i]));
		}
		if (ans == -1) printf("-1\n");
		else printf("%.10lf\n", ans);
	}

	fclose(stdin);
	fclose(stdout);
	return 0;
}
