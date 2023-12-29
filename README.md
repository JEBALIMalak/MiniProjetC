
E-Bus-Travel est une application qui assure la réservation d'un bus pour faire un voyage offrant aux utilisateurs la possibilité de planifier et de gérer leurs voyages en bus de manière pratique et efficace. 
Les utilisateurs peuvent créer des comptes voyageurs, se connecter, réserver des places dans différents bus, annuler des réservations, et accéder à des informations détaillées sur les voyages disponibles. 
L'application propose également une fonctionnalité d'avis, permettant aux utilisateurs de donner leur feedback et de consulter les avis d'autres voyageurs.

Voici une description du fonctionnement général de l'application :

1\Menu Principal :\n

-Lorsque l'application démarre, elle affiche un menu principal offrant trois options :
.Login (Connexion) : Les utilisateurs peuvent se connecter avec leur nom d'utilisateur et leur mot de passe. Les informations d'identification sont vérifiées par rapport à une liste de voyageurs enregistrés.
..Créer un Compte Voyageur : Les utilisateurs peuvent créer un nouveau compte voyageur en fournissant un nom d'utilisateur et un mot de passe. Ces informations sont ensuite ajoutées à la liste des voyageurs enregistrés.
...Exit (Quitter) : Permet de quitter l'application.

2\Menu Voyageur
Une fois connecté, un voyageur voit un menu spécifique offrant diverses fonctionnalités :
1.Réserver : Permet de réserver des places dans un bus en spécifiant le nombre de passagers et le numéro du bus.
2.Afficher les Détails d'une Réservation : Permet d'afficher les détails d'une réservation en entrant le nom du passager.
3.Annuler une Réservation : Permet d'annuler une réservation en entrant le nom du passager.
4.Afficher les Détails des Voyages : Affiche les détails des voyages disponibles.
5.Afficher les Informations d'un Bus : Affiche les informations détaillées d'un bus en spécifiant son numéro.
6.Donner un Avis : Permet aux voyageurs de donner leur avis sur l'application en fournissant leur nom, une note sur cinq étoiles, et un commentaire.
7.Afficher les Avis des Autres Utilisateurs : Affiche les avis des autres utilisateurs.
8.Logout (Déconnexion) : Permet de se déconnecter et de revenir au menu principal.

3\Base de Données des Bus :
Les informations sur les bus, y compris leur numéro, départ, destination, nombre total de places, places disponibles, tarif, nom du chauffeur, et les services disponibles (wifi, climatisation), sont stockées dans un tableau de structures.

4\Gestion des Comptes Voyageurs :
Les informations des voyageurs, y compris leur nom d'utilisateur et mot de passe, sont stockées dans une liste chaînée. Les utilisateurs peuvent se connecter en vérifiant leurs informations d'identification.

5\Gestion des Réservations :
Les réservations sont gérées à l'aide d'une liste chaînée de passagers. Lorsqu'un utilisateur réserve des places dans un bus, un nouveau nœud est ajouté à la liste avec les détails du passager.

6\Fichiers de Stockage :
Les détails des bus sont stockés dans un fichier texte appelé "file_bus.txt".
Les avis des utilisateurs sont stockés dans un fichier texte appelé "file_avis.txt".
