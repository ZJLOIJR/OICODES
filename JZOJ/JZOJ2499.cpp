#include <cstdio>
#include <cstring>

const int LEN = 5e3 + 7;

int x, y, tx, ty, len, T;
char str[LEN];

int main()
{
	scanf("%s%d", str + 1, &T);
	len = strlen(str + 1);
	for (int i = 1; i <= len; i++)
		if (str[i] == 'N') tx++;
		else if (str[i] == 'S') tx--;
		else if (str[i] == 'W') ty--;
		else ty++;
	x = tx * (T / len), y = ty * (T / len);
	T %= len;
	for (int i = 1; i <= T; i++)
		if (str[i] == 'N') x++;
		else if (str[i] == 'S') x--;
		else if (str[i] == 'W') y--;
		else y++;
	printf("%d %d\n", y, x);
	return 0;
}
