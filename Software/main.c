#include <system.h>
#include <altera_avalon_pio_regs.h>
#include <sys/alt_stdio.h>
#include <alt_types.h>
#include <unistd.h>
#include <stdint.h>

// Variables globales pour le chenillard
uint8_t led = 0x01;     // Variable pour stocker l'état des LEDs, initialisée à 1
uint8_t direction = -1; // 1 pour aller de gauche à droite, -1 pour aller de droite à gauche

// Fonction pour faire clignoter les LEDs
void chenillard(void)
{
    // Mettre à jour l'état des LEDs
    IOWR_ALTERA_AVALON_PIO_DATA(LEDS_BASE, led);

    // Inverser la direction lorsque l'une des extrémités est atteinte
    if (led == 0x01 || led == 0x80)
        direction = -direction;

    // Déplacer la séquence de LED vers la gauche (direction == -1) ou la droite (direction == 1)
    led = (direction == 1) ? led << 1 : led >> 1;

    // Attendre pendant un certain temps (100 000 microsecondes)
    usleep(100000);
}

int main(void)
{
    // Boucle principale pour exécuter le chenillard en continu
    while (1)
    {
        chenillard(); // Appeler la fonction chenillard pour faire clignoter les LEDs
    }

    return 0;
}
