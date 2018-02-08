#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 2e5 + 3;

int n, a[N];

void swap(int& a, int& b)
{ int t = a; a = b, b = t; }

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", a + i);
	for (int gap = n >> 1; gap > 0; gap >>= 1)
		for (int i = gap + 1; i <= n; i++)
		{
			int j = i;
			while (j - gap > 0 && a[j] < a[j - gap])
			{
				swap(a[j], a[j - gap]);
				j -= gap;
			}
		}
	for (int i = 1; i <= n; i++)
		printf("%d\n", a[i]);
	return 0;
}
