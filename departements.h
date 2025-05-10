
typedef struct departements
{
    char name[20];
    int code;
} DEPART;

typedef struct elem_d
{
    DEPART info;
    struct elem_d *seguinte;
} ELEM_D;

int verifDepartNum(ELEM_D *inicio, int num);

int getDepartsNumb(ELEM_D *incio);

ELEM_D *importDeparts();

int departsRelease(ELEM_D **inicio);

void printDeparts(ELEM_D *inicio);

int registrarDeparts(DEPART equip, ELEM_D **inicio);

int eliminarDepart(ELEM_D **inicio, int numero);

ELEM_D *procurarDepart(ELEM_D *inicio, int numero);

int writeChangesDeparts(ELEM_D *inicio);

void refreshDepartCodes(ELEM_D **inicio);