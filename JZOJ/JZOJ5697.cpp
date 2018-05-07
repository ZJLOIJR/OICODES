#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
inline int max(int a, int b) { return a > b ? a : b; }

const int N = 1e5 + 3;

int n, sum, tot, rt, ans = 1, flag;
int a[N], num[N], buc[N * 10];

int main()
{
	freopen("farm.in", "r", stdin);
	freopen("farm.out", "w", stdout);

	sum = tot = 0;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", a + i), sum += a[i], buc[sum] = 1;
	rt = sqrt(sum), num[++tot] = 1, num[++tot] = sum;
	for (int i = 2; i <= rt; i++) if (sum % i == 0) num[++tot] = i, num[++tot] = sum / i;
	for (int i = 1; i <= tot; i++)
	{
		flag = 1;
		for (int j = 1; j <= sum / num[i]; j++) if (!buc[num[i] * j]) { flag = 0; break; }
		if (flag) ans = max(ans, sum / num[i]);
	}
	printf("%d\n", ans);

	fclose(stdin);
	fclose(stdout);
	return 0;
}
