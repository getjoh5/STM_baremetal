# STM32L475 bare metal

Ce dépôt est une initiation au développement bare metal sur STM32L475. L'objectif est de partir d'un projet minimal, sans HAL, pour comprendre le démarrage du microcontrôleur, le script de link, la table des vecteurs, la configuration des GPIO, la gestion des interruptions et l'utilisation d'un timer matériel comme base de temps applicative.

## Matériel cible

- Carte STM32L475.
- Sonde ST-Link V2.1 intégrée, utilisée ici comme sonde J-Link Segger.
- Port série USB exposé sous Linux, généralement `/dev/ttyACM0`.

Configuration série typique :

- 115200 bauds
- 8 bits
- pas de parité
- pas de contrôle de flux

## Prérequis

Installer les outils suivants :

- `arm-none-eabi-gcc`
- `arm-none-eabi-as`
- `gdb-multiarch` ou `arm-none-eabi-gdb`
- `JLinkGDBServer`
- Python 3 avec `Pillow`, utilisé par l'outil de conversion d'image ST7789.

Le serveur J-Link est disponible dans le pack officiel Segger : <https://www.segger.com/downloads/jlink/#J-LinkSoftwareAndDocumentationPack>

Si la carte n'est accessible qu'en `root`, vérifier l'installation des règles `udev` pour la sonde.

## Compilation

Compiler le firmware :

```sh
make
```

Les fichiers principaux générés sont :

```text
test.elf
final.map
```

`test.elf` est le firmware compilé. `final.map` est généré automatiquement par
le linker grâce à l'option `-Wl,-Map=final.map`; il permet de vérifier le
placement des fonctions, variables et sections en mémoire.

Nettoyer les fichiers générés :

```sh
make clean
```

## Debug et flash

Dans un premier terminal, lancer le serveur J-Link :

```sh
make connect
```

Dans un second terminal, lancer GDB :

```sh
make debug
```

Créer un fichier `.gdbinit` à la racine du projet pour automatiser la connexion et le flash :

```gdb
target ext :2331
mon endian little
mon halt

define flash
  dont-repeat
  mon reset
  load
end
```

Commandes GDB utiles :

```gdb
flash
cont
```

- `flash` charge le programme sur la carte.
- `cont` démarre ou reprend l'exécution.
- `layout split`, `layout asm` et `layout regs` sont utiles pour afficher le code et les registres pendant le debug.

## Organisation du projet

- `Makefile` : règles de compilation, nettoyage, debug et connexion J-Link.
- `linker.lds` : description mémoire et placement des sections.
- `bootloader.s` : point d'entrée assembleur `_start`.
- `startup_file.c` : table des vecteurs, handlers faibles, initialisation mémoire et `Reset_handler`.
- `startup_filel.h` : déclarations utilisées par le code de démarrage.
- `main.c` : point d'entrée applicatif.
- `drivers/gpio.c/.h` : driver GPIO bas niveau pour les LED et les lignes de controle SPI.
- `drivers/Timer.c/.h` : driver TIM2 et SysTick bas niveau, avec une resolution de 1 ms.
- `drivers/spi.c/.h` : driver SPI1 bas niveau, avec transmission bloquante et transmission DMA.
- `drivers/dma.c/.h` : configuration de DMA1 Channel3 pour les transferts SPI1_TX en 8 bits.
- `firmware/led_service.c/.h` : couche applicative pour le service LED.
- `firmware/timer_service.c/.h` : service applicatif de temporisation non bloquante base sur TIM2.
- `Application.c/.h` : couche applicative principale, ecran de demarrage, messages et barre de chargement.
- `Application_def.h` : constantes, messages et etapes de l'application.
- `ST7789-STM32-master/ST7789/` : driver ST7789, fontes et tableaux d'images RGB565.
- `tools/generate_st7789_image.py` : conversion d'une photo PNG/JPG en tableau C RGB565 240x240.
- `tools/StartImage.c` : image RGB565 240x240 utilisee comme fond de l'ecran de demarrage.
- `button_configuration.c/.h` : configuration du bouton et des interruptions associées, conservée comme code d'exemple.
- `cmsis/` : en-têtes CMSIS pour le STM32L4.

Le `Makefile` compile actuellement :

- `startup_file.c`
- `main.c`
- `drivers/gpio.c`
- `drivers/Timer.c`
- `drivers/dma.c`
- `drivers/spi.c`
- `firmware/led_service.c`
- `firmware/timer_service.c`
- `ST7789-STM32-master/ST7789/st7789.c`
- `ST7789-STM32-master/ST7789/fonts.c`
- `Application.c`
- `tools/StartImage.c`
- `bootloader.s`

Le symbole `STM32L475xx` est défini à la compilation afin que `stm32l4xx.h`
inclue automatiquement les définitions propres au STM32L475.

## Démarrage du programme

Le démarrage suit cette séquence :

