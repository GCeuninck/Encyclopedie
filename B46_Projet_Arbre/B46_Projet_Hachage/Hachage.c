#include "Hachage.h"

FILE * ouvrir_fichier(FILE* fichier, char * choix){
    fichier = NULL;
    printf("%s\n", choix);

    if(fopen(choix, "r") != NULL){
        //Ajoute les informations du fichiers à la varible si l'ouverture a bien eu lieu
        fichier = fopen(choix, "r");
    }else{
        printf("ERREUR LORS DE L'OUVERTURE\n\n\n");
    }
    return fichier;
}


Encyclopedie initialisation_encyclopedie(FILE * fichier, Encyclopedie e){
    char ligne_actuelle[TAILLE_MAX];

    int identifiant;
    char * token_identifiant;
    char * token_titre;
    char * token_contenu;

    //Caractère en différentes informations
    const char separation[2] = "|";

    //Tant que les lignes ne sont pas vides / Infomrations séparées par changement de ligne
    while(fgets(ligne_actuelle, TAILLE_MAX, fichier) != NULL){

        //Respecte le format du fichier: Identifiant|Titre|Contenu
        token_identifiant = strtok(ligne_actuelle, separation);
        //Conversion de l'identifiant char*->int
        identifiant = atoi(token_identifiant);
        token_titre = strtok(NULL, separation);
        token_contenu = strtok(NULL, separation);

        if((identifiant != NULL && token_titre != NULL) && token_contenu != NULL){
            e = inserer(e, identifiant, token_titre, token_contenu);
        }
    }
    return e;
}


int hachage(int clef){

    int identifiant = NULL;
    //Si la clef existe : On transforme la clef sous forme d'indice de tableau
    if(clef!=NULL){
        identifiant = clef % TAILLE_TAB;
    }
    return identifiant;
}


void afficher_maillons(EncyclopedieMAILLON e){

    /*Si la liste chainee e n'est pas vide :
    on affiche l'identifiant, le titre et le contenu de chaque article de cette liste*/
    if(e!=NULL){
        printf("N %d : %s\n",e->clef, e->titre);
        afficher_maillons(e->suivant);
    }
}


void afficher_encyclopedie(Encyclopedie e){

    int i;

    /*Si le tableau de listes chainees e n'est pas vide :
    on affiche l'indice du tableau, l'identifiant, le titre et le contenu de chaque article à cet indice*/
    if(e!=NULL){
        for(i=0;i<TAILLE_TAB;i++){
            printf("Indice : %d\n",i);
            afficher_maillons(e[i]);
            printf("\n");
        }
    }
}


int est_vide(Encyclopedie e){

    int res=0, i;

    //Si le tableau de listes chainees e existe
    if(e!=NULL){
        //Si tous les articles sont vides : res = VRAI
        for(i=0;i<TAILLE_TAB;i++){
            if(e[i] == NULL){
                res=1;
            }
        }
    }
    return res;
}


Encyclopedie creer_encyclopedie(){

    Encyclopedie e;
    e = (Encyclopedie)malloc(sizeof(struct EncyclopedieSt)*TAILLE_TAB);
    int i;

    //On cree un tableau de listes chainees vides
    for(i=0; i<TAILLE_TAB; i++){
        e[i] = NULL;
    }

    return e;
}


EncyclopedieMAILLON insererMAILLON(EncyclopedieMAILLON e, int identifiant, char * titre, char * contenu){

    /*Si on est en bout de chaine et que les champs a inserer existent :
    On cree un nouveau maillon contenant les informations a inserer*/
    if(e==NULL  && identifiant != NULL && titre != NULL && contenu != NULL){
        e = (EncyclopedieMAILLON)malloc(sizeof(struct EncyclopedieSt));

        e->clef = identifiant;

        e->titre = (char *)malloc(sizeof(char)*strlen(titre)+1);
        strcpy(e->titre,titre);

        e->contenu = (char *)malloc(sizeof(char)*strlen(contenu)+1);
        strcpy(e->contenu,contenu);

        e->suivant = NULL;
    }

    //Si l'identifiant et donc l'article existe deja : Message d'erreur
    else if(e->clef == identifiant){
        printf("IDENTIFIANT EXISTE DEJA\n");
    }

    //Si on est pas en bout de chaine : On recommence avec le maillon suivant
    else{
        e->suivant = insererMAILLON(e->suivant, identifiant, titre, contenu);
    }

    return e;
}


Encyclopedie inserer(Encyclopedie e, int identifiant, char * titre, char * contenu){

    int ID_TABLE;

    //Si e n'est pas vide et que les champs a inserer sont definis
    if(e!=NULL  && identifiant != NULL && titre != NULL && contenu != NULL){

        //On transforme l'identifiant en indice
        ID_TABLE = hachage(identifiant);

        //On insere a l'indice trouve avec la methode d'insertion en liste chainee
        e[ID_TABLE] = insererMAILLON(e[ID_TABLE],identifiant,titre,contenu);
    }

    return e;
}


