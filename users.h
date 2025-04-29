
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

int passwordVerif(char username[20], char passwd[20]);

int usernameVerif(char flg[20]);

int registrar(char username[20], char password[20]);

int insIniLista(ELEM **inicio, USER info);

ELEM *importUsers();