#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "fonctions.h"
#include "etablissement.h"
#include "utilisateur.h"
#include "fiche.h"

int confirmation = 1;
int confirmation_modif = 1;
condMedical choix[8];
condMedical choixm[8];
dem_poche_sang demande_selec;
int selectionne = 0;

void
on_GDPS_actualiser_button_clicked      (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *fenetre_gestion;
GtkWidget *treeview;

fenetre_gestion = lookup_widget(objet, "gestion");

treeview = lookup_widget(fenetre_gestion, "treeview");

afficher_demande(treeview);
}


void
on_gdps_ajouter_clicked                (GtkWidget       *button,
                                        gpointer         user_data)
{
GtkWidget *fenetre_ajouter;
GtkWidget *combobox1;
chaine* tab;
int l;

etab_comb (&l, &tab);

fenetre_ajouter = lookup_widget(button, "fenetre_ajouter");
fenetre_ajouter = create_fenetre_ajouter();
combobox1 = lookup_widget(fenetre_ajouter, "combobox1");

for (int i = 0; i < l; i++)
{
gtk_combo_box_append_text (GTK_COMBO_BOX (combobox1), _(tab[i].a));
}
gtk_widget_show(fenetre_ajouter);
}


void
on_gdps_oui_radio_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(GTK_RADIO_BUTTON(togglebutton)))
	confirmation = 1;
}


void
on_gdps_non_radio_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(GTK_RADIO_BUTTON(togglebutton)))
	confirmation = 0;
}


void
on_gdps_ajouter_button_clicked         (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *combobox1;
GtkWidget *q_apos;
GtkWidget *q_opos;
GtkWidget *q_bpos;
GtkWidget *q_abpos;
GtkWidget *q_aneg;
GtkWidget *q_oneg;
GtkWidget *q_bneg;
GtkWidget *q_abneg;
GtkWidget *jours;
GtkWidget *mois;
GtkWidget *annees;
GtkWidget *fenetre_ajout;
GtkWidget *msg_conf;
//GtkWidget *fenetre_ges;
//GtkWidget *treeview;

dem_poche_sang demande;
dem_poche_sang d;
int x;
int count;
int val_id;

combobox1 = lookup_widget(objet, "combobox1");
q_apos = lookup_widget(objet, "gdps_apos_spin");
q_opos = lookup_widget(objet, "gdps_opos_spin");
q_bpos = lookup_widget(objet, "gdps_bpos_spin");
q_abpos = lookup_widget(objet, "gdps_abpos_spin");
q_aneg = lookup_widget(objet, "gdps_aneg_spin");
q_oneg = lookup_widget(objet, "gdps_oneg_spin");
q_bneg = lookup_widget(objet, "gdps_bneg_spin");
q_abneg = lookup_widget(objet, "gdps_abneg_spin");
jours = lookup_widget(objet, "gdps_datelim_jours_spin");
mois = lookup_widget(objet, "gdps_datelim_mois_entry");
annees = lookup_widget(objet, "gdps_datelim_annees");
msg_conf = lookup_widget(objet, "gdps_msg_conf");
fenetre_ajout = lookup_widget(objet, "fenetre_ajouter");
//fenetre_ges = lookup_widget(objet, "gestion");
//fenetre_ges = create_fenetre_ges();
//treeview = lookup_widget(fenetre_ges, "treeview");

///recuperation des valeur des spin buttons
demande.date_lim.jours = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (jours));
demande.date_lim.annees = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (annees));
demande.T[0].nbr_poches = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (q_apos));
demande.T[1].nbr_poches = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (q_opos));
demande.T[2].nbr_poches = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (q_bpos));
demande.T[3].nbr_poches = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (q_abpos));
demande.T[4].nbr_poches = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (q_aneg));
demande.T[5].nbr_poches = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (q_oneg));
demande.T[6].nbr_poches = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (q_bneg));
demande.T[7].nbr_poches = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (q_abneg));

//recuperation des valeurs des comboboxs
char idetab[20];

strcpy(idetab, gtk_combo_box_get_active_text(GTK_COMBO_BOX(combobox1)));
demande.id_etab = atoi(idetab);

strcpy(demande.date_lim.mois, gtk_combo_box_get_active_text(GTK_COMBO_BOX(mois)));

//remplir le numere de la demande
count = dern_num_dem ("demande.txt");
demande.id_dem = count;

//remplir le tableau des types de sangs
strcpy(demande.T[0].type, "A+");
strcpy(demande.T[1].type, "O+");
strcpy(demande.T[2].type, "b+");
strcpy(demande.T[3].type, "AB+");
strcpy(demande.T[4].type, "A-");
strcpy(demande.T[5].type, "O-");
strcpy(demande.T[6].type, "B-");
strcpy(demande.T[7].type, "AB-");

demande.trait = 0;

demande.date_dem.jours = 7;
demande.date_dem.annees = 2023;
strcpy(demande.date_dem.mois, "Decembre");

//remplir le tableau des choix
strcpy (choix[0].cond, "Chirurgie");
strcpy (choix[1].cond, "Traumatisme");
strcpy (choix[2].cond, "Anemie Severe");
strcpy (choix[3].cond, "Maladies du sang");
strcpy (choix[4].cond, "Cansers");
strcpy (choix[5].cond, "Interventions cardiaque");
strcpy (choix[6].cond, "Hemorragie interne");
strcpy (choix[7].cond, "Complication pendant la grossesse");


//recuperer la valeur de la condition medical
int test = 0;
for (int i = 0; i < 8; i++)
{
if (choix[i].val == 1)
{
test = 1;
}
}
strcpy (demande.cond_med, "");
if (test == 1)
{
for (int i = 0; i< 8; i++)
{
    if (choix[i].val == 1)
    {
	strcat(demande.cond_med, choix[i].cond);
	strcat(demande.cond_med, ",");
    }
}
}
if (strcmp(demande.cond_med, "") == 0)
{
	strcpy(demande.cond_med, "Pas de choix,");
}


demande.cond_med[strlen(demande.cond_med) - 1] = 46;
for (int i = 0; i < strlen (demande.cond_med); i++)
{
    if (demande.cond_med[i] == ' ')
	demande.cond_med[i] = '-';
}


//appel a la fonction d'ajout
if (confirmation == 1)
{
x = ajouter ("demande.txt", demande);
ajout_cond_m ("condition-medical.txt", choix, demande);
gtk_widget_destroy(fenetre_ajout);
//afficher_demande(treeview);
}

else
{
gtk_label_set_text(GTK_LABEL(msg_conf), "Vous devez confirmer votre choix!!");
}


//Rendre les valeurs de variables choix a 0;
for (int i = 0; i < 8; i++)
{
    choix[i].val = 0;
}

}


void
on_gdps_cm_choix8_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
    if (gtk_toggle_button_get_active(togglebutton))
    {
    choix[7].val = 1;
    strcpy (choix[7].cond, "Complication pendant la grossesse");
    }
    else
	choix[7].val = 0;
}


