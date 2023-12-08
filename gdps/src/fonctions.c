#include <stdio.h>
#include "fonctions.h"
#include <string.h>
#include <gtk/gtk.h>
#include "etablissement.h"


int ajouter (char *File_name, dem_poche_sang demande)
{

    FILE *f;
    f = fopen (File_name, "a");
    if (f != NULL)
    {
        fprintf(f, "%d %d ", demande.id_dem, demande.id_etab);
        for (int i = 0; i < 8; i++)
        {
            fprintf(f, "%s %d ", demande.T[i].type, demande.T[i].nbr_poches);
        }
        fprintf(f, "%s %d %s %d %d %s %d %d\n", demande.cond_med, demande.date_dem.jours, demande.date_dem.mois, demande.date_dem.annees, demande.date_lim.jours, demande.date_lim.mois, demande.date_lim.annees, demande.trait);
        fclose(f);
        return 1;
    }
    else return 0;
}





int modifier (char *File_name, int id, dem_poche_sang nouv)
{
    int tr = 0;
    FILE *f1;
    FILE *f2;

    dem_poche_sang temp;
    f1 = fopen(File_name, "r");
    f2 = fopen("nouv.txt", "w");

    if ((f1 != NULL)&& (f2 != NULL))
    {
        while ((fscanf(f1, "%d %d %s %d %s %d %s %d %s %d %s %d %s %d %s %d %s %d %s %d %s %d %d %s %d %d", &temp.id_dem, &temp.id_etab, temp.T[0].type, &temp.T[0].nbr_poches, temp.T[1].type, &temp.T[1].nbr_poches, temp.T[2].type, &temp.T[2].nbr_poches, temp.T[3].type, &temp.T[3].nbr_poches, temp.T[4].type, &temp.T[4].nbr_poches, temp.T[5].type, &temp.T[5].nbr_poches, temp.T[6].type, &temp.T[6].nbr_poches, temp.T[7].type, &temp.T[7].nbr_poches, temp.cond_med, &temp.date_dem.jours, temp.date_dem.mois, &temp.date_dem.annees, &temp.date_lim.jours, temp.date_lim.mois, &temp.date_lim.annees, &temp.trait)) != EOF)
        if (1)
        {
            if (temp.id_dem == id)
            {
            fprintf(f2, "%d %d ", nouv.id_dem, nouv.id_etab);
            for (int i = 0; i < 8; i++)
            {
                fprintf(f2, "%s %d ", nouv.T[i].type, nouv.T[i].nbr_poches);
            }
            fprintf(f2, "%s %d %s %d %d %s %d %d\n", nouv.cond_med, nouv.date_dem.jours, nouv.date_dem.mois, nouv.date_dem.annees, nouv.date_lim.jours, nouv.date_lim.mois, nouv.date_lim.annees, nouv.trait);
            tr = 1;
            }
            else
            {
                fprintf(f2, "%d %d ", temp.id_dem, temp.id_etab);
                for (int i = 0; i < 8; i++)
                {
                    fprintf(f2, "%s %d ", temp.T[i].type, temp.T[i].nbr_poches);
                }
                fprintf(f2, "%s %d %s %d %d %s %d %d\n", temp.cond_med, temp.date_dem.jours, temp.date_dem.mois, temp.date_dem.annees, temp.date_lim.jours, temp.date_lim.mois, temp.date_lim.annees, temp.trait);
            }
        }
    }
    fclose(f1);
    fclose(f2);
    remove(File_name);
    rename("nouv.txt", File_name);
    return tr;
}


