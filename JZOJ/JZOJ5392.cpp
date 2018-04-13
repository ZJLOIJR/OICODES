#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 1e6 + 3;

int n, k;
char str[N];

int main()
{
	freopen("trans.in", "r", stdin);
	freopen("trans.out", "w", stdout);

	while (~scanf("%d%d%s", &n, &k, str + 1))
	{
		for (int i = 1; i <= n && k; i++)
		{
			if (str[i] == '2' && str[i + 1] == '3' && str[i + 2] == '3' && (i & 1)) k &= 1;
			if (k && str[i] == '2' && str[i + 1] == '3') str[i] = str[i + 1] = (i & 1) ? '2' : '3', i -= 2, k--;
		}
		printf("%s\n", str + 1);
	}

	fclose(stdin);
	fclose(stdout);
	return 0;
}
