#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

const int L = 3e2, W = 6e2, LEN = 30;

int w, l;
char str[L], words[W][LEN];
int f[L];

inline int min(int a, int b) { return a < b ? a : b; }

int main()
{
	freopen("lexicon.in", "r", stdin);
	freopen("lexicon.out", "w", stdout);

	scanf("%d%d%s", &w, &l, str + 1);
	for (int i = 1; i <= w; i++)
		scanf("%s", words[i] + 1);
	for (int i = 1; i <= l; i++)
	{
		f[i] = i;
		for (int j = 1; j <= w; j++)
		{
			int po = i, k = strlen(words[j] + 1), sum = 0;
			while (po && k)
			{
				if (str[po] == words[j][k]) k--;
				else sum++;
				po--;
			}
			if (!k) f[i] = min(f[i], f[po] + sum);
		}
	}
	printf("%d\n", f[l]);

	fclose(stdin);
	fclose(stdout);
	return 0;
}