int supprimer (char *File_name, int id)
{
    int tr = 0;
    FILE *f1;
    FILE *f2;

    dem_poche_sang temp;

    f1 = fopen(File_name, "r");
    f2 = fopen("nouv.txt", "w");

    if ((f1 != NULL)&& (f2 != NULL))
    {
        while ((fscanf(f1, "%d %d %s %d %s %d %s %d %s %d %s %d %s %d %s %d %s %d %s %d %s %d %d %s %d %d", &temp.id_dem, &temp.id_etab, temp.T[0].type, &temp.T[0].nbr_poches, temp.T[1].type, &temp.T[1].nbr_poches, temp.T[2].type, &temp.T[2].nbr_poches, temp.T[3].type, &temp.T[3].nbr_poches, temp.T[4].type, &temp.T[4].nbr_poches, temp.T[5].type, &temp.T[5].nbr_poches, temp.T[6].type, &temp.T[6].nbr_poches, temp.T[7].type, &temp.T[7].nbr_poches, temp.cond_med, &temp.date_dem.jours, temp.date_dem.mois, &temp.date_dem.annees, &temp.date_lim.jours, temp.date_lim.mois, &temp.date_lim.annees, &temp.trait)) != EOF)
        {
            if (temp.id_dem == id)
            {
            tr = 1;
            }
            else
            {
                fprintf(f2, "%d %d ", temp.id_dem, temp.id_etab);
                for (int i = 0; i < 8; i++)
                {
                    fprintf(f2, "%s %d ", temp.T[i].type, temp.T[i].nbr_poches);
                }
                fprintf(f2, "%s %d %s %d %d %s %d %d\n", temp.cond_med, temp.date_dem.jours, temp.date_dem.mois, temp.date_dem.annees, temp.date_lim.jours, temp.date_lim.mois, temp.date_lim.annees, temp.trait);
            }
        }
    }

    fclose(f1);
    fclose(f2);
    remove(File_name);
    rename("nouv.txt", File_name);
    return tr;
}


dem_poche_sang chercher (char *File_name, int id)
{
    FILE *f;
    dem_poche_sang temp;
    int tr = 0;
    f = fopen(File_name, "r");
    if (f != NULL)
    {
        while ((fscanf(f, "%d %d %s %d %s %d %s %d %s %d %s %d %s %d %s %d %s %d %s %d %s %d %d %s %d %d", &temp.id_dem, &temp.id_etab, temp.T[0].type, &temp.T[0].nbr_poches, temp.T[1].type, &temp.T[1].nbr_poches, temp.T[2].type, &temp.T[2].nbr_poches, temp.T[3].type, &temp.T[3].nbr_poches, temp.T[4].type, &temp.T[4].nbr_poches, temp.T[5].type, &temp.T[5].nbr_poches, temp.T[6].type, &temp.T[6].nbr_poches, temp.T[7].type, &temp.T[7].nbr_poches, temp.cond_med, &temp.date_dem.jours, temp.date_dem.mois, &temp.date_dem.annees, &temp.date_lim.jours, temp.date_lim.mois, &temp.date_lim.annees, &temp.trait)) != EOF)
        {
            if (temp.id_dem == id)
            {
                tr = 1;
                break;
            }
        }
    }

    fclose(f);

    if (tr == 0)
    {
        temp.id_dem = -1;
    }
    return temp;
}



float pourcentage (char *File_name, int id)
{
    FILE *f;
    dem_poche_sang temp;
    int nbr_dem = 0;
    int nbr_dem_etab = 0;
    float pourcent;

    f = fopen(File_name, "r");
    if (f != NULL)
    {
        while ((fscanf(f, "%d %d %s %d %s %d %s %d %s %d %s %d %s %d %s %d %s %d %s %d %s %d %d %s %d %d", &temp.id_dem, &temp.id_etab, temp.T[0].type, &temp.T[0].nbr_poches, temp.T[1].type, &temp.T[1].nbr_poches, temp.T[2].type, &temp.T[2].nbr_poches, temp.T[3].type, &temp.T[3].nbr_poches, temp.T[4].type, &temp.T[4].nbr_poches, temp.T[5].type, &temp.T[5].nbr_poches, temp.T[6].type, &temp.T[6].nbr_poches, temp.T[7].type, &temp.T[7].nbr_poches, temp.cond_med, &temp.date_dem.jours, temp.date_dem.mois, &temp.date_dem.annees, &temp.date_lim.jours, temp.date_lim.mois, &temp.date_lim.annees, &temp.trait)) != EOF)

        {
            if(temp.id_etab == id)
            {
                nbr_dem++;
                nbr_dem_etab++;
            }
            else
                nbr_dem++;
        }
    }
    fclose(f);
    pourcent = (float) nbr_dem_etab / nbr_dem;
    return pourcent;
}


