#include <stdio.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "fiche.h"
#include "callbacks.h"
#include <gtk/gtk.h>

void listeRDV(GtkTreeView *liste,int ets)
{
GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    GtkTreeIter iter ;
    GtkListStore *store;
    ut p;
gchar np[50], sexe[10], date[20];
    store=NULL;
    FILE *f;
    
    store=GTK_LIST_STORE(gtk_tree_view_get_model(liste));
    if(store==NULL){
        
        renderer=gtk_cell_renderer_text_new();
        column=gtk_tree_view_column_new_with_attributes("Cin",renderer,"text",0,NULL);
        gtk_tree_view_append_column(liste,column);

        renderer=gtk_cell_renderer_text_new();
        column=gtk_tree_view_column_new_with_attributes("nom et prenom",renderer,"text",1,NULL);
        gtk_tree_view_append_column(liste,column);

        renderer=gtk_cell_renderer_text_new();
        column=gtk_tree_view_column_new_with_attributes("email",renderer,"text",2,NULL);
        gtk_tree_view_append_column(liste,column); 

        renderer=gtk_cell_renderer_text_new();
        column=gtk_tree_view_column_new_with_attributes("ets",renderer,"text",3,NULL);
        gtk_tree_view_append_column(liste,column);

	renderer=gtk_cell_renderer_text_new();
        column=gtk_tree_view_column_new_with_attributes("sexe",renderer,"text",4,NULL);
        gtk_tree_view_append_column(liste,column);

	renderer=gtk_cell_renderer_text_new();
        column=gtk_tree_view_column_new_with_attributes("poid",renderer,"text",5,NULL);
        gtk_tree_view_append_column(liste,column);
	
	renderer=gtk_cell_renderer_text_new();
        column=gtk_tree_view_column_new_with_attributes("sang",renderer,"text",6,NULL);
        gtk_tree_view_append_column(liste,column);
	
	renderer=gtk_cell_renderer_text_new();
        column=gtk_tree_view_column_new_with_attributes("date",renderer,"text",7,NULL);
        gtk_tree_view_append_column(liste,column);

         
    }
          
    store=gtk_list_store_new(8,G_TYPE_INT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INT, G_TYPE_STRING, G_TYPE_INT, G_TYPE_INT, G_TYPE_STRING);
    f=fopen("user.txt","r");
    if(f==NULL){return;}
    else
    {
                 f=fopen("user.txt","a+");
         while(fscanf(f,"%d %s %s %s %s %d %s %d %d %d %d %d\n",&(p.cin),p.nom,p.prenom,p.email,p.gs,&(p.sexe),(p.mala),&(p.poid),&(p.ets),&(p.d.j),&(p.d.m),&(p.d.a))!=EOF )
         {
	    if(p.ets==ets){
		sprintf(np, "%s %s", p.nom, p.prenom);
		sprintf(date,"%d/%d/%d",p.d.j,p.d.m,p.d.a);
		sprintf(sexe,p.sexe==0?"Homme":"Femme");
                gtk_list_store_append(store,&iter);
                gtk_list_store_set(store,&iter,0,p.cin,1,np,2,p.email,3,p.ets,4,sexe,5,p.poid,6,p.mala,7,date,-1);
             }
	}
     fclose(f);
     gtk_tree_view_set_model(liste,GTK_TREE_MODEL(store));
     g_object_unref(store);
    }}

void ajouter_f(ut u, char *fname){
GtkWidget *pQuestion;
FILE *f;
int b=0;
gpointer user_data;
ut p;
f=fopen(fname,"a+");
if(f!=NULL)
{	
	while(fscanf(f,"%d %s %s %s %s %d %s %d %d %d %d %d\n",&(p.cin),p.nom,p.prenom,p.email,p.gs,&(p.sexe),(p.mala),&(p.poid),&(p.ets),&(p.d.j),&(p.d.m),&(p.d.a))!=EOF)
	{	
		if(u.cin==p.cin)
		b=1;
	}
	if(b==0){
	fprintf(f,"%d %s %s %s %s %d %s %d %d %d %d %d\n",u.cin,u.nom,u.prenom,u.email,u.gs,u.sexe,u.mala,u.poid,u.ets,u.d.j,u.d.m,u.d.a);
	}
	pQuestion=gtk_message_dialog_new(GTK_WINDOW(user_data),GTK_DIALOG_MODAL,b==0?GTK_MESSAGE_INFO:GTK_MESSAGE_WARNING,GTK_BUTTONS_OK,b==0?"DonneurInfo ajouté avec succès !":"infoDonneur déja existant !");
	switch(gtk_dialog_run(GTK_DIALOG(pQuestion)))
	{
	case GTK_RESPONSE_OK:
	gtk_widget_destroy(pQuestion);
	break;
	}
	fclose(f);
}
}

