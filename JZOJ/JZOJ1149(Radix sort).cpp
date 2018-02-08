#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
using namespace std;

int n, d[200005];

int getdig(int n, int x)
{
	x--;
	while (x--)
		n /= 10;
	return n % 10;
}

void radix_sort(int a[], int len)
{
	vector<int> b[10];
	int po = 1;
	do
	{
		int l = 0;
		for (int i = 1; i <= len; i++)
			b[getdig(a[i], po)].push_back(a[i]);
		for (int i = 0; i < 10; i++)
		{
			int s = b[i].size();
			for (int j = 0; j < s; j++)
				a[++l] = b[i].at(j);
				b[i].clear();
		}
		po++;
	} while (po < 15);
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", d + i);
	radix_sort(d, n);
	for (int i = 1; i <= n; i++)
		printf("%d\n", d[i]);
	return 0;
}