int quantiteDemandee_type(char* File_name, char* type_sang)
{
    FILE *f;
    int quant = 0;
    dem_poche_sang temp;
    f = fopen(File_name, "r");
    if (f != NULL)
    {
        while ((fscanf(f, "%d %d %s %d %s %d %s %d %s %d %s %d %s %d %s %d %s %d %s %d %s %d %d %s %d %d", &temp.id_dem, &temp.id_etab, temp.T[0].type, &temp.T[0].nbr_poches, temp.T[1].type, &temp.T[1].nbr_poches, temp.T[2].type, &temp.T[2].nbr_poches, temp.T[3].type, &temp.T[3].nbr_poches, temp.T[4].type, &temp.T[4].nbr_poches, temp.T[5].type, &temp.T[5].nbr_poches, temp.T[6].type, &temp.T[6].nbr_poches, temp.T[7].type, &temp.T[7].nbr_poches, temp.cond_med, &temp.date_dem.jours, temp.date_dem.mois, &temp.date_dem.annees, &temp.date_lim.jours, temp.date_lim.mois, &temp.date_lim.annees, &temp.trait)) != EOF)
        {
            for (int i = 0; i < 8; i++)
            {
                if (strcmp(temp.T[i].type, type_sang) == 0)
                {
                    quant += temp.T[i].nbr_poches;
                }
            }
        }
    }

    fclose(f);
    return quant;
}


int sang_demande(char* File_name, char* sangDemande)
{
    int max = 0;
    int i_max;
    sang tab[8] = {{"A+", 0}, {"O+", 0}, {"B+", 0}, {"AB+", 0}, {"A-", 0}, {"O-", 0}, {"B-", 0}, {"AB-", 0}};
    FILE *f;
    dem_poche_sang temp;

    f = fopen(File_name, "r");
    if (f != NULL)
    {
        while ((fscanf(f, "%d %d %s %d %s %d %s %d %s %d %s %d %s %d %s %d %s %d %s %d %s %d %d %s %d %d", &temp.id_dem, &temp.id_etab, temp.T[0].type, &temp.T[0].nbr_poches, temp.T[1].type, &temp.T[1].nbr_poches, temp.T[2].type, &temp.T[2].nbr_poches, temp.T[3].type, &temp.T[3].nbr_poches, temp.T[4].type, &temp.T[4].nbr_poches, temp.T[5].type, &temp.T[5].nbr_poches, temp.T[6].type, &temp.T[6].nbr_poches, temp.T[7].type, &temp.T[7].nbr_poches, temp.cond_med, &temp.date_dem.jours, temp.date_dem.mois, &temp.date_dem.annees, &temp.date_lim.jours, temp.date_lim.mois, &temp.date_lim.annees, &temp.trait)) != EOF)
        {
            for(int i = 0; i < 8; i++)
            {
                tab[i].nbr_poches = quantiteDemandee_type(File_name, tab[i].type);
            }
        }
    }

    fclose(f);
    for (int i = 0; i < 8; i++)
    {
        if (tab[i].nbr_poches > max)
        {
            max = tab[i].nbr_poches;
        }
    }
    for (int i = 0; i <8; i++)
    {
        if(tab[i].nbr_poches == max)
            i_max = i;
    }
    strcpy (sangDemande, tab[i_max].type);
return max;
}

