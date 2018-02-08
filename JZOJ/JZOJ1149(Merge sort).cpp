#include <cstdio>
#include <cstdlib>

const int N = 2e5 + 3;

int n, a[N];

void merge(int l, int r)
{
	int mid = (l + r) >> 1;
	int i = l, j = mid + 1, le = 0;
	int *p = (int*)malloc(sizeof(int) * (r - l + 10));
	while (i <= mid && j <= r)
		if (a[i] < a[j])
			p[++le] = a[i], i++;
		else
			p[++le] = a[j], j++;
	while (i <= mid)
		p[++le] = a[i], i++;
	while (j <= r)
		p[++le] = a[j], j++;
	for (int i = l; i <= r; i++)
		a[i] = p[i - l + 1];
	free(p);
}

int mergesort(int l, int r)
{
	if (l < r)
	{
		int mid = (l + r) >> 1;
		mergesort(l, mid);
		mergesort(mid + 1, r);
	}
	merge(l, r);
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", a + i);
	mergesort(1, n);
	for (int i = 1; i <= n; i++)
		printf("%d\n", a[i]);
	return 0;
}
