
/**
 * @file equipements.h
 * Header file responsável pela gestão dos equipamentos.
 * @author Henrique Fernandes
 */

/**
 * @brief Estrutura data dos equipamentos
 *
 */
typedef struct date
{
    int day, month, year;
} DATE;

/**
 * @brief Estrutura dos equipamentos
 *
 */
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
    char tecnico[20];
} EQUIPE;

/**
 * @brief Estrutura de cada elemento da lista ligada dos equipamentos.
 *
 */
typedef struct elem_e
{
    EQUIPE info;
    struct elem_e *seguinte;
} ELEM_E;

/**
 * @fn importEquips();
 * @brief Importa o conteúdo do ficheiro data/equipamentos.dat para a lista ligada dos equipamentos.
 * Retorna o apontador do inicio da lista ligada.abort
 * Retorna NULL, se ocorrer um erro ao abrir o ficheiro.
 * @return ELEM_E*
 */
ELEM_E *importEquips();

// Funções de procura

/**
 * @fn procurarEquipManutencaoUser(ELEM_E *inicio, int num, char username[]);
 * @brief Procura um determinado equipamento em manutencção de um tecnico em específico.
 * Retorna o apontador do elemento que possui o equipamento encontrado.
 * Retorna NULL se nenhum resultado for encontrado.
 * @param inicio
 * @param num
 * @param username
 * @return ELEM_E*
 */
ELEM_E *procurarEquipManutencaoUser(ELEM_E *inicio, int num, char username[]);

/**
 * @fn procurarEquip(ELEM_E *inicio, int numero);
 * @brief Procura um determiando equipamento na lista ligada dos equipamentos.
 * Retorna o apontador do elemento que possui o equipamento encontrado.
 * Retorna NULL se nenhum resultado for encontrado.
 * @param inicio
 * @param numero
 * @return ELEM_E*
 */
ELEM_E *procurarEquip(ELEM_E *inicio, int numero);

/**
 * @fn procurarEquipDanificados(ELEM_E *inicio, int num);
 * @brief Procura um determinado equipamento danificado
 * Retorna o apontador do elemento que possui o equipamento encontrado.
 * Retorna NULL se nenhum resultado for encontrado.
 * @param inicio
 * @param num
 * @return ELEM_E*
 */
ELEM_E *procurarEquipDanificados(ELEM_E *inicio, int num);

/**
 * @fn procurarEquipUsoDesativado(ELEM_E *inicio, int num);
 * @brief Procura por um determinado equipamento em uso ou desativado
 * Retorna o apontador do elemento que possui o equipamento encontrado.
 * Retorna NULL se nenhum resultado for encontrado.
 * @param inicio
 * @param num
 * @return ELEM_E*
 */
ELEM_E *procurarEquipUsoDesativado(ELEM_E *inicio, int num);

/**
 * @fn verifEquipDeparts(ELEM_E *inicio, int num);
 * @brief Verifica se existe equipamentos atribuidos à um determinado departamento.
 * Retorna 1 se exisitr.
 * Retorna 0 se não encontrar nenhum resultado.
 * @param inicio
 * @param num
 * @return ELEM_E*
 */
int verifEquipDeparts(ELEM_E *inicio, int num);

/**
 * @fn verifNumSerie(ELEM_E *inicio, int num_serie);
 * @brief Verifica se já existe um equipamento com o mesmo número de serie.
 * Retorna 1, se existir
 * Retorna 0, se não exisitir
 * @param inicio
 * @param num_serie
 * @return int
 */
int verifNumSerie(ELEM_E *inicio, int num_serie);

/**verifEquipsExistTecnico(ELEM_E *inicio, char tecnico[])
 * @brief Verifica se existe um equipamento atribuido a um determinado,
 * Retorna 1 se existir
 * Retorna 0 se não exisitr
 * @param inicio
 * @param tecnico
 * @return int
 */
int verifEquipsExistTecnico(ELEM_E *inicio, char tecnico[]);

/**
 * @fn equipsRelease(ELEM_E **inicio);
 * @brief Liberta a memória ocupada pela lista ligada dos equipamentos.
 * Retorna 0, operação concluida com sucesso.
 * Retorna -1, lista vazia
 * @param inicio
 * @return int
 */
int equipsRelease(ELEM_E **inicio);

/**
 * @fn getEquipsNumb(ELEM_E *inicio);
 * @brief Calcula o número de equipamentos.
 * Retorna o número de equipamentos.
 * Retorna 0, se a lista for vazia
 * @param inicio
 * @return int
 */