void date_string (date date_struct, char *date_s)
{
    date_s[0] = (char) ((date_struct.jours / 10) + 48);
    date_s[1] = (char) ((date_struct.jours % 10) + 48);
    date_s[2] = (char) 47;
    int l = strlen(date_struct.mois);
    for (int i = 3; i < l + 3; i++)
    {
        date_s[i] = date_struct.mois[i-3];
    }
    date_s[l+3] = (char) 47;
    date_s[l+4] = (char) ((date_struct.annees / 1000) + 48);
    date_s[l+5] = (char) (((date_struct.annees % 1000) / 100) + 48);
    date_s[l+6] = (char) (((date_struct.annees % 100) / 10) + 48);
    date_s[l+7] = (char) ((date_struct.annees % 10) + 48);
    date_s[l+8] = '\0';
}

void type_sang_str (dem_poche_sang temp, char* ts)
{
    strcpy(ts, "");
    sang* tab;
    sang* tabn;
    int len = 1;
    tab = (sang*) malloc(len * sizeof(sang));
    char nouv[10];

    for (int i = 0; i < 8; i++)
        {
            if (temp.T[i].nbr_poches != 0)
            {
                tab[len-1] = temp.T[i];
                len++;
                tabn = realloc(tab, len * sizeof(sang));
                tab = tabn;
            }
        }
    len--;
    tabn = realloc(tab, len * sizeof(sang));
    tab = tabn;
    for (int i = 0; i < len; i++)
    {
        if (i != (len - 1))
        {
            sprintf(nouv, "%s: %d, ", tab[i].type, tab[i].nbr_poches);
        }

        if (i == (len - 1))
        {
            sprintf(nouv, "%s: %d.", tab[i].type, tab[i].nbr_poches);
        }
        strcat(ts, nouv);
    }
}
///////////////////

void afficher_demande(GtkWidget *liste)
{
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store;

        store = NULL;

store = gtk_tree_view_get_model(liste);
if (store == NULL)
{
        renderer = gtk_cell_renderer_text_new ();
        column = gtk_tree_view_column_new_with_attributes ("Num: ", renderer, "text", ENUM, NULL);
        gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

        renderer = gtk_cell_renderer_text_new ();
        column = gtk_tree_view_column_new_with_attributes ("Nom Etablissemnet", renderer, "text", ENOM, NULL);
        gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

        renderer = gtk_cell_renderer_text_new ();
        column = gtk_tree_view_column_new_with_attributes ("Types et quantites de sangs", renderer, "text", ETYPE, NULL);
        gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

	renderer = gtk_cell_renderer_text_new ();
        column = gtk_tree_view_column_new_with_attributes ("Conditions Mediacales", renderer, "text", ECOND, NULL);
        gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

        renderer = gtk_cell_renderer_text_new ();
        column = gtk_tree_view_column_new_with_attributes ("date de la demande", renderer, "text", EDATEDEM, NULL);
        gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

        renderer = gtk_cell_renderer_text_new ();
        column = gtk_tree_view_column_new_with_attributes ("date limite de livraison", renderer, "text", EDATELIM, NULL);
        gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

        renderer = gtk_cell_renderer_text_new ();
        column = gtk_tree_view_column_new_with_attributes ("livre", renderer, "text", ETRAITE, NULL);
        gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
}

        store = gtk_list_store_new (COLUMNS, G_TYPE_INT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING ,G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);


    FILE* f;
    dem_poche_sang temp;
    int numdem;
    char nometab[40];
    char date1[20];
    char date2[20];
    char TQ_sang[50];
    char condit_med[300];
    char trait[5];

    f = fopen("demande.txt", "r");
    if (f == NULL)
        return;
    else
    {
        while ((fscanf(f, "%d %d %s %d %s %d %s %d %s %d %s %d %s %d %s %d %s %d %s %d %s %d %d %s %d %d", &temp.id_dem, &temp.id_etab, temp.T[0].type, &temp.T[0].nbr_poches, temp.T[1].type, &temp.T[1].nbr_poches, temp.T[2].type, &temp.T[2].nbr_poches, temp.T[3].type, &temp.T[3].nbr_poches, temp.T[4].type, &temp.T[4].nbr_poches, temp.T[5].type, &temp.T[5].nbr_poches, temp.T[6].type, &temp.T[6].nbr_poches, temp.T[7].type, &temp.T[7].nbr_poches, temp.cond_med, &temp.date_dem.jours, temp.date_dem.mois, &temp.date_dem.annees, &temp.date_lim.jours, temp.date_lim.mois, &temp.date_lim.annees, &temp.trait)) != EOF)
        {

	    numdem = temp.id_dem;
	    //idetab = temp.id_etab;
	    convertid_nom("etablissement.txt", nometab, temp.id_etab);
	    if(temp.trait == 1)
		strcpy(trait, "Oui");
	    else
		strcpy(trait, "Non");
            date_string (temp.date_dem, date1);
            date_string (temp.date_lim, date2);
            type_sang_str(temp, TQ_sang);
	    strcpy (condit_med, temp.cond_med);
//remplacer le vergules par \n
	    for (int i = 0; i < strlen(condit_med); i++)
	    {
		if (condit_med[i] == ',')
		    condit_med[i] = '\n';
	    }

            gtk_list_store_append (store, &iter);
            gtk_list_store_set (store, &iter, ENUM, numdem, ENOM, nometab, ETYPE, TQ_sang, ECOND, condit_med, EDATEDEM, date1, EDATELIM, date2, ETRAITE, trait, -1);
        }
        fclose (f);
        gtk_tree_view_set_model (GTK_TREE_VIEW (liste), GTK_TREE_MODEL (store));
        g_object_unref (store);
    }
}