void
on_gdps_cm_choix7_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
    if (gtk_toggle_button_get_active(togglebutton))
    {
    choix[6].val = 1;
    strcpy (choix[6].cond, "Hemorragie interne");
    }
    else
	choix[6].val = 0;
}


void
on_gdps_cm_choix6_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
    if (gtk_toggle_button_get_active(togglebutton))
    {
    choix[5].val = 1;
    strcpy (choix[5].cond, "Interventions cardiaque");
    }
    else
	choix[5].val = 0;
}


void
on_gdps_cm_choix5_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
    if (gtk_toggle_button_get_active(togglebutton))
    {
    choix[4].val = 1;
    strcpy (choix[4].cond, "Cansers");
    }
    else
	choix[4].val = 0;
}


void
on_gdps_cm_choix4_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
    if (gtk_toggle_button_get_active(togglebutton))
    {
    choix[3].val = 1;
    strcpy (choix[3].cond, "Maladies du sang");
    }
    else
	choix[3].val = 0;
}


void
on_gdps_cm_choix3_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
    if (gtk_toggle_button_get_active(togglebutton))
    {
    choix[2].val = 1;
    strcpy (choix[2].cond, "Anemie Severe");
    }
    else
	choix[2].val = 0;
}


void
on_gdps_cm_choix2_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
    if (gtk_toggle_button_get_active(togglebutton))
    {
    choix[1].val = 1;
    strcpy (choix[1].cond, "Traumatisme");
    }
    else
	choix[1].val = 0;
}


void
on_gdps_cm_choix1_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
    if (gtk_toggle_button_get_active(togglebutton))
    {
    choix[0].val = 1;
    strcpy (choix[0].cond, "Chirurgie");
    }
    else
	choix[0].val = 0;
}



void
on_treeview_row_activated              (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
	
	GtkTreeIter iter;
	gint* id;
	gint* idEtab;
	gchar* tyqt;
	gchar* condmedic;
	gchar* date1;
	gchar* date2;
	gchar* traite;
	int numdem;
	
	
GtkTreeModel *model = gtk_tree_view_get_model(treeview);

if (gtk_tree_model_get_iter(model, &iter, path))
{
	gtk_tree_model_get (GTK_LIST_STORE(model), &iter, 0, &id, 1, &idEtab, 2, &tyqt, 3, &condmedic, 4, &date1, 5, date2, 6, traite, -1);
	numdem = id;
	demande_selec = chercher("demande.txt", numdem);
	selectionne = 1;
}

}


void
on_gdps_modifier_clicked               (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget* fenetre_modifier;
GtkWidget* sortie_id_dem;
GtkWidget* sortie_nom_etab;
GtkWidget* msg_erreur;
GtkWidget* choix1;
GtkWidget* choix2;
GtkWidget* choix3;
GtkWidget* choix4;
GtkWidget* choix5;
GtkWidget* choix6;
GtkWidget* choix7;
GtkWidget* choix8;

GtkWidget *q_apos;
GtkWidget *q_opos;
GtkWidget *q_bpos;
GtkWidget *q_abpos;
GtkWidget *q_aneg;
GtkWidget *q_oneg;
GtkWidget *q_bneg;
GtkWidget *q_abneg;
char iddem[20];
char nometab[30];
int trouve;

fenetre_modifier = lookup_widget(objet, "fenetre_modifier");
fenetre_modifier = create_fenetre_modifier();
sortie_id_dem = lookup_widget(fenetre_modifier, "gdps_modif_iddem_sortie");
sortie_nom_etab = lookup_widget(fenetre_modifier, "gdps_modif_idetab_sortie");
msg_erreur = lookup_widget(objet, "gdps_msg_erreur");
choix1 = lookup_widget(fenetre_modifier, "gdps_modif_choix1");
choix2 = lookup_widget(fenetre_modifier, "gdps_modif_choix2");
choix3 = lookup_widget(fenetre_modifier, "gdps_modif_choix3");
choix4 = lookup_widget(fenetre_modifier, "gdps_modif_choix4");
choix5 = lookup_widget(fenetre_modifier, "gdps_modif_choix5");
choix6 = lookup_widget(fenetre_modifier, "gdps_modif_choix6");
choix7 = lookup_widget(fenetre_modifier, "gdps_modif_choix7");
choix8 = lookup_widget(fenetre_modifier, "gdps_modif_choix8");

q_apos = lookup_widget(fenetre_modifier, "gdps_apos_old");
q_opos = lookup_widget(fenetre_modifier, "gdps_opos_old");
q_bpos = lookup_widget(fenetre_modifier, "gdps_bpos_old");
q_abpos = lookup_widget(fenetre_modifier, "gdps_abpos_old");
q_aneg = lookup_widget(fenetre_modifier, "gdps_aneg_old");
q_oneg = lookup_widget(fenetre_modifier, "gdps_oneg_old");
q_bneg = lookup_widget(fenetre_modifier, "gdps_bneg_old");
q_abneg = lookup_widget(fenetre_modifier, "gdps_abneg_old");

char apos[10];
char opos[10];
char bpos[10];
char abpos[10];
char aneg[10];
char oneg[10];
char bneg[10];
char abneg[10];



if (selectionne == 1)
{
sprintf(iddem, "%d", demande_selec.id_dem);
convertid_nom("etablissement.tx", nometab, demande_selec.id_etab);
gtk_label_set_text(GTK_LABEL(sortie_id_dem), iddem);
gtk_label_set_text(GTK_LABEL(sortie_nom_etab), nometab);
gtk_widget_show(fenetre_modifier);

//appel a la fonctikon lire conditon medical et modifier le tableau des choix
trouve = lire_cond_m ("condition-medical.txt", choixm, demande_selec.id_dem);

//reconvertir '-' en espace
for (int i = 0; i < 8; i++)
{
for (int j = 0; j < strlen(choix[i].cond); j++)
{
	if (choix[i].cond[j] == '-')
	    choix[i].cond[j] = ' ';
}
}

//afficher les quantites de sangs
sprintf(apos, "%d", demande_selec.T[0].nbr_poches);
gtk_label_set_text(GTK_LABEL(q_apos), apos);

sprintf(opos, "%d", demande_selec.T[1].nbr_poches);
gtk_label_set_text(GTK_LABEL(q_opos), opos);

sprintf(bpos, "%d", demande_selec.T[2].nbr_poches);
gtk_label_set_text(GTK_LABEL(q_bpos), bpos);

sprintf(abpos, "%d", demande_selec.T[3].nbr_poches);
gtk_label_set_text(GTK_LABEL(q_abpos), abpos);

sprintf(aneg, "%d", demande_selec.T[4].nbr_poches);
gtk_label_set_text(GTK_LABEL(q_aneg), aneg);

sprintf(oneg, "%d", demande_selec.T[5].nbr_poches);
gtk_label_set_text(GTK_LABEL(q_oneg), oneg);

sprintf(bneg, "%d", demande_selec.T[6].nbr_poches);
gtk_label_set_text(GTK_LABEL(q_bneg), bneg);

sprintf(abneg, "%d", demande_selec.T[7].nbr_poches);
gtk_label_set_text(GTK_LABEL(q_abneg), abneg);

//preselectionner les boutton a coucher
if (choixm[0].val == 1)
{
gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(choix1), TRUE);
}
if (choixm[1].val == 1)
{
gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(choix2), TRUE);
}
if (choixm[2].val == 1)
{
gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(choix3), TRUE);
}
if (choixm[3].val == 1)
{
gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(choix4), TRUE);
}
if (choixm[4].val == 1)
{
gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(choix5), TRUE);
}
if (choixm[5].val == 1)
{
gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(choix6), TRUE);
}
if (choixm[6].val == 1)
{
gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(choix7), TRUE);
}
if (choixm[7].val == 1)
{
gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(choix8), TRUE);
}

