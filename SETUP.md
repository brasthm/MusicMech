# Installer le projet sur un nouveau poste

Récapitulatif pour repartir de zéro. Tout le code et le contenu du jeu sont dans git ;
seules les dépendances système sont à réinstaller.

## 1. Prérequis à installer

| Outil | Version | Notes |
|---|---|---|
| Git | récent | pour cloner |
| Visual Studio | 2019 ou 2022 | charge de travail « Développement Desktop en C++ » |
| CMake | ≥ 3.17 | à mettre dans le PATH |
| SFML | **2.6.x** | ⚠️ pas 3.x (API incompatible). Télécharger depuis sfml-dev.org |

Le dépôt embarque déjà `cmake_modules/FindSFML.cmake` : il suffit que SFML soit
installé à un emplacement standard (ou que `SFML_ROOT` pointe dessus).

## 2. Récupérer le dépôt

```bash
git clone https://github.com/brasthm/MusicMech.git
cd MusicMech
```

## 3. Fichiers locaux NON suivis (optionnel)

Ces fichiers ne sont **pas** dans git (volontairement). À recopier à la main depuis
l'ancien poste si besoin :

- `rc/OldBeatmaps/` (74 Mo) — anciennes beatmaps sous droits, référence locale.
- `PROFILE*.dat` — sauvegardes de profils (régénérées en jouant).

## 4. Compiler

Depuis la racine du dépôt :

```bash
cmake -S MusicMech_Client -B build/client -A Win32
cmake --build build/client --config Release

cmake -S MusicMech_Server -B build/server -A Win32
cmake --build build/server --config Release
```

Résultat :

- Client : `build/client/Release/Synchrobeat.exe`
- Serveur : `build/server/Release/MusicMech_Server.exe`

## 5. Lancer

Toujours depuis la **racine du dépôt** (le dossier `rc/` doit être accessible) :

```bash
./build/server/Release/MusicMech_Server.exe
./build/client/Release/Synchrobeat.exe
```

Le client démarre sur une **console de débogage** : taper `run` pour lancer le jeu
(`console()` est le point d'entrée actuel dans `MusicMech_Client/main.cpp`).

## 6. Configuration

- **IP du serveur** : dans `src/main.h`, `SERVER_IP` (défaut `127.0.0.1`). Modifier puis
  recompiler — ou la changer au runtime via le menu Réglages.
- Ports (TCP 41101, UDP 41102/41103, admin 41110) : codés en dur dans `src/main.h`.

## 7. Pièges connus

- **SFML 3.x ne compile pas** : installer explicitement une 2.6.x.
- Le client utilise `console()` par défaut (`game()` est commenté) : ne pas oublier
  `run` au prompt `>>`.
- Sous Linux/macOS, adapter le générateur CMake (le projet est vérifié sous
  Windows/MSVC).