////////////////

void etab_comb (int *x, chaine** ta)
{
    chaine* tab;
    chaine* TAB;
    tab = (chaine*) malloc(50 * sizeof(chaine));
    int t;
    etablissement temp;
    char num;
    char id[10];
    int l = 1;
    FILE* f;
    f = fopen("etablissement.txt", "r");
    if (f == NULL)
        return;
    else
    {
        while (fscanf(f, "%d %s %s %d %s %s %s %d %d %d %d %d %d", &temp.id, temp.nom_ETS, temp.lieu_ETS, &temp.cap, temp.adr, temp.tele, temp.adr_email, &temp.service[0], &temp.service[1], &temp.service[2], &temp.service[3], &temp.service[4], &temp.type) != EOF)
        {
            t= temp.id;
            sprintf(id, "%d", t);
            strcpy(tab[l-1].a, id);
            l++;
            TAB = realloc(tab, l * sizeof(chaine));
            tab = TAB;
        }
        fclose(f);
    }
    *x = l-1;
    *ta = tab;
}

void ajout_cond_m (char* File_name, condMedical* t, dem_poche_sang d)
{
    char chaine[70];
    FILE* f;
    f = fopen(File_name, "a");
    if (f == NULL)
        return;
    else
    {
	fprintf(f, "%d ", d.id_dem);
        for (int i = 0; i < 8; i++)
        {
            strcpy(chaine, t[i].cond);
            for (int j = 0; j < strlen(chaine); j++)
            {
                if (chaine[j] == ' ')
                    chaine[j] = '-';
            }
            fprintf(f, "%s %d ", chaine, t[i].val);
        }
        fprintf(f, "\n");
    }
    fclose(f);
}

