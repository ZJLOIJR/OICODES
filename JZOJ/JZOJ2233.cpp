#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

int k, m, num[32];

int main()
{
	scanf("%d", &k);
	if (k == 1) printf("4\n");
	m = 1;
	while (k > (1 << m)) k -= (1 << m), m++;
	k--;
	while (k) { num[++num[0]] = k & 1, k >>= 1; }
	for (int i = m; i >= 1; i--) putchar(num[i] ? '7' : '4');
	putchar('\n');
	return 0;
}
