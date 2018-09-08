#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 2e5 + 7;

int n, a[N];
struct note { int val, cnt; } up[N], down[N];
int buc[N];

int operator<(note x, note y) { return x.val == y.val ? x.cnt < y.cnt : x.val < y.val; }
note max(note x, note y) { return x < y ? y : x; }
note min(note x, note y) { return x < y ? x : y; }

int main()
{
	freopen("seq.in", "r", stdin);
	freopen("seq.out", "w", stdout);

	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", a + i);
	up[1] = down[1] = (note){1, 1};
	a[1] = 1;
	for (int i = 2; i <= n; i++)
	{
		if (up[i - 1].cnt == 2) up[i] = (note){up[i - 1].val + 1, 1};
		else up[i] = (note){up[i - 1].val, 2};
		if (down[i - 1].cnt == 5) down[i] = (note){down[i - 1].val + 1, 1};
		else down[i] = (note){down[i - 1].val, down[i - 1].cnt + 1};
		if (a[i])
		{
			up[i] = min(up[i], (note){a[i], 2});
			down[i] = max(down[i], (note){a[i], 1});
		}
		if (i == n && up[i].cnt == 1) up[i] = (note){up[i - 1].val, up[i - 1].cnt + 1};
		if (i == n && down[i].cnt == 1) down[i] = (note){down[i - 1].val, down[i - 1].cnt + 1};
	}
	if (a[n] > 0)
	{
		if (a[n] > up[n].val || a[n] < down[n].val) { printf("-1\n"); return 0; }
	}
	else a[n] = up[n].val;
	for (int i = n; i >= 3; i--)
	{
		buc[a[i]]++;
		int nx = buc[a[i]] == 5 ? a[i] - 1 : a[i];
		if (nx > up[i - 1].val) nx = up[i - 1].val;
		if (down[i - 1].val <= nx && nx <= up[i - 1].val) a[i - 1] = nx;
		else { printf("-1\n"); return 0; }
	}
	printf("%d\n", a[n]);
	for (int i = 1; i <= n; i++) printf("%d ", a[i]);

	fclose(stdin);
	fclose(stdout);
	return 0;
}
