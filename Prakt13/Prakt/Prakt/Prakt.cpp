#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

typedef struct {
    int from;
    int to;
    double w;
} edge_t;

typedef struct set_t {
    struct set_t* p;
} set_t;

int NS;
set_t* sets;
int NE;
edge_t* E;
int NV;

int cmpw(edge_t* a, edge_t* b)
{
    if (a->w > b->w) return 1;
    if (a->w < b->w) return -1;
    return 0;
}

set_t*
get_set_id(set_t* s)
{
    if (s == s->p)
        return s;
    else {
        set_t* p = get_set_id(s->p);
        s->p = p;
        return p;
    }
}

set_t*
join_sets(set_t* a, set_t* b)
{
    a->p = b;
    return a;
}

void
take_edge(int edge_id)
{
    printf("%d %d %lf\n", E[edge_id].from, E[edge_id].to, E[edge_id].w);
}

int
main()
{
    int i;
    double W = 0;
    scanf_s("%d%d", &NV, &NE);
    E = (edge_t*)malloc(NE * sizeof(edge_t));
    sets = (set_t*)malloc(NV * sizeof(set_t));
    for (i = 0; i < NE; i++)
    {
        scanf_s("%d%d%lf", &E[i].from, &E[i].to, &E[i].w);
    }

    qsort(E, NE, sizeof(edge_t), (int (*)(const void*, const void*)) cmpw);

    NS = NV;
    for (i = 0; i < NS; i++)
        sets[i].p = &sets[i];

    for (i = 0; NS > 1 && i < NE; i++)
    {
        if (get_set_id(&sets[E[i].from]) == get_set_id(&sets[E[i].to]))
            continue;
        join_sets(get_set_id(&sets[E[i].from]), get_set_id(&sets[E[i].to]));
        NS--;
        take_edge(i);
        W += E[i].w;
    }

    if (NS != 1)
        fprintf(stderr, "warning: Graph is not connected.\n");
    printf("Covering tree weight = %lf\n", W);
}