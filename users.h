
typedef struct aluno
{
    char username[20];
    char password[20];
    int state;
} USER;

typedef struct elem
{
    USER info;
    struct elem *seguinte;
} ELEM;

int AdminSetup(ELEM *inicio);

int AdminPasswordChange(ELEM *inicio);

int resetAdmin(ELEM *inicio);

int passwordVerif(char username[20], char passwd[20], ELEM inicio);

int usernameVerif(char username[20], ELEM *inicio);

int registrar(char username[20], char password[20], ELEM *inicio);

int insIniLista(ELEM **inicio, USER info);

ELEM *importUsers();

int usersRelease(ELEM **inicio);

int ativarUtilizadores(ELEM *inicio);