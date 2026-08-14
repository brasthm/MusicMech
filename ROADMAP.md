# Feuille de route

> Document de reprise, rédigé après l'analyse du dépôt en août 2026.
> Le projet est en sommeil depuis le 11 juin 2023.

## Objectif

**Une démo publique jouable.** Deux ou trois musiques dont les droits sont dégagés,
chacune en deux difficultés (classique / expert), diffusable sans restriction.

---

## Où en est le projet

Les **étapes 0, 1 et 2 sont terminées** (août 2026) : le projet compile sous Windows
(MSVC 2019 + SFML 2.6), les chorégraphies sont des fichiers `.mm` chargés au runtime,
et chaque musique peut décliner plusieurs variantes (solo / normal / expert).
Plus aucune chorégraphie n'est codée en dur.

### Ce qui fonctionne

- **Moteur de jeu** — 19 types de mécaniques, cycle de vie complet
  (`onInit` / `onApproach` / `onCheck` / `onPassed` / `onFailed` / `onFade`), système de
  ciblage générique et récursif, debuffs, arène animée multi-rectangles, timing par
  beats avec sections et checkpoints, reprise par phase avec compteur de morts.
- **Réseau** — protocole maison TCP (lobby) + UDP (positions), multi-lobbies,
  synchronisation d'horloge, ping, keepalive, RNG seedé partagé.
  **Le serveur est autoritatif** : il rejoue la chorégraphie et décide de l'échec.
- **Rendu** — formes géométriques custom, 10 shaders GLSL, carrousels, transitions.
- **Contenu** — 5 musiques libres de droits, chacune en 3 variantes (`solo` / `normal` /
  `expert`), soit 15 fichiers `.mm` dans `rc/Beatmaps/0001` à `0005`.
- **Variantes** — plusieurs `.mm` par musique : le second carrousel de la sélection
  choisit la variante, propagée au serveur via `mode` (`effectif:indexVariante`).
- **Menus** — la chaîne complète existe, du titre à l'écran de fin.

### Ce qui manque

| Manque | Impact |
|---|---|
| Aucun mode solo | 🔴 Bloquant : le jeu est injouable sans serveur |
| Écran de fin partiel (objectifs, morts, checkpoints affichés ; pas de score ni titres) | 🟡 Manque le score détaillé et l'attribution de titres |
| Titres jamais attribués | 🟠 Progression morte |
| IP serveur modifiable dans le menu, mais pas de fichier de config | 🟡 Reste à externaliser résolution, volume, plein écran |
| Musiques sous droits | ⚫ Résolu : remplacées par 5 morceaux libres de droits |

---

## Décisions

**Août 2026 — Périmètre du contenu : option A.**
La matrice « 2 difficultés × 4 effectifs (1/2/4/8 joueurs) » représentait 24
chorégraphies, soit environ 10 000 lignes à écrire à la main — plus du double de tout
le contenu jamais produit sur le projet (11 chorégraphies, ~4 400 lignes, en 13 mois
d'activité). Risque d'abandon jugé trop élevé.

**Retenu :** 3 musiques × 2 difficultés, avec **un seul effectif canonique** par
chorégraphie, plus une variante solo. Les autres effectifs seront ajoutés plus tard,
si le projet tient dans la durée.

*Conséquence technique :* le chantier « partages relatifs à l'effectif » (rendre
`nbShare` dépendant du nombre de joueurs actifs dans `Spread`, `Donut` et `Cone`) sort
du chemin critique. À reprendre le jour où les effectifs multiples reviendront au
programme.

---

## Plan

### Étape 0 — Rétablir la boucle de compilation · ✅ Terminé

MSVC 2019 (Win32) + SFML 2.6 installés, les deux cibles compilent sans erreur.
`RessourceLoader` et `DJ.h` (supprimés à tort) ont été restaurés.

### Étape 1 — Sortir les chorégraphies du code · ✅ Terminé

Les 13 chorégraphies sont exportées en `.mm`, chargées par `Game::loadFromFile` (client)
et `Lobby::load` (serveur), et `MapsCode.cpp` est supprimé. Le format `.mm` a gagné deux
sections au passage : `[RandomSequences]` (séquences aléatoires) et le champ optionnel
`colorScheme` des `SPREAD`.

### Étape 2 — Variantes classique / expert · ✅ Terminé

`beatmap_list.txt` accepte plusieurs `.mm` par identifiant
(`id|solo.mm|normal.mm|expert.mm`). `SongDatabase` expose la variante sélectionnée,
le second carrousel de `BeatmapSelection.cpp` la choisit, et la chaîne réseau `mode`
porte désormais `effectif:indexVariante` (création **et** changement de beatmap).
La variante est propagée aux autres clients via le paquet 41. Détail :
[docs/etape-2.md](docs/etape-2.md).

### Étape 3 — Mode solo · 2-3 j

Instancier `Game` sans `Client`. Double bénéfice : c'est **le banc d'essai du charting**
(pas de serveur, redémarrage instantané) *et* l'un des modes livrés dans la démo.
Développer le solo, c'est déjà produire du contenu.

### Étape 4 — Boucle d'itération pour le charting · 1-2 j

Rechargement à chaud du `.mm` et saut direct à un beat donné. Les
`//music.setPlayingOffset(sf::seconds(99));` commentés qui traînaient dans les anciennes
chorégraphies codées en dur racontent exactement la douleur à supprimer : éditer un
nombre, relancer, pour revoir quatre mesures.

Sans cette étape, écrire une chorégraphie de 500 lignes reste un supplice.

