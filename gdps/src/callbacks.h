#include <gtk/gtk.h>


void
on_GDPS_actualiser_button_clicked      (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_gdps_ajouter_clicked                (GtkWidget       *button,
                                        gpointer         user_data);

void
on_gdps_oui_radio_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_gdps_non_radio_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_gdps_ajouter_button_clicked         (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_gdps_cm_choix8_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_gdps_cm_choix7_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_gdps_cm_choix6_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_gdps_cm_choix5_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_gdps_cm_choix4_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_gdps_cm_choix3_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_gdps_cm_choix2_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_gdps_cm_choix1_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_treeview_row_activated              (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_gdps_modifier_clicked               (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_gdps_modifer_button_clicked         (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_gdps_modif_oui_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_gdps_modif_non_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_gdps_modif_choix1_toggled           (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_gdps_modif_choix2_toggled           (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_gdps_modif_choix3_toggled           (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_gdps_modif_choix4_toggled           (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_gdps_modif_choix5_toggled           (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_gdps_modif_choix6_toggled           (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_gdps_modif_choix7_toggled           (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_gdps_modif_choix8_toggled           (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_gdps_supprimer_button_clicked       (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_gdps_statistique_button_clicked     (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_gdps_chercher_button_clicked        (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_auth_connecter_button_clicked       (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_button_aj_clicked                   (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_user_quit_aj_clicked                (GtkWidget       *button,
                                        gpointer         user_data);



void
on_user_ajout_clicked                  (GtkButton       *button,
                                        gpointer         user_data);
///////

void
on_user_quit_mod_clicked               (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_mod_clicked                  (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_check_id_clicked                    (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_user_modifer_clicked                (GtkButton       *button,
                                        gpointer         user_data);

void
on_treeview1_row_activated              (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_button7_clicked                     (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_button_af_clicked                   (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_button9_clicked                     (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_user_quit_aff_clicked               (GtkButton       *button,
                                        gpointer         user_data);

void
on_user_affichier_clicked              (GtkButton       *button,
                                        gpointer         user_data);


void
on_button8_clicked                     (GtkWidget *objet_graphique, gpointer user_data);

void
on_nombreEts_clicked                   (GtkWidget *objet_graphique, gpointer user_data);

void
on_okmoyenne_clicked                   (GtkWidget *objet_graphique, gpointer user_data);

void
on_button12_clicked                    (GtkWidget *objet_graphique, gpointer user_data);

void
on_button13_clicked                    (GtkWidget *objet_graphique, gpointer user_data);



void
on_U_button_rechercher_clicked         (GtkButton       *button,
                                        gpointer         user_data);

void
on_Uajouter_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_U_button_modifier_clicked           (GtkButton       *button,
                                        gpointer         user_data);

void
on_U_button_supprimer_clicked          (GtkButton       *button,
                                        gpointer         user_data);

void
on_actualiser_clicked                  (GtkButton       *button,
                                        gpointer         user_data);

void
on_U_button_afficher_clicked           (GtkButton       *button,
                                        gpointer         user_data);

void
on_treeview_ugestion_row_activated     (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_Uconfirmer_clicked                  (GtkButton       *button,
                                        gpointer         user_data);

void
on_radiobuttonresponsable_toggled      (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_radiobuttoninfirmier_toggled        (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_radiobuttonmedecin_toggled          (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_uhomme_toggled                      (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_ufemme_toggled                      (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_checkbutton13h_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_checkbutton18h_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_checkbutton08h_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_Uretourajout_clicked                (GtkButton       *button,
                                        gpointer         user_data);

void
on_femme_clicked                       (GtkButton       *button,
                                        gpointer         user_data);

void
on_homme_clicked                       (GtkButton       *button,
                                        gpointer         user_data);


void
on_U_stat_clicked                      (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_gdps_deconnecter_clicked            (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_fiche_don_deconnecter_clicked       (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_u_deconnecter_clicked               (GtkWidget       *objet,
                                        gpointer         user_data);
