#include <cstdio>
#include <cstring>

const int N = 100007;

int q, t, cnt = 0, tot = 0;
char c;

int len[N];

struct ChairmanTree
{
    int rt[N], val[N << 5], lson[N << 5], rson[N << 5];

    void build(int &rt, int fa, int l, int r, int po)
    {
        if (!rt)
            rt = ++tot;
        if (l == r)
        {
            val[rt] = c;
            return;
        }
        int mid = (l + r) >> 1;
        if (po <= mid)
            rson[rt] = rson[fa], build(lson[rt], lson[fa], l, mid, po);
        if (mid + 1 <= po)
            lson[rt] = lson[fa], build(rson[rt], rson[fa], mid + 1, r, po);
    }

    char qry(int rt, int l, int r, int po)
    {
        if (l == r)
            return val[rt];
        int mid = (l + r) >> 1;
        if (po <= mid)
            return qry(lson[rt], l, mid, po);
        if (mid + 1 <= po)
            return qry(rson[rt], mid + 1, r, po);
    }
} CT;

int main()
{
    scanf("%d", &q);
    while (q--)
    {
        scanf(" %c", &c);
        if (c == 'T')
        {
            scanf(" %c", &c);
            len[++cnt] = len[cnt - 1] + 1;
            CT.build(CT.rt[cnt], CT.rt[cnt - 1], 1, N, len[cnt]);
        }
        else if (c == 'U')
        {
            scanf("%d", &t);
            len[++cnt] = len[cnt - t - 1];
            CT.rt[cnt] = CT.rt[cnt- t - 1];
        }
        else
        {
            scanf("%d", &t);
            printf("%c\n", CT.qry(CT.rt[cnt], 1, N, t));
        }
    }
    return 0;
}
