# STM32L475 Baremetal montage partant de rien.

ce dépot est une initiation au barre metal afin dàidéla communauté 

## intallation de la tool chain arm-none-eaby-
## Outils de débug
  La carte de développement intègre une sonde JTAG, ce qui est bien pratique. Elle est disponible sur le connecteur de la figure ci-dessus appelé "USB Débug" (!). Plus exactement, ce connecteur USB vous donne accès à deux choses :

    la sonde JTAG intégrée
    un port série sur USB, vu sous Linux comme /dev/ttyACM0 (115200 baud, pas de parité, 8 bits, pas de contrôle de flux)

La sonde JTAG intégrée native est une sonde STLink V2.1.  Nous avons reflashé ces sondes de façon à ce qu'elles se comportent comme des sondes JLink de Segger, qui comptent parmi les sondes les plus efficaces du marché et vous offrent des possibilités de débug qui vous seront bien utiles dans la suite du TP.

Comme pour toutes les sondes JTAG, nous devrons utiliser un "driver" pour faire le pont entre gdb et la sonde. Ce driver s'appelle JLinkGDBServer ou JLinkGDBServerExe en version graphique. Il est disponible [ici](https://www.segger.com/downloads/jlink/#J-LinkSoftwareAndDocumentationPack) (pour ceux qui souhaitent travailler sur leur portable). Ce "driver" est installé sur toutes les stations de la A406. Il est aussi disponible dans les paquets de la distribution ArchLinux. Si votre carte n'est reconnue que lorsque vous êtes root, c'est que vous avez probablement oublié d'installer les règles udev nécessaires 
## Pilotage de la sonde
créer un .gdinit qui sera exécuté à chaque lancement de arm-none-eabi-gdb.
```.gdbinit
target ext :2331
mon endian little
mon halt

# interface with asm, regs and cmd windows
define split
  layout split
  layout asm
  layout regs
  focus cmd
end

# interface with C source, regs and cmd windows
define ss
  layout split
  layout src
  layout regs
  focus cmd
end

define flash
  dont-repeat
  mon reset
  load
end

# Usefull function when the processor is in hardfault to see
# where it comes from.
define armex
  printf "EXEC_RETURN (LR):\n",
  info registers $lr
    if ($lr & 0x4)
      printf "Uses MSP 0x%x return.\n", $MSP
      set $armex_base = $MSP
    else
      printf "Uses PSP 0x%x return.\n", $PSP
      set $armex_base = $PSP
    end

    printf "xPSR            0x%x\n", *($armex_base+28)
    printf "ReturnAddress   0x%x\n", *($armex_base+24)
    printf "LR (R14)        0x%x\n", *($armex_base+20)
    printf "R12             0x%x\n", *($armex_base+16)
    printf "R3              0x%x\n", *($armex_base+12)
    printf "R2              0x%x\n", *($armex_base+8)
    printf "R1              0x%x\n", *($armex_base+4)
    printf "R0              0x%x\n", *($armex_base)
    printf "Return instruction:\n"
    x/i *($armex_base+24)
    printf "LR instruction:\n"
    x/i *($armex_base+20)
end

document armex
ARMv7 Exception entry behavior.
xPSR, ReturnAddress, LR (R14), R12, R3, R2, R1, and R0
end
```
Une fois que vous avez ce .gdbinit en place (pensez à le committer), tout ce que vous avez à faire est :

   1.flash, pour charger le programme sur le processeur.
    Si vous avez défini un ENTRY point dans votre script de link, gdb positionne automatiquement le PC à la bonne valeur
   2.cont pour démarrer le programme.
   
## Création d'un exécutable
1. Création d'un script de link avec le code (.text .rodata .isr_vector) logé en flash les variables globales (.data, .bss) sont logé en ram 
2. Création d'un chargeur qui seras écrit en assembleur qui va contenir la fonction qui seras le point d'entré de notre PC pour le gdb. cette fonction va faire les opŕation de copie entre la flash et les SRAM ensuite va appelé le main on définira un point de sortie. La nécéssité ici est de pouvoir manipuler les rǵistres du cortex M4.
3. Un fichier startup qui contiendras les fonction nécessaire à la copie et la définition de la table de vecteur 
4. le fichier main.c seras le fichier qui exécute notre application.

## Configuration d'un GPIO
1. activation de l'horloge du GPIO dans le registe RCC relié au bus AHB1
2. Définir le mode GPIO_MODER
3. Utiliser le GPIO_BSRR pour écride da le GPIO_ODR pour des outputs ou lire dans le idr dans le cas des inputs
(lire la doc de ref)

## IRQ
1.Bien definir la table de vecteur
``` c
void *vector_table[] = {
    // Stack and Reset Handler
    &_stack,            /* Top of stack */
    _start,             /* Reset handler */

    // ARM internal exceptions
    NMI_Handler,        /* NMI handler */
    HardFault_Handler,  /* Hard Fault handler */
    MemManage_Handler,
    BusFault_Handler,
    UsageFault_Handler,
    0,                  /* Reserved */
    0,                  /* Reserved */
    0,                  /* Reserved */
    0,                  /* Reserved */
    SVC_Handler,        /* SVC handler */
    0,                  /* Reserved */
    0,                  /* Reserved */
    PendSV_Handler,     /* Pending SVC handler */
    SysTick_Handler,    /* SysTick hanlder */

    // STM32L475 External interrupts
    WWDG_IRQHandler,         /* Watchdog IRQ */
    PVD_PVM_IRQHandler,      /* ... */
    TAMP_STAMP_IRQHandler,   /* ... */
    ...
```

2. les étapes de l'activation des EXTI sont 
  * configuration de la ligne avec SYSCF (en fonction du pin)
  * configuration de la ligne entant que interruption ou alors un évênement EXTI_IM
  * Configuration du front déclancheur RTS et FTSR......
  * la conftion de la table de vecteur 