selectionne = 0;
gtk_label_set_text(GTK_LABEL(msg_erreur), "");
}
else
{
gtk_label_set_text(GTK_LABEL(msg_erreur), "Selctionner une demande dans le tableau avant de modifier!!");
}

}


void
on_gdps_modifer_button_clicked         (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *q_apos;
GtkWidget *q_opos;
GtkWidget *q_bpos;
GtkWidget *q_abpos;
GtkWidget *q_aneg;
GtkWidget *q_oneg;
GtkWidget *q_bneg;
GtkWidget *q_abneg;
GtkWidget *msg_conf;
GtkWidget *fenetre_modifier;
//GtkWidget *fenetre_ges;
//GtkWidget *treeview;

dem_poche_sang nouv_demande;
dem_poche_sang d;
int x;
int x2;
int count;
int val_id;

q_apos = lookup_widget(objet, "gdps_modif_apos");
q_opos = lookup_widget(objet, "gdps_modif_opos");
q_bpos = lookup_widget(objet, "gdps_modif_bpos");
q_abpos = lookup_widget(objet, "gdps_modif_abpos");
q_aneg = lookup_widget(objet, "gdps_modif_aneg");
q_oneg = lookup_widget(objet, "gdps_modif_oneg");
q_bneg = lookup_widget(objet, "gdps_modif_bneg");
q_abneg = lookup_widget(objet, "gdps_modif_abneg");
msg_conf = lookup_widget(objet, "gdps_modif_msg_conf");
fenetre_modifier = lookup_widget(objet, "fenetre_modifier");
//fenetre_ges = lookup_widget(objet, "gestion");
//treeview = lookup_widget(fenetre_ges, "treeview");

///recuperation des valeur des spin buttons
nouv_demande.T[0].nbr_poches = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (q_apos));
nouv_demande.T[1].nbr_poches = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (q_opos));
nouv_demande.T[2].nbr_poches = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (q_bpos));
nouv_demande.T[3].nbr_poches = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (q_abpos));
nouv_demande.T[4].nbr_poches = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (q_aneg));
nouv_demande.T[5].nbr_poches = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (q_oneg));
nouv_demande.T[6].nbr_poches = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (q_bneg));
nouv_demande.T[7].nbr_poches = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (q_abneg));


//remplir le numere de la demande
nouv_demande.id_dem = demande_selec.id_dem;

//remplir le tableau des types de sangs
strcpy(nouv_demande.T[0].type, "A+");
strcpy(nouv_demande.T[1].type, "O+");
strcpy(nouv_demande.T[2].type, "b+");
strcpy(nouv_demande.T[3].type, "AB+");
strcpy(nouv_demande.T[4].type, "A-");
strcpy(nouv_demande.T[5].type, "O-");
strcpy(nouv_demande.T[6].type, "B-");
strcpy(nouv_demande.T[7].type, "AB-");

nouv_demande.trait = 0;

//remplir la date limite
nouv_demande.date_lim.jours = demande_selec.date_lim.jours;
strcpy (nouv_demande.date_lim.mois, demande_selec.date_lim.mois);
nouv_demande.date_lim.annees = demande_selec.date_lim.annees;

//remplir id etablissement
nouv_demande.id_etab = demande_selec.id_etab;

nouv_demande.date_dem.jours = 7;
nouv_demande.date_dem.annees = 2023;
strcpy(nouv_demande.date_dem.mois, "Decembre");

//remplir le tableau des choix
strcpy (choixm[0].cond, "Chirurgie");
strcpy (choixm[1].cond, "Traumatisme");
strcpy (choixm[2].cond, "Anemie Severe");
strcpy (choixm[3].cond, "Maladies du sang");
strcpy (choixm[4].cond, "Cansers");
strcpy (choixm[5].cond, "Interventions cardiaque");
strcpy (choixm[6].cond, "Hemorragie interne");
strcpy (choixm[7].cond, "Complication pendant la grossesse");

//recuperer la valeur de la condition medical
strcpy (nouv_demande.cond_med, "");
for (int i = 0; i< 8; i++)
{
    if (choixm[i].val == 1)
    {
	strcat(nouv_demande.cond_med, choixm[i].cond);
	strcat(nouv_demande.cond_med, ",");
    }
}
nouv_demande.cond_med[strlen(nouv_demande.cond_med) - 1] = 46;
for (int i = 0; i < strlen (nouv_demande.cond_med); i++)
{
    if (nouv_demande.cond_med[i] == ' ')
	nouv_demande.cond_med[i] = '-';
}
char test[10];
if (confirmation_modif == 1)
{
x = modifier ("demande.txt", demande_selec.id_dem, nouv_demande);
x2 = modifier_cond_m ("condition-medical.txt", choixm, demande_selec.id_dem);
gtk_widget_destroy(fenetre_modifier);
selectionne = 0;
//afficher_demande(treeview);
//gtk_label_set_text(GTK_LABEL(msg_conf), test);
}
else 
{
gtk_label_set_text(GTK_LABEL(msg_conf), "Vous devez confirmer votre choix!!");
}

}


void
on_gdps_modif_oui_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(GTK_RADIO_BUTTON(togglebutton)))
	confirmation_modif = 1;
}


void
on_gdps_modif_non_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(GTK_RADIO_BUTTON(togglebutton)))
	confirmation_modif = 0;
}


void
on_gdps_modif_choix1_toggled           (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
    if (gtk_toggle_button_get_active(togglebutton))
    {
    choixm[0].val = 1;
    strcpy (choix[0].cond, "Chirurgie");
    }
    else
	choixm[0].val = 0;
}


void
on_gdps_modif_choix2_toggled           (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
    if (gtk_toggle_button_get_active(togglebutton))
    {
    choixm[1].val = 1;
    strcpy (choix[1].cond, "Traumatisme");
    }
    else
	choixm[1].val = 0;
}


void
on_gdps_modif_choix3_toggled           (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
    if (gtk_toggle_button_get_active(togglebutton))
    {
    choixm[2].val = 1;
    strcpy (choix[2].cond, "Anemie Severe");
    }
    else
	choixm[2].val = 0;
}


void
on_gdps_modif_choix4_toggled           (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
    if (gtk_toggle_button_get_active(togglebutton))
    {
    choixm[3].val = 1;
    strcpy (choix[3].cond, "Maladies du sang");
    }
    else
	choixm[3].val = 0;
}


