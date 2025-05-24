
/**
 * @file departements.h
 * Header file responsável pela gestão dos departamentos.
 * @author Henrique Fernandes
 */

/**
 * @brief Estrutura de cada departamento
 */
typedef struct departements
{
    char name[20];
    int code;
} DEPART;

/**
 * @brief Estrutura de cada elemento da lista ligada dos departamentos
 */
typedef struct elem_d
{
    DEPART info;
    struct elem_d *seguinte;
} ELEM_D;

/**
 * @fn verifDepartNum(ELEM_D *inicio, int num);
 * @brief Verifica se o numero passado por argumento, corresponde ao numero de um departamento
 * Retorna 1, se encontrar
 * Retorna 0, se nenhum resultado for encontrado
 * @param inicio
 * @param num
 * @return int
 */
int verifDepartNum(ELEM_D *inicio, int num);

/**
 * @fn getDepartsNumb(ELEM_D *incio);
 * @brief Percorre a lista ligada dos departmaentos e retorna o numero de departamentos
 * Retorna 0, lista vazia
 * @param incio
 * @return int
 */
int getDepartsNumb(ELEM_D *incio);

ELEM_D *importDeparts();

int departsRelease(ELEM_D **inicio);

void printDeparts(ELEM_D *inicio);

int registrarDeparts(DEPART equip, ELEM_D **inicio);

int eliminarDepart(ELEM_D **inicio, int numero);

ELEM_D *procurarDepart(ELEM_D *inicio, int numero);

int writeChangesDeparts(ELEM_D *inicio);

void refreshDepartCodes(ELEM_D *inicio);