
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//definition d une structure pour reserver les infos des bus
 typedef struct  {
	int numbus;
	char depart[50];
	char destination[50];
	int totalplaces;
	int placesvalables;
	float tarif;
	char nomchauf[25];
	char wifi[4];
	char climatisation[3];
}Bus;

//definition d une structure pour reserver les infos des passagers
struct Passenger {
	char nom[50];
	int age;
	int numplace;
	int busNumber;
	struct Passenger *suivant;
};

//definition d une structure pour reserver les infos de connections
   struct voyageur {
	char username[50];
	char *password;
	struct voyageur *suivant;
};


struct voyageur* CreerCompteV(char username[], char password[]) {
    struct voyageur *nouveau = (struct voyageur*)malloc(sizeof(struct voyageur));

    if (nouveau != NULL) {
        // Initialisation des champs de la structure
        strcpy(nouveau->username, username);
        nouveau->password = password;
        nouveau->suivant = NULL;
    }

    return nouveau;
}
// Fonction pour ajouter un compte voyageur à la fin de la liste
void ajouterCompte(struct  voyageur **tete, char username[50], char password[50]) {
    struct voyageur *nouveau = CreerCompteV(username, password);

    if (nouveau == NULL) {
        printf("Erreur lors de la création de la personne\n");
        return;
    }

    if (*tete == NULL) {
        // Si la liste est vide, le nouveau compte devient la tête de la liste
        *tete = nouveau;
    } else {
        // Sinon, parcourir la liste jusqu'à la fin et ajouter le compte
        struct voyageur *courant = *tete;
        while (courant->suivant != NULL) {
            courant = courant->suivant;
        }
        courant->suivant = nouveau;
    }
}

// fonction pour afficher le menu principal
void displayMainMenu()
{
	printf("\n=== E-Bus-Travel ===\n");
	printf("1. Login\n");
	printf("2. Creer un compte voyageur\n");
	printf("3. Exit\n");

	printf("Entrer votre choix : ");
}

// Fonction pour afficher le menu du voyageur
void displayUserMenu()
{
	printf("\n=== Menu Voyageur ===\n");
	printf("1. Reserver \n");
	printf("2. Afficher les details d'une reservation  \n");
	printf("3. Annuler une reservation \n");
	printf("4. Afficher les details des voyages \n");
	printf("5. Afficher les informations d' un bus  \n");
	printf("6. Donner votre avis a propos de notre application   \n");
	printf("7. Afficher les avis des autres utilisateurs   \n");
	printf("8. Logout\n");
	printf("Entrer votre choix: ");
}
int VoyageurExiste(struct voyageur *tete, char username[],char *password) {
    struct voyageur *courant = tete;

    while (courant != NULL) {
        if ((strcmp(courant->username, username) == 0)&&(strcmp(courant->password, password) == 0)) {
            // La personne avec le nom spécifié a été trouvée dans la liste
            return 1; // true
        }
        courant = courant->suivant;
    }

    // La personne n'a pas été trouvée dans la liste
    return -1;
}