1. Le processeur lit le pointeur de pile initial et l'adresse du reset handler dans la table des vecteurs.
2. `_start`, défini dans `bootloader.s`, appelle `Reset_handler`.
3. `Reset_handler` initialise la mémoire :
   - copie des données initialisées vers la SRAM ;
   - mise à zéro de la section `.bss`.
4. `_start` appelle `main`.
5. `main` configure les périphériques puis entre dans la boucle principale.

## Script de link

Le script `linker.lds` décrit les régions mémoire du STM32L475 :

- `flash` : code et constantes ;
- `sram1` : variables globales et statiques ;
- `sram2` : pile.

Les sections principales sont :

- `.text` : table des vecteurs et code ;
- `.rodata` : données constantes ;
- `.data` : variables initialisées ;
- `.bss` : variables non initialisées, remises à zéro au démarrage.

## Configuration d'un GPIO

La configuration d'un GPIO suit généralement ces étapes :

1. Activer l'horloge du port GPIO dans `RCC`.
2. Configurer le mode du pin avec `GPIOx_MODER`.
3. Configurer les options nécessaires : pull-up/pull-down, vitesse, type de sortie.
4. Pour une sortie, écrire via `GPIOx_BSRR` ou `GPIOx_ODR`.
5. Pour une entrée, lire via `GPIOx_IDR`.

Toujours vérifier les registres dans la documentation de référence du STM32L475.

## Base de temps TIM2 et SysTick

Le projet conserve TIM2 comme compteur libre 32 bits et configure aussi SysTick
comme base de temps partagee avec le service timer. La configuration est faite
dans `drivers/Timer.c` :

- activation de l'horloge TIM2 via `RCC->APB1ENR1`;
- arrêt du timer pendant la configuration;
- `PSC = 3999`;
- `ARR = 0xFFFFFFFF`;
- remise à zéro de `CNT`;
- génération d'un update event avec `TIM2->EGR = TIM_EGR_UG`;
- démarrage du compteur avec `TIM_CR1_CEN`.
- configuration de SysTick pour generer une interruption periodique;
- incrementation de `GlobalSystick` dans `SysTick_Handler`.

Avec une horloge timer de 4 MHz, le prescaler donne :

```text
4 MHz / (3999 + 1) = 1000 Hz
```

TIM2 avance donc à 1000 ticks par seconde. Le service timer utilise maintenant
`GlobalSystick` comme source de temps; un tick vaut 1 ms, et une durée de
`1000` ticks correspond à `1000 ms`, soit 1 seconde.

Le service `firmware/timer_service.c` ne configure pas le timer matériel. Il
reçoit seulement l'adresse du compteur, par exemple `&GlobalSystick`, puis
compare la valeur courante avec une valeur capturée au dernier reset. La
comparaison utilise une soustraction unsigned :

```c
(*sourceTimer - CaptureValue) >= ResetValue
```

Cette forme reste correcte même lorsque le compteur 32 bits déborde et revient
à zéro.

## SPI1, DMA et ST7789

Le driver SPI1 fonctionne en trames de 8 bits. Les commandes ST7789 et les
petits buffers sont envoyes avec `spi_write()`, en mode bloquant classique.
Les gros buffers de donnees passent par `spi_write_dma()`, qui configure le
transfert DMA, active `SPI_CR2_TXDMAEN`, attend le flag de fin DMA puis attend
que le SPI ait termine physiquement l'envoi.

La configuration DMA est initialisee une fois depuis `spi_init()` :

- `DMA1_Channel3` est utilise pour `SPI1_TX`;
- la direction est memoire vers peripherique;
- l'incrementation memoire est activee;
- `PSIZE` et `MSIZE` restent en 8 bits, alignes avec la taille de trame SPI;
- `dma_spi_tx_start_u8()` recharge seulement l'adresse source et la taille du
  prochain transfert.

Dans le driver ST7789, `ST7789_WriteData()` choisit automatiquement entre SPI
bloquant et SPI DMA selon la taille du buffer. Les transferts de moins de
`DMA_MIN_SIZE` octets restent en SPI bloquant, afin d'eviter le cout de
preparation DMA pour quelques octets de commande ou de parametres.

Pour le remplissage plein ecran, le projet n'utilise pas de framebuffer complet
240x240. Il utilise un petit buffer `disp_buf` de `ST7789_WIDTH * HOR_LEN`
pixels. Avec `HOR_LEN = 5`, cela represente 5 lignes de l'ecran, soit 2400
octets pour un ecran 240x240 en RGB565. Le buffer est rempli avec la couleur
demandee, puis envoye plusieurs fois par DMA jusqu'a couvrir toute la hauteur
de l'ecran.

## Couche Application

Le module `Application.c` regroupe la sequence de demarrage visible par
l'utilisateur. La fonction principale est :

```c
int App_init(Application_t *app, volatile uint32_t *Tim);
```

Elle verifie les pointeurs d'entree, initialise l'ecran ST7789, affiche l'image
de fond `StartImage`, initialise le service timer applicatif, puis affiche une
petite sequence de bienvenue et une barre de chargement.

