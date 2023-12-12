#ifndef UTILISATEUR_H_INCLUDED
#define UTILISATEUR_H_INCLUDED
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gtk/gtk.h>
 typedef struct  {
    int jour;
    int mois;
    int annee;
} Date;

typedef struct Utilisateur {
    
    char nom[20];
    char prenom[20];
    char CIN [20] ;
    char role[50];
    char adresse_email[50];
    char telephone [20];
    char region[20];
    char sexe[20];
    char dns [20];
    char pointage [20]; 
    
} Utilisateur;

 
 enum
{
	
    	ENOMU ,
    	EPRENOM ,
        ECIN ,
	EROLE ,
	EADRESSE_EMAIL,
	ETELEPHONE ,
     	EREGION ,
     	ESEXE ,
        EDNS,
    	EPOINTAGE ,

	COLUMS,
	
};
   
int  ajouter_utilisateur(Utilisateur U);
int supprimer_u(Utilisateur U);
void rechercher_utilisateur(const char *search_term, GtkWidget *treeview);
void UserRole(char *filename, char role [20]);
void pourcentageUSer(char *filename ,int *nbHomme, int *nbFemme,int *totalUsers);
void afficher_utilisateur(GtkWidget *liste);
Utilisateur chercher_utlis (char* File_name, char* email);


#endif
