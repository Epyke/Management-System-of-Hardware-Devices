
typedef struct
{
    char username[20];
    char password[20];
    int state;
} USER;

int passwordVerif(char username[20], char passwd[20]);

int usernameVerif(char flg[20]);

int registrar(char newUsername[20]);