EncyclopedieMAILLON supprimerMAILLON(EncyclopedieMAILLON e, int identifiant){

    EncyclopedieMAILLON suppr;

    //Si la liste chainee e est vide ou que l'identifiant est non defini : Message d'erreur
    if (e == NULL || identifiant == NULL){
        printf("ENCYCLOPEDIE VIDE\n\n");
    }

    //Si le dernier element de la chaine n'est toujours pas l'article selectionne : Message d'erreur
    else if(e->suivant==NULL && e->clef != identifiant){
        printf("IDENTIFIANT INCONNU\n\n");
    }

    //Si le 1er maillon est celui a supprimer
    else if(identifiant == e->clef){
        suppr = e;
        e = e->suivant;
        free(suppr);
    }

    //Si le prochain maillon est celui a supprimer
    else if(e->suivant->clef == identifiant){

        suppr = e->suivant;
        e->suivant = e->suivant->suivant;
        free(suppr->titre);
        free(suppr->contenu);
        free(suppr);
    }

    //Si le maillon n'est pas celui a supprimer : On recommence avec le maillon suivant
    else{
        e->suivant = supprimerMAILLON(e->suivant, identifiant);
    }

    return e;
}

Encyclopedie supprimer(Encyclopedie e, int identifiant){

    int ID_TABLE = NULL;

    //Si e n'est pas vide et que l'identifiant est defini
    if(e != NULL && identifiant != NULL){

        //On transforme l'identifiant en indice
        ID_TABLE = hachage(identifiant);

        //On supprime a l'indice trouve avec la methode de suppression en liste chainee
        e[ID_TABLE] = supprimerMAILLON(e[ID_TABLE],identifiant);
    }

    return e;
}


char * rechercher_articleMAILLON(EncyclopedieMAILLON e, int identifiant){

    //Initialisation de la variable qui contiendra le contenu de l'article
    char * res = NULL;

    //Si la liste chainee e est vide ou que l'identifiant est non defini : Message d'erreur
    if(e == NULL || identifiant == NULL){
        printf("ENCYCLOPEDIE VIDE OU IDENTIFIANT INCONNU\n\n");
    }

    //Si le maillon est celui selectionne : res contient le contenu de cet article
    else if(e->clef == identifiant){
        res = e->contenu;
    }

    //Si le maillon n'est pas celui selectionne : On recommence avec le maillon suivant
    else{
        res = rechercher_articleMAILLON(e->suivant, identifiant);
    }

    return res;
}


char * rechercher_article(Encyclopedie e, int identifiant){

    int ID_TABLE;

    //Initialisation de la variable qui contiendra le contenu de l'article
    char * res = NULL;

    //Si e n'est pas vide et que l'identifiant est defini
    if(e != NULL && identifiant != NULL){

        //On transforme l'identifiant en indice
        ID_TABLE = hachage(identifiant);

        //On recherche l'article a l'indice trouve avec la methode de recherche d'article en liste chainee
        res = rechercher_articleMAILLON(e[ID_TABLE],identifiant);
    }

    return res;
}


EncyclopedieMAILLON rechercher_article_plein_texteMAILLON(EncyclopedieMAILLON e, char * mot){

    //Creation d'une nouvelle liste chainee qui contiendra les articles selectionnes par mot
    EncyclopedieMAILLON res = NULL;

    //Si la liste chainee e n'est vide et que mot est defini
    if(e!=NULL && mot != NULL){

        //Si le contenu du maillon contient le mot : on insere ce maillon dans res, on recommence avec le suivant
        if(strstr(e->contenu, mot)){
            res = insererMAILLON(res, e->clef, e->titre, e->contenu);
            res->suivant = rechercher_article_plein_texteMAILLON(e->suivant, mot);

        }

        //Si le maillon n'est pas celui selectionne : On recommence avec le maillon suivant
        else{
            res = rechercher_article_plein_texteMAILLON(e->suivant, mot);
        }
    }

    return res;
}


Encyclopedie rechercher_article_plein_texte(Encyclopedie e, char * mot){

    int i;

    //Creation d'une nouvelle encyclopedie qui contiendra les articles selectionnes par mot
    Encyclopedie res = creer_encyclopedie();

    //Si e n'est pas vide et que le mot est defini
    if(e != NULL && mot != NULL){

        //On recherche pour chaque indice avec la methode de recherche d'article plein texte en liste chainee
        for(i=0;i<TAILLE_TAB;i++){
             res[i] = rechercher_article_plein_texteMAILLON(e[i], mot);
        }
    }

    return res;
}


void detruire_encyclopedieMAILLON(EncyclopedieMAILLON e){

    EncyclopedieMAILLON suppr;

    /*Tant qu'on a pas parcouru toute la liste chainee :
    Le maillon est remplace par son suivant puis on supprime ses informations*/
    while(e!=0){
        suppr = e;
        e = e->suivant;
        free(suppr->titre);
        free(suppr->contenu);
        free(suppr);
    }
}

void detruire_encyclopedie(Encyclopedie e){

    int i;

    //Si e existe : On detruit pour chaque indice avec la methode de destruction en liste chainee
    if(e!=NULL){
        for(i=0;i<TAILLE_TAB;i++){
            detruire_encyclopedieMAILLON(e[i]);
            e[i]=NULL;
        }
    }
}



void menu(){
    //CREATION DE L'ENCYCLOPEDIE
    Encyclopedie e = creer_encyclopedie();
    int menu = NULL;

    printf("----------------MENU--------------------\n");
    printf("\t Creation de l'encyclopedie\n");
    printf("1. Manuellement\n");
    printf("2. Par fichier externe\n");

    while(menu == NULL){
            printf("Votre choix : ");
            scanf("%d", &menu);

            switch(menu){
            case 1:
                menu_manuel(e);
                break;

            case 2:
                menu_automatique(e);
                break;

            default:
                printf("Entrer une valeur valide\n\n");
                break;
        }
    }
}


void menu_automatique(Encyclopedie e){
    FILE * fichier;
    char * choix = NULL;
    int menu;

    printf("----------------MENU--------------------\n");
    printf("\t Choisir le fichier\n");
    printf("1. Echantillons de 500 articles\n");
    printf("2. Articles tries\n");
    printf("3. Articles non tries\n\n");

    while(choix == NULL){
        printf("Votre choix : ");
        scanf("%d", &menu);

        switch(menu){
            case 1:
                choix = "B46_wikipedia_test.dat";
                break;

            case 2:
                choix = "B46_wikipedia_500K_sorted.dat";
                break;

            case 3:
                choix = "B46_wikipedia_500K_random.dat";
                break;

            default:
                printf("Entrer une valeur adaptee\n\n");
                break;
        }
    }

    fichier = ouvrir_fichier(fichier, choix);
    e = initialisation_encyclopedie(fichier, e);
    fclose(fichier);
    menu_principal(e);
}


void menu_manuel(Encyclopedie e){
    int nb_articles, i, identifiant;
    char titre[TAILLE_MAX];
    char contenu[TAILLE_MAX];

    printf("----------------MENU--------------------\n");
    printf("Saisir le nombre d'articles a ajouter : ");
    scanf("%d", &nb_articles);

    for(i = 0 ; i < nb_articles ; i++){

        printf("Identifiant : ");
        scanf("%d", &identifiant);
        fflush(stdin);  //Permet de vider le buffer d'entrée de stdin

        printf("Titre : ");
        fgets(titre, TAILLE_MAX, stdin);
        fflush(stdin);

        printf("Contenu : ");
        fgets(contenu, TAILLE_MAX, stdin);
        fflush(stdin);

        printf("\n");

        e = inserer(e, identifiant, titre, contenu);
    }
    menu_principal(e);
}


void menu_principal(Encyclopedie e){
    int menu = NULL;
    int sortie = 0;

    //Initialisation variables pour recherches/suppression
    int choix;
    char mot_clef[26];

    //Initialisation des variables pour l'ajout
    int identifiant;
    char titre[TAILLE_MAX];
    char contenu[TAILLE_MAX];

    Encyclopedie e1 = creer_encyclopedie(e1);

    do{
            printf("----------------MENU--------------------\n");
            printf("\t Accueil\n");
            printf("1. Supprimer un article\n");
            printf("2. Rechercher par identifiant\n");
            printf("3. Rechercher par un mot\n");
            printf("4. Inserer un article\n");
            printf("5. Afficher encyclopedie\n\n");
            printf("6. Quitter\n\n");

            printf("Votre choix : ");
            scanf("%d", &menu);
            printf("\n");

            switch(menu){
            case 1:     //Supression d'article
                printf("Suppression\n");
                printf("Article a supprimer : ");
                scanf("%d", &choix);
                e = supprimer(e, choix);
                break;

            case 2:     //Recherche par identifiant
                printf("Debut recherche\n");
                printf("Article a rechercher : ");
                scanf("%d", &choix);
                printf("\n");
                printf("%s", rechercher_article(e, choix));
                printf("\n\n");
                break;

            case 3:     //Recherche par mot
                printf("Debut recherche\n");
                printf("Mot a rechercher :\n");
                scanf("%s", &mot_clef);
                e1 = rechercher_article_plein_texte(e, mot_clef);
                afficher_encyclopedie(e1);
                break;

             case 4:    // Insérer un article
                printf("Identifiant : ");
                scanf("%d", &identifiant);
                fflush(stdin);  //Permet de vider le buffer d'entrée de stdin

                printf("Titre : ");
                fgets(titre, TAILLE_MAX, stdin);
                fflush(stdin);

                printf("Contenu : ");
                fgets(contenu, TAILLE_MAX, stdin);
                fflush(stdin);

                printf("\n");

                e = inserer(e, identifiant, titre, contenu);
                break;

            case 5:     //Afficher arbre
                afficher_encyclopedie(e);
                printf("\n");
                break;

            case 6:     //Quitter
                detruire_encyclopedie(e1);
                detruire_encyclopedie(e);
                e = NULL;
                e1 = NULL;
                sortie = 1;
                break;

            default:
                printf("Entrer une valeur adaptee\n\n");
                break;
        }
    }while(sortie == 0);
    if(sortie != 1){
        menu_principal(e);
    }
}
