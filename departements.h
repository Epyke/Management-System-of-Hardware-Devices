#include "equipements.h"

typedef struct departements
{
    char name[20];
    int code;
    ELEM_E *inicioEquips;
} DEPART;

typedef struct elem_d
{
    DEPART info;
    struct elem_d *seguinte;
} ELEM_D;

int getDepartsNumb(ELEM_D *incio);

ELEM_D *importDeparts();

int departsRelease(ELEM_D **inicio);

void printDeparts(ELEM_D *inicio);

int registrarDeparts(DEPART equip, ELEM_D **inicio);