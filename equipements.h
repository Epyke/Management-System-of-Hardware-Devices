typedef struct equipe
{
    int id;
    char type[30];
    char brand[20];
    int num_serie;
    char date[11];
    char state[20];
    char departement[30];
} EQUIPE;

typedef struct elem
{
    EQUIPE info;
    struct elem *seguinte;
} ELEM_E;

ELEM_E *importEquips();

int equipsRelease(ELEM_E **inicio);