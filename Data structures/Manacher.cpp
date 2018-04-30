#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

const int N = 1e7 + 1e6 + 7;

int n, len, mx = 0, id, ans = 0;
char s[N], str[N << 1];
int rad[N << 1];

int main()
{
	scanf("%s", s + 1);
	n = strlen(s + 1);
	str[0] = '!', str[++len] = '#';
	for (int i = 1; i <= n; i++) str[++len] = s[i], str[++len] = '#';
	str[++len] = '$';
	for (int i = 1; i <= len; i++)
	{
		if (mx > i) rad[i] = min(rad[id * 2 - i], mx - i);
		else rad[i] = 1;
		while (str[i + rad[i]] == str[i - rad[i]]) rad[i]++;
		if (i + rad[i] > mx)
		{
			mx = i + rad[i];
			id = i;
		}
		ans = max(ans, rad[i]);
	}
	printf("%d\n", ans - 1);
	return 0;
}