void
on_gdps_modif_choix5_toggled           (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
    if (gtk_toggle_button_get_active(togglebutton))
    {
    choixm[4].val = 1;
    strcpy (choix[4].cond, "Cansers");
    }
    else
	choixm[4].val = 0;
}


void
on_gdps_modif_choix6_toggled           (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
    if (gtk_toggle_button_get_active(togglebutton))
    {
    choixm[5].val = 1;
    strcpy (choix[5].cond, "Interventions cardiaque");
    }
    else
	choixm[5].val = 0;
}


void
on_gdps_modif_choix7_toggled           (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
    if (gtk_toggle_button_get_active(togglebutton))
    {
    choixm[6].val = 1;
    strcpy (choix[6].cond, "Hemorragie interne");
    }
    else
	choixm[6].val = 0;
}


void
on_gdps_modif_choix8_toggled           (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
    if (gtk_toggle_button_get_active(togglebutton))
    {
    choixm[7].val = 1;
    strcpy (choixm[7].cond, "Complication pendant la grossesse");
    }
    else
	choix[7].val = 0;
}


void
on_gdps_supprimer_button_clicked       (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget* msg_erreur;

msg_erreur = lookup_widget(objet, "gdps_msg_erreur");

int x;
if (selectionne == 1);
{
x = supprimer ("demande.txt", demande_selec.id_dem);
if (x == 1)
{
gtk_label_set_text(GTK_LABEL(msg_erreur), "Supression avec succes!!");
}
else
{
gtk_label_set_text(GTK_LABEL(msg_erreur), "Supression echoue!!");
}
}
if (selectionne == 0)
{
gtk_label_set_text(GTK_LABEL(msg_erreur), "Selctionner une demande dans le tableau avant de supprimer!!");
}
}


void
on_gdps_statistique_button_clicked     (GtkWidget       *objet,
                                        gpointer         user_data)
{

GtkWidget* pourcetab;
GtkWidget* sangdem;
GtkWidget* idetabentry;
GtkWidget* quant;


char id_etabch[20];
int id_etab;
float pourcent;
char pourcentagech[30];
char sang_dem[20];
int max;
char quant_a[20];

idetabentry = lookup_widget(objet, "gdps_choixeatb");
pourcetab = lookup_widget(objet, "gdps_stat1_label");
sangdem = lookup_widget(objet, "gdps_stat2_label");
quant = lookup_widget(objet, "gdps_quant_pd");


strcpy(id_etabch, gtk_combo_box_get_active_text(GTK_COMBO_BOX(idetabentry)));

id_etab = strtof(id_etabch, NULL);

pourcent = pourcentage ("demande.txt", id_etab);
max = sang_demande("demande.txt", sang_dem);

sprintf(pourcentagech, "%.2f", pourcent);
sprintf(quant_a, "%d", max);
gtk_label_set_text(GTK_LABEL(pourcetab), pourcentagech);
gtk_label_set_text(GTK_LABEL(sangdem), sang_dem);
gtk_label_set_text(GTK_LABEL(quant), quant_a);

}


void
on_gdps_chercher_button_clicked        (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *fenetre_gestion;
GtkWidget *treeview;
GtkWidget *numdem;
GtkWidget *msg;

char numd[20];
int num;
dem_poche_sang d;
int x;
char test[10];

fenetre_gestion = lookup_widget(objet, "gestion");
msg = lookup_widget(objet, "gdps_msg_erreur");
treeview = lookup_widget(objet, "treeview");
numdem = lookup_widget(fenetre_gestion, "gdps_chercher_entry");

strcpy (numd, gtk_entry_get_text(GTK_ENTRY(numdem)));

num = atoi(numd);
d = chercher ("demande.txt", num);

if (d.id_dem != -1)
{
x = ajouter_cher ("chercher.txt", d);

if (x == 1)
{
gtk_label_set_text(GTK_LABEL(msg), "Demande trouve");
afficher_demande_cher(treeview);
remove ("chercher.txt");
}
else
{
gtk_label_set_text(GTK_LABEL(msg), "Echoue");
}

}
else
{
gtk_label_set_text(GTK_LABEL(msg), "Demande non trouve");
afficher_demande_cher_n(treeview);
}
}


void
on_auth_connecter_button_clicked       (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *email;
GtkWidget *mdp;
GtkWidget *msg1;
GtkWidget *msg2;
GtkWidget *gestion;
GtkWidget *fiche_don_user;
GtkWidget *gestionu;
GtkWidget *combobox1;
GtkWidget *treeview;
GtkWidget *authentification;

email = lookup_widget(objet, "auth_email_entry");
mdp = lookup_widget(objet, "auth_mdp_entry");
msg1 = lookup_widget(objet, "auth_msg1");
msg2 = lookup_widget(objet, "auth_msg2");
authentification = lookup_widget(objet, "authentification");

char e_mail[35];
char mdpasse[15];
Utilisateur u;

chaine* tab;
int l;

strcpy (e_mail, gtk_entry_get_text(GTK_ENTRY(email)));
strcpy (mdpasse, gtk_entry_get_text(GTK_ENTRY(mdp)));

u = chercher_utlis ("utilisateur.txt", e_mail);

if (strcmp(u.adresse_email, "-1") == 0)
{
	gtk_label_set_text(GTK_LABEL(msg1), "Utilisateur non trouve!!");
}
else
{
	if (strcmp(u.CIN, mdpasse) != 0)
	{
		gtk_label_set_text(GTK_LABEL(msg2), "Mot de passe incorrecte!!");
	}
	else if (strcmp(u.CIN, mdpasse) == 0)
	{
	if (strcmp(u.role, "responsable_ETS") == 0)
	{
	gestion = create_gestion ();
	gtk_widget_show (gestion);
        combobox1 = lookup_widget(gestion, "gdps_choixeatb");
	treeview = lookup_widget(gestion, "treeview");
        afficher_demande(treeview);
        etab_comb (&l, &tab);
        for (int i = 0; i < l; i++)
        {
        gtk_combo_box_append_text (GTK_COMBO_BOX (combobox1), _(tab[i].a));
        }
	gtk_widget_destroy (authentification);
	}
	else if (strcmp(u.role, "infermier") == 0)
	{
	fiche_don_user = create_fiche_don_user ();
	gtk_widget_show (fiche_don_user);
	gtk_widget_destroy (authentification);
	}
	else if (strcmp(u.role, "administrateur") == 0)
	{
	gestionu = create_gestionu ();
	gtk_widget_show (gestionu);
	gtk_widget_destroy (authentification);
	}
	}
}

}

//////////////////////////////////////////////////////

