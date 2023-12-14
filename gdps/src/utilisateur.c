#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utilisateur.h"
#include <gtk/gtk.h>





int ajouter_utilisateur(Utilisateur U)
{
    FILE *f = fopen("utilisateur.txt", "a+");
    if (f != NULL)
    {

        fprintf(f,"%s %s %s %s %s %s %s %s %s %s\n" , U.nom , U.prenom ,U.CIN,U.role, U.adresse_email ,U.telephone ,U.region , U.sexe , U.dns , U.pointage  
           );


        fclose(f);
       return 1;}
   else 
        return 0;
    
    
}


void afficher_utilisateur(GtkWidget *liste)
{
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store;
	
	Utilisateur U;

	
	if(store==NULL)
	{



		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("nom",renderer, "text",ENOMU, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer = gtk_cell_renderer_text_new();	
		column =   
                           gtk_tree_view_column_new_with_attributes("prenom",renderer, "text",EPRENOM, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

           		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("CIN",renderer, "text",ECIN, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

                        renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("role",renderer, "text",EROLE, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

                        renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("adresse_email",renderer, "text",EADRESSE_EMAIL, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

                        renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("telephone",renderer, "text",ETELEPHONE, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("region",renderer, "text",EREGION, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		
	renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("sexe",renderer, "text",ESEXE, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
 	
	
        renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("dns",renderer, "text",EDNS, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("pointage",renderer, "text",EPOINTAGE, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

	}
	FILE* f;	
	store=gtk_list_store_new(COLUMS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING);
	f= fopen("utilisateur.txt","r");

	if (f==NULL)
	{
		return;
	}
	else
	{
		
		while(fscanf(f,"%s %s %s %s %s %s %s %s %s %s \n" ,U.nom ,U.prenom,U.CIN ,U.role ,U.adresse_email ,U.telephone ,U.region  ,U.sexe  ,U.dns ,U.pointage )!=EOF)
		{
			gtk_list_store_append(store, &iter);
			gtk_list_store_set(store, &iter,ENOMU ,U.nom ,EPRENOM ,U.prenom,ECIN,U.CIN ,EROLE ,U.role,EADRESSE_EMAIL ,U.adresse_email,ETELEPHONE,U.telephone,EREGION  ,U.region,  ESEXE,U.sexe,EDNS,U.dns,EPOINTAGE ,U.pointage , -1);
		}
		fclose(f);
		gtk_tree_view_set_model (GTK_TREE_VIEW(liste),GTK_TREE_MODEL (store));
		
	}
}

 int supprimer_u(Utilisateur U)
{
    Utilisateur U2 ;
    FILE *f = fopen("utilisateur.txt", "r");
    FILE *f2 = fopen("nouv.txt", "w");
    if (f == NULL || f2 == NULL)
     {
    
    printf("Error opening file for reading or writing.\n");
    return;
      }
    {
        while (fscanf(f, "%s %s %s %s %s %s %s %s %s %s \n" ,U2.nom , U2.prenom ,U2.CIN, U2.role, U2.adresse_email, U2.telephone,U2.region ,U2.sexe   ,U2.dns, U2.pointage  ) ==10)

        {
          if (strcmp(U.nom, U2.nom) != 0 || strcmp(U.prenom,U2.prenom ) != 0 || strcmp(U.CIN, U2.CIN) != 0 || strcmp(U.role, U2.role) != 0 || strcmp(U.adresse_email, U2.adresse_email) != 0 || strcmp(U.telephone,U2.telephone) != 0 || strcmp(U.region,U2.region) != 0|| strcmp(U.sexe, U2.sexe) != 0|| strcmp(U.dns, U2.dns) != 0|| strcmp(U.pointage, U2.pointage) != 0)

{   fprintf(f2, "%s %s %s %s %s %s %s %s %s %s \n" ,U2.nom , U2.prenom ,U2.CIN, U2.role, U2.adresse_email, U2.telephone,U2.region ,U2.sexe   ,U2.dns, U2.pointage);
          }

}
    fclose(f);
    fclose(f2);
    remove("utilisateur.txt");
    rename("nouv.txt", "utilisateur.txt");
    }



    
}


void rechercher_utilisateur(const char *search_term, GtkWidget *treeview)
{
    GtkTreeIter iter;
    GtkTreeModel *model = gtk_tree_view_get_model(GTK_TREE_VIEW(treeview));
    gboolean valid;
    gchar *nom, *prenom, *CIN, *role, *adresse_email, *telephone, *region, *sexe, *dns, *pointage;

    valid = gtk_tree_model_get_iter_first(model, &iter);

    while (valid)
    {
        gtk_tree_model_get(model, &iter, ENOMU, &nom, EPRENOM, &prenom, ECIN, &CIN, EROLE, &role, EADRESSE_EMAIL, &adresse_email, ETELEPHONE, &telephone, EREGION, &region, ESEXE, &sexe, EDNS, &dns, EPOINTAGE, &pointage, -1);

        
        gchar nom_lower[20], prenom_lower[20], CIN_lower[20], role_lower[50], adresse_email_lower[50],    telephone_lower[20], region_lower[20], sexe_lower[20], dns_lower[20], pointage_lower[20];
        g_strlcpy(nom_lower, nom, sizeof(nom_lower));
        g_strlcpy(prenom_lower, prenom, sizeof(prenom_lower));
        g_strlcpy(CIN_lower, CIN, sizeof(CIN_lower));
        g_strlcpy(role_lower, role, sizeof(role_lower));
        g_strlcpy(adresse_email_lower, adresse_email, sizeof(adresse_email_lower));
        g_strlcpy(telephone_lower, telephone, sizeof(telephone_lower));
        g_strlcpy(region_lower, region, sizeof(region_lower));
        g_strlcpy(sexe_lower, sexe, sizeof(sexe_lower));
        g_strlcpy(dns_lower, dns, sizeof(dns_lower));
        g_strlcpy(pointage_lower, pointage, sizeof(pointage_lower));


        if (strstr(nom_lower, search_term) != NULL ||
            strstr(prenom_lower, search_term) != NULL ||
            strstr(CIN_lower, search_term) != NULL ||
            strstr(role_lower, search_term) != NULL ||
            strstr(adresse_email_lower, search_term) != NULL ||
            strstr(telephone_lower, search_term) != NULL ||
            strstr(region_lower, search_term) != NULL ||
            strstr(sexe_lower, search_term) != NULL ||
            strstr(dns_lower, search_term) != NULL ||
            strstr(pointage_lower, search_term) != NULL)
        {
            gtk_tree_selection_select_iter(gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview)), &iter);

            GtkTreePath *path = gtk_tree_model_get_path(model, &iter);
            gtk_tree_view_scroll_to_cell(GTK_TREE_VIEW(treeview), path, NULL, FALSE, 0.5, 0.0);

            g_free(nom);
            g_free(prenom);
            g_free(CIN);
            g_free(role);
            g_free(adresse_email);
            g_free(telephone);
            g_free(region);
            g_free(sexe);
            g_free(dns);
            g_free(pointage);

            return;
        }

        g_free(nom);
        g_free(prenom);
        g_free(CIN);
        g_free(role);
        g_free(adresse_email);
        g_free(telephone);
        g_free(region);
        g_free(sexe);
        g_free(dns);
        g_free(pointage);

        valid = gtk_tree_model_iter_next(model, &iter);
    }

    g_print("No matching user found.\n");
}



 void rechercher_par_role(const char *search_role, GtkWidget *treeview)
{
    GtkTreeIter iter;
    GtkTreeModel *model = gtk_tree_view_get_model(GTK_TREE_VIEW(treeview));
    gboolean valid;
    gchar *nom, *prenom, *CIN, *role, *adresse_email, *telephone, *region, *sexe, *dns, *pointage;
    GList *selected_rows = NULL; 

    valid = gtk_tree_model_get_iter_first(model, &iter);

    while (valid)
    {
        gtk_tree_model_get(model, &iter, ENOMU, &nom, EPRENOM, &prenom, ECIN, &CIN, EROLE, &role, EADRESSE_EMAIL, &adresse_email, ETELEPHONE, &telephone, EREGION, &region, ESEXE, &sexe, EDNS, &dns, EPOINTAGE, &pointage, -1);

        
        if (strcmp(role, search_role) == 0)
        {
            
            GtkTreePath *path = gtk_tree_model_get_path(model, &iter);
            selected_rows = g_list_append(selected_rows, path);
        }

       
        g_free(nom);
        g_free(prenom);
        g_free(CIN);
        g_free(role);
        g_free(adresse_email);
        g_free(telephone);
        g_free(region);
        g_free(sexe);
        g_free(dns);
        g_free(pointage);

        valid = gtk_tree_model_iter_next(model, &iter);
    }

    // Select all rows stored in the list
    gtk_tree_selection_unselect_all(gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview)));
    GList *iter_list = selected_rows;
    while (iter_list != NULL)
    {
        GtkTreePath *path = iter_list->data;
        gtk_tree_selection_select_path(gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview)), path);
        iter_list = g_list_next(iter_list);
    }

    // Free allocated memory for the list
    g_list_free_full(selected_rows, (GDestroyNotify)gtk_tree_path_free);
}   


void calculate_female_percentage(int *totalUsers, float *femalePercentage)
{
 Utilisateur U3;
    FILE *f = fopen("utilisateur.txt", "r");
    if (f == NULL)
    {
        printf("Error opening file for reading.\n");
        return;
    }

    *totalUsers = 0;
    int femaleCount = 0;
   

    while (fscanf(f, "%*s %*s %*s %*s %*s %*s %*s %s %*s %*s", U3.sexe) == 1)
    {
        (*totalUsers)++;
        if (strcmp(U3.sexe, "femme") == 0)
        {
            femaleCount++;
        }
    }

    fclose(f);

    if (*totalUsers > 0)
    {
        *femalePercentage = (float)femaleCount / *totalUsers * 100.0;
    }
    else
    {
        *femalePercentage = 0.0;
    }
}

void calculate_male_percentage(int *totalUsers, float *malePercentage)
{
 Utilisateur U4;
    FILE *f = fopen("utilisateur.txt", "r");
    if (f == NULL)
    {
        printf("Error opening file for reading.\n");
        return;
    }

    *totalUsers = 0;
    int maleCount = 0;
   

    while (fscanf(f, " %*s %*s %*s %*s %*s %*s %*s %s %*s %*s", U4.sexe) == 1)
    {
        (*totalUsers)++;
        if (strcmp(U4.sexe, "homme") == 0)
        {
            maleCount++;
        }
    }

    fclose(f);

    if (*totalUsers > 0)
    {
        *malePercentage = (float)maleCount / *totalUsers * 100.0;
    }
    else
    {
        *malePercentage = 0.0;
    }

 }
////////////////////////////////////
 
Utilisateur chercher_utlis (char* File_name, char* email)
{

FILE* f;
Utilisateur temp;
int tr = 0;
f = fopen(File_name, "r");

if (f == NULL)
	return;
else
{
while ((fscanf(f, "%s %s %s %s %s %s %s %s %s %s", temp.nom, temp.prenom, temp.CIN, temp.role, temp.adresse_email, temp.telephone, temp.region, temp.sexe, temp.dns, temp.pointage) != EOF))
{
    if (strcmp(email, temp.adresse_email) == 0)
    {
	tr = 1;  
	break; 
    }
}
fclose (f);
}

if (tr == 1)
	return temp;
else
{
strcpy (temp.CIN, "-1");
strcpy (temp.adresse_email, "-1");
return temp;
}
}