int modifier_cond_m (char* File_name, condMedical* nouv, int id_c)
{
int id = 0;
char chaine[70];
condMedical temp[8];
FILE* f1;
FILE* f2;
f1 = fopen(File_name, "r");
f2 = fopen("nouv.txt", "a");
int tr = 0;

if ((f1 == NULL) || (f2 == NULL))
	return;
else
{
while (fscanf(f1, "%d %s %d %s %d %s %d %s %d %s %d %s %d %s %d %s %d", &id, temp[0].cond, &temp[0].val, temp[1].cond, &temp[1].val ,temp[2].cond, &temp[2].val ,temp[3].cond, &temp[3].val ,temp[4].cond, &temp[4].val ,temp[5].cond, &temp[5].val ,temp[6].cond, &temp[6].val ,temp[7].cond, &temp[7].val) != EOF)
{
if (id_c == id)
{
	fprintf(f2, "%d ", id);
        for (int i = 0; i < 8; i++)
        {
	if (temp[i].val == nouv[i].val)
	{
            strcpy(chaine, temp[i].cond);
            for (int j = 0; j < strlen(chaine); j++)
            {
                if (chaine[j] == ' ')
                    chaine[j] = '-';
            }
            fprintf(f2, "%s %d ", chaine, 1);
	
	}
	else if (temp[i].val != nouv[i].val)
	{
            strcpy(chaine, temp[i].cond);
            for (int j = 0; j < strlen(chaine); j++)
            {
                if (chaine[j] == ' ')
                    chaine[j] = '-';
            }
            fprintf(f2, "%s %d ", chaine, 0);
	}
        }
        fprintf(f2, "\n");
	tr = 1;
}
else
{
	fprintf(f2, "%d ", id);
	for (int i = 0; i < 8; i++)
	{
	strcpy(chaine, temp[i].cond);
            for (int j = 0; j < strlen(chaine); j++)
            {
                if (chaine[j] == ' ')
                    chaine[j] = '-';
            }
            fprintf(f2, "%s %d ", chaine, temp[i].val);
	}
fprintf(f2, "\n");
}
}
}
    fclose(f1);
    fclose(f2);
    remove(File_name);
    rename("nouv.txt", File_name);
    return tr;
}


void convertid_nom(char* File_name, char* nom, int id_etab)
{
etablissement temp;
FILE* f;
int l;

    f = fopen("etablissement.txt", "r");

    if (f == NULL)

        return;

    else

    {

        while (fscanf(f, "%d %s %s %d %s %s %s %d %d %d %d %d %d", &temp.id, temp.nom_ETS, temp.lieu_ETS, &temp.cap, temp.adr, temp.tele, temp.adr_email, &temp.service[0], &temp.service[1], &temp.service[2], &temp.service[3], &temp.service[4], &temp.type) != EOF)
        {

	if (temp.id == id_etab)
	{
		strcpy(nom, temp.nom_ETS);
	}
        }
    }
fclose(f);
}

int lire_cond_m (char* File_name, condMedical* t, int id)
{
int tr = 0;
    int id_dem;
    FILE* f;
    f = fopen(File_name, "r");
    if (f == NULL)
        return;
    else
    {
        while (fscanf(f, "%d %s %d %s %d %s %d %s %d %s %d %s %d %s %d %s %d", &id_dem, t[0].cond, &t[0].val, t[1].cond, &t[1].val, t[2].cond, &t[2].val, t[3].cond, &t[3].val, t[4].cond, &t[4].val, t[5].cond, &t[5].val, t[6].cond, &t[6].val, t[7].cond, &t[7].val))
        {
            if (id_dem == id)
{
		tr = 1;
                break;
}
        }
    }
    fclose(f);
}