void
on_button_aj_clicked                   (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *aj1, *aj2, *aj3, *aj4, *aj5, *aj6, *aj7, *aj8, *aj9, *aj10, *aj11, *aj12, *aj13, *aj14, *pInfo;
ut u;
char ch[100];
strcpy(ch, "");
aj1=lookup_widget(objet,"aj1");
aj2=lookup_widget(objet,"aj2");
aj3=lookup_widget(objet,"aj3");
aj4=lookup_widget(objet,"aj4");
aj5=lookup_widget(objet,"aj5");
aj6=lookup_widget(objet,"aj6");
aj7=lookup_widget(objet,"aj7");
aj8=lookup_widget(objet,"aj8");
aj9=lookup_widget(objet,"aj9");
aj10=lookup_widget(objet,"aj10");
aj11=lookup_widget(objet,"aj11");
aj12=lookup_widget(objet,"aj12");
aj13=lookup_widget(objet,"aj13");
aj14=lookup_widget(objet,"aj14");
bool a=gtk_toggle_button_get_active(GTK_CHECK_BUTTON(aj13));
u.cin=atoi(gtk_entry_get_text(GTK_ENTRY(aj1)));
strcpy(u.nom,gtk_entry_get_text(GTK_ENTRY(aj2)));
strcpy(u.prenom,gtk_entry_get_text(GTK_ENTRY(aj3)));
strcpy(u.email,gtk_entry_get_text(GTK_ENTRY(aj4)));
strcpy(u.gs,gtk_combo_box_get_active_text(GTK_COMBO_BOX(aj5)));
u.ets = atoi(gtk_entry_get_text(GTK_ENTRY(aj6)));
u.sexe=gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(aj7))?0:1;
u.d.j=gtk_spin_button_get_value(GTK_SPIN_BUTTON(aj9));
u.d.m=gtk_spin_button_get_value(GTK_SPIN_BUTTON(aj10));
u.d.a=gtk_spin_button_get_value(GTK_SPIN_BUTTON(aj11));
u.poid=gtk_spin_button_get_value(GTK_SPIN_BUTTON(aj12));
strcpy(u.mala,gtk_combo_box_get_active_text(GTK_COMBO_BOX(aj14)));


if(!Check_Email_Addr(u.email))
strcat(ch, "Email invalide\n");
if(!valid_cin(gtk_entry_get_text(GTK_ENTRY(aj1))))
strcat(ch, "CIN invalide\n");
if(!a)
strcat(ch, "Veuillez confirmer");
if(strcmp(ch,"")==0)
ajouter_f(u, "user.txt");
else{
pInfo=gtk_message_dialog_new(GTK_WINDOW(user_data),GTK_DIALOG_MODAL,GTK_MESSAGE_WARNING,GTK_BUTTONS_OK,ch);
	switch(gtk_dialog_run(GTK_DIALOG(pInfo)))
	{
	case GTK_RESPONSE_OK:
	gtk_widget_destroy(pInfo);
	break;
	}
}

}

void
on_user_quit_aj_clicked                (GtkWidget       *button,
                                        gpointer         user_data)
{
	GtkWidget *user;
	GtkWidget *aj;
	aj=lookup_widget(button,"aj");
	gtk_widget_destroy(aj);
	user=lookup_widget(button,"fiche_don_user");
	user=create_fiche_don_user();
	gtk_widget_show(user);
}



void
on_user_ajout_clicked                  (GtkButton       *button,
                                        gpointer         user_data)
{	
	GtkWidget *user;
	GtkWidget *aj;
	user=lookup_widget(button,"fiche_don_user");
	gtk_widget_destroy(user);
	aj=lookup_widget(button,"aj");
	aj=create_aj();
	gtk_widget_show(aj);


}


void
on_user_quit_mod_clicked               (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *user;
	GtkWidget *modif;
	modif=lookup_widget(button,"modif");
	gtk_widget_destroy(modif);
	user=lookup_widget(button,"fiche_don_user");
	user=create_fiche_don_user();
	gtk_widget_show(user);
}


void
on_button_mod_clicked                  (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *mod1, *mod2, *mod3, *mod4, *mod5, *mod6, *mod7, *mod8, *mod9, *mod10, *mod11, *mod12, *mod13, *mod14, *pInfo;
ut u;
mod1=lookup_widget(objet,"mod1");
mod2=lookup_widget(objet,"mod2");
mod3=lookup_widget(objet,"mod3");
mod4=lookup_widget(objet,"mod4");
mod5=lookup_widget(objet,"mod5");
mod6=lookup_widget(objet,"mod6");
mod7=lookup_widget(objet,"mod7");
mod8=lookup_widget(objet,"mod8");
mod9=lookup_widget(objet,"mod9");
mod10=lookup_widget(objet,"mod10");
mod11=lookup_widget(objet,"mod11");
mod12=lookup_widget(objet,"mod12");
mod13=lookup_widget(objet,"mod13");
mod14=lookup_widget(objet,"mod14");
u.cin=atoi(gtk_entry_get_text(GTK_ENTRY(mod1)));
strcpy(u.mala,gtk_combo_box_get_active_text(GTK_COMBO_BOX(mod14)));
strcpy(u.nom,gtk_entry_get_text(GTK_ENTRY(mod2)));
strcpy(u.prenom,gtk_entry_get_text(GTK_ENTRY(mod3)));
strcpy(u.email,gtk_entry_get_text(GTK_ENTRY(mod4)));
strcpy(u.gs,gtk_combo_box_get_active_text(GTK_COMBO_BOX(mod5)));
u.ets = atoi(gtk_entry_get_text(GTK_ENTRY(mod6)));
u.sexe=gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(mod7))?0:1;
u.d.j=gtk_spin_button_get_value(GTK_SPIN_BUTTON(mod9));
u.d.m=gtk_spin_button_get_value(GTK_SPIN_BUTTON(mod10));
u.d.a=gtk_spin_button_get_value(GTK_SPIN_BUTTON(mod11));
u.poid=gtk_spin_button_get_value(GTK_SPIN_BUTTON(mod12));
bool a=gtk_toggle_button_get_active(GTK_CHECK_BUTTON(mod13));
if(a)
modifier_f(u,"user.txt");
else{
pInfo=gtk_message_dialog_new(GTK_WINDOW(user_data),GTK_DIALOG_MODAL,GTK_MESSAGE_WARNING,GTK_BUTTONS_OK,"Veuillez confirmer");
	switch(gtk_dialog_run(GTK_DIALOG(pInfo)))
	{
	case GTK_RESPONSE_OK:
	gtk_widget_destroy(pInfo);
	break;
	}
}
}


