typedef struct date
{
    int day, month, year;
} DATE;

typedef struct historico
{
    char tipo[20];
    char desc[50];
    DATE data;
} HISTORICO;

typedef struct elem
{
    HISTORICO info;
    struct elem *seguinte;
} ELEM_H;

ELEM_H *importHistorico();

int insIniListaHistorico(ELEM_H **inicio, HISTORICO info);

int registrarHistorico(HISTORICO equip, ELEM_H **inicio);