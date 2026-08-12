# Feuille de route

> Document de reprise, rédigé après l'analyse du dépôt en août 2026.
> Le projet est en sommeil depuis le 11 juin 2023.

## Objectif

**Une démo publique jouable.** Deux ou trois musiques dont les droits sont dégagés,
chacune en deux difficultés (classique / expert), diffusable sans restriction.

---

## Où en est le projet

Dernier commit de code : `ac7209b` « I'M BACK », 11 juin 2023 — un gros push après six
mois d'interruption, qui ajoutait le menu principal, l'écran de fin, les profils, les
bannières et les shaders. Le commit suivant (`4847f57`) ne fait que nettoyer des fichiers
mal committés. Le commit `a59f560` (12 août 2026) ajoute les présents README et ROADMAP.
**Le projet s'est arrêté en plein milieu du chantier « méta-progression ».**

L'arbre de travail est propre et tout est poussé sur `origin/main`. Rien n'est perdu.

### Ce qui fonctionne

- **Moteur de jeu** — 19 types de mécaniques, cycle de vie complet
  (`onInit` / `onApproach` / `onCheck` / `onPassed` / `onFailed` / `onFade`), système de
  ciblage générique et récursif, debuffs, arène animée multi-rectangles, timing par
  beats avec sections et checkpoints, reprise par phase avec compteur de morts.
- **Réseau** — protocole maison TCP (lobby) + UDP (positions), multi-lobbies,
  synchronisation d'horloge, ping, keepalive, RNG seedé partagé.
  **Le serveur est autoritatif** : il rejoue la chorégraphie et décide de l'échec.
- **Rendu** — formes géométriques custom, 10 shaders GLSL, carrousels, transitions.
- **Contenu** — 13 chorégraphies dans `MapsCode.cpp` (33 à 1074 lignes), dont 11
  substantielles, un stub (`intoYou`, 33 lignes) et un doublon (`lazySong`).
- **Menus** — la chaîne complète existe, du titre à l'écran de fin.

### Ce qui manque

| Manque | Impact |
|---|---|
| Chorégraphies codées en dur (`MapsCode.cpp`, 4661 lignes) | 🔴 Bloquant : toute map impose un recompilation + redéploiement des deux binaires |
| Aucun mode solo | 🔴 Bloquant : le jeu est injouable sans serveur |
| Aucun système de variantes (1 musique = 1 chorégraphie) | 🔴 Bloquant pour classique/expert |
| Écran de fin partiel (objectifs, morts, checkpoints affichés ; pas de score ni titres) | 🟡 Manque le score détaillé et l'attribution de titres |
| Titres jamais attribués | 🟠 Progression morte |
| IP serveur modifiable dans le menu, mais pas de fichier de config | 🟡 Reste à externaliser résolution, volume, plein écran |
| Musiques sous droits | ⚫ Résolu par le changement de musiques |

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

### Étape 0 — Rétablir la boucle de compilation · ~1 j

Installer CMake et **SFML 2.6** (pas la 3.x, voir [README](README.md)), faire compiler
les deux cibles, corriger les éventuelles régressions de compilateur depuis 2023.
Sans ça, rien n'est vérifiable.

### Étape 1 — Sortir les chorégraphies du code · 2-3 j 🔴

**L'étape la plus importante du plan.** Écrire six chorégraphies avec un cycle
*éditer → recompiler 22 000 lignes → relancer client et serveur* est intenable.

Toute l'infrastructure existe déjà et fonctionne :

| Brique | État |
|---|---|
| Parseur `.mm` (19 types d'objets) | ✅ `src/System/Song.cpp:178-423` |
| `toString()` sur chaque mécanique | ✅ les 19 classes |
| `Song::save()` | ✅ `src/System/Song.cpp:644` |
| `Game::loadFromFile()` | ✅ écrit, mais **jamais appelé** |
| Bascule dans le jeu | ❌ `src/RoomMenu.cpp:13`, ligne commentée |

**Marche à suivre :**

1. Corriger les deux bugs de sérialisation (annexe ci-dessous) — sinon l'export est
   corrompu ou plante au rechargement.
2. Faire écrire à `Song::save()` l'en-tête de métadonnées, qu'il omet actuellement.
3. Pour chaque map : charger via `loadFromCode`, exporter via `save()`, recharger via
   `loadFromFile`, vérifier que la partie est identique.
4. Basculer `RoomMenu.cpp:12-13` sur `loadFromFile`, côté client **et** côté serveur
   (`src/Network/Lobby.cpp:304`).
5. Supprimer `MapsCode.cpp` — **seulement une fois les 13 exports validés**.

> Garder les anciennes maps comme corpus de test, même celles qu'on ne pourra pas
> diffuser : ce sont les seuls cas réels couvrant les 19 types de mécaniques.

### Étape 2 — Variantes classique / expert · 1-2 j

Aujourd'hui `rc/Beatmaps/beatmap_list.txt` associe **un seul `.mm` par identifiant** et
le champ `Difficulty:` est purement décoratif.

Version minimale suffisante pour l'option A : permettre plusieurs `.mm` par musique et
choisir lequel charger. Le branchement réseau existe déjà — la chaîne `mode` circule
client → serveur à la création du lobby **et** au changement de beatmap
(`Client::requestBeatmapChange(beatmap, mode)`). Il suffit de lui faire porter
l'identifiant de la chorégraphie en plus de l'effectif. Le second carrousel de
`BeatmapSelection.cpp` est déjà en place pour l'interface.

### Étape 3 — Mode solo · 2-3 j

Instancier `Game` sans `Client`. Double bénéfice : c'est **le banc d'essai du charting**
(pas de serveur, redémarrage instantané) *et* l'un des modes livrés dans la démo.
Développer le solo, c'est déjà produire du contenu.

### Étape 4 — Boucle d'itération pour le charting · 1-2 j

Rechargement à chaud du `.mm` et saut direct à un beat donné. Les
`//music.setPlayingOffset(sf::seconds(99));` commentés un peu partout dans
`MapsCode.cpp` racontent exactement la douleur à supprimer : éditer un nombre,
recompiler, relancer, pour revoir quatre mesures.

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

## Chantier connexe : purger l'historique

Les musiques sous droits pèsent 71 Mo dans `rc/Beatmaps/` **et sont aussi dans
l'historique git** — d'où les 293 Mo de `.git` pour un dépôt de 22 000 lignes.

Le passage aux musiques libres est le bon moment pour un `git filter-repo` : on obtient
un dépôt sain et publiable, avant de recommencer à committer du contenu. À faire
**avant** l'étape 5, pas après.

---

## Annexe — Bugs identifiés à l'analyse

Aucun `TODO` ni `FIXME` n'existe dans les 22 000 lignes du projet : cette annexe tient
lieu de liste. Les trois premiers sont sur le chemin critique de l'étape 1.

### 1. 🔴 `TEXTINDICATOR` : le parseur lit sa cible deux fois

`src/System/Song.cpp:239-240`

```cpp
int off = t.parse(5, words);
t.parse(off, words);          // ← relit au-delà de la fin de ligne
```

`TEXTINDICATOR` n'a qu'une seule cible, mais elle est parsée deux fois. Le second appel
lit `words[off]` alors que `off` pointe après la fin de la ligne → **accès hors bornes**.
Comparer avec `TETHERINDICATOR` (lignes 222-223) qui, lui, a bien deux cibles distinctes.

`TextIndicator` est utilisé **36 fois** dans les chorégraphies : ce bug plantera dès le
premier rechargement. Correctif : supprimer la seconde ligne.

### 2. 🟠 `Song::save()` n'écrit pas l'en-tête de métadonnées

`src/System/Song.cpp:644-667`

La fonction n'émet que `[Arena]`, `[TimingPoints]`, `[Checkpoints]` et `[Objects]`. Tout
l'en-tête (`AudioFilename`, `BackgroundImage`, `VignetteImage`, `PreviewTime`, `Title`,
`Artist`, `Difficulty`, `Players`) est perdu — le fichier `output.txt` à la racine du
dépôt en est la preuve, il commence directement par `[Arena]`.

Or `SongDatabase` a besoin de cet en-tête pour peupler la sélection de musiques. Sans
correctif, chaque export devra être recomplété à la main.

### 3. 🟡 `MOVEARENA` : virgule manquante avant la cible

`src/Mechanics/MoveArena.cpp:18-20`

```cpp
std::string res = "MOVEARENA," + std::to_string(beat_) + "," + std::to_string(speed_);
res += target_.to_string();   // ← pas de virgule séparatrice
```

La vitesse et le premier champ de la cible sont collés (`500.000000` + `0` →
`500.0000000`), ce qui décale d'un cran tous les champs suivants et corrompt la cible
au rechargement.

**Latent aujourd'hui** : `MoveArena` n'est utilisé dans aucune chorégraphie. À corriger
avant de s'en servir.

### 4. 🟠 Fuite mémoire côté serveur

`src/Network/Lobby.cpp:67` et `:296-303`

`Lobby::~Lobby()` est vide alors que `mechanics_` est un `std::vector<Mechanic*>` de
pointeurs bruts. Pire, `Lobby::load()` fait `mechanics_.clear()` sans `delete` avant de
réallouer. **Chaque changement de beatmap fuit toute la liste de mécaniques**, ce qui
s'accumule sur un serveur de longue durée.

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
