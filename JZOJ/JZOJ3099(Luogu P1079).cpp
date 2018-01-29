#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

const int LEN = 1007;

int lenkey, lenm;
char key[LEN], m[LEN];

char R(char x, char y)
{
	int upcase = x < 'a';
	x = x + upcase * 32;
	return ((x - 'a') - (y - 'a') + 26) % 26 + 'a' - upcase * 32;
}

int main()
{
	scanf("%s%s", key + 1, m + 1);
	lenkey = strlen(key + 1), lenm = strlen(m + 1);
	for (int i = 1; i <= lenkey; i++) key[i] = key[i] < 'a' ? key[i] + 32 : key[i];
	for (int i = 1, j = 1; i <= lenm; i++)
	{
		if (j > lenkey) j = 1;
		putchar(R(m[i], key[j++]));
	}
	return 0;
}
