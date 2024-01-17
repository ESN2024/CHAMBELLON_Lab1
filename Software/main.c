#include <system.h>
#include <altera_avalon_pio_regs.h>
#include <sys/alt_stdio.h>
#include <alt_types.h>
#include <unistd.h>
#include <stdint.h>
#include <stdbool.h>

// Variables globales pour le chenillard
uint8_t led = 0x01;     // Variable pour stocker l'état des LEDs, initialisée à 1
uint8_t direction = -1; // 1 pour aller de gauche à droite, -1 pour aller de droite à gauche
bool launch = false;    // Indicateur pour lancer ou arrêter le chenillard

uint8_t speed = 0x00;
long udelay = 500000;

// Gestionnaire d'interruption du bouton
static void interruption_bouton(void *context, alt_u32 id)
{
    IOWR_ALTERA_AVALON_PIO_EDGE_CAP(BUTTON_BASE, 0x01);
    launch = true; // Active le chenillard
    alt_printf("interruption bouton\n");
}

// Gestionnaire d'interruption du switch
static void interruption_switch(void *context, alt_u32 id)
{
    IOWR_ALTERA_AVALON_PIO_EDGE_CAP(SWITCH_BASE, 0x0F);
    speed = IORD_ALTERA_AVALON_PIO_DATA(SWITCH_BASE);
    alt_printf("speed = %x\n", speed);
    udelay = 500000 / (speed+1);
}

// Initialisation du bouton et de l'interruption
static void initialisation_bouton(void)
{
    /* Activer les interruptions pour le bouton */
    IOWR_ALTERA_AVALON_PIO_IRQ_MASK(BUTTON_BASE, 0x01);
    /* Réinitialiser le registre de capture des fronts montants */
    IOWR_ALTERA_AVALON_PIO_EDGE_CAP(BUTTON_BASE, 0x01);
    /* Enregistrer le gestionnaire d'interruption. */
    alt_irq_register(BUTTON_IRQ, NULL, (void *)interruption_bouton);
    alt_printf("initialisation bouton\n");
}

// Initialisation du switch et de l'interruption
static void initialisation_switch(void)
{
    /* Activer les interruptions pour le switch */
    IOWR_ALTERA_AVALON_PIO_IRQ_MASK(SWITCH_BASE, 0x0F);
    /* Réinitialiser le registre de capture des fronts montants */
    IOWR_ALTERA_AVALON_PIO_EDGE_CAP(SWITCH_BASE, 0x0F);
    /* Enregistrer le gestionnaire d'interruption. */
    alt_irq_register(SWITCH_IRQ, NULL, (void *)interruption_switch);
    alt_printf("initialisation switch\n");
}

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

    // Attendre pendant un certain temps
    usleep(udelay);
}

int main(void)
{


    initialisation_bouton();
    initialisation_switch();

    alt_printf("bonjour main et init\n");

    // Boucle principale pour exécuter le chenillard en continu
    while (1)
    {
        if (launch)
        {
            chenillard(); // Appeler la fonction chenillard pour faire clignoter les LEDs
        }
    }

    return 0;
}
