#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <gtk/gtk.h>
typedef struct date_f{
int j;
int m;
int a;
}date_f;

typedef struct ut{
int cin;
char nom[30];
char prenom[30];
char email[40];
char gs[15];
int sexe;
char mala[15];
int poid;
int ets;
date_f d;
}ut;


void ajouter_f(ut u, char *fname);
void supprimer_f(ut u, char *fname);
void modifier_f(ut u, char *fname);
void afficher_f(GtkWidget *liste, char *fname, char *id, char *email, char *nom);
ut chercher_f(int id, char *fname);
char* age_moyen(char *filename);
char* e_bv(char *filename);
int Check_Email_Addr(char *EM_Addr);
bool valid_cin(char *cin);
int nbETS();
float moy_ETS(date_f d);
void listeRDV(GtkTreeView *liste, int ets);


