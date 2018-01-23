#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 1e5 + 3, M = 4e6 + 7;

int n, q, po, len;
char str[M];
int f[N][26];

int main()
{
	freopen("isfind.in", "r", stdin);
	freopen("isfind.out", "w", stdout);

	memset(f, 0xff, sizeof(f));
	scanf("%d%d%s", &n, &q, str + 1);
	for (int i = n; i >= 1; i--)
		for (int j = 0; j < 26; j++)
			if (j + 'a' == str[i]) f[i][j] = i;
			else f[i][j] = f[i + 1][j];
	while (q--)
	{
		scanf("%s", str + 1);
		po = 1, len = strlen(str + 1);
		for (int i = 1; i <= len; i++)
		{
			po = f[po][str[i] - 'a'];
			if (po == -1)
			{
				printf("N\n");
				break;
			}
			else po++;
		}
		if (po != -1) printf("Y\n");
	}

	fclose(stdin);
	fclose(stdout);
	return 0;
}