void modifier_f(ut u, char *fname){
ut p;
GtkWidget *pInfo;
gpointer user_data;
FILE *f, *g;
f=fopen(fname,"r");
g=fopen("dump.txt","w");
if(f==NULL||g==NULL)
{
	return;
}
else{
	while(fscanf(f,"%d %s %s %s %s %d %s %d %d %d %d %d\n",&(p.cin),p.nom,p.prenom,p.email,p.gs,&(p.sexe),(p.mala),&(p.poid),&(p.ets),&(p.d.j),&(p.d.m),&(p.d.a))!=EOF)
	{
		if(p.cin!=u.cin)
			fprintf(g,"%d %s %s %s %s %d %s %d %d %d %d %d\n",p.cin,p.nom,p.prenom,p.email,p.gs,p.sexe,p.mala,p.poid,p.ets,p.d.j,p.d.m,p.d.a);
		else
			fprintf(g,"%d %s %s %s %s %d %s %d %d %d %d %d\n",u.cin,u.nom,u.prenom,u.email,u.gs,u.sexe,u.mala,u.poid,u.ets,u.d.j,u.d.m,u.d.a);
	}
	pInfo=gtk_message_dialog_new(GTK_WINDOW(user_data),GTK_DIALOG_MODAL,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,"infoDonneur modifié avec succès !");
	switch(gtk_dialog_run(GTK_DIALOG(pInfo)))
	{
	case GTK_RESPONSE_OK:
	gtk_widget_destroy(pInfo);
	break;
	}
	fclose(f);
	fclose(g);
remove(fname);
rename("dump.txt",fname);
}
}

void afficher_f(GtkWidget *liste, char *fname, char *id, char *email, char *nom)
{
ut p;
GtkCellRenderer *renderer; 
GtkTreeViewColumn *column; 
GtkTreeIter iter;
GtkListStore *store;
gchar np[50], sexe[10], date[20];
FILE *f;
store=gtk_tree_view_get_model(liste);
renderer=gtk_cell_renderer_text_new();
column=gtk_tree_view_column_new_with_attributes(" CIN", renderer,"text",0, NULL);
if (store==NULL)
gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
gtk_tree_view_column_set_expand(column,TRUE);

renderer=gtk_cell_renderer_text_new();
column=gtk_tree_view_column_new_with_attributes(" Nom et prénom", renderer,"text",1, NULL);
if (store==NULL)
gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
gtk_tree_view_column_set_expand(column,TRUE);

renderer=gtk_cell_renderer_text_new();
column=gtk_tree_view_column_new_with_attributes(" Email", renderer,"text",2, NULL);
if (store==NULL)
gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
gtk_tree_view_column_set_resizable(column,TRUE);
gtk_tree_view_column_set_expand(column,TRUE);

renderer=gtk_cell_renderer_text_new();
column=gtk_tree_view_column_new_with_attributes(" ID-ETS", renderer,"text",3, NULL);
if (store==NULL)
gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
gtk_tree_view_column_set_expand(column,TRUE);

renderer=gtk_cell_renderer_text_new();
column=gtk_tree_view_column_new_with_attributes(" Sexe", renderer,"text",4, NULL);
if (store==NULL)
gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
gtk_tree_view_column_set_expand(column,TRUE);

renderer=gtk_cell_renderer_text_new();
column=gtk_tree_view_column_new_with_attributes(" Poid", renderer,"text",5, NULL);
if (store==NULL)
gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
gtk_tree_view_column_set_expand(column,TRUE);

renderer=gtk_cell_renderer_text_new();
column=gtk_tree_view_column_new_with_attributes(" Groupe Sanguin", renderer,"text",6, NULL);
if (store==NULL)
gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
gtk_tree_view_column_set_expand(column,TRUE);

renderer=gtk_cell_renderer_text_new();
column=gtk_tree_view_column_new_with_attributes(" Date", renderer,"text",7, NULL);
if (store==NULL)
gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
gtk_tree_view_column_set_expand(column,TRUE);

store=gtk_list_store_new(8, G_TYPE_UINT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INT, G_TYPE_STRING, G_TYPE_INT, G_TYPE_INT, G_TYPE_STRING);
if (strcmp(id,"")==0&&strcmp(email,"")==0&&strcmp(nom,"")==0){
f=fopen(fname,"r");
if(f!=NULL)
{ f = fopen(fname,"a+");
		while(fscanf(f,"%d %s %s %s %s %d %s %d %d %d %d %d\n",&(p.cin),p.nom,p.prenom,p.email,p.gs,&(p.sexe),(p.mala),&(p.poid),&(p.ets),&(p.d.j),&(p.d.m),&(p.d.a))!=EOF)
	{
sprintf(np, "%s %s", p.nom, p.prenom);
sprintf(date,"%d/%d/%d",p.d.j,p.d.m,p.d.a);
sprintf(sexe,p.sexe==0?"Homme":"Femme");
gtk_list_store_append(store,&iter);
gtk_list_store_set(store,&iter,0,p.cin,1,np,2,p.email,3,p.ets,4,sexe,5,p.poid,6,p.mala,7,date,-1);
	}
	fclose(f);
gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
g_object_unref(store);
}
}
else{
f=fopen(fname,"r");
if(f!=NULL)
{ f = fopen(fname,"a+");
		while(fscanf(f,"%d %s %s %s %s %d %s %d %d %d %d %d\n",&(p.cin),p.nom,p.prenom,p.email,p.gs,&(p.sexe),(p.mala),&(p.poid),&(p.ets),&(p.d.j),&(p.d.m),&(p.d.a))!=EOF)
	{
if(p.cin==atoi(id)||strcmp(p.email,email)==0||strcmp(p.nom,nom)==0){
sprintf(np, "%s %s", p.nom, p.prenom);
sprintf(date,"%d/%d/%d",p.d.j,p.d.m,p.d.a);
sprintf(sexe,p.sexe==0?"Homme":"Femme");
gtk_list_store_append(store,&iter);
gtk_list_store_set(store,&iter,0,p.cin,1,np,2,p.email,3,p.ets,4,sexe,5,p.poid,6,p.mala,7,date,-1);
}
	}
	fclose(f);
gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
g_object_unref(store);
}
}
gtk_tree_view_set_reorderable(GTK_TREE_VIEW(liste),TRUE);
gtk_tree_view_set_rules_hint(GTK_TREE_VIEW(liste),TRUE);
gtk_tree_view_set_enable_search(GTK_TREE_VIEW(liste),TRUE);
gtk_tree_view_set_search_column(GTK_TREE_VIEW(liste),0);
gtk_tree_view_set_enable_tree_lines(GTK_TREE_VIEW(liste),TRUE);
gtk_tree_view_set_grid_lines(GTK_TREE_VIEW(liste),GTK_TREE_VIEW_GRID_LINES_BOTH);
}

