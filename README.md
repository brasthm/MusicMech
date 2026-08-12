# Synchrobeat (MusicMech)

Jeu de rythme coopératif en ligne : des mécaniques de raid façon MMO (partages, cônes,
donuts, liens, zones interdites) qu'il faut esquiver et résoudre en groupe, calées sur
les temps de la musique.

Le projet s'appelle `MusicMech` dans le dépôt et l'arborescence, mais **Synchrobeat**
dans le jeu lui-même (titre de la fenêtre, nom de la cible CMake du client, protocole
serveur `SYNCHROBEATSERV`).

> **État : reprise en cours.** Les étapes 0 (compilation) et 1 (chorégraphies dans des
> fichiers `.mm`) sont terminées. Le moteur, le réseau et 13 chorégraphies sont
> fonctionnels. Voir [ROADMAP.md](ROADMAP.md) pour l'état détaillé et le plan.

---

## Architecture

Deux exécutables qui **compilent tous les deux l'intégralité de `src/`** :

| Cible | Dossier | Rôle |
|---|---|---|
| `Synchrobeat` | `MusicMech_Client/` | Client de jeu (rendu, entrées, audio, menus) |
| `MusicMech_Server` | `MusicMech_Server/` | Serveur autoritatif (lobbies, synchronisation, validation) |

Le serveur **rejoue la chorégraphie de son côté** et fait autorité sur l'échec : il
simule les positions des joueurs, applique les mécaniques et décide seul du game over.
Le client n'est jamais cru sur parole.

Le code différencie les deux rôles à l'exécution via le drapeau global `IS_SERVER`
(`src/main.h`), positionné dans chaque `main.cpp`.

### Réseau

| Canal | Port | Usage |
|---|---|---|
| TCP | 41101 | Connexion, lobbies, contrôle |
| UDP | 41102 | Positions des joueurs en jeu (tick 200 ms) |
| UDP | 41103 | Login |
| UDP | 41110 | Console d'administration |

Ces valeurs, ainsi que **l'adresse IP du serveur**, sont codées en dur dans
`src/main.h`. Voir « Limitations connues » plus bas.

---

## Dépendances

- **CMake** ≥ 3.17
- Un compilateur **C++20** (GCC 11+, Clang 13+, MSVC 2019+)
- **SFML 2.5 ou 2.6** — modules `system`, `window`, `graphics`, `network`, `audio`

> ⚠️ **SFML 3.x n'est pas compatible.** La version 3.0 (2024) introduit des ruptures
> d'API majeures (énumérations scopées, `pollEvent` renvoyant un `std::optional`,
> disparition de `sf::Style::Fullscreen`). Le dépôt embarque un `FindSFML.cmake` de
> facture SFML 2.x. Installe explicitement une **2.6.x**.

Sous Debian/Ubuntu :

```bash
sudo apt install build-essential cmake libsfml-dev
```

---

## Compilation

Le client et le serveur se compilent séparément, chacun depuis son propre dossier.

**Client :**

```bash
cmake -S MusicMech_Client -B build/client -DCMAKE_BUILD_TYPE=Release && cmake --build build/client -j
```

**Serveur :**

```bash
cmake -S MusicMech_Server -B build/server -DCMAKE_BUILD_TYPE=Release && cmake --build build/server -j
```

> Vérifié sous Windows avec **Visual Studio 2019** (Win32) et **SFML 2.6** : les deux
> cibles compilent sans erreur. Sous Linux/macOS, adapter le générateur CMake.

---

## Lancement

### Ressources

Le jeu cherche ses ressources via `RessourceLoader` (musiques, polices, shaders,
beatmaps). **Le dossier `rc/` doit être accessible depuis le répertoire de travail
de l'exécutable.** Le plus simple est de lancer les binaires depuis la racine du
dépôt, ou de créer un lien symbolique vers `rc/` à côté du binaire.

### Serveur

```bash
./build/server/MusicMech_Server
```

Le serveur affiche son adresse locale et publique au démarrage, puis écoute. Il
accepte des commandes d'administration sur le port UDP 41110 (dont `GOD_MODE`, qui
bascule l'invulnérabilité pour tous les lobbies).

### Client

```bash
./build/client/Synchrobeat
```

Le client démarre **en plein écran 1920×1080** et se connecte à l'IP inscrite dans
`src/main.h`. Il faut donc y mettre l'adresse de ton serveur (ou `127.0.0.1` en local)
**et recompiler** avant de lancer.

Une console de débogage existe dans `MusicMech_Client/main.cpp` (fonction `console()`,
désactivée par défaut au profit de `game()`). Elle offre `connect`, `disconnect`,
`ip <adresse>`, `name <nom>`, `lc <lobby>`, `run`, `save`, `limit`, `port`, `shader`.
La commande `save` écrit la chorégraphie chargée dans `output.txt` au format `.mm` —
voir [mm-format.md](mm-format.md).

### Contrôles

Clavier et manette sont gérés. En jeu : déplacement, `Échap` pour la pause. La manette
utilise les axes analogiques avec zone morte (`JOYSTICK_DEADZONE` dans `src/main.h`).

---

## Organisation du dépôt

```
src/                    Code partagé client + serveur (~22 000 lignes)
├── Entity/             Joueurs, totems, gestionnaire d'entités, ciblage
├── Graphics/           Formes custom, boutons, carrousel, écran de chargement
├── Mechanics/          Les 19 mécaniques de jeu + leur classe de base
├── Network/            Client, serveur, lobbies, sockets TCP/UDP
├── System/             Chanson, timing, arène, debuffs, profils, statistiques
├── main.h              Constantes globales, IP serveur, couleurs, titres
└── *.cpp               Un fichier par écran (menus, jeu, écran de fin)

MusicMech_Client/       Cible client (main.cpp + CMakeLists)
MusicMech_Server/       Cible serveur (main.cpp + CMakeLists)
rc/                     Ressources : beatmaps (`.mm`), musiques, images, polices, shaders
refs/                   Références de conception : maquettes, palettes, storyboards
scripts/                Utilitaires (calcul de paramètres de flou)
```

---

## Limitations connues

Détail complet et plan de résolution dans [ROADMAP.md](ROADMAP.md).

- **Pas de rechargement à chaud** des `.mm` : modifier une chorégraphie nécessite de
  relancer client et serveur (plus de recompilation, mais pas de hot reload).
- **L'adresse IP du serveur est en dur** dans `src/main.h` — aucun fichier de
  configuration (mais modifiable au runtime via le menu Réglages).
- **Le mode Solo ne fait rien.** Les entrées Succès (écran d'achievements) et
  Réglages (changement d'IP serveur) sont fonctionnelles. Le multijoueur reste le
  seul mode de jeu, ce qui rend le jeu inutilisable sans serveur.
- **L'écran de fin est partiel** : il affiche les objectifs, le compteur de retries,
  les checkpoints et les marqueurs de mort, mais pas encore de score détaillé ni
  d'attribution de titres, alors que les statistiques sont collectées.
- **Options limitées** : l'IP serveur est modifiable via le menu Réglages, mais la
  résolution, le volume et le plein écran restent figés dans le code.
- **Les mécaniques de partage ne s'adaptent pas à l'effectif.** Le nombre de joueurs
  attendu dans une zone est une constante inscrite dans chaque mécanique : une
  chorégraphie écrite pour 4 joueurs est infaisable à 2 ou à 8.
- **Les musiques présentes dans `rc/Beatmaps/` sont sous droits** et ne peuvent pas
  être rediffusées.

---

## Licence

Aucune licence n'est déclarée à ce jour. Les ressources audio du dossier `rc/Beatmaps/`
appartiennent à leurs ayants droit respectifs et ne sont pas redistribuables.