int dern_num_dem (char* File_name)
{
    dem_poche_sang temp;
    temp.id_dem = -1;
    int num = 1;
    int aux;
    FILE* f;
    f = fopen (File_name, "r");
    if (f == NULL)
        return;
    else
        {
        while ((fscanf(f, "%d %d %s %d %s %d %s %d %s %d %s %d %s %d %s %d %s %d %s %d %s %d %d %s %d %d", &temp.id_dem, &temp.id_etab, temp.T[0].type, &temp.T[0].nbr_poches, temp.T[1].type, &temp.T[1].nbr_poches, temp.T[2].type, &temp.T[2].nbr_poches, temp.T[3].type, &temp.T[3].nbr_poches, temp.T[4].type, &temp.T[4].nbr_poches, temp.T[5].type, &temp.T[5].nbr_poches, temp.T[6].type, &temp.T[6].nbr_poches, temp.T[7].type, &temp.T[7].nbr_poches, temp.cond_med, &temp.date_dem.jours, temp.date_dem.mois, &temp.date_dem.annees, &temp.date_lim.jours, temp.date_lim.mois, &temp.date_lim.annees, &temp.trait)) != EOF)
        {
	if (temp.id_dem != -1)
	{
            aux = temp.id_dem;
            if (num < aux)
            {
                num = aux;
            }
	}
	else
	    num = 0;
        }
        }
    fclose(f);
    return num + 1;
}

//////////////////////////////////////////////////////////
void afficher_demande_cher(GtkWidget *liste)
{
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store;

        store = NULL;

store = gtk_tree_view_get_model(liste);
if (store == NULL)
{
        renderer = gtk_cell_renderer_text_new ();
        column = gtk_tree_view_column_new_with_attributes ("Num: ", renderer, "text", ENUM, NULL);
        gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

        renderer = gtk_cell_renderer_text_new ();
        column = gtk_tree_view_column_new_with_attributes ("Nom Etablissemnet", renderer, "text", ENOM, NULL);
        gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

        renderer = gtk_cell_renderer_text_new ();
        column = gtk_tree_view_column_new_with_attributes ("Types et quantites de sangs", renderer, "text", ETYPE, NULL);
        gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

	renderer = gtk_cell_renderer_text_new ();
        column = gtk_tree_view_column_new_with_attributes ("Conditions Mediacales", renderer, "text", ECOND, NULL);
        gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

        renderer = gtk_cell_renderer_text_new ();
        column = gtk_tree_view_column_new_with_attributes ("date de la demande", renderer, "text", EDATEDEM, NULL);
        gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

        renderer = gtk_cell_renderer_text_new ();
        column = gtk_tree_view_column_new_with_attributes ("date limite de livraison", renderer, "text", EDATELIM, NULL);
        gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

        renderer = gtk_cell_renderer_text_new ();
        column = gtk_tree_view_column_new_with_attributes ("livre", renderer, "text", ETRAITE, NULL);
        gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
}

        store = gtk_list_store_new (COLUMNS, G_TYPE_INT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING ,G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);


    FILE* f;
    dem_poche_sang temp;
    int numdem;
    char nometab[40];
    char date1[20];
    char date2[20];
    char TQ_sang[50];
    char condit_med[300];
    char trait[5];

    f = fopen("chercher.txt", "r");
    if (f == NULL)
        return;
    else
    {
        while ((fscanf(f, "%d %d %s %d %s %d %s %d %s %d %s %d %s %d %s %d %s %d %s %d %s %d %d %s %d %d", &temp.id_dem, &temp.id_etab, temp.T[0].type, &temp.T[0].nbr_poches, temp.T[1].type, &temp.T[1].nbr_poches, temp.T[2].type, &temp.T[2].nbr_poches, temp.T[3].type, &temp.T[3].nbr_poches, temp.T[4].type, &temp.T[4].nbr_poches, temp.T[5].type, &temp.T[5].nbr_poches, temp.T[6].type, &temp.T[6].nbr_poches, temp.T[7].type, &temp.T[7].nbr_poches, temp.cond_med, &temp.date_dem.jours, temp.date_dem.mois, &temp.date_dem.annees, &temp.date_lim.jours, temp.date_lim.mois, &temp.date_lim.annees, &temp.trait)) != EOF)
        {

	    numdem = temp.id_dem;
	    //idetab = temp.id_etab;
	    convertid_nom("etablissement.txt", nometab, temp.id_etab);
	    if(temp.trait == 1)
		strcpy(trait, "Oui");
	    else
		strcpy(trait, "Non");
            date_string (temp.date_dem, date1);
            date_string (temp.date_lim, date2);
            type_sang_str(temp, TQ_sang);
	    strcpy (condit_med, temp.cond_med);
//remplacer le vergules par \n
	    for (int i = 0; i < strlen(condit_med); i++)
	    {
		if (condit_med[i] == ',')
		    condit_med[i] = '\n';
	    }

            gtk_list_store_append (store, &iter);
            gtk_list_store_set (store, &iter, ENUM, numdem, ENOM, nometab, ETYPE, TQ_sang, ECOND, condit_med, EDATEDEM, date1, EDATELIM, date2, ETRAITE, trait, -1);
        }
        fclose (f);
        gtk_tree_view_set_model (GTK_TREE_VIEW (liste), GTK_TREE_MODEL (store));
        g_object_unref (store);
    }
}

