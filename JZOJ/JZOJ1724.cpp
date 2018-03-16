#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 53;

int T, n;
int score[N];
char str[N];

int main()
{
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d", &n);
		memset(score, 0, sizeof(score));
		for (int i = 1; i <= n; i++)
		{
			scanf("%s", str + 1);
			for (int j = 1; j <= n; j++)
			{
				if (str[j] == '-') continue;
				if (str[j] == 'W') score[i] += 3;
				else if (str[j] == 'D') score[i]++, score[j]++;
				else if (str[j] == 'L') score[j] += 3;
			}
		}
		for (int i = 1; i <= n; i++) printf("%d ", score[i]);
		putchar('\n');
	}
	return 0;
}