void
on_check_id_clicked                    (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *mod1, *mod2, *mod3, *mod4, *mod5, *mod6, *mod7, *mod8, *mod9, *mod10, *mod11, *mod12, *mod13, *mod14, *pInfo;
int a=0;
int id;
char ets[10], mala[20];
FILE *f;
mod1=lookup_widget(objet,"mod1");
mod2=lookup_widget(objet,"mod2");
mod3=lookup_widget(objet,"mod3");
mod4=lookup_widget(objet,"mod4");
mod5=lookup_widget(objet,"mod5");
mod6=lookup_widget(objet,"mod6");
mod7=lookup_widget(objet,"mod7");
mod8=lookup_widget(objet,"mod8");
mod9=lookup_widget(objet,"mod9");
mod10=lookup_widget(objet,"mod10");
mod11=lookup_widget(objet,"mod11");
mod12=lookup_widget(objet,"mod12");
mod13=lookup_widget(objet,"mod13");
mod14=lookup_widget(objet,"mod14");
id = atoi(gtk_entry_get_text(GTK_ENTRY(mod1)));
ut p = chercher_f(id, "user.txt");
if(p.cin!=-1){
sprintf(ets,"%d",p.ets);
sprintf(mala,"%s",p.mala);
gtk_entry_set_text(GTK_ENTRY(mod2),p.nom);
gtk_entry_set_text(GTK_ENTRY(mod3),p.prenom);
gtk_entry_set_text(GTK_ENTRY(mod4),p.email);
gtk_entry_set_text(GTK_ENTRY(mod5),p.gs);
gtk_entry_set_text(GTK_ENTRY(mod6),ets);
gtk_entry_set_text(GTK_ENTRY(mod14),mala);
gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(mod7),p.sexe==0?TRUE:FALSE);
gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(mod8),p.sexe==0?FALSE:TRUE);
gtk_spin_button_set_value(GTK_SPIN_BUTTON(mod9),p.d.j);
gtk_spin_button_set_value(GTK_SPIN_BUTTON(mod10),p.d.m);
gtk_spin_button_set_value(GTK_SPIN_BUTTON(mod11),p.d.a);
gtk_spin_button_set_value(GTK_SPIN_BUTTON(mod12),p.poid);
}
else{
pInfo=gtk_message_dialog_new(GTK_WINDOW(user_data),GTK_DIALOG_MODAL,GTK_MESSAGE_ERROR,GTK_BUTTONS_OK,"InfoDonneur introuvable");
	switch(gtk_dialog_run(GTK_DIALOG(pInfo)))
	{
	case GTK_RESPONSE_OK:
	gtk_widget_destroy(pInfo);
	break;
	}
}
}


void
on_user_modifer_clicked                (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *user;
	GtkWidget *mod;
	user=lookup_widget(button,"fiche_don_user");
	gtk_widget_destroy(user);
	mod=lookup_widget(button,"mod");
	mod=create_mod();
	gtk_widget_show(mod);


}


void
on_treeview1_row_activated              (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
	GtkTreeIter iter;
	guint id;
	ut u;
	GtkWidget *pInfo, *objet, *af;
	GtkTreeModel *model=gtk_tree_view_get_model(treeview);
	if(gtk_tree_model_get_iter(model,&iter,path)){
	gtk_tree_model_get(GTK_LIST_STORE(model),&iter,0,&id,-1);
	u.cin=id;
	pInfo=gtk_message_dialog_new(GTK_WINDOW(user_data),GTK_DIALOG_MODAL,GTK_MESSAGE_QUESTION,GTK_BUTTONS_YES_NO,"Voulez-vous vraiment\nsupprimer infoDonneur?");
	switch(gtk_dialog_run(GTK_DIALOG(pInfo)))
	{
	case GTK_RESPONSE_YES:
	gtk_widget_destroy(pInfo);
	supprimer_f(u,"user.txt");
	afficher_f(treeview,"user.txt", "", "", "");
	break;
	case GTK_RESPONSE_NO:
	gtk_widget_destroy(pInfo);
	break;
}	
}
}


void
on_button7_clicked                     (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *treeview, *af, *e1, *e2, *e3;
char id[10], email[50], nom[20];
af=lookup_widget(objet,"af");
treeview=lookup_widget(af,"treeview1");
e1=lookup_widget(objet, "entry1");
e2=lookup_widget(objet, "entry2");
e3=lookup_widget(objet, "entry3");
strcpy(id,gtk_entry_get_text(GTK_ENTRY(e1)));
strcpy(email,gtk_entry_get_text(GTK_ENTRY(e2)));
strcpy(nom,gtk_entry_get_text(GTK_ENTRY(e3)));
afficher_f(treeview, "user.txt", id, email, nom);
}


void
on_button_af_clicked                   (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *treeview, *af;
af=lookup_widget(objet,"af");
gtk_widget_destroy(af);
af=lookup_widget(objet,"af");
af=create_af();
gtk_widget_show(af);
treeview=lookup_widget(af,"treeview1"); 
afficher_f(treeview,"user.txt", "", "", "");
}


void
on_button9_clicked                     (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *pInfo;
char *ch = e_bv("user.txt");
pInfo=gtk_message_dialog_new(GTK_WINDOW(user_data),GTK_DIALOG_MODAL,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,ch);
	switch(gtk_dialog_run(GTK_DIALOG(pInfo)))
	{
	case GTK_RESPONSE_OK:
	gtk_widget_destroy(pInfo);
	break;
	}
}


void
on_user_quit_aff_clicked               (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *user;
	GtkWidget *af;
	af=lookup_widget(button,"af");
	gtk_widget_destroy(af);
	user=lookup_widget(button,"fiche_don_user");
	user=create_fiche_don_user();
	gtk_widget_show(user);
}

void
on_user_affichier_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{	
	GtkWidget *user;
	GtkWidget *af;
	user=lookup_widget(button,"fiche_don_user");
	gtk_widget_destroy(user);
	af=lookup_widget(button,"af");
	af=create_af();
	gtk_widget_show(af);
	GtkWidget *treeview;
	treeview=lookup_widget(af,"treeview1");
	afficher_f(treeview,"user.txt", "", "", "");



}


void
on_button8_clicked                     (GtkWidget *objet_graphique, gpointer user_data)
{
GtkWidget*n;
GtkWidget*p;
n=lookup_widget(objet_graphique, "af");
p=lookup_widget(objet_graphique, "Statistique");
p=  create_Statistique();
gtk_widget_show(p);
gtk_widget_destroy(n);
}


void
on_nombreEts_clicked                   (GtkWidget *objet_graphique, gpointer user_data)
{
GtkWidget*label;
int t=0;
char text1[50];
label=lookup_widget(objet_graphique, "label63");
t=nbETS();

        g_snprintf(text1, sizeof(text1), "%d",t);
        gtk_label_set_text(GTK_LABEL(label), text1);
}


void
on_okmoyenne_clicked                   (GtkWidget *objet_graphique, gpointer user_data)
{
GtkWidget*j,*m,*a,*label;
date_f d;
float t=0.0;
char text1[50];
label=lookup_widget(objet_graphique, "moyeene");
j=lookup_widget(objet_graphique, "spinbutton1");
m=lookup_widget(objet_graphique, "spinbutton2");
a=lookup_widget(objet_graphique, "spinbutton3");
d.j=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(j));
d.m=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(m));
d.a=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(a));
t=moy_ETS(d);
g_snprintf(text1, sizeof(text1), "%.2f", t);
gtk_label_set_text(GTK_LABEL(label), text1);
}


void
on_button12_clicked                    (GtkWidget *objet_graphique, gpointer user_data)
{
GtkWidget*ets,*treeview;
int t=0;
const gchar* entry_text;
char* endptr;
treeview=lookup_widget(objet_graphique,"treeview1");
GtkTreeModel *model=gtk_tree_view_get_model(GTK_TREE_VIEW(treeview));
gtk_list_store_clear(GTK_LIST_STORE(model));
ets=lookup_widget(objet_graphique, "etsrecherche");
entry_text= gtk_entry_get_text(GTK_ENTRY(ets));
t=(int)strtol(entry_text, &endptr, 10);
listeRDV(GTK_TREE_VIEW(treeview),t);
}


