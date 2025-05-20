
typedef struct date
{
    int day, month, year;
} DATE;

typedef struct equipe
{
    int id;
    char type[30];
    char brand[20];
    char model[20];
    int num_serie;
    DATE date;
    char state[20];
    int departement;
} EQUIPE;

typedef struct elem_e
{
    EQUIPE info;
    struct elem_e *seguinte;
} ELEM_E;

ELEM_E *importEquips();

ELEM_E *procurarEquip(ELEM_E *inicio, int numero);

ELEM_E *procurarEquipDeparts(ELEM_E *inicio, int num);

int verifNumSerie(ELEM_E *inicio, int num_serie);

int equipsRelease(ELEM_E **inicio);

int getEquipsNumb(ELEM_E *inicio);

int registrarEquips(EQUIPE equip, ELEM_E **inicio);

void printEquips(ELEM_E *inicio);

int insIniListaEquips(ELEM_E **inicio, EQUIPE info);

int writeChangesEquips(ELEM_E *inicio);

int eliminarEquip(ELEM_E **inicio, int numero);

int RemoverEquipsDepartsNum(ELEM_E **inicio, int num);

void refreshEquipCodes(ELEM_E *inicio);

void refreshEquipDeparts(ELEM_E *inicio, int num);

int findExistingStrState(ELEM_E *inicio, char str[]);

int findExistingStrType(ELEM_E *inicio, char str[]);

int filterEquipsType(ELEM_E *inicio, char type[]);

int filterEquipsState(ELEM_E *inicio, char state[]);

int filterEquipsDeparts(ELEM_E *inicio, int num);

// Relatorio
int escreverRelatorioDeparts(ELEM_E *inicioEquips, int num);

int escreverRelatorioEstado(ELEM_E *inicioEquips, char state[]);

// Ordenar
ELEM_E *split(ELEM_E *inicioEquips);

ELEM_E *mergeEstado(ELEM_E *first, ELEM_E *second);

ELEM_E *MergeSort(ELEM_E *inicioEquips, int num);