int getEquipsNumb(ELEM_E *inicio);

/**
 * @fn registrarEquips(EQUIPE equip, ELEM_E **inicio);
 * @brief Regista um novo equipamento
 * Retorna 0, operação concluida com sucesso.
 * Retorna -1, Erro ao abrir o ficheiro.
 * @param equip
 * @param inicio
 * @return int
 */
int registrarEquips(EQUIPE equip, ELEM_E **inicio);

/**
 * @fn printEquips(ELEM_E *inicio);
 * @brief Escreve as informações de todos os equipamentos
 * @param inicio
 */
void printEquips(ELEM_E *inicio);

/**
 * @brief Escreve as informação de todos equipamentos que foram adquiridos hà mais de 5 anos
 * @param inicio
 */
void printAlertas(ELEM_E *inicio);

/**
 * @brief  Escreve as informação dos equipamentos de um determinado técnico.
 *
 * @param inicio
 * @param tecnico
 */
void printEquipsTecnico(ELEM_E *inicio, char tecnico[]);

/**
 * @brief Inserir um novo elemento no inicio da lista ligada dos equipamentos
 * Retorna 0, operação conluida com sucesso.
 * Retorna -1, out of memory.
 * @param inicio
 * @param info
 * @return int
 */
int insIniListaEquips(ELEM_E **inicio, EQUIPE info);

/**
 * @fn writeChangesEquips(ELEM_E *inicio);
 * @brief Guarda as alterações efetuadas nos equipamentos no ficheiro data/equipements.dat.
 * Retorna 0, operação concluida com sucesso.
 * Retorna -1, erro ao abrir o ficheiro.
 * @param inicio
 * @return int
 */
int writeChangesEquips(ELEM_E *inicio);

/**
 * @fn eliminarEquip(ELEM_E **inicio, int numero);
 * @brief Elimina um determinado equipamento da lista ligada.
 * Reotrna 0, operação concluida com sucesso
 * Retorna -1,nenhum equipamento encontrado.
 * @param inicio
 * @param numero
 * @return int
 */
int eliminarEquip(ELEM_E **inicio, int numero);

/**
 * @fn RemoverEquipsDepartsNum(ELEM_E **inicio, int num);
 * @brief Remove todos os equipamentos atribuidos à um determinado departamento.
 * Retorna o número de equipamentos removidos.
 * @param inicio
 * @param num
 * @return int
 */
int RemoverEquipsDepartsNum(ELEM_E **inicio, int num);

/**
 * @fn refreshEquipCodes(ELEM_E *inicio);
 * @brief Atualiza o ID dos equipamentos de foram a estes serem números consecutivos.
 * Função para usar após a remoção de um equipamento.
 * @param inicio
 */
void refreshEquipCodes(ELEM_E *inicio);

/**
 * @fn refreshEquipDeparts(ELEM_E *inicio, int num);
 * @brief Atualiza o num do departamento atribuida a cada equipamento, de forma a este ser consecutivo.
 * Função para usar após a remoção de um departamento.
 *
 * @param inicio
 * @param num
 */
void refreshEquipDeparts(ELEM_E *inicio, int num);

/**
 * @fn findExistingStrState(ELEM_E *inicio, char str[]);
 * @brief Verifica se existe um determinado estado.
 * Retorna 1, se existir
 * Retorna 0, se não encontrar
 * @param inicio
 * @param str
 * @return int
 */
int findExistingStrState(ELEM_E *inicio, char str[]);

/**
 * @fn findExistingStrType(ELEM_E *inicio, char str[]);
 * @brief Verifica se existe um determinado tipo de equipamento.
 * Retorna 1, se existir
 * Retorna 0, se não encontrar
 * @param inicio
 * @param str
 * @return int
 */
int findExistingStrType(ELEM_E *inicio, char str[]);

/**
 * @fn findExistingTypeDanificadoUso(ELEM_E *inicio);
 * @brief Verifica se existe esquipamentos danificados ou em uso
 * Retorna 1, se existir
 * Retorna 0, se não encontrar
 * @param inicio
 * @return int
 */
int findExistingStateDanificadoUso(ELEM_E *inicio);

/**
 * @fn filterEquipsType(ELEM_E *inicio, char type[]);
 * @brief Filtra os equipamentos por um determinado tipo.
 * Retorna 0, operação concluida com sucesso.
 * Retorna -1, se não existir nenhum equipamento com o tipo introduzido
 * @param inicio
 * @param type
 * @return int
 */
int filterEquipsType(ELEM_E *inicio, char type[]);