void
on_button13_clicked                    (GtkWidget *objet_graphique, gpointer user_data)
{
GtkWidget*n;
GtkWidget*p;
n=lookup_widget(objet_graphique, "Statistique");
p=lookup_widget(objet_graphique, "af");
p=  create_af();
gtk_widget_show(p);
gtk_widget_destroy(n);
}


////////////////////////////////////////////////////


void
on_U_button_rechercher_clicked         (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *entryrechercher, *treeview1;
    const char *search_term;

   
    entryrechercher = lookup_widget(button, "U_recherche");
    treeview1 = lookup_widget(button, "treeview_ugestion");

   
    search_term = gtk_entry_get_text(GTK_ENTRY(entryrechercher));

    
    rechercher_utilisateur(search_term, treeview1);
}


void
on_Uajouter_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *ajouteru, *gestionu;
 gestionu=lookup_widget(button,"gestionu");

 gtk_widget_destroy(gestionu);
 ajouteru=create_ajouteru();
 gtk_widget_show(ajouteru);

}


void
on_U_button_modifier_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{

  GtkWidget *unom ,*uprenom ,*ucin , *radiobuttonresponsable ,*radiobuttoninfirmier,*radiobuttonmedecin ,*uadresse , *utelephone ;
GtkWidget*boxregion ,*uhomme ,*ufemme ,*checkbutton08h ,*checkbutton13h ,*checkbutton18h,*calendar1 ;
   GtkTreeSelection *selection;
   GtkWidget *treeview_ugestion;
    GtkTreeModel *model;
    GtkTreeIter iter;
    gchar *nom;
    gchar *prenom;
    gchar *CIN;
    gchar *role; 
    gchar *adresse_email;
    gchar *telephone;
    gchar *region;
    gchar *sexe;
    gchar *dns ;
    gchar *pointage;
	treeview_ugestion = lookup_widget(GTK_WIDGET(button), "treeview_ugestion");
        selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview_ugestion));

        
     if (!gtk_tree_selection_get_selected(selection, &model, &iter))
    {
       
        return;
    }
     gtk_tree_model_get(GTK_LIST_STORE(model), &iter, 0, &nom, 1, &prenom,2, &CIN, 3, &role, 4, &adresse_email, 5, &telephone, 6, &region, 7, &sexe, 8, &dns,9,&pointage, -1);

    GtkWidget *ajouteru = lookup_widget(button, "ajouteru");
    gtk_widget_destroy(ajouteru);
    ajouteru = create_ajouteru();
    gtk_widget_show(ajouteru);




     unom = lookup_widget(ajouteru, "unom");
     uprenom = lookup_widget(ajouteru, "uprenom");
     ucin = lookup_widget(ajouteru, "ucin");
     radiobuttonresponsable = lookup_widget(ajouteru, "radiobuttonresponsable");
     radiobuttoninfirmier = lookup_widget(ajouteru, "radiobuttoninfirmier");
     radiobuttonmedecin = lookup_widget(ajouteru, "radiobuttonmedecin");
     uadresse= lookup_widget(ajouteru, "uadresse");
     utelephone = lookup_widget(ajouteru, "utelephone");
     boxregion= lookup_widget(ajouteru, "boxregion");
     uhomme = lookup_widget(ajouteru, "uhomme");
     ufemme= lookup_widget(ajouteru, "ufemme");
     checkbutton08h = lookup_widget(ajouteru, "checkbutton08h");
     checkbutton13h = lookup_widget(ajouteru, "checkbutton13h");
     checkbutton18h = lookup_widget(ajouteru, "checkbutton18h");
     calendar1 =lookup_widget(ajouteru,"calendar1");

    

    gtk_entry_set_text(GTK_ENTRY(unom), nom);
    gtk_entry_set_text(GTK_ENTRY(uprenom), prenom);
    gtk_entry_set_text(GTK_ENTRY(ucin), CIN);
    
    if (strcmp(role, "responsable") == 0)
       gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radiobuttonresponsable), TRUE);

    else if (strcmp(role, "infirmier") == 0)
       gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radiobuttoninfirmier), TRUE); 
    else if (strcmp(role, "medecin") == 0)
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radiobuttonmedecin), TRUE); 


    gtk_entry_set_text(GTK_ENTRY(uadresse), adresse_email);
    gtk_entry_set_text(GTK_ENTRY(utelephone), telephone);
    gtk_combo_box_set_active(GTK_COMBO_BOX(boxregion), region);

     

     if (strcmp(sexe, "homme") == 0)
       gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(uhomme), TRUE);

       else if (strcmp(sexe, "femme") == 0)
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(ufemme), TRUE); 


   //  if (strcmp(pointage, "checkbutton08h") == 0)
       //{ gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(checkbutton08h), TRUE);}

    //else if (strcmp(pointage, "checkbutton13h") == 0)
       // {gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(checkbutton13h), TRUE); }
   // else if (strcmp(pointage, "checkbutton18h") == 0)
        //{gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(checkbutton18h), TRUE); }

   
    
}


void
on_U_button_supprimer_clicked          (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *treeview_ugestion;
    GtkTreeSelection *selection;
    GtkTreeModel *model;
    GtkTreeIter iter;
    gchar *CIN;
    Utilisateur U;

    
    treeview_ugestion = lookup_widget(button, "treeview_ugestion");
    selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview_ugestion));

    
    if (gtk_tree_selection_get_selected(selection, &model, &iter))
    {
        
        gtk_tree_model_get(model, &iter, 0, &CIN, -1);
        strcpy(U.CIN,CIN);

        
        GtkListStore *liststore = GTK_LIST_STORE(model);
        gtk_list_store_remove(liststore, &iter);

        
        supprimer_u(U);
    }
}


void
on_actualiser_clicked                  (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *fenetre_gestionu;
GtkWidget *treeview;

fenetre_gestionu = lookup_widget(button, "gestionu");

treeview = lookup_widget(fenetre_gestionu, "treeview_ugestion");

afficher_utilisateur(treeview);
}


void
on_U_button_afficher_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *comboboxrole, *treeview_ugestion;
    const gchar *search_role;

   
    comboboxrole = lookup_widget(button, "comboboxrole");
    treeview_ugestion = lookup_widget(button, "treeview_ugestion");

   
    search_role = gtk_combo_box_get_active_text(GTK_COMBO_BOX(comboboxrole));

    
    if (search_role != NULL)
    {
        
        rechercher_par_role(search_role, treeview_ugestion);

      
        g_free(search_role);
    }
    else
    {
        g_print("Please select a role to search.\n");
    }

}

