#include "users.c"

typedef struct user
{
    char username[20];
    char password[20];
    int state;
} USER;

int passwordVerif(char username[20], char passwd[20]);

int usernameVerif(char flg[20]);