### Étape 5 — Écriture des chorégraphies

Le cœur du projet, et l'essentiel du temps. 3 musiques × 2 difficultés.

### Étape 6 — Écran de fin et titres · 2-3 j

Le commit de reprise a déjà bien avancé le chantier : l'écran de fin affiche désormais
les 3 objectifs (clear / no-hit / no-retry), le compteur de retries, les marqueurs de
mort sur la timeline et les checkpoints. Les statistiques sont collectées dans toutes
les mécaniques (distance, temps immobile, ciblages, dégâts pris, temps passé à *greed*,
participation aux partages) et `StatisticCounter::getOutlier()` sait désigner le joueur
extrême sur chaque critère. Ces données partent encore dans un `std::cout`
(`src/Game.cpp:578-590`) au lieu d'être affichées.

Reste à brancher : statistiques → attribution de titre → affichage dans l'écran de fin
→ sauvegarde dans le profil. Les 27 titres sont définis dans `src/main.h:121`.

*Volontairement après la démo : c'est du confort, pas du jouable.*

### Étape 7 — Configuration et hygiène · 1-2 j

- ~~Sortir l'IP serveur de `src/main.h`~~ → déjà fait : modifiable via le menu Réglages.
  Reste à en faire un vrai fichier de configuration.
- Options de résolution, de volume, de plein écran.
- Corriger la fuite mémoire de `Lobby` (annexe).
- Supprimer le code mort : `LobbyMenu` (232 lignes, instancié mais jamais appelé),
  l'écran `TestShadder`, le doublon `lazySong`.
- Retirer les bannières de débogage de la liste utilisateur (`src/main.h:98-100`).

---

## Chantier connexe : purger l'historique · ✅ Fait

Les musiques sous droits ont été retirées de `rc/Beatmaps/` **et de l'historique git**
(`git filter-repo` sur les anciens dossiers de beatmaps et `rc/Music/Hysteric Night
Girl.mp3`). Le dépôt ne contient plus que le contenu libre (5 morceaux,
`rc/Beatmaps/0001` à `0005`) et pèse désormais une fraction de sa taille précédente.

Les anciennes beatmaps restent disponibles localement dans `rc/OldBeatmaps/` (ignoré
par git) si besoin de référence.

---

## Annexe — Bugs identifiés à l'analyse

Aucun `TODO` ni `FIXME` n'existe dans les 22 000 lignes du projet : cette annexe tient
lieu de liste. Les trois premiers ont été corrigés pendant l'étape 1.

### 1. ✅ `TEXTINDICATOR` : le parseur lit sa cible deux fois — corrigé

`src/System/Song.cpp:239-240`

La seconde ligne a été supprimée lors de l'export. Bug fermé.

### 2. ✅ `Song::save()` n'écrit pas l'en-tête de métadonnées — corrigé

`src/System/Song.cpp:644-667`

L'en-tête (`AudioFilename`, `PreviewTime`, `Title`, `Artist`, `BackgroundImage`,
`VignetteImage`, `Difficulty`, `Players`) est désormais écrit. Bug fermé.

### 3. ✅ `MOVEARENA` : virgule manquante avant la cible — corrigé

`src/Mechanics/MoveArena.cpp:18-20`

La virgule séparatrice a été ajoutée. Bug fermé.

### 4. 🟠 Fuite mémoire côté serveur (partiellement corrigé)

`src/Network/Lobby.cpp:67` et `:296-303`

`Lobby::~Lobby()` est encore vide alors que `mechanics_` est un `std::vector<Mechanic*>`
de pointeurs bruts. La fuite à chaque `Lobby::load()` a disparu (plus de
`mechanics_.clear()` sans `delete` — `Song::load` supprime les mécaniques avant de
recharger), mais le destructeur reste à compléter.

Corollaire : `Lobby` a un constructeur de copie `= default` tout en possédant des
pointeurs bruts. Non déclenché aujourd'hui (les 50 lobbies sont pré-alloués une seule
fois), mais c'est un double-`free` en sommeil.

### 5. 🟡 Lecture de flottant non initialisé

`src/Game.cpp:90` et `:104`

`godmode_tracker` est enregistré dans la fenêtre de débogage puis déréférencé en
`*(float*)` par `DebugWindow::draw`, alors qu'il **n'est jamais assigné**.

### 6. 🟡 État *god mode* incohérent côté client

Le serveur diffuse bien son état en UDP (`src/Network/Server.cpp:411-413`) et le client
le stocke, mais la valeur renvoyée par `Client::getGodMode()` **n'est consommée nulle
part**. La variable locale `godmode` de `Game::run` (`src/Game.cpp:55`) est initialisée
à `false` et jamais mise à jour, tandis que le client force `GOD_MODE = true` au
démarrage (`MusicMech_Client/main.cpp:287`).

### 7. 🟡 Champs textuels non échappés

Le format `.mm` étant séparé par des virgules, une virgule dans un champ texte
(`TEXTINDICATOR`) ou dans un chemin d'image (`DISPLAYIMAGE`) casse le parsing. Aucun
échappement n'est prévu. Voir [mm-format.md](mm-format.md).

### 8. ✅ `TCP_Socket::obsolete_` non initialisé — corrigé (étape 2)

Le constructeur de `TCP_Socket` n'initialisait pas `obsolete_` : selon le contenu de la
mémoire, `Server::cleanup()` détruisait une connexion fraîchement acceptée, d'où des
échecs de connexion intermittents (~1 sur 2). Initialisé à `false`, et `Lobby::variant`
initialisé à `0` par la même occasion.
