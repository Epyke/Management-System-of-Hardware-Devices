
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

/**
 * @fn importDeparts();
 * @brief Importa o contéudo do ficheiro data/departements.dat, criando uma lista ligada
 * Retorna o apontador do inicio da lista ligada
 * Retorna NULL, erro ao abrir o ficheiro
 * @return ELEM_D*
 */
ELEM_D *importDeparts();

/**
 * @fn departsRelease(ELEM_D **inicio);
 * @brief Liberta a memoria ocupada pela lista ligada de departamentos.
 * Retorn -1, lista vazia
 * Retorna 0, operação concluida
 * @param inicio
 * @return int
 */
int departsRelease(ELEM_D **inicio);

/**
 * @fn printDeparts(ELEM_D *inicio);
 * @brief Escreve todos os departamentos da respetiva lista ligada.
 * @param inicio
 */
void printDeparts(ELEM_D *inicio);

/**
 * @fn registrarDeparts(DEPART equip, ELEM_D **inicio);
 * @brief Regista um novo departamento.
 * Escreve a estrutura passada como argumento para o ficheiro data/departements.dat
 * Insere a estrutura passada como paramêtre no inicio da lista ligada dos departamentos.
 * Retorna
 * @param equip
 * @param inicio
 * @return int
 */
int registrarDeparts(DEPART equip, ELEM_D **inicio);

/**
 * @fn eliminarDepart(ELEM_D **inicio, int numero);
 * @brief Elimina um determinado departamento, escolhido pelo argumento número.
 * Retorna 0, operação concluida com sucesso.
 * Retorna -1, nenhum resultado encontrado.
 * @param inicio
 * @param numero
 * @return int
 */
int eliminarDepart(ELEM_D **inicio, int numero);

/**
 * @fn procurarDepart(ELEM_D *inicio, int numero);
 * @brief Função que procura um determinado departamento consoante o argumento número.
 * Retorna o apontador para o elemento da lista que possui o departamento encontrado
 * Retorna NULL, nenhum resultado encontrado
 * @param inicio
 * @param numero
 * @return ELEM_D*
 */
ELEM_D *procurarDepart(ELEM_D *inicio, int numero);

/**
 * @fn writeChangesDeparts(ELEM_D *inicio);
 * @brief Escreve para o ficheiro data/departements.c a lista ligada dos departamentos.
 * Retorna 0, operação concluida com sucesso
 * Retorna -1, Erro ao abrir o ficheiro
 * @param inicio
 * @return int
 */
int writeChangesDeparts(ELEM_D *inicio);

/**
 * @fn refreshDepartCodes(ELEM_D *inicio);
 * @brief Atualiza o número dos departamentos, de modo a estes serem todos consecutivos.
 * Função usada quando se elimina um elemento.
 * @param inicio
 */
void refreshDepartCodes(ELEM_D *inicio);