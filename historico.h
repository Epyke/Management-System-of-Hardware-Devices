typedef struct date_h
{
    int day, month, year;
} DATE_H;

typedef struct historico
{
    char tipo[20];
    int id;
    char type[30];
    char brand[20];
    char model[20];
    char desc[100];
    DATE_H data;
} HISTORICO;

typedef struct elem_h
{
    HISTORICO info;
    struct elem_h *seguinte;
} ELEM_H;

ELEM_H *importHistorico();

int insIniListaHistorico(ELEM_H **inicio, HISTORICO info);

int registrarHistorico(HISTORICO equip, ELEM_H **inicio);

void printHistorico(ELEM_H *inicio);