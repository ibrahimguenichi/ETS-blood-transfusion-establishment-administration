#include "utilisateur.h"
#include <string.h>
#include <gtk/gtk.h>
#include <stdio.h>

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
while (fscanf(f, "%s %s %s %s %s %s %s %s %s %s", temp.nom, temp.prenom, temp.CIN, temp.role, temp.adresse_email, temp.telephone, temp.region, temp.sexe, temp.dns, temp.pointage) != EOF)
{
    if (strcmp(email, temp.adresse_email) == 1)
	tr = 1;
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