void supprimer_f(ut u, char *fname)
{
ut p;
GtkWidget *pInfo;
gpointer user_data;
FILE *f, *g;
f=fopen(fname,"r");
g=fopen("dump.txt","w");
if(f!=NULL&&g!=NULL){
	while(fscanf(f,"%d %s %s %s %s %d %s %d %d %d %d %d\n",&(p.cin),p.nom,p.prenom,p.email,p.gs,&(p.sexe),(p.mala),&(p.poid),&(p.ets),&(p.d.j),&(p.d.m),&(p.d.a))!=EOF)
	{
		if(p.cin!=u.cin)
			fprintf(g,"%d %s %s %s %s %d %s %d %d %d %d %d\n",p.cin,p.nom,p.prenom,p.email,p.gs,p.sexe,p.mala,p.poid,p.ets,p.d.j,p.d.m,p.d.a);
	}
	pInfo=gtk_message_dialog_new(GTK_WINDOW(user_data),GTK_DIALOG_MODAL,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,"infoDonneur supprimé avec succès");
	switch(gtk_dialog_run(GTK_DIALOG(pInfo)))
	{
	case GTK_RESPONSE_OK:
	gtk_widget_destroy(pInfo);
	break;
	}
	fclose(f);
	fclose(g);
remove(fname);
rename("dump.txt",fname);
}
}

ut chercher_f(int id, char *fname){
FILE *f;
ut p, e={cin:-1};
f=fopen(fname,"r");
if(f!=NULL)
{
	while(fscanf(f,"%d %s %s %s %s %d %s %d %d %d %d %d\n",&(p.cin),p.nom,p.prenom,p.email,p.gs,&(p.sexe),(p.mala),&(p.poid),&(p.ets),&(p.d.j),&(p.d.m),&(p.d.a))!=EOF)
	{
	if(p.cin==id)
            return p;
	}
	fclose(f);
}
    return e;

}

