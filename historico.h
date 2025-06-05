/**
 * @file historico.h
 * Header file responsável pela gestão do histórico.
 * @author Henrique Fernandes
 */

/**
 * @brief Estrutura data do historico
 */
typedef struct date_h
{
    int day, month, year;
} DATE_H;

/**
 * @brief Estruta avaria
 */
typedef struct avaria
{
    int gravidade;
    char descAvaria[50];
    int recorrencias;
} AVARIA;

/**
 * @brief Estrutura manutencao
 */
typedef struct manutencao
{
    char tecnico[20];
} MANUTENCAO;

/**
 * @brief Estrutura reparacao
 */
typedef struct reparacao
{
    float custo;
    char tecnico[20];
    char pecas_substituidas[20];
} REPARACAO;

/**
 * @brief Estrutura movimentacao
 */
typedef struct movimentacao
{
    char previousDep[20];
    char newDep[20];
} MOVIMENTACAO;

/**
 * @brief Estrutura historico com varios tipos (avaria, manutencao, movimentacao, reparacao).
 */
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

/**
 * @brief Estrutura de cada elemento, da lista ligada Historico
 */
typedef struct elem_h
{
    HISTORICO info;
    struct elem_h *seguinte;
} ELEM_H;

/**
 * @fn importHistorico();
 * @brief Importa os dados presentes no ficheiro data/historico.dat, para uma lista ligada.
 * Retorna um apontador para o inicio da lista ligada Historico
 * Retorna NULL, erro ao abrir o ficheiro
 * @return ELEM_H*
 */
ELEM_H *importHistorico();

/**
 * @fn historicoRelease(ELEM_H **inicio);
 * @brief Liberta a memória ocupada por a lista ligada, com a estrutura (ELEM_H) como elemento.
 * Retorna 0, operação concluida
 * Retorna -1, lista vazia
 * @param inicio
 * @return int
 */
int historicoRelease(ELEM_H **inicio);

/**
 * @fn insIniListaHistorico(ELEM_H **inicio, HISTORICO info);
 * @brief Insere um elemento no inicio da lista ligada com a estrutura (ELEM_H).
 * return 0, operação concluida com sucesso
 * return -1, out of memory
 * @param inicio
 * @param info
 * @return int
 */
int insIniListaHistorico(ELEM_H **inicio, HISTORICO info);

/**
 * @fn registrarHistorico(HISTORICO historico, ELEM_H **inicio);
 * @brief Guarda os dados da estrutura HISTORICO
 * Escreve para o ficheiro data/historico.dat
 * Retorna 0, operação concludia com sucesso
 * Retorna -1, erro ao abrir o ficheiro
 * @param equip
 * @param inicio
 * @return int
 */
int registrarHistorico(HISTORICO historico, ELEM_H **inicio);

/**
 * @fn void printHistorico(ELEM_H *inicio);
 * @brief Escreve o historico de movimentações, manutenções, reparações e avarias de todos os equipamentos.
 * @param inicio
 */
void printHistorico(ELEM_H *inicio);

/**
 * @fn void printHistoricoEquipID(ELEM_H *inicio, int ID);
 * @brief Escreve o historico de movimentações, manutenções, reparações e avarias de um equipamento em específico (ID passado por parâmetro).
 * @param inicio
 * @param ID
 */
void printHistoricoEquipID(ELEM_H *inicio, int ID);

/**
 * @fn printAvariasRecorrencia(ELEM_H *inicio);
 * @brief Escreve as avarias recorrentes (recorrencia > 3)
 * Retorna 0, oepração concluida
 * Retorna -1, Lista vazia
 * @param inicio
 * @return int
 */
int printAvariasRecorrencia(ELEM_H *inicio);

/**
 * @fn verifMesmaAvariaExistente(ELEM_H *inicio, char descAvaria[]);
 * @brief Verifica se existe duas avarias iguais
 * Returna o número de recorrencias de uma avaria
 * Return 0, se não existir recorrencia
 * @param inicio
 * @param descAvaria
 * @param ID
 * @return int
 */
int verifMesmaAvariaExistente(ELEM_H *inicio, char descAvaria[], int ID);

/**
 * @fn verifAvariasRecorrentes(ELEM_H *inicio);
 * @brief Verifica se existe uma avaria recorrente
 * Retorna 1 se existir
 * Retorna 0 se não existir
 * @param inicio
 */
int verifAvariasRecorrentes(ELEM_H *inicio);

/**
 * @fn verifExistingAvariaRecorrente(ELEM_H *inicio)
 * @brief Verifica se existe uam avaria recorrente
 * Retorna 1 se existir
 * Retorna 0 se não existir
 */
int verifExistingAvariaRecorrente(ELEM_H *inicio);