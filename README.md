# Labyrinth
Un générateur de labyrinthe fait en C. Un mini-projet scolaire fait avec un binôme.

## Manuel d'utilisateur

### Compilation
`gcc -Wall -ansi Labyrinthe.c -o Labyrinthe`

### Éxécution
`./Labyrinthe [--OPTION]`

### Liste des options :
Pour l'éxécution, vous avez le choix d'utiliser les options ci-dessous:

`--taille=mxn` : Définit la taille du labyrinthe généré, `m` étant la longueur et `n` la largeur.

`--graine=X`: Fixe la graine du labyrinthe, ce qui permet de sélectionner un labyrinthe généré en particulier. `X` étant l'identifiant du labyrinthe.

`attente=X` : Ajoute un délai de `X` seconde(s) à chaque suppression de mur, ce qui permet de voir comment est généré le labyrinthe plus en détails.

`--mode=texte` : Affiche une version textuelle du labyrinthe dans le terminal.

`--unique` : Permet d'avoir un labyrinthe à chemin unique.


## Informations supplémentaires
Lire le rapport (intitulé `Rapport_Dylan_Canet_-_Diagne_Ben.pdf`) pour plus d'informations sur le déroulement de ce projet.
