#ifndef FONCTIONS_H_INCLUDED
#define FONCTIONS_H_INCLUDED
#include <gtk/gtk.h>

typedef struct sang
{
    char type[4];
    int nbr_poches;
} sang;

typedef struct date
{
    int jours;
    char mois[20];
    int annees;
} date;

typedef struct dem_poche_sang
{
    int id_dem;
    int id_etab;
    sang T[8];
    char cond_med[300];
    date date_dem;
    date date_lim;
    int trait;
} dem_poche_sang;

enum
{
	ENUM,
	ENOM,
	ETYPE,
	ECOND,
	EDATEDEM,
	EDATELIM,
	ETRAITE,
	COLUMNS
};

typedef struct chaine
{
    char a[10];
} chaine;

typedef struct condMedical
{
    int val;
    char cond[70];
} condMedical;


int ajouter (char *File_name, dem_poche_sang demande);
int modifier (char *File_name, int id, dem_poche_sang nouv);
int supprimer (char *File_name, int id);
dem_poche_sang chercher (char *File_name, int id);
float pourcentage (char *File_name, int id);
int quantiteDemandee_type(char* File_name, char* type_sang);
int sang_demande(char* File_name, char* sangDemande);
void date_string (date date_struct, char *date_dem);
void type_sang_str(dem_poche_sang dem, char *ts);
void afficher_demande(GtkWidget *liste);
void etab_comb (int *x, chaine** tab);
void ajout_cond_m (char* File_name, condMedical* t, dem_poche_sang demande);
void convertid_nom(char* File_name, char* nom, int id_etab);
int lire_cond_m (char* File_name, condMedical* t, int id);
int dern_num_dem (char* File_name);
int modifier_cond_m (char* File_name, condMedical* nouv, int id);
void afficher_demande_cher(GtkWidget *liste);
int ajouter_cher (char *File_name, dem_poche_sang demande);
void afficher_demande_cher_n(GtkWidget *liste);

#endif // FONCTIONS_H_INCLUDED

