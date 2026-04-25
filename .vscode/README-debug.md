# Debug STM32L475 dans VS Code

Utilise la configuration:

```text
Debug STM32L475 (make connect + flash)
```

La sequence lance:

1. `make`
2. `make connect`
3. `gdb-multiarch test.elf`
4. `source .gdbinit`
5. `flash`
6. `continue`

Les boutons de debug de VS Code restent ensuite disponibles:

- Continue / pause
- Step over
- Step into
- Step out
- Restart
- Stop
- Breakpoints dans la marge de l'editeur
