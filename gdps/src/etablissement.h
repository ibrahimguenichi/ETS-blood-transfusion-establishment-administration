#ifndef ETABLISSEMENT_H_INCLUDED
#define ETABLISSEMENT_H_INCLUDED

typedef struct etablissement {
    int id;
    char nom_ETS[30];
    char lieu_ETS[30];
    int cap;
    char adr[30];
    char tele[30];
    char adr_email[50];
    int service[5];
    int type;
} etablissement;


#endif // ETABLISSEMENT_H_INCLUDED