// Fonction pour reserver
void bookTicket( Bus buses[], int numBuses, struct Passenger **passengerList) {
    int size;
    printf("Donner le nombre des passagers:\n ");
    scanf("%d", &size);

    // Demander le numéro de bus
    printf("\nEntrer le numero de bus: ");
    int busNumber;
    scanf("%d", &busNumber);

    // Trouver le bus avec le numéro donné
    int busIndex = -1;
    for (int i = 0; i < numBuses; i++) {
        if (buses[i].numbus == busNumber) {
            busIndex = i;
            break;
        }
    }

    if (busIndex == -1) {
        printf("Bus numero %d n est pas trouvee.\n", busNumber);
    } else if (buses[busIndex].placesvalables == 0) {
        printf("Desole, le bus est totalement reservee.\n");
    } else {
        for (int i = 0; i < size; i++) {
            // Créer un nouveau passager
            struct Passenger *newPassenger = (struct Passenger *)malloc(sizeof(struct Passenger));

            if (newPassenger != NULL) {
                printf("Entrer votre nom: ");
                scanf("%s", newPassenger->nom);

                printf("Entrer votre age: ");
                scanf("%d", &newPassenger->age);

                // Assigner un numéro de siège au passager
                newPassenger->numplace = buses[busIndex].totalplaces - buses[busIndex].placesvalables + 1;

                // Mettre à jour le numéro de bus du passager
                newPassenger->busNumber = busNumber;

                // Mettre à jour les sièges disponibles
                buses[busIndex].placesvalables--;

                // Ajouter le nouveau passager à la liste
                newPassenger->suivant = *passengerList;
                *passengerList = newPassenger;

                printf("Place reservee avec succes!\n");
            } else {
                printf("Erreur lors de l'allocation de mémoire pour le passager.\n");
                break;
            }
        }
    }
}
//fonction pour afficher les details d un bus
void afficherDetailsReservation(struct Passenger *passengerList) {
    printf("\nEntrer le nom du passager dont vous voulez afficher les details : ");
    char name[50];
    scanf("%s",name);
    name[strcspn(name, "\n")] = '\0'; // Supprimer le caractère de nouvelle ligne

    struct Passenger *current = passengerList;
    int found = 0;

    while (current != NULL) {
        if (strcmp(current->nom, name) == 0) {
            found = 1;
            printf("\nDetails de la reservation pour %s :\n", current->nom);
            printf("Age : %d\n", current->age);
            printf("Numero de place : %d\n", current->numplace);
            printf("Numero de bus : %d\n", current->busNumber);
            break;
        }

        current = current->suivant;
    }

    if (!found) {
        printf("Passager avec ce nom %s n'est pas trouve.\n", name);
    }
}


// Fonction pour annuler un billet avec une liste chaînée
void cancelTicket( Bus buses[], int numBuses, struct Passenger **passengerList, int userId) {
    printf("\nEntrer votre nom : ");
    char name[50];
    scanf("%s",name);
    name[strcspn(name, "\n")] = '\0';

    struct Passenger *current = *passengerList;
    struct Passenger *previous = NULL;
    int found = 0;

    while (current != NULL) {
        if ((strcmp(current->nom, name) == 0) && (current->busNumber == buses[userId].numbus)&&(userId<3)) {
            // Augmenter le nombre de places disponibles
            buses[userId].placesvalables++;
            userId++;

            // Retirer l'entrée du passager de la liste
            if (previous != NULL) {
                previous->suivant = current->suivant;
            } else {
                *passengerList = current->suivant;
            }

            free(current);
            found = 1;
            printf("Reservation annulee avec succes!\n");
            break;
        }

        previous = current;
        current = current->suivant;
    }

    if (!found) {
        printf("Passager avec ce nom %s n'est pas trouve.\n", name);
    }
}

// Fonction pour afficher les details des bus
void checkBusStatus( Bus buses[], int numBuses,
					int userId)
{
	printf("\nBus Number: %d\n", buses[userId].numbus);
	printf("Depart: %s\n", buses[userId].depart);
	printf("Destination: %s\n", buses[userId].destination);
	printf("Total des places: %d\n", buses[userId].totalplaces);
	printf("Places valables: %d\n",
		buses[userId].placesvalables);
	printf("Tarif : %.2f\n", buses[userId].tarif);
	printf("Nom du chauffeur: %s\n", buses[userId].nomchauf);
	printf("Wifi: %s\n", buses[userId].wifi);
	printf("Climatisation: %s\n", buses[userId].climatisation);
}

int main()

