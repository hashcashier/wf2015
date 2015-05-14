#include <cstdio>
#include <cstring>
#include <algorithm>

typedef struct {
    char name[11];
    int on_hand;
    float buy, sell;
} Ware;

int Read(char **name, int *i1, float *f1, float *f2)
{
    static char str[20];
    *name = str;
    scanf("%s", str);

    if(!strcmp(str, "report")) return 5;

    if(!strcmp(str, "new")) {
        scanf("%s %f %f", str, f1, f2);
        return 1;
    } else if(!strcmp(str, "delete")) {
        scanf("%s", str);
        return 2;
    } else if(!strcmp(str, "buy")) {
        scanf("%s %d", str, i1);
        return 3;
    } else if(!strcmp(str, "sell")) {
        scanf("%s %d", str, i1);
        return 4;
    } else {
        return 0;
    }
}

int Cmp(const void *av, const void *bv)
{
    Ware *a = (Ware*)av;
    Ware *b = (Ware*)bv;
    return strcmp(a->name, b->name);
}

int Lookup(Ware w[], int nw, char *name)
{
    int i;

    for(i = 0; i < nw; i++)
        if(!strcmp(w[i].name, name))
            return i;

    return 0;
}

int main()
{
    Ware w[100];
    int nw, cmd, i, in;
    float f, g, profit = 0;
    char *name;

    while((cmd = Read(&name, &i, &f, &g))) {
        if(cmd == 5) {
            qsort(w, nw, sizeof(Ware), Cmp);
            printf("%35s", "INVENTORY REPORT\n");
            printf("Item Name     Buy At      Sell At      On Hand        Value\n");
            printf("---------     ------      -------      -------        -----\n");
            f = 0;

            for(i = 0; i < nw; i++) {
                printf("%-14s%6.2f%13.2f%13d%13.2f\n", w[i].name, w[i].buy,
                       w[i].sell, w[i].on_hand, w[i].on_hand * w[i].buy);
                f += w[i].on_hand * w[i].buy;
            }

            printf("------------------------\n");
            printf("Total value of inventory %34.2f\n", f);
            printf("Profit since last report %34.2f\n\n", profit);
            profit = 0;
        } else {
            if(cmd != 1) in = Lookup(w, nw, name);

            switch(cmd) {
                case 1:
                    strcpy(w[nw].name, name);
                    w[nw].buy = f;
                    w[nw].sell = g;
                    w[nw].on_hand = 0;
                    nw++;
                    break;

                case 2:
                    profit -= w[in].on_hand * w[in].buy;
                    w[in] = w[--nw];
                    break;

                case 3:
                    w[in].on_hand += i;
                    break;

                case 4:
                    profit += i * (w[in].sell - w[in].buy);
                    w[in].on_hand -= i;
                    break;
            }
        }
    }

    return 0;
}
