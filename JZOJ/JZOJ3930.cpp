#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

const int RES[5][5] = {{2, 0, 1, 1, 0}, {1, 2, 0, 1, 0}, {0, 1, 2, 0, 1}, {0, 0, 1, 2, 1}, {1, 1, 0, 0, 2}};

int gcd(int x, int y)
{ return y ? gcd(y, x % y) : x; }

int n, na, nb, lcm, ans1, ans2, sum1, sum2;
int a[203], b[203];

int main()
{
	scanf("%d%d%d", &n, &na, &nb);
	for (int i = 1; i <= na; i++) scanf("%d", a + i);
	for (int i = 1; i <= nb; i++) scanf("%d", b + i);
	lcm = na * nb / gcd(na, nb);
	sum1 = sum2 = 0;
	for (int i = 1, j = 1, k = 1; i <= lcm; i++)
	{
		if (RES[a[j]][b[k]] == 1) sum1++;
		else if (RES[b[k]][a[j]] == 1) sum2++;
		j++, k++;
		if (j > na) j = 1;
		if (k > nb) k = 1;
	}
	ans1 += n / lcm * sum1, ans2 += n / lcm * sum2;
	n %= lcm;
	for (int i = 1, j = 1, k = 1; i <= n; i++)
	{
		if (RES[a[j]][b[k]] == 1) ans1++;
		else if (RES[b[k]][a[j]] == 1) ans2++;
		j++, k++;
		if (j > na) j = 1;
		if (k > nb) k = 1;
	}
	printf("%d %d\n", ans1, ans2);
	return 0;
}
