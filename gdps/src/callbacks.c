#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "fonctions.h"
#include "etablissement.h"

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

//strcpy (id_etabch, gtk_entry_get_text(GTK_ENTRY(idetabentry)));
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
//sprintf(test, "%d", x);
//gtk_label_set_text(GTK_LABEL(msg), test);

}

