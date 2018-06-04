#include <cstdio>

int a, b, c, mx, mxans = 0;
int buc[100];

int main()
{
	scanf("%d%d%d", &a, &b, &c);
	for (int i = 1; i <= a; i++)
		for (int j = 1; j <= b; j++)
			for (int k = 1; k <= c; k++)
				buc[i + j + k]++;
	for (int i = 99; i >= 1; i--) if (buc[i] >= mx) mx = buc[i], mxans = i;
	printf("%d\n", mxans);
	return 0;
}
