typedef struct date_h
{
    int day, month, year;
} DATE_H;

typedef struct avaria
{
    int gravidade;
    char descAvaria[50];
    int recorrencias;
} AVARIA;

typedef struct manutencao
{
    char tecnico[20];
} MANUTENCAO;

typedef struct reparacao
{
    float custo;
    char tecnico[20];
    char pecas_substituidas[20];
} REPARACAO;

typedef struct movimentacao
{
    char previousDep[20];
    char newDep[20];
} MOVIMENTACAO;

typedef struct historico
{
    char tipo[20];
    int id;
    char equipTipo[30];
    char brand[20];
    char model[20];
    DATE_H data;

    union
    {
        AVARIA avaria;
        MANUTENCAO manutencao;
        REPARACAO reparacao;
        MOVIMENTACAO movimentacao;
    } desc;

} HISTORICO;

typedef struct elem_h
{
    HISTORICO info;
    struct elem_h *seguinte;
} ELEM_H;

ELEM_H *importHistorico();

int insIniListaHistorico(ELEM_H **inicio, HISTORICO info);

int registrarHistorico(HISTORICO equip, ELEM_H **inicio);

void printHistoricoMovMan(ELEM_H *inicio);

void printHistoricoEquipIDMovMan(ELEM_H *inicio, int ID);