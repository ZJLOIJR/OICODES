#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 8e4 + 3;

typedef long long ll;
int n, top, sta[N];
ll ans, h[N];

int main()
{
	freopen("badhair.in", "r", stdin);
	freopen("badhair.out", "w", stdout);

	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%lld", h + i);
	ans = 0LL, sta[top = 1] = n + 1, h[n + 1] = 0x3f3f3f3f3f3fLL;
	for (int i = n; i >= 1; i--)
	{
		while (top && h[i] > h[sta[top]]) top--;
		ans += sta[top] - i - 1;
		sta[++top] = i;
	}
	printf("%lld\n", ans);

	fclose(stdin);
	fclose(stdout);
	return 0;
}