/**
 * @fn filterEquipsState(ELEM_E *inicio, char state[]);
 * @brief Filtra os equipamentos por um determinado estado.
 * Retorna 0, operação concluida com sucesso.
 * Retorna -1, se não existir nenhum equipamento com o estado introduzido
 * @param inicio
 * @param state
 * @return int
 */
int filterEquipsState(ELEM_E *inicio, char state[]);

/**
 * @fn filterEquipsDeparts(ELEM_E *inicio, int num);
 * @brief Filtra os equipamentos por um determinado departamento.
 * Retorna 0, operação concluida com sucesso.
 * Retorna -1, se não existir nenhum equipamento atribuido ao departamento introduzido
 * @param inicio
 * @param num
 * @return int
 */
int filterEquipsDeparts(ELEM_E *inicio, int num);

/**
 * @fn filterEquipsStateUsoDesativado(ELEM_E *inicio);
 * @brief Filtra os equipamentos de modo a obtermos apenas os equipamentos em uso ou desativados.
 * Retorna 0, operação concluida com sucesso.
 * Retorna -1, se não existir nenhum equipamento em uso ou desativados.
 * @param inicio
 * @return int
 */
int filterEquipsStateUsoDesativado(ELEM_E *inicio);

// Relatorio

/**
 * @fn escreverRelatorioDeparts(ELEM_E *inicioEquips, int num);
 * @brief Escreve um relatorio acerca dos equipamentos de um determinado departamento.
 * Retorna 0, relatorio criado com sucesso.
 * Retorna -1, Erro ao abrir o ficheiro
 * @param inicioEquips
 * @param num
 * @return int
 */
int escreverRelatorioDeparts(ELEM_E *inicioEquips, int num);

/**
 * @fn escreverRelatorioEstado(ELEM_E *inicioEquips, char state[]);
 * @brief Escreve um relatorio sobre os equipamentos que possuem um determinado estado.
 * Retorna 0, relatorio criado com sucesso.
 * Retorna -1, Erro ao abrir o ficheiro
 * @param inicioEquips
 * @param state
 * @return int
 */
int escreverRelatorioEstado(ELEM_E *inicioEquips, char state[]);

/**
 * @fn escreverEquipsCSV(ELEM_E *inicioEquips, char username[]);
 * @brief Escreve um ficheiro CSV de todos os equipamentos.abort
 * Retorna 0, relatorio criado com sucesso.
 * Retorna -1, Erro ao abrir o ficheiro
 * Retorna 1, Nenhum equipamento existente ou atribuido ao utilizador
 * @param inicioEquips
 * @param username
 * @return int
 */
int escreverEquipsCSV(ELEM_E *inicioEquips, char username[]);

// Ordenar

/**
 * @fn split(ELEM_E *inicioEquips);
 * @brief Encontra o meio de uma lista ligada e divide-a em dois.
 * @param inicioEquips
 * @return ELEM_E*
 */
ELEM_E *split(ELEM_E *inicioEquips);

/**
 * @fn split(ELEM_E *inicioEquips);
 * @brief Junta cada conjunto de elementos de forma a organizá-los
 * O parâmetro num refere-se ao tipo de comparação que vai ser efetuada.
 * 1 - ID crescente
 * 2 - ID descrescente
 * 3 - Data mais recente
 * 4 - Estado do equipamento
 * 5 - Tipo de equipamento
 *
 * Retorna um apontador para a estrutura first, se second for nulo
 * Retorna um apontador para a estrutura second, se first for nulo
 * Retorna um apontador da lista ligada resultande da junção de first e second.
 * @param inicioEquips
 * @return ELEM_E*
 */
ELEM_E *merge(ELEM_E *first, ELEM_E *second, int num);

/**
 * @brief Função que organiza a lista ligada.
 * A função merge vai chamar a função split() e mergeEstado() recursivamente até a lista ligada estar organizada
 * O parâmetro num refere-se ao tipo de ordenação que vai ser efetuada.
 * 1 - ID crescente
 * 2 - ID descrescente
 * 3 - Data mais recente
 * 4 - Estado do equipamento
 * 5 - Tipo de equipamento
 * @param inicioEquips
 * @param num
 * @return ELEM_E*
 */
ELEM_E *MergeSort(ELEM_E *inicioEquips, int num);

/**
 * @fn verifAlertasEquipamentos(ELEM_E *inicio)
 * @brief Verifica se existe alertas (>5anos)
 * Retorna 1 se existir
 * Retorna 0 se não existir
 */
int verifAlertasEquipamentos(ELEM_E *inicio);