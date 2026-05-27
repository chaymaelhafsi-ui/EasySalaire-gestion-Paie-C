#include <stdio.h>
#include <string.h>

// Déclaration des fonctions obligatoires de l'énoncé
void ajouterEmploye(char nom[][30], float h_normales[], float h_supp[], int *n);
float calculBrut(float h_normales, float h_supp);
float calculNet(float brut);
float calculPrime(float heures);
void afficherBulletin(char nom[][30], float salaire_net[], int n);

int main() {
    // Les variables données dans l'énoncé
    char nom[50][30];
    float h_normales[50];
    float h_supp[50];
    float salaire_brut[50]; // Pour stocker le brut de chaque employé
    float salaire_net[50];  // Pour stocker le net de chaque employé
    int n = 0; // Au début, il y a 0 employé

    int choix; // Notre variable interrupteur pour le menu

    do {
        // Affichage du menu pour l'utilisateur
        printf("\n--- MENU EASYSALAIRE ---\n");
        printf("1. Ajouter un employe\n");
        printf("2. Afficher les bulletins de paie\n");
        printf("3. Quitter\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                // 1. On appelle la fonction pour taper le nom et les heures
                ajouterEmploye(nom, h_normales, h_supp, &n);

                // 2. On fait les calculs tout de suite pour l'employé qu'on vient d'ajouter
                // Sa position dans le tableau est juste avant le nouveau 'n' (donc n - 1)
                int i = n - 1;

                // Calcul de la prime (Heures normales + Heures supp)
                float total_h = h_normales[i] + h_supp[i];
                float ma_prime = calculPrime(total_h);

                // Calcul du brut de base + ajout de la prime
                salaire_brut[i] = calculBrut(h_normales[i], h_supp[i]) + ma_prime;

                // Calcul du net final à partir du brut
                salaire_net[i] = calculNet(salaire_brut[i]);
                break;

            case 2:
                // On affiche les bulletins avec le tableau salaire_net
                afficherBulletin(nom, salaire_net, n);

                // Petit bonus débutant : on réaffiche les détails textuels ici
                // en refaisant le calcul rapide pour l'affichage de l'exemple
                if (n > 0) {
                    printf("\n--- DETAILS VISUELS ---\n");
                    for (int j = 0; j < n; j++) {
                        float tot = h_normales[j] + h_supp[j];
                        printf("Nom : %s\n", nom[j]);
                        printf("Salaire Brut : %.0f\n", salaire_brut[j]);
                        printf("Salaire Net : %.0f\n", salaire_net[j]);
                        printf("Prime : %.0f\n", calculPrime(tot));
                        printf("-------------------------------------\n");
                    }
                }
                break;

            case 3:
                printf("Au revoir !\n");
                break;

            default:
                printf("Choix incorrect, veuillez recommencer.\n");
        }
    } while (choix != 3); // On boucle tant que l'utilisateur ne tape pas 3

    return 0;
}

// 1. Fonction pour ajouter un employé (Saisie des données)
void ajouterEmploye(char nom[][30], float h_normales[], float h_supp[], int *n) {
    // *n permet de lire et modifier la variable 'n' du main
    if (*n >= 50) {
        printf("Erreur : Le tableau est plein !\n");
    } else {
        printf("\n--- Saisie des donnees ---\n");
        printf("Entrez le nom de l'employe : ");
        scanf("%s", nom[*n]);

        printf("Entrez les heures normales : ");
        scanf("%f", &h_normales[*n]);

        printf("Entrez les heures supplementaires : ");
        scanf("%f", &h_supp[*n]);

        // On augmente n de 1 dans le main
        (*n)++;
        printf("Employe enregistre dans le tableau.\n");
    }
}

// 2. Fonction pour calculer le salaire brut
float calculBrut(float h_normales, float h_supp) {
    float taux = 10.0; // On choisit un taux simple de 10 DT par heure
    float resultat_brut;

    // Application de la formule de l'énoncé
    resultat_brut = (h_normales * taux) + (h_supp * taux * 1.5);

    return resultat_brut; // On renvoie le résultat
}

// 3. Fonction pour calculer le salaire net
float calculNet(float brut) {
    float taxes;
    float resultat_net;

    taxes = brut * 0.15; // 15% de retenues fiscales
    resultat_net = brut - taxes;

    return resultat_net;
}

// 4. Fonction pour calculer la prime
float calculPrime(float heures) {
    // Si l'employé dépasse 160 heures au total
    if (heures > 160.0) {
        return 200.0; // Il gagne une prime de 200 DT
    } else {
        return 0.0;   // Sinon, pas de prime
    }
}

// 5. Fonction pour afficher le bulletin (Prévu par l'énoncé)
void afficherBulletin(char nom[][30], float salaire_net[], int n) {
    if (n == 0) {
        printf("Le tableau est vide. Aucun bulletin a afficher.\n");
    } else {
        printf("\n--- BULLETINS DE PAIE (SALAIRES NETS) ---\n");
        for (int i = 0; i < n; i++) {
            printf("Employe : %s | Salaire Net : %.2f DT\n", nom[i], salaire_net[i]);
        }
    }
}
