# 8-puzzle

## Como compilar e executar

No terminal PowerShell dentro da pasta do projeto:

```powershell
New-Item -ItemType Directory -Force 'src/output' | Out-Null
& 'C:/mingw32/bin/g++.exe' -Wall -Wextra -g3 'src/main.cpp' 'src/puzzle.cpp' 'src/BFS.cpp' 'src/aEstrela.cpp' -I 'src/headers' -static -static-libgcc -static-libstdc++ -o 'src/output/8puzzle.exe'
```

Depois execute:

```powershell
& 'src/output/8puzzle.exe'
```
