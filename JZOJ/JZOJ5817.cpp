#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 1e3 + 7;

int T, lens, lent;
char ch, s[N], t[N];
char buc[256];

int let(char c) { return c >= 'a' && c <= 'z'; }
int dig(char c) { return c >= '0' && c <= '9'; }
int check(char c) { return let(c) || c == ' ' || c == ';' || dig(c); }

int main()
{
	freopen("copycat.in", "r", stdin);
	freopen("copycat.out", "w", stdout);

	scanf("%d", &T); getchar();
	while (T--)
	{
		memset(buc, 0, sizeof(buc));
		memset(s, 0, sizeof(s));
		memset(t, 0, sizeof(t));
		lens = lent = 0;
		do
		{
			ch = getchar();
			s[++lens] = ch;
		} while (check(ch));
		do
		{
			ch = getchar();
			t[++lent] = ch;
		} while (check(ch));
		lens--, lent--;
		int flag = 1;
		if (lens != lent) { printf("0\n"); continue; }
		for (int i = 1; i <= lens; i++)
		{
			if (!let(s[i]) && s[i] != t[i]) { flag = 0; break; }
			else if (let(s[i]))
			{
				if (buc[s[i]] && t[i] != buc[s[i]]) { flag = 0; break; }
				else buc[s[i]] = t[i];
			}
		}
		printf("%d\n", flag);
	}
	
	fclose(stdin);
	fclose(stdout);
	return 0;
}
