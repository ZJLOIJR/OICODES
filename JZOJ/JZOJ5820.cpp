#include <cstdio>
#include <cstring>
#include <cstdlib>

typedef long long ll;
const int LEN = 1e4 + 7;
const ll MAX = 2147483648;

int T, len;
char ch, str[LEN];

int range(ll a) { return -MAX <= a && a < MAX; }
int ok(char c) { return (c >= '0' && c <= '9') || c == '-'; }

void check()
{
	if (len <= 0) { printf("Input Error\n"); return; }
	if (!ok(str[1]) || !ok(str[len])) { printf("Input Error\n"); return; }
	int sp = 1;
	while (str[sp] != ' ' && sp <= len) sp++;
	if (sp > len) { printf("Input Error\n"); return; }
	for (int i = 1, cntf = 0; i <= sp - 1; i++)
	{
		if (!ok(str[i])) { printf("Input Error\n"); return; }
		if (str[i] == '-') cntf++;
		if (cntf > 1) { printf("Input Error\n"); return; }
	}
	for (int i = sp + 1, cntf = 0; i <= len; i++)
	{
		if (!ok(str[i])) { printf("Input Error\n"); return; }
		if (str[i] == '-') cntf++;
		if (cntf > 1) { printf("Input Error\n"); return; }
	}
	ll a = 0, b = 0;
	int i = 1, f = 1;
	if (str[i] == '-') i++, f = -1;
	if (str[i] == '0')
	{
		if (str[i - 1] == '-' || sp - i - 1) { printf("Input Error\n"); return; }
	}
	if (sp - i < 1) { printf("Input Error\n"); return; }
	for (; i <= sp - 1; i++)
	{
		if (!(str[i] >= '0' && str[i] <= '9')) { printf("Input Error\n"); return; }
		a = a * 10 + str[i] - '0';
		if (!range(f * a)) { printf("Input Error\n"); return; }
	}
	a *= f;
	i = sp + 1, f = 1;
	if (str[i] == '-') i++, f = -1;
	if (len - i + 1 < 1) { printf("Input Error\n"); return; }
	if (str[i] == '0')
	{
		if (str[i - 1] == '-' || len - i) { printf("Input Error\n"); return; }
	}
	for (; i <= len; i++)
	{
		if (!(str[i] >= '0' && str[i] <= '9')) { printf("Input Error\n"); return; }
		b = b * 10 + str[i] - '0';
		if (!range(f * b)) { printf("Input Error\n"); return; }
	}
	b *= f;
	printf("%lld\n", a + b);
}

int main()
{
	freopen("aplusb.in", "r", stdin);
	freopen("aplusb.out", "w", stdout);

	scanf("%d", &T); getchar();
	while (T--)
	{
		len = 0; memset(str, 0, sizeof(str));
		do
		{
			ch = getchar();
			str[++len] = ch;
		} while (ch != '\n');
		len--;
		check();
	}

	fclose(stdin);
	fclose(stdout);
	return 0;
}