void
on_treeview_ugestion_row_activated     (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
GtkTreeIter iter;
   
    gchar *nom;
    gchar *prenom;
    gchar *CIN;
    gchar *role; 
    gchar *adresse_email;
    gchar *telephone;
    gchar *region;
    gchar *sexe;
    gchar *dns ;
    gchar *pointage;

    Utilisateur U;
    GtkTreeModel *model = gtk_tree_view_get_model(treeview);

    if (gtk_tree_model_get_iter(model, &iter, path)) {
        gtk_tree_model_get(GTK_LIST_STORE(model), &iter, 0, &nom, 1, &prenom,2, &CIN, 3, &role, 4, &adresse_email, 5, &telephone, 6, &region, 7, &sexe, 8, &dns,9,&pointage, -1);
        
        {strcpy(U.nom, nom);
        strcpy(U.prenom, prenom);
        strcpy(U.CIN, CIN);
        strcpy(U.role, role);
        strcpy(U.adresse_email, adresse_email);
        strcpy(U.telephone, telephone);
        strcpy(U.region, region); 
        strcpy(U.sexe, sexe);
        strcpy(U.dns, dns);
        strcpy(U.pointage, pointage);

        GtkWidget *treeview_ugestion = lookup_widget(treeview, "treeview_ugestion");
        afficher_utilisateur(treeview_ugestion);
}
}
}


void
on_Uconfirmer_clicked                  (GtkButton       *button,
                                        gpointer         user_data)
{
Utilisateur U;

    gint day, month , year;
    GtkWidget *ajouteru = lookup_widget(button, "ajouteru");
   
    GtkWidget *nom = lookup_widget(button, "unom");
    GtkWidget *prenom = lookup_widget(button, "uprenom");
    GtkWidget *CIN = lookup_widget(button, "ucin");
    GtkWidget *responsable = lookup_widget(button, "radiobuttonresponsable");
    GtkWidget *infirmier = lookup_widget(button, "radiobuttoninfirmier");
    GtkWidget *medecin = lookup_widget(button, "radiobuttonmedecin");
    GtkWidget *adresse = lookup_widget(button, "uadresse");
    GtkWidget *telephone = lookup_widget(button, "utelephone");
    GtkWidget *region = lookup_widget(button, "boxregion");
    GtkWidget *homme = lookup_widget(button, "uhomme");
    GtkWidget *femme = lookup_widget(button, "ufemme");
    GtkWidget *checkbutton08h = lookup_widget(button, "checkbutton08h");
    GtkWidget *checkbutton13h = lookup_widget(button, "checkbutton13h");
    GtkWidget *checkbutton18h = lookup_widget(button, "checkbutton18h");
    GtkWidget *cal =lookup_widget(button,"calendar1");
    GtkWidget *aff1 = lookup_widget(button, "label6");
    GtkWidget *aff2 = lookup_widget(button, "label7");
    GtkWidget *msg = lookup_widget(button, "u_ajout_msg");
    
    strcpy(U.nom, gtk_entry_get_text(GTK_ENTRY(nom)));
    strcpy(U.prenom, gtk_entry_get_text(GTK_ENTRY(prenom)));
    strcpy(U.CIN, gtk_entry_get_text(GTK_ENTRY(CIN)));

    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(responsable)))
      {  strcpy(U.role, "responsable");}
        
     else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(infirmier)))
        { strcpy(U.role, "infirmier");}
     else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(medecin)))
         {  strcpy(U.role, "medecin");}

    strcpy(U.adresse_email, gtk_entry_get_text(GTK_ENTRY(adresse)));
    strcpy(U.telephone, gtk_entry_get_text(GTK_ENTRY(telephone)));
    strcpy(U.region, gtk_combo_box_get_active_text(GTK_COMBO_BOX(region)));

    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(homme)))
       { strcpy(U.sexe, "homme");}
     else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(femme)))
       { strcpy(U.sexe, "femme");}
     gtk_calendar_get_date (GTK_CALENDAR(cal),&year,&month,&day);
    sprintf(U.dns,"%d/%d/%d",day,month+1,year);

    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(checkbutton08h)))
       { strcpy(U.pointage, "08h/12h");}
    else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(checkbutton13h)))
       { strcpy(U.pointage, "13h/17h");}
    else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(checkbutton18h)))
        {strcpy(U.pointage, "18h/21h");}


   if(strlen(U.CIN) != 8)
   {gtk_label_set_text(GTK_LABEL(aff1),"cin invalide\n");}
   if(strlen(U.telephone) != 8)
   {gtk_label_set_text(GTK_LABEL(aff2),"numero invalide\n");}


   ajouter_utilisateur(U);

}


void
on_radiobuttonresponsable_toggled      (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

}


void
on_radiobuttoninfirmier_toggled        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

}


void
on_radiobuttonmedecin_toggled          (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

}


void
on_uhomme_toggled                      (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

}


void
on_ufemme_toggled                      (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

}


void
on_checkbutton13h_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

}


void
on_checkbutton18h_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

}


void
on_checkbutton08h_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

}


void
on_Uretourajout_clicked                (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *ajouteru, *gestionu;
	ajouteru=lookup_widget(button,"ajouteru");

	gtk_widget_destroy(ajouteru);
	gestionu=create_gestionu();
	gtk_widget_show(gestionu);
}


void
on_femme_clicked                       (GtkButton       *button,
                                        gpointer         user_data)
{
Utilisateur U3;

GtkWidget *affichage,*label_resultat  ; 

  affichage = lookup_widget(button, "affichage");
  label_resultat = lookup_widget(button, "label_resultat");

    int totalUsers;
    float femalePercentage;
    
   calculate_female_percentage(&totalUsers, &femalePercentage) ;
      char femalePer[20];
      sprintf(femalePer, "%.2f %%", femalePercentage);
    
    gtk_label_set_text(GTK_LABEL(label_resultat), femalePer);
}


void
on_homme_clicked                       (GtkButton       *button,
                                        gpointer         user_data)
{
Utilisateur U4;

 	GtkWidget *affichage,*label_resultat ; 

   	affichage = lookup_widget(button, "affichage");
  	label_resultat = lookup_widget(button, "label_resultat");

    	int totalUsers;
    	float malePercentage;
    
    	calculate_male_percentage(&totalUsers, &malePercentage);
      	char malePer[20];
      	sprintf(malePer, "%.2f %%", malePercentage);
    
    	gtk_label_set_text(GTK_LABEL(label_resultat), malePer);
}


void
on_U_stat_clicked                      (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *affichage;

affichage = create_affichage ();
gtk_widget_show(affichage);

}

///////////////////////////////////////////

void
on_gdps_deconnecter_clicked            (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *authentification;
GtkWidget *gestion;

authentification = create_authentification ();
gestion = lookup_widget(objet, "gestion");

gtk_widget_destroy(gestion);
gtk_widget_show(authentification);

}


void
on_fiche_don_deconnecter_clicked       (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *authentification;
GtkWidget *gestion;

authentification = create_authentification ();
gestion = lookup_widget(objet, "fiche_don_user");

gtk_widget_destroy(gestion);
gtk_widget_show(authentification);
}


void
on_u_deconnecter_clicked               (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *authentification;
GtkWidget *gestion;

authentification = create_authentification ();
gestion = lookup_widget(objet, "gestionu");

gtk_widget_destroy(gestion);
gtk_widget_show(authentification);
}

