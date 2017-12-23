#include <cstdio>
#include <cstring>

const int N = 5000007;

int n, len, mx, id, ans;

char s[N], str[N << 1];

int rad[N << 1];

inline int max(int a, int b) { return a > b ? a : b; }
inline int min(int a, int b) { return a < b ? a : b; }

void init()
{
	scanf("%s", s + 1);

	str[len = 0] = '$';
	str[++len] = '#';
	
	n = strlen(s + 1);
	for (int i = 1; i <= n; i++)
		str[++len] = s[i], str[++len] = '#';
	str[++len] = '!';
}

void solve()
{
	mx = id = ans = 0;

	for (int i = 1; i <= len; i++)
	{
		if (mx > i)
			rad[i] = min(rad[(id << 1) - i], mx - i);
		else
			rad[i] = 1;

		while (str[i + rad[i]] == str[i - rad[i]])
			rad[i]++;

		if (i + rad[i] > mx)
		{
			mx = i + rad[i];
			id = i;
		}

		ans = max(ans, rad[i]);
	}

	printf("%d\n", ans - 1);
}

int main()
{
	init();
	solve();
	return 0;
}
