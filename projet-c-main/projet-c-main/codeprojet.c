/****************************************************\
* C'est notre code pour nos projet C                 *
* team:                                              *
*          hale dhaouadi                             *
*          achref jarboui                            *
*          mohammed gharab/                          *
*                                                    *
\****************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include <windows.h>
enum state{main_menu,login_system};
enum state currentwindow=main_menu;
typedef struct date
{
  int month;
  int day;
  int year;
}date;
typedef struct Travel
{   int ID_destination;
    char destination[100];
    date date_start;
    date date_end;
    float price;
    int place_number;
    struct Travel *next;
}Travel;
typedef struct managerprofile
{   char manager_name[100];
    char manager_password[100];
    struct managerprofile *next;
}managerprofile ;
managerprofile* InitializeListing(managerprofile*);
managerprofile* Adding_manager(managerprofile*);
void Color(int couleurDuTexte,int couleurDeFond);
void login(managerprofile* );
void WriteToFile_manager( managerprofile*);
void logout();
Travel* Initialize_Travel(Travel*);
Travel* add_Travel(Travel*);
void WriteToFile_travel( Travel*);
void changing_pass(managerprofile*);
void Travel_description(Travel*);
void delete_Travel(Travel*);
void modify_Travel(Travel*);
void research_Travel(Travel*);
void exit_system();
char current_manager[100];
int main()
{  Color(11,0);
    printf("\n\n\t\t\t\t**** || Inscription du proprietaire de l'agence || ****\n\n\n\n");
     Color(15,0);
    printf("\t\t\t\t __Ici le manager peut entrer ces coordonnes__ \n \t\t\t__ afin d'avoir l'acces au differentes operations qu'il peut gerer __\n\n");
    managerprofile *hello=NULL;
    Travel *hi=NULL;
    int choice1,choice2;
    hello=InitializeListing(hello);
    hi=Initialize_Travel(hi);
    while (1)
    {

        if(currentwindow==main_menu)
        {

            printf("\n\t\t\t\t\t\t1- S'inscrire\n\t\t\t\t\t\t2- S'identifier \n\t\t\t\t\t\t3- Sortir \n\n\n\t\t\t\t\t");
            Color(14,0);
            printf("Entrer le nombre de voter choix:") ;
            Color(15,0);
            scanf("%d",&choice1);
            switch(choice1)
            {
                case 1:
                    hello=Adding_manager(hello);
                    break;
                case 2:
                    login(hello);
                    break;
                case 3:
                    exit_system();
                    exit(0);
                    break;
                default:
                    printf("\t\tAucune entree valide a ce stade \n");
            }
        }
        else if(currentwindow==login_system)
        {
        system("CLS");
        Color(3,0);
        printf("\n\t\t\t\t\t=========================");
		printf("\n\t\t\t\t\t Systeme d'exploitation");
		printf("\n\t\t\t\t\t=========================");
		Color(7,0);
		printf("\n\n\n\t\t __Le manager peut a travers ces operations de gerer les dates de voyages ,__ \n \t__ modifier les voyages , ajouter un autre tout en affichant son discription ou le supprimer __\n\n");
		Color(7,0);
            printf("\n\t\t\t\t1-Ajouter un voyage \n\t\t\t\t2-La description d'un voyage \n\t\t\t\t3-Supprimer un voyage  \n\t\t\t\t4-Modifier un voyage \n\t\t\t\t5-Recherche les voyages disponibles"
                   "\n\t\t\t\t6-Changer le mot de passe   \n\t\t\t\t7-Se deconnecter \n\t\t\t\t8-Sortir\n\n\t\t\t\t");
            scanf("%d",&choice2);
            switch(choice2)
            {
                case 1:
                    add_Travel(hi);
                    system("PAUSE");
                    system("CLS");
                    break;
                case 2:
                    Travel_description(hi);
                    system("PAUSE");
                    system("CLS");

                    break;
                case 3:
                    delete_Travel(hi);
                    system("PAUSE");
                    system("CLS");
                    break;
                case 4:
                    modify_Travel(hi);
                    system("PAUSE");
                    system("CLS");
                    break;
                case 5:
                    research_Travel(hi);
                    system("PAUSE");
                    system("CLS");
                    break;
                case 6:
                    changing_pass(hello);
                    system("PAUSE");
                    system("CLS");
                    break;
                case 7:
                    logout();
                    system("PAUSE");
                    system("CLS");
                    break;

                case 8:
                    exit_system();
                    exit(0);
                    break;
                default:
                    printf("\t\tAucune entree valide a ce stade\n");
            }
        }
    }
    return 0;
}
managerprofile* InitializeListing(managerprofile *hello)
{
    managerprofile* text,*p,temporary;
    FILE *fileope;
    int counting_cooridantes=0,z;
    float following;
    fileope=fopen("managers.txt","r");

    if(fileope==NULL)
        return NULL;

    if(fgetc(fileope)==EOF)
        return NULL;

    rewind(fileope);
	while(fscanf(fileope,"%s %s ",temporary.manager_name,temporary.manager_password)!=EOF)
	{
		p=(managerprofile*)malloc(sizeof(managerprofile));
		strcpy(p->manager_name,temporary.manager_name);
		strcpy(p->manager_password,temporary.manager_password);
		p->next=NULL;

		if(hello==NULL)
            hello=text=p;
		else
		{
			hello->next=p;
			hello=p;
		}
	}
	fclose(fileope);
    return text;
}
void login(managerprofile* hello)
{
    char m_name[100];
    char m_password[100];
    fflush(stdin);
    printf("\n\n");
    printf("\t\tEntrer votre Email/Pseudo:\n\t\t");
    scanf("%s", m_name);
    fflush(stdin);
    printf("\n\t\tEntrer votre mot de passe:\n\t\t");
    scanf(" %[^\n]s",m_password);
    while(hello!=NULL)
    {
        if((!strcmp(hello->manager_name,m_name)) && (!strcmp(hello->manager_password,m_password)))
        {
            currentwindow=login_system;
            strcpy(current_manager,m_name);

            printf("\n\n\t\tVous etes connecte avec succes  ");
            system("PAUSE");
            return;
        }
        else if((!strcmp(hello->manager_name,m_name)) && (strcmp(hello->manager_password  ,current_manager)))
        {
            printf("\t\tMot de passe errone\n");
            return;
        }
        hello=hello->next;
    }
    printf("\t\tDesole, aucun profil n'est trouve\n");
}
Travel* Initialize_Travel(Travel *hello)
{
    Travel* text,*p,temporary;
    FILE *fileopen;
    fileopen=fopen("trips.txt","r");
    if(fileopen==NULL)
        return NULL;
    if(fgetc(fileopen)==EOF)
        return NULL;
    rewind(fileopen);
	while(fscanf(fileopen,"%s  %d %d %d %d %d %d %f %d %d",temporary.destination,&temporary.date_start.day,&temporary.date_start.month,&temporary.date_start.year,&temporary.date_end.day,&temporary.date_end.month,&temporary.date_end.year,&temporary.price,&temporary.place_number,&temporary.ID_destination)!=EOF)
	{
		p=(Travel*)malloc(sizeof(Travel));
		strcpy(p->destination,temporary.destination);
		p->date_start=temporary.date_start;
		p->date_end=temporary.date_end;
		p->price=temporary.price;
		p->place_number=temporary.place_number;
		p->ID_destination=temporary.ID_destination;
		p->next=NULL;
		if(hello==NULL)
            hello=text=p;
		else
		{
			hello->next=p;
			hello=p;
		}
	}
	fclose(fileopen);
    return text;}
void WriteToFile_manager(managerprofile *hello)
{
    FILE *fileopen;
    fileopen=fopen("managers.txt","w");
    while(hello!=NULL)
    {
        fprintf(fileopen,"%s %s \n",hello->manager_name,hello->manager_password);
        hello=hello->next;
    }
    fclose(fileopen);
}
void WriteToFile_travel(Travel *hi)
{
    FILE *fileopen;
    fileopen=fopen("trips.txt","w");
    while(hi!=NULL)
    {
        fprintf(fileopen,"%s %d %d %d %d %d %d %f %d %d\n",hi->destination,hi->date_start.day,hi->date_start.month,hi->date_start.year,hi->date_end.day,hi->date_end.month,hi->date_end.year,hi->price,hi->place_number,hi->ID_destination);
        hi=hi->next;
    }
    fclose(fileopen);
}
managerprofile* Adding_manager(managerprofile* hello)
{
    managerprofile *trans;
    trans=hello;
    managerprofile *newwonderers;
    newwonderers=(managerprofile*)malloc(sizeof(managerprofile));
    fflush(stdin);
    printf("\n\t\t\t\tEnter Username or Email\n\t\t");
    scanf("%s",newwonderers->manager_name);
    while(hello!=NULL)
    {
        if(!strcmp(hello->manager_name,newwonderers->manager_name))
        {
            printf("\t\t\t\tCe email existe deja\n");
            return trans;
        }
        hello=hello->next;
    }
    hello=trans;
    fflush(stdin);
    int nb1=0,nb2=0,nb3=0;
  bool test=false;
  printf("\n\t\t\t\tles conditions pour ecrire un mot de passe: \n");
  printf("\n\t\t\t\t**la longeur doit etre >=6 et a des letter en majuscules \n\t\t\t\tet minuscules et des numeros ** \n");
  printf("\n\t\t\t\tEntrer le mot de passe\n\t\t");
  scanf("%s",newwonderers->manager_password);
  while(!test){
    int i=0;
    while(newwonderers->manager_password[i]!='\0'){
    if(islower(newwonderers->manager_password[i]))nb1++;
    if(isupper(newwonderers->manager_password[i]))nb2++;
    if(isdigit(newwonderers->manager_password[i]))nb3++;
    i++;}
    if(strlen(newwonderers->manager_password)>=6 && nb1>0 && nb2>0  && nb3>0){
            test=true;
        printf("\n\n\t\t\t\tVous etes inscrit avec succes  ");
        }
    else  {
        test =false;
        printf("\n\n\t\t\t\tle mot de passe est ne verife  pas tous les conditions susmentionees");
        printf("\n\n\t\t\t\tEntrer un nouveau mot de passe qui verifie ces conditions\n\n\t\t");
        scanf(" %s",newwonderers->manager_password);
        }

  }
    newwonderers->next=NULL;
    if(hello==NULL)
    {
        hello=trans=newwonderers;
    }
    else
    {
        while(hello->next!=NULL)
        {
            hello=hello->next;
        }
        hello->next=newwonderers;
    }
    WriteToFile_manager(trans);
    return trans;
}

Travel* add_Travel(Travel* hi)
{
	bool test=false ;
    Travel *trans;
    trans=hi;
    Travel *newwonderers;
    newwonderers=(Travel*)malloc(sizeof(Travel));
    fflush(stdin);
    printf("\t\tEnter destination \n\t\t");
    scanf("%s",newwonderers->destination);

    fflush(stdin);
    while (!( test)){
    	int val1,val2;
    	bool test1=false;
    	bool test2=false ;
	    while (!( test1)){

        printf("\t\tEntrer la date debut de ce voyage(Remplir le date:jour puis espace puis mois puis espace puis annee)\n\t\t");
        scanf("%d%d%d",&newwonderers->date_start.day,&newwonderers->date_start.month,&newwonderers->date_start.year);
        val1=fct_ValidDate(&(newwonderers->date_start.day),&(newwonderers->date_start.month),&(newwonderers->date_start.year));
        if (val1== 1)
        test1=true;
         else printf("\t\tattention!\n");}
        while (!( test2)){

        printf("\t\tEntrer la date fin de ce voyage(Remplir le date:jour puis espace puis moi puis espace puis annee)\n\t\t");
        scanf("%d%d%d",&newwonderers->date_end.day,&newwonderers->date_end.month,&newwonderers->date_end.year);
		val2=fct_ValidDate(&(newwonderers->date_end.day),&(newwonderers->date_end.month),&(newwonderers->date_end.year));
        if (val2== 1)
        test2=true;
        else printf("\t\tattention!\n");}
		 if(newwonderers->date_end.year>newwonderers->date_start.year)
                      test=true;
           else if (newwonderers->date_end.year==newwonderers->date_start.year){
                if(newwonderers->date_end.month>newwonderers->date_start.month)
                test=true ;
                else if (newwonderers->date_end.month==newwonderers->date_start.month){
                         if(newwonderers->date_end.day>newwonderers->date_start.day)
                         test=true;
                         else printf("\t\tdate debut et date fin non incompatibles\n");}

               else printf("\t\tdate debut et date fin non incompatibles\n");}

         else printf("\t\tdate debut et date fin non incompatibles\n");}


	printf("\t\tEntrer le prix de ce voyage:\n\t\t");
    scanf("%f",&newwonderers->price);
    printf("\t\tEntrer les nombres de places disponnibles :\n\t\t");
    scanf("%d",&newwonderers->place_number);
    newwonderers->next=NULL;

    if(hi==NULL)
    { newwonderers->ID_destination=50000;
        hi=trans=newwonderers;
        WriteToFile_travel(trans);
        printf("\t\t votre premiere voyage est bien enregitre , merci d'entrer au nouveau");
         exit_system();
        exit(0);
    }
    else
    {
        while(hi->next!=NULL)
        {
            hi=hi->next;
        }
        newwonderers->ID_destination=hi->ID_destination+1;
        hi->next=newwonderers;}

    WriteToFile_travel(trans);
    return trans;
}
int fct_ValidDate(int *pjour,int *pmois,int *pannee)
 {
    int jour[]={31,28,31,30,31,30,31,31,30,31,30,31};
    int annee=2022;
    int val=1;
    int nbrJmois=0;

    if(*pannee<annee)
    {
        val=0;

    }

    if ((*pmois<1)||(*pmois>12))
    {
        val=0;

    }
    else
    {

        nbrJmois = jour[*pmois-1];

        if((*pannee%4==0)&&(*pannee%400==0)||(*pannee%100!=0)&&(*pmois==2))
        {
                ++ nbrJmois ;
        }

        if((*pjour<1)||(*pjour>nbrJmois))
        {
            val=0;

        }
    }

    return val;

 }
void modify_Travel(Travel *hi){
    Travel *trans=hi;
    char dest[100];
    fflush(stdin);
    printf("\t\tEntrer ta destination actuelle :\n\t\t");
    scanf(" %[^\n]s",dest);
    while(hi!=NULL)
    {   int answer;
        if(!strcmp(hi->destination,dest)){
            printf("\t\t vous souhaitez modifier le voyage %s avec l'identifiant %d \n\t\t 1-Oui\n\t\t 2-Non \n\t\t", dest,hi->ID_destination);
            scanf("%3d",&answer);
            if(answer==1){    printf("\t\tEntrer le nouveau prix(prix precedent%f):\n\t\t",hi->price);
            scanf("%f",&hi->price);
            printf("\t\tEntrer les nombres de places disponnibles actuellement(nombre precedent:%d) :\n\t\t",hi->place_number);
            scanf("%3d",&hi->place_number);
            printf("\t\tEntrer la nouvelle date du debut du voyage(date precedente:%d/%d/%d) :\n\t\t",hi->date_start.day,hi->date_start.month,hi->date_start.year);
            scanf("%d%d%d",&hi->date_start.day,&hi->date_start.month,&hi->date_start.year);
           printf("\t\tEntrer la nouvelle date du fin du voyage(date precedente:%d/%d/%d) :\n\t\t",hi->date_end.day,hi->date_end.month,hi->date_end.year);
           scanf("%d%d%d",&hi->date_end.day,&hi->date_end.month,&hi->date_end.year);}}
        hi=hi->next;
    }
    if(hi==NULL)
        return;

    WriteToFile_travel(trans);
return;

}
void delete_Travel(Travel *hi){
    char dest[100];
    printf("\t\tdonner la destination à supprimer :");
    scanf("%s",dest);
    if (hi == NULL)
         return(hi);
FILE *f,*t;
f=fopen("trips.txt","r");
t=fopen("tmp-trips.txt","a");
fscanf(f,"%s %d %d %d %d %d %d %f %d %d\n",hi->destination,&hi->date_start.day,&hi->date_start.month,&hi->date_start.year,&hi->date_end.day,&hi->date_end.month,&hi->date_end.year,&hi->price,&hi->place_number,&hi->ID_destination);

  Travel  *pred,*ptr;
  pred=hi;
  ptr=hi->next;
while(ptr != NULL)
{
  fscanf(f,"%s %d %d %d %d %d %d %f %d %d\n",ptr->destination,&ptr->date_start.day,&ptr->date_start.month,&ptr->date_start.year,&ptr->date_end.day,&ptr->date_end.month,&ptr->date_end.year,&ptr->price,&ptr->place_number,&ptr->ID_destination);
  if (!strcmp(ptr->destination ,dest))
  {printf("vous souhaiter effacer la voyage %s d'identfiant %d \n\t\t 1-Oui\n\t\t 2-Non \n\t\t",dest,ptr->ID_destination);
int b=0;
scanf("%d",&b);
if(b==1){
        Travel *tmp=ptr;
        ptr=ptr->next;
        free(tmp);
   }
else{
fprintf(t,"%s %d %d %d %d %d %d %f %d %d\n",ptr->destination,ptr->date_start.day,ptr->date_start.month,ptr->date_start.year,ptr->date_end.day,ptr->date_end.month,ptr->date_end.year,ptr->price,ptr->place_number,ptr->ID_destination);
pred->next=ptr;
pred=ptr;
ptr= ptr->next; }}
else
{
fprintf(t,"%s %d %d %d %d %d %d %f %d %d\n",ptr->destination,ptr->date_start.day,ptr->date_start.month,ptr->date_start.year,ptr->date_end.day,ptr->date_end.month,ptr->date_end.year,ptr->price,ptr->place_number,ptr->ID_destination);
pred->next=ptr;
pred=ptr;
ptr=ptr->next;
}}
if (!strcmp(hi->destination ,dest))
  {printf("vous souhaiter effacer la voyage %s d'identfiant %d \n\t\t 1-Oui\n\t\t 2-Non \n\t\t",dest,hi->ID_destination);
int b=0;
scanf("%d",&b);
if(b==1){
    Travel *tmp=hi;
    hi=hi->next;
    free(tmp);

}
else{
         fprintf(t,"%s %d %d %d %d %d %d %f %d %d\n",hi->destination,hi->date_start.day,hi->date_start.month,hi->date_start.year,hi->date_end.day,hi->date_end.month,hi->date_end.year,hi->price,hi->place_number,hi->ID_destination);}}
else{
        fprintf(t,"%s %d %d %d %d %d %d %f %d %d\n",hi->destination,hi->date_start.day,hi->date_start.month,hi->date_start.year,hi->date_end.day,hi->date_end.month,hi->date_end.year,hi->price,hi->place_number,hi->ID_destination);}
fclose(f);
fclose(t);
    remove("trips.txt");
    rename("tmp-trips.txt","trips.txt");
    printf("suppression effectuee avec success");

return(hi);

}

void changing_pass(managerprofile *hello)
{
    managerprofile *trans=hello;
    char passcurr[100];
    fflush(stdin);
    printf("\t\tEntrer ton mot de passe actuelle pour continuer:\n");
    scanf(" %[^\n]s",passcurr);
    while(hello!=NULL)
    {
        if(!strcmp(hello->manager_name,current_manager))
         break;
        hello=hello->next;
    }
    if(hello==NULL)
        return;
    if(!strcmp(passcurr,hello->manager_password))
    {
        int nb1=0,nb2=0,nb3=0;
  bool test=false;
  printf("\n\t\t\t\tles conditions pour ecrire un mot de passe: \n");
  printf("\n\t\t\t\t**la longeur doit etre >=6 et a des letter en majuscules \n\t\t\t\tet minuscules et des numeros ** \n");
  printf("\n\t\tEntrer le nouveau mot de passe\n\t\t");
  scanf(" %[^\n]s",hello->manager_password);
  while(!test){
    int i=0;
    while(hello->manager_password[i]!='\0'){
    if(islower(hello->manager_password[i]))nb1++;
    if(isupper(hello->manager_password[i]))nb2++;
    if(isdigit(hello->manager_password[i]))nb3++;
    i++;}
    if(strlen(hello->manager_password)>=6 && nb1>0 && nb2>0  && nb3>0){
            test=true;
        printf("\n\n\t\tVous etes modifier ce mot de passe avec succes  ");}
    else {
        test =false;
        printf("\n\n\t\t\t\tle mot de passe est ne verife  pas tous les conditions susmentionee");
        printf("\n\n\t\t\t\tEntrer un nouveau mot de passe qui verife ces conditions\n\n\t\t");
        scanf(" %[^\n]s",hello->manager_password);
  }}
    }
    WriteToFile_manager(trans);
}
void Travel_description(Travel *hi){
    int nbdest=0;
    Travel *trans=hi;
  printf("\t\tVoici la liste des voyages :\n");
    while(trans!=NULL){
        printf("\t\t %s avec identifiant %d **\n",trans->destination,trans->ID_destination);
        trans=trans->next;
    }
    char dest[100];
    fflush(stdin);
    printf("\n\t\tSi vous voulais la description d'une telle voyage \n");
    printf("\t\tEntrer votre destination choisie :\t\t");
    scanf(" %[^\n]s",dest);
    while(hi!=NULL)
    {
        if(!strcmp(hi->destination,dest)) {
            int choice=0;
            nbdest++;
            printf("\t\tLa distination %s d'identifiant %d \n\n",hi->destination,hi->ID_destination);
            printf("\t\tLe prix de votre destination est :%f \n\n",hi->price);
            printf("\t\tLe nombres de places disponnibles est : %d  \n\n",hi->place_number);
            printf("\t\tLa date du debut du voyage est : %d/%d/%d  \n\n",hi->date_start.day,hi->date_start.month,hi->date_start.year);
            printf("\t\tLa date du fin du voyage est : %d/%d/%d \n\n",hi->date_end.day,hi->date_end.month,hi->date_end.year);
            printf("\t\tSi vous vaulais completer le recherche  \n\t\t 1-Oui\n\t\t 2-Non \n\t\t  ");
            scanf("%d",&choice);
            if(choice!=1)break;

            }

        hi=hi->next;
    }
    if( nbdest==0 && hi==NULL){
            printf("\t\tVotre destination n'a pas ete affecte\n\t\t ");
        }
    else {printf("\t\tAucun plus de voyages pour cette destination\n\t\t");}

return;
}
void research_Travel(Travel *hi){

    date d,f;
    int s=0;
    printf("\t\t Cette fonction aide vous pour decouvrir vos voyages entre deux dates \n\t\t(Remplir le date:jour puis espace puis mois puis espace puis annee)\n ");
    printf("\t\tDonner votre date debut\n\t\t");
    scanf("%d%d%d",&d.day,&d.month,&d.year);
    printf("\t\tDonner votre date fin\n\t\t");
    scanf("%d%d%d",&f.day,&f.month,&f.year);
    while(hi!=NULL){
           int k=0 ;
           bool test=false;
           bool test1=false;
           if(hi->date_start.year>d.year)
                      test=true;
           else if (hi->date_start.year==d.year){
                if(hi->date_start.month>d.month)
                test=true ;
                else if (hi->date_start.month==d.month){
                         if(hi->date_start.day>=d.day)
                         test=true;
                   }}
           if(hi->date_end.year<f.year)
                      test1=true;
           else if (hi->date_end.year==f.year){
                if(hi->date_end.month<f.month)
                test1=true ;
                else if (hi->date_end.month==f.month){
                         if(hi->date_end.day<=f.day)
                         test1=true;}}
            if (test1 && test && hi!=NULL){
                s++;
                printf("\t\tLe voyage numero %d disponnible avec identifiant %d entre ces deux dates : %s \n" ,s,hi->ID_destination,hi->destination);
                printf("\t\tVoulez-vous voir la description de cette destination ? \n\t\t 1-Oui \n\t\t 2-Non \n\t\t ");
               scanf("%d",&k);
            if ((k==1)&& (test1 && test)){
                    printf("\n\t\tle prix de votre destination est :%f\n\n",hi->price);
                    printf("\t\tle nombres de places disponnibles est : %d\n\n",hi->place_number);
                    printf("\t\tla date du debut du voyage est : %d/%d/%d\n\n",hi->date_start.day,hi->date_start.month,hi->date_start.year);
                    printf("\t\tla date du fin du voyage est : %d/%d/%d\n\n",hi->date_end.day,hi->date_end.month,hi->date_end.year);

            }}

           hi=hi->next;

}
 if(s==0){printf("Aucune voyage entre ces deux dates");}

return;

}
void Color(int t,int f)
{
    HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H,f*16+t);
}
void logout()
{
    if(currentwindow==main_menu || strcmp(current_manager,"\0")==0)
    {
        printf("\t\tVous devez vous inscrire puis vous identifier \n");
        return;
    }
    strcpy(current_manager,"\0");
    currentwindow=main_menu;
    printf("\t\tVous avez reussit pour s'inscrire\n");
}
void exit_system()
{
    printf("\t\tSortir...\n\t\t aucun enregistement \n\n\t\tPress \"Entrer/Retourner\" Pour sortir");
    char exitprog;
    fflush(stdin);
    scanf("%c",&exitprog);
}
