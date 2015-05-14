#include <cstdio>
#include <cstdlib>
#include <cstring>

typedef struct {
    char used;
    char *name;
    double cost, sell;
    int n;
} ITEM;

ITEM item[100];

char *StrDup(char *s)
{
    char *p = (char*)malloc(strlen(s) + 1);
    strcpy(p, s);
    return p;
}

int Comp_Item(void const *a, void const *b)
{
    return strcmp((*((ITEM**)a))->name, (*((ITEM**)b))->name);
}

int main()
{
    int i, n, c = 0;
    char cmd[16], name[16];
    double profit = 0.0;
    memset(item, 0, 100 * sizeof(ITEM));

    while(scanf("%s", cmd) == 1 && *cmd != '*') {
        if(*cmd == 'n') { //new
            for(i = 0; i < 100; i++)
                if(!item[i].used) break;

            scanf("%s %lf %lf", name, &item[i].cost, &item[i].sell);
            item[i].used = 1, item[i].n = 0, item[i].name = StrDup(name);
            continue;
        }

        if(*cmd == 'r') { //report
            ITEM *ptr[100];
            double total = 0.0;

            for(i = n = 0; i < 100; i++)
                if(item[i].used) ptr[n++] = &item[i],
                                                total += (double)item[i].n * item[i].cost;

            qsort(ptr, n, sizeof(ITEM*), Comp_Item);

            if(c++) printf("\n");

            printf("                  INVENTORY REPORT\n");
            printf("Item Name     Buy At      Sell At      On Hand"
                   "        Value\n");
            printf("---------     ------      -------      -------"
                   "        -----\n");

            for(i = 0; i < n; i++)
                printf("%-14s%6.2f%13.2f%13d%13.2f\n",
                       ptr[i]->name, ptr[i]->cost, ptr[i]->sell, ptr[i]->n,
                       (double)ptr[i]->n * ptr[i]->cost);

            printf("------------------------\n");
            printf("Total value of inventory%35.2f\n", total);
            printf("Profit since last report%35.2f\n", profit);
            profit = 0.0;
            continue;
        }

        scanf("%s", name);

        for(i = 0; i < 100; i++)
            if(item[i].used && strcmp(item[i].name, name) == 0) break;

        if(*cmd == 'd') { //delete
            profit -= (double)item[i].n * item[i].cost, item[i].used = 0;
            free(item[i].name);
        } else if(*cmd == 's') { //sell
            scanf("%d", &n);
            profit += (double)n * (item[i].sell - item[i].cost);
            item[i].n -= n;
        } else if(*cmd == 'b') { //buy
            scanf("%d", &n);
            item[i].n += n;
        }
    }
	return 0;
}