{   FILE *fbus;
    fbus=fopen("file_bus.txt","w");
    fprintf(fbus,"Num Bus | Depart | Arrivee |Nb places |  TARIF \n");
    fprintf       (fbus,"1         Tunis     Gabes       50       25.0 \n");
    fprintf       (fbus, "2         Tunis    Monastir     40       20.0 \n");
    fprintf       (fbus, "3         Tunis     Mahdia      30       15.0 \n ");
    fclose(fbus);
    FILE *avis;
    avis=fopen("file_avis.txt","w");

	struct voyageur *liste = NULL;
      struct Passenger *passengerList = NULL;


	// Initialisation de la base de donnees des bus
	 Bus buses[3] = {
		{ 1, "Tunis", "Gabes", 50, 50, 25.0 ,"Mohamed Cherif","oui","oui"},
		{ 2, "Tunis", "Monastir", 40, 40, 20.0 ,"Aymen Saleh","non","oui"},
		{ 3, "Tunis", "Mahdia", 30, 30, 15.0,"Mohamed Ali","oui","oui" },
	};
	int numBuses = 3;

	int loggedInUserId = -1;

	while (1) {
		if (loggedInUserId == -1)  {
			displayMainMenu();
			int choice;
			scanf("%d", &choice);
            switch(choice){
			   case 1:
				{char username[50];
				char password[50];

				printf("Entrer votre nom: ");
				scanf("%s", username);
				printf("Entrer votre mot de passe : ");
				scanf("%s", password);

				loggedInUserId = VoyageurExiste(liste,username,password);

				if (loggedInUserId == -1) {
					printf("La connexion a echoue. Verifiez s'il vous plait "
"votre nom d'utilisateur et votre mot de passe.\n");
				}
				else {
					printf(
						"Connexion reussie. Bienvenue, %s!\n",
						username);
				}}
			break;

            case 2 :

                {char nom_v[50],password_v[50];
                printf("Entrer votre nom: ");
				scanf("%s", nom_v);
				printf("Entrer votre mot de passe: ");
				scanf("%s", password_v);
                ajouterCompte(&liste,nom_v,password_v);
                 printf("votre compte a ete creer avec succes !");

                 loggedInUserId=-1;}
                 break;


			case 3:
				printf("Quitter l'application.\n");
				break;

			default:
				printf("Choix invalide. Veuillez réessayer.\n");
			break;
		}}
		else {
			displayUserMenu();
			int userChoice;
			scanf("%d", &userChoice);

			switch (userChoice) {
			case 1:
				bookTicket(buses, numBuses,&passengerList);
				break;
            case 2 :
                afficherDetailsReservation(passengerList);
                break;
			case 3:
				cancelTicket(buses, numBuses, &passengerList,0);
				break;
			case 4:
				{ char *buffer;
                 long fileLength;
                fbus=fopen("file_bus.txt","r");
                if (fbus == NULL) {
                printf("Impossible d'ouvrir le fichier.\n");
                return 1; // Return an error code
                 }
                fseek(fbus, 0, SEEK_END); // Move the file pointer to the end of the file
                fileLength = ftell(fbus); // Get the current position (which is the file length)
                fseek(fbus, 0, SEEK_SET);
                buffer = (char *)malloc(fileLength + 1);
                if (buffer == NULL) {
                printf("Memory allocation failed.\n");
                fclose(fbus);
                return 1; // Return an error code
                }
                fread(buffer, 1, fileLength, fbus);
                buffer[fileLength] = '\0';
                fclose(fbus);
                printf("File content:\n%s\n", buffer);
                free(buffer);}
				break;
            case 5:
                {int id;
                printf("Donner le numero de bus \n");
                 scanf("%d",&id);
                 checkBusStatus(buses, numBuses,id-1);
                               }
                               break;
            case 6:
                {   char nom[50],a[6],com[200];
                    printf("Votre avis nous interesse !\n ");
                    printf("Donner votre nom : \n");
                    scanf("%s",nom);
                    fprintf(avis,"%s : ",nom);
                    printf("Donner une note sur ***** : \n");
                    gets(a);
                    fprintf(avis,"%s \n",a);
                    printf("Vous pouvez ajouter un commentaire  \n");
                    gets(com);
                    fprintf(avis,"%s\n",com);
                    fclose(avis);


                }

                 break;
            case 7:
                { char *buffer;
                 long fileLength;
                fbus=fopen("file_avis.txt","r");
                if (avis == NULL) {
                printf("Impossible d'ouvrir le fichier.\n");
                return 1;
                 }
                fseek(avis, 0, SEEK_END);
                fileLength = ftell(avis);
                fseek(avis, 0, SEEK_SET);
                buffer = (char *)malloc(fileLength + 1);
                if (buffer == NULL) {
                printf("Memory allocation failed.\n");
                fclose(avis);
                return 1;
                }
                fread(buffer, 1, fileLength, fbus);
                buffer[fileLength] = '\0';
                fclose(avis);
                printf("File content:\n%s\n", buffer);
                free(buffer);}
				break;


                break;
			case 8:
				printf("Au revoir <3.\n");
				loggedInUserId = -1;
				break;
			default:
				printf(
					"Choix invalide. Veuillez reessayer.\n");
			}
		}
	}

	return 0;
}

