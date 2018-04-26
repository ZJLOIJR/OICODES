#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 1e6 + 3;

int n, m, head, tail, a[N], que[N];

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%d", a + i);
	head = 1, tail = 0;
	for (int i = 1; i <= n; i++)
	{
		while (head <= tail && que[head] < i - m + 1) head++;
		while (head <= tail && a[i] <= a[que[tail]]) tail--;
		que[++tail] = i;
		if (i >= m) printf("%d ", a[que[head]]);
	}
	putchar('\n');
	head = 1, tail = 0;
	for (int i = 1; i <= n; i++)
	{
		while (head <= tail && que[head] < i - m + 1) head++;
		while (head <= tail && a[i] >= a[que[tail]]) tail--;
		que[++tail] = i;
		if (i >= m) printf("%d ", a[que[head]]);
	}
	return 0;
}
