#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 1e5 + 3;

int n, ans = 0, a[N], b[N], c[N], cnt1[N], cnt2[N], del[N];

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", a + i);
	for (int i = 1; i <= n; i++) scanf("%d", b + i), cnt1[b[i]]++;
	for (int i = 1; i <= n; i++) scanf("%d", c + i), cnt2[c[i]]++;
	while (1)
	{
		int flag = 0;
		for (int i = 1; i <= n; i++)
			if (!del[i] && (!cnt1[a[i]] || !cnt2[a[i]]))
				ans++, del[i] = 1, cnt1[b[i]]--, cnt2[c[i]]--, flag = 1;
		if (!flag) break;
	}
	printf("%d\n", ans);
	return 0;
}
