#include <cstdio>
#include <cstring>
#include <cstdlib>

const int LEN = 40;

int l, r;
int f[LEN][LEN];
int len, num[LEN];

int solve(int n)
{
	len = 0;
	while (n) num[++len] = n & 1, n >>= 1;
	int ret = 0;
	for (int i = n; i >= 0; i--)
		if (i > n / 2) ret += dfs(n, i, );
}

int main()
{
	freopen("input", "r", stdin);
	freopen("output", "w", stdout);
	//freopen("rndnum.in", "r", stdin);
	//freopen("rndnum.out", "w", stdout);
	
	scanf("%d%d", &l, &r);
	printf("%d\n", solve(r) - solve(l - 1));

	fclose(stdin);
	fclose(stdout);
	return 0;
}