/////////////////////////////////////////////////////////////


int ajouter_cher (char *File_name, dem_poche_sang demande)
{

    FILE *f;
    f = fopen (File_name, "a");
    if (f != NULL)
    {
        fprintf(f, "%d %d ", demande.id_dem, demande.id_etab);
        for (int i = 0; i < 8; i++)
        {
            fprintf(f, "%s %d ", demande.T[i].type, demande.T[i].nbr_poches);
        }
        fprintf(f, "%s %d %s %d %d %s %d %d\n", demande.cond_med, demande.date_dem.jours, demande.date_dem.mois, demande.date_dem.annees, demande.date_lim.jours, demande.date_lim.mois, demande.date_lim.annees, demande.trait);
        fclose(f);
        return 1;
    }
    else return 0;
}

///////////////////////////////////////////////////////////////
void afficher_demande_cher_n(GtkWidget *liste)
{
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store;

        store = NULL;

store = gtk_tree_view_get_model(liste);
if (store == NULL)
{
        renderer = gtk_cell_renderer_text_new ();
        column = gtk_tree_view_column_new_with_attributes ("Num: ", renderer, "text", ENUM, NULL);
        gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

        renderer = gtk_cell_renderer_text_new ();
        column = gtk_tree_view_column_new_with_attributes ("Nom Etablissemnet", renderer, "text", ENOM, NULL);
        gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

        renderer = gtk_cell_renderer_text_new ();
        column = gtk_tree_view_column_new_with_attributes ("Types et quantites de sangs", renderer, "text", ETYPE, NULL);
        gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

	renderer = gtk_cell_renderer_text_new ();
        column = gtk_tree_view_column_new_with_attributes ("Conditions Mediacales", renderer, "text", ECOND, NULL);
        gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

        renderer = gtk_cell_renderer_text_new ();
        column = gtk_tree_view_column_new_with_attributes ("date de la demande", renderer, "text", EDATEDEM, NULL);

        gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

        renderer = gtk_cell_renderer_text_new ();
        column = gtk_tree_view_column_new_with_attributes ("date limite de livraison", renderer, "text", EDATELIM, NULL);
        gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

        renderer = gtk_cell_renderer_text_new ();
        column = gtk_tree_view_column_new_with_attributes ("livre", renderer, "text", ETRAITE, NULL);
        gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
}

        store = gtk_list_store_new (COLUMNS, G_TYPE_INT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING ,G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);

gtk_list_store_append (store, &iter);
            gtk_list_store_set (store, &iter, ENUM, 0000, ENOM, "demande non trouve", ETYPE, "!!!!", ECOND, "!!!!", EDATEDEM, "!!!!", EDATELIM, "!!!!", ETRAITE, "!!!!", -1);


        gtk_tree_view_set_model (GTK_TREE_VIEW (liste), GTK_TREE_MODEL (store));
        g_object_unref (store);
    
}