char* e_bv(char *fname){
FILE *f;
f=fopen(fname,"r");
ut p;
int x[100][2] = {};
int b, c=0, n = 0;
char* ch = malloc(500);
char tmp[50];
strcpy(ch, "");
while(fscanf(f,"%d %s %s %s %s %d %s %d %d %d %d %d\n",&(p.cin),p.nom,p.prenom,p.email,p.gs,&(p.sexe),(p.mala),&(p.poid),&(p.ets),&(p.d.j),&(p.d.m),&(p.d.a))!=EOF)
	{
		b=0;
		for (int i=0;i<100;i++){
			if (x[i][0] == p.ets){
				x[i][1] = x[i][1] + 1;
				b=1;
				break;
			}
		}
        if(b == 0){
			x[n][0] = p.ets;
			x[n][1] = 1;
			n++;
		}
		c++;
	}
	for (int i=0; i<n; i++){
        for (int j=i+1; j<n; j++){
            if (x[i][1] < x[j][1]){
                int s1 = x[j][0];
                int s2 = x[j][1];
                x[j][0] = x[i][0];
                x[j][1] = x[i][1];
                x[i][0] = s1;
                x[i][1] = s2;
            }
	}
	}


	for (int j=0;j<n;j++){
	    sprintf(tmp, "ID-ETS %d : %d Donneurs\n", x[j][0], x[j][1]);
	    strcat(ch, tmp);
}
return ch;
} 

int Check_Email_Addr(char *EM_Addr) {
int count = 0;
int i = 0;
char conv_buf[50];
char *c, *domain;
char *special_chars = "()<>@,;:\"[]";
strcpy(conv_buf,EM_Addr);

for(c = conv_buf; *c; c++) {
   if (*c == 34 && (c == conv_buf || *(c - 1) == 46 || *(c - 1) == 34)) {
      while (*++c) {
         
         if (*c == 34)
            break;
         
         if (*c == 92 && (*++c == 32))
            continue;
         
         if (*c <= 32 || *c > 127)
            return 0;
         }
      
      if (!*c++)
         return 0;
      
      if (*c == 64)
         break;
      
      if (*c != 46)
         return 0;
      continue;
      }
   if (*c == 64) {
      break;
      }
   
   if (*c <= 32 || *c > 127) {
      return 0;
      }
   
   if (strchr(special_chars, *c)) {
      return 0;
      }
   } 
if (c == conv_buf || *(c - 1) == 46)
   return 0;

if (!*(domain = ++c))
   return 0;
do {
  
   if (*c == 46) {
      
      if (c == domain || *(c - 1) == 46)
         return 0;
      
      count++;
      }
   
   if (*c <= 32 || *c >= 127)
      return 0;
   if (strchr(special_chars, *c))
      return 0;
   } while (*++c); 
return (count >= 1); 
}

bool valid_cin(char *cin){
if(strspn(cin, "0123456789") == strlen(cin))
return true;
return false;
}
int nbETS() {
    FILE* f = fopen("user.txt", "r");
    ut p;
    int t = 0;
    int unique_ets[100] = {0};  

    if (f == NULL) {
        return 0;
    } else {
        while (fscanf(f, "%d %s %s %s %s %d %s %d %d %d %d %d\n",
                      &(p.cin), p.nom, p.prenom, p.email, p.gs, &(p.sexe),
                      (p.mala), &(p.poid), &(p.ets), &(p.d.j), &(p.d.m), &(p.d.a)) != EOF) {
           
            int isUnique = 1;
            for (int i = 0; i < t; i++) {
                if (unique_ets[i] == p.ets) {
                    isUnique = 0;
                    break;
                }
            }

          
            if (isUnique) {
                unique_ets[t++] = p.ets;
            }
        }

        fclose(f);
        return t;  
    }
}
float moy_ETS(date_f d){
FILE* f = fopen("user.txt", "r");
    ut p;
    int t=0,t2=0;
 if (f == NULL) {
        return 0;
    } else {
	t=nbETS();
        while (fscanf(f, "%d %s %s %s %s %d %s %d %d %d %d %d\n",
                      &(p.cin), p.nom, p.prenom, p.email, p.gs, &(p.sexe),
                      (p.mala), &(p.poid), &(p.ets), &(p.d.j), &(p.d.m), &(p.d.a)) != EOF) {
		if((d.a==p.d.a)&&(d.j==p.d.j)&&(d.m==p.d.m)){
		t2++;
}
}
if(t==0) return 0.0;
else return ((float)t2 / t);

 }          
}
