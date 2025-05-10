typedef struct equipe
{
    int id;
    char type[30];
    char brand[20];
    int num_serie;
    char date[11];
    char state[20];
    int departement;
} EQUIPE;

typedef struct elem
{
    EQUIPE info;
    struct elem *seguinte;
} ELEM_E;

ELEM_E *importEquips();

int verifNumSerie(ELEM_E *inicio, int num_serie);

int equipsRelease(ELEM_E **inicio);

int getEquipsNumb(ELEM_E *inicio);

int registrarEquips(EQUIPE equip, ELEM_E **inicio);

void printEquips(ELEM_E *inicio);

int insIniListaEquips(ELEM_E **inicio, EQUIPE info);

int writeChangesEquips(ELEM_E *inicio);