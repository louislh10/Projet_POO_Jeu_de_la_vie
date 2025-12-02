🧬 Jeu de la Vie – Projet POO (C++ / SFML)

Projet réalisé dans le cadre du module Programmation Orientée Objet, suivant l’implémentation du Jeu de la Vie de Conway.
Ce projet propose deux modes d’affichage :

Mode Console

Mode Graphique via SFML

Il s’appuie sur une architecture orientée objet conforme aux diagrammes UML fournis (Diagramme de classes, d’activité et de séquence).
Architecture Objet (résumé UML) :

Le projet repose sur les classes principales suivantes :

Cellule (classe abstraite) :
estVivante(), calculerEtatFutur(), appliquerEtatFutur()

CelluleVivante / CelluleMorte :
Implémentation concrète du comportement d’une cellule.

Regle (classe abstraite) :
Définition générique d’une règle d’évolution.

RegleC :
Implémente les règles classiques du Jeu de la Vie.

Grille :
Contient une matrice dynamique de Cellule*
Applique la règle à l’ensemble des cellules

Jeu :
Gère le chargement d’un fichier texte
Possède une Grille et une Regle
Pilote les générations

FenetreSFML :
Affiche la grille dans une fenêtre graphique
Gère les événements / rafraîchissement

Le projet utilise un format simple :  
hauteur largeur
0 1 0 0 1
1 1 0 0 0
0 0 1 1 0

🛠️ Compilation & Configuration
⚙️ Prérequis

Visual Studio 2022

SFML 2.5 ou 2.6 (déjà configuré dans ce projet)

C++17 minimum

📌 Bibliothèques SFML utilisées

sfml-graphics

sfml-window

sfml-system

L’intégration SFML est déjà prête dans les paramètres du projet.

📄 Licence

Projet académique — utilisation libre à des fins pédagogiques.
