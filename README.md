# STM32L475 bare metal

Ce dépôt est une initiation au développement bare metal sur STM32L475. L'objectif est de partir d'un projet minimal, sans HAL, pour comprendre le démarrage du microcontrôleur, le script de link, la table des vecteurs, la configuration des GPIO et la gestion des interruptions.

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

Le serveur J-Link est disponible dans le pack officiel Segger : <https://www.segger.com/downloads/jlink/#J-LinkSoftwareAndDocumentationPack>

Si la carte n'est accessible qu'en `root`, vérifier l'installation des règles `udev` pour la sonde.

## Compilation

Compiler le firmware :

```sh
make
```

Le binaire généré est :

```text
test.elf
```

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
- `main.c` : point d'entrée applicatif.
- `pripherique_config.c/.h` : configuration des périphériques.
- `button_configuration.c/.h` : configuration du bouton et des interruptions associées.
- `cmsis/` : en-têtes CMSIS pour le STM32L4.

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
