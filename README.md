#CHAMBELLON_Lab1

L'objectif de ce LAB1 est de créer un effet de chenillard avec 8 LEDS sur la carte DE10-Lite. Vous démarrez le chenillard en appuyant sur un bouton poussoir et ajustez la vitesse avec 4 interrupteurs.

Voici l'architecture de ce système :

![image](https://github.com/ESN2024/CHAMBELLON_Lab1/assets/156073044/6433b95e-b5cc-4132-9241-d1f59fedac9f)

Pour concevoir le système, vous avez besoin de :

    RAM pour stocker les données
    Bouton poussoir et boutons switchs pour le contrôle.
    CPU (NIOS II).
    JTAG (UART) pour le chargement du programme.
    LEDS pour l'affichage.

Quand vous appuyez sur le bouton poussoir, une interruption active le chenillard. Les boutons switchs modifient la vitesse comme suit :

    Entre l'affichage de chaque LED successivement, on applique un délai de valeur udelay = 500000 / (speed+1);
    La variable speed correspondant à la valeur (3downto0) des 4 switchs, plus la variable speed est grande, moins la valeur du délai est importante, et ainsi le chenillard va plus vite.
    Le speed+1 permet d'éviter le cas ou les 4 switchs sont à zéro et on aurait une division par 0.

Pour créer le système, on conçoit d'abord l'architecture matérielle avec "Platform Designer" de "QUARTUS". Les principaux composants sont :

![image](https://github.com/ESN2024/CHAMBELLON_Lab1/assets/156073044/a1dd59b2-db50-4546-b379-52a1d373c903)

    LEDs : 8 LEDS.
    Button : Bouton poussoir.
    Switch : 4 boutons switchs.

On configure le bouton poussoir pour générer une interruption, et faites de même pour les switchs.

Ensuite, il faut éditer le code VHDL et ajouter les connexions et assignations de broches, compiler avec QUARTUS et charger le fichier ".sof".

Dans le main.c exécuté par le CPU, on a la méthode finale du lab1 avec l'utilisation d'une interruption pour lancer le chenillard.

Une vidéo de démonstration est disponible pour comprendre le fonctionnement :

https://github.com/ESN2024/CHAMBELLON_Lab1/assets/156073044/648a399c-63c6-4a5f-9521-3d2640bc48c4

Ce TP nous a permis de prendre en main l'utilisation de Nios2 sur le logiciel Quartus, savoir configurer des LEDs, switch et bouton, ceci à travers l'exercice de réalisation d'un chenillard.
