/**
 * @file users.h
 * Header file responsável pela gestão dos utilizadores.
 * @author Henrique Fernandes
 */

/**
 * @brief Estrutura de cada utilizador
 */
typedef struct utilizador
{
    char username[20];
    char password[20];
    int state;
} USER;

/**
 * @brief Estrutura de cada elemento da lista ligada Users
 */
typedef struct elem_u
{
    USER info;
    struct elem_u *seguinte;
} ELEM_U;

/**
 * @fn AdminSetup(ELEM_U **inicio);
 * @brief Cria um administrador "admin", se não existir nenhum.
 * Retorna 1 se já existir uma conta admin
 * Retorna 0 se criou uma nova comta admin
 * Retorna -1 se ocorreu um erro na abertura do ficheiro binário.
 * @param inicio
 * @return int
 */
int AdminSetup(ELEM_U **inicio);

/**
 * @fn AdminPasswordChange(ELEM_U *inicio);
 * @brief Verifica se é a primeira sessão iniciado como admin e pede a alteração da senha.
 * Retorna 0 se for a primeira sessão
 * Retorna 1 se o admin já alterou a senha
 * @param inicio
 * @return int
 */
int AdminPasswordChange(ELEM_U *inicio);

/**
 * @fn resetAdmin(ELEM_U **inicio);
 * @brief Reinicia a conta admin, como primeira sessão iniciada
 * Retorna 0, se operação concluida com sucesso
 * Retorna -1, se ocorreu um erro
 * @param inicio
 * @return int
 */
int resetAdmin(ELEM_U **inicio);

/**
 * @fn passwordVerif(char username[], char passwd[], ELEM_U inicio);
 * @brief Verifica se a senha introduzida corresponde ao username introduzido
 * Retorna 0, senha corresponde, login concluido
 * Retorna -1, senha incorreta
 * @param username
 * @param passwd
 * @param inicio
 * @return int
 */
int passwordVerif(char username[], char passwd[], ELEM_U inicio);

/**
 * @fn usernameVerif(char username[20], ELEM_U **inicio);
 * @brief Verificia se o username passado por parâmetro existe na lista ligada Users.
 * Retorna 0, se encontrou
 * Retorna -1, se não encontrou
 * @param inicio
 * @return int
 */
int usernameVerif(char username[20], ELEM_U **inicio);

/**
 * @fn registrar(char username[], char password[], ELEM_U **inicio);
 * @brief Regista um novo user, escreve para o ficheiro data/users.dat e insere o novo utilizador na respetiva lista ligada
 * Retorna 0, operação concluida
 * Retorna -1, erro ao abrir o ficheiro
 * @param username
 * @param password
 * @param inicio
 * @return int
 */
int registrar(char username[], char password[], ELEM_U **inicio);

/**
 * @fn insIniLista(ELEM_U **inicio, USER info);
 * @brief Insere um novo elemento (ELEM_U) na respetiva lista ligada.
 * Retorna 0, operação concluida
 * Retorna -1, out of memory
 * @param inicio
 * @param info
 * @return int
 */
int insIniLista(ELEM_U **inicio, USER info);

/**
 * @fn importUsers();
 * @brief Importa a conta dos utilizadores como uma lista ligada, lendo o ficheiro binário data/users.dat
 * Retorna um apontador para o inicio da lista ligada.
 * Retorna NULL, erro ao abrir o ficheiro
 * @return ELEM_U*
 */
ELEM_U *importUsers();

/**
 * @fn usersRelease(ELEM_U **inicio);
 * @brief Liberta a memoria ocupada pela lista ligada Users
 * Retorna -1, se esta for vazia
 * Retorna 0, operação concluida
 * @param inicio
 * @return int
 */
int usersRelease(ELEM_U **inicio);

/**
 * @fn procurarUser(ELEM_U *inicio, char username[]);
 * @brief Procura um tecnico com o username introduzido pelo utilizador.
 * Retorna um apontador para o elemento encontrado
 * Retorna NULL, nenhum resultado encontrado
 * @param inicio
 * @param username
 * @return ELEM_U*
 */
ELEM_U *procurarUser(ELEM_U *inicio, char username[]);

/**
 * @fn procurarUserAtivo(ELEM_U *inicio, char username[]);
 * @brief Procura um tecnico ativo com o username introduzido pelo utilizador.
 * Retorna um apontador para o elemento encontrado
 * Retorna NULL, nenhum resultado encontrado
 * @param inicio
 * @param username
 * @return ELEM_U*
 */
ELEM_U *procurarUserAtivo(ELEM_U *inicio, char username[]);

/**
 * @fn printUtilizadores(ELEM_U *inicio);
 * @brief Escreve todos os utilizadores
 * @param inicio
 */
void printUtilizadores(ELEM_U *inicio);

/**
 * @fn ativarUtilizadores(ELEM_U *inicio, char username[]);
 * @brief Ativa ou desativa um tecnico
 * retorna -1, se utilizador procurado não existir
 * retorna  0, operacao concludia com sucesso
 * @param inicio
 * @param username
 * @return int
 */
int ativarUtilizadores(ELEM_U *inicio, char username[]);
