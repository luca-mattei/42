#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

// Fonction pour compter le nombre de mots dans la chaîne et allouer un tableau.
char **ft_tab(char const *s, char c) {
    size_t i = 0;
    size_t tab_size = 0;
    char **tab;

    // Compte le nombre de mots en vérifiant les transitions entre c et les caractères.
    while (s[i]) {
        // Un nouveau mot commence si on est dans un caractère non-c et que le précédent était c.
        if (s[i] != c && (i == 0 || s[i - 1] == c)) {
            tab_size++;
        }
        i++;
    }

    // Allocation de mémoire pour le tableau de chaînes.
    tab = (char **)malloc(sizeof(char *) * (tab_size + 1)); // +1 pour le terminateur NULL.
    if (!tab) {
        return (NULL); // Renvoie NULL en cas d'échec d'allocation.
    }
    tab[tab_size] = NULL; // Ajout du terminateur NULL pour indiquer la fin du tableau.
    return (tab);
}

// Fonction pour allouer et copier une chaîne de caractères d'un intervalle donné.
char *ft_case(const char *s, size_t start, size_t end) {
    char *tab = (char *)malloc(sizeof(char) * (end - start + 1)); // Allocation pour la chaîne.
    if (!tab) {
        return (NULL); // Renvoie NULL en cas d'échec d'allocation.
    }

    size_t j = 0;
    // Copie les caractères de s de start à end.
    while (start < end) {
        tab[j++] = s[start++];
    }
    tab[j] = '\0'; // Ajoute le terminateur NULL à la fin de la chaîne.
    return tab;
}

// Fonction principale pour diviser la chaîne en mots.
char **ft_split(char const *s, char c) {
    char **tab = ft_tab(s, c); // Appel de ft_tab pour obtenir le tableau.
    size_t j = 0; // Indice pour le tableau de mots.
    size_t start = 0; // Indice de début d'un mot.
    size_t i = 0; // Indice pour parcourir la chaîne.

    if (!tab) {
        return (NULL); // Vérifie si l'allocation a échoué.
    }

    // Parcourt la chaîne pour extraire les mots.
    while (s[i]) {
        if (s[i] != c) {
            // Marque le début d'un mot.
            if (start == 0 || s[i - 1] == c) {
                start = i;
            }
        }
        // Vérifie si on est à la fin d'un mot.
        if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0')) {
            tab[j++] = ft_case(s, start, i + 1); // Copie le mot extrait dans le tableau.
        }
        i++;
    }
    return tab; // Renvoie le tableau de mots.
}

int main(void) {
    char const *s = ",salut,ca,va";
    char c = ',';
    char **tab = ft_split(s, c); // Appel de ft_split pour diviser la chaîne.

    if (tab) {
        // Affiche chaque mot extrait et libère la mémoire.
        for (size_t i = 0; tab[i]; i++) {
            printf("%s\n", tab[i]);
            free(tab[i]); // Libération de la mémoire pour chaque chaîne.
        }
        free(tab); // Libération de la mémoire pour le tableau de chaînes.
    }
    return 0;
}