Comme le firmware est linke avec `-nostdlib`, `Application.c` utilise un helper
local `app_copy_string()` au lieu de `strcpy()`. Cela evite de dependre de la
libc tout en gardant les messages termines par `'\0'`.

Pour effacer un texte transparent sans detruire l'image de fond, le module
utilise `restore_photo_area()`. Cette fonction restaure une zone depuis
`StartImage` ligne par ligne, car une sous-zone d'une image 240x240 n'est pas
stockee comme un bloc compact en memoire.

La barre de chargement utilise les constantes definies dans `Application.h` :

```c
#define BAR_X      0
#define BAR_Y      221
#define BAR_W      240
#define BAR_H      18
#define BAR_BORDER WHITE
#define BAR_FILL   WHITE
```

Le remplissage est fait par tranches : le code calcule la largeur deja affichee
et ne dessine que la nouvelle partie de la barre, afin de reduire le nombre de
pixels envoyes sur SPI.

## Blink LED 1 seconde

`main.c` initialise les GPIO, TIM2 et le service timer. La LED de démarrage
signale que l'initialisation s'est bien passée, puis la boucle principale
bascule `LED_USER` toutes les secondes :

```c
timer_reset_serv(&oTimer, 1000);

while(1){
    if(timer_expired_serv(&oTimer) == 1){
        /* Toggle LED_USER. */
        timer_reset_serv(&oTimer, 1000);
    }
}
```

Cette logique est non bloquante : il n'y a plus de boucle d'attente logicielle
pour créer le délai. Le processeur peut donc continuer à exécuter d'autres
tâches dans la boucle principale entre deux expirations du timer.

## Preparation SPI1

Le projet contient un driver SPI1 bas niveau utilise par l'ecran ST7789.
`drivers/spi.c` configure SPI1 en maitre, transmission MOSI seule, trames 8
bits et ordre MSB first. La configuration des broches est faite dans
`drivers/gpio.c` :

- PA5 : `SPI1_SCK` en fonction alternative AF5;
- PA7 : `SPI1_MOSI` en fonction alternative AF5;
- PA3 : ligne `Data/Command` en sortie GPIO;
- PA4 : ligne `Reset` en sortie GPIO.

Les fonctions `GPIO_PA3_ON/OFF` et `GPIO_PA4_ON/OFF` permettent de piloter les
lignes de controle depuis les couches plus hautes.

## Ecran ST7789 240x240

Le firmware initialise l'ecran avec `ST7789_Init()`, puis affiche un tableau
RGB565 240x240 avec :

```c
ST7789_DrawImage(0, 0, 240, 240, (uint16_t*)StartImage);
```

Le tableau `StartImage` est defini dans `tools/StartImage.c`. Un tableau
complet 240x240 occupe environ 115 Ko en flash, car il contient `240 * 240`
pixels de 16 bits.

## Convertir une photo pour l'ecran

L'outil `tools/generate_st7789_image.py` convertit une image PNG/JPG en tableau
C RGB565 240x240. Il corrige l'orientation EXIF, recadre l'image au centre en
format carre, redimensionne en 240x240, puis genere les valeurs RGB565.

Pour remplacer directement l'image de fond affichee par l'application :

```sh
tools/generate_st7789_image.py photo.jpg --replace tools/StartImage.c --byteswap
```

`--byteswap` est adapte au driver actuel, car `ST7789_DrawImage()` transmet le
buffer `uint16_t` directement sur SPI depuis une architecture little-endian. Si
les couleurs apparaissent inversees ou incoherentes sur l'ecran, refaire un
essai sans cette option :

```sh
tools/generate_st7789_image.py photo.jpg --replace tools/StartImage.c
```

Pour generer un fichier C separe sans modifier `fonts.c` :

```sh
tools/generate_st7789_image.py photo.jpg -o StartImage.c
```

## Interruptions

Pour utiliser une interruption :

1. Déclarer le handler dans la table des vecteurs.
2. Configurer le périphérique qui déclenche l'interruption.
3. Configurer la ligne EXTI si l'interruption vient d'un GPIO :
   - sélectionner le port dans `SYSCFG`;
   - démasquer la ligne dans `EXTI_IMR`;
   - choisir le front déclencheur avec `EXTI_RTSR` et/ou `EXTI_FTSR`.
4. Activer l'interruption dans le NVIC.
5. Dans le handler, traiter l'événement puis effacer le pending bit.

Exemple simplifié de table des vecteurs :

```c
void *vector_table[] = {
    &_stack,
    _start,
    NMI_Handler,
    HardFault_Handler,
    MemManage_Handler,
    BusFault_Handler,
    UsageFault_Handler,
    0,
    0,
    0,
    0,
    SVC_Handler,
    0,
    0,
    PendSV_Handler,
    SysTick_Handler,
    WWDG_IRQHandler,
    PVD_PVM_IRQHandler,
    TAMP_STAMP_IRQHandler,
};
```
