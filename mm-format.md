# Le format `.mm`

Spécification du format de chorégraphie de Synchrobeat, reconstituée depuis le code.

**Sources faisant autorité :**
- Lecture : `src/System/Song.cpp:96-429` (`Song::load`)
- Écriture : `src/System/Song.cpp:644-667` (`Song::save`) et les `toString()` des mécaniques
- Cibles : `src/Entity/EntityManager.cpp:61-92` (`Target::to_string` / `Target::parse`)
- Métadonnées : `src/System/SongData.cpp:11-47` (`SongDatabase`)

> ⚠️ Le format est **hérité d'osu!** (`.osu`) et en garde des traces, notamment des
> champs de `[TimingPoints]` qui ne sont jamais lus.

---

## Vue d'ensemble

Un fichier `.mm` est un fichier texte composé d'un en-tête `clé:valeur`, puis de quatre
sections entre crochets. Les valeurs des sections sont **séparées par des virgules**.

```
AudioFilename:audio.mp3
BackgroundImage:bg.jpg
VignetteImage:vignette.png
PreviewTime:150120
Title:Ai Kotoba IV feat. Hatsune Miku
Artist:DECO*27
Difficulty:12
Players:2
[Arena]
0,0,1000,1000
[TimingPoints]
552,431.655,4,2,1,60,1,0
[Checkpoints]
0,0
18,48
[Objects]
SPREAD,4.000000,1,120.000000,8.000000,0,0.000000,0,0,0,300.000000,200.000000,0,NULL
ENDMAP,274.000000
```

### ⚠️ L'ordre des sections est imposé

`Song::load` avance dans une liste séquentielle et **ne revient jamais en arrière** :

```
AudioFilename:  →  [Arena]  →  [TimingPoints]  →  [Checkpoints]  →  [Objects]
```

Une section placée hors de cet ordre est **silencieusement ignorée**, sans erreur. Les
autres clés d'en-tête (`Title`, `Artist`…) peuvent en revanche apparaître n'importe où
avant `[Arena]` : elles sont lues séparément par `SongDatabase`.

Côté serveur, `Song::load` est appelé avec `music == nullptr` et la séquence démarre
directement à `[Arena]` — `AudioFilename` n'y est pas attendu.

---

## En-tête

Lu par `SongDatabase` pour peupler l'écran de sélection. Une clé par ligne, sans espace
autour du `:`.

| Clé | Type | Usage |
|---|---|---|
| `AudioFilename` | chemin | Fichier audio, **relatif au dossier du `.mm`**. Seule clé lue par `Song::load`. |
| `BackgroundImage` | chemin | Fond affiché en jeu et sur l'écran de fin |
| `VignetteImage` | chemin | Miniature du carrousel de sélection |
| `PreviewTime` | entier (ms) | Position de départ de l'extrait joué dans les menus |
| `Title` | texte | Titre affiché |
| `Artist` | texte | Artiste affiché |
| `Difficulty` | entier | **Purement décoratif.** Affiché, jamais interprété. |
| `Players` | entier | Effectif prévu. Ne fait que pré-positionner le sélecteur de mode. |

> 🐛 `Song::save()` **n'écrit pas cet en-tête** — il ne produit que les quatre sections.
> Tout export doit être recomplété à la main tant que ce n'est pas corrigé
> (voir [ROADMAP.md](../ROADMAP.md), annexe 2).

---

## `[Arena]`

Un rectangle de plancher jouable par ligne. L'arène est l'union de ces rectangles ; un
joueur qui en sort échoue.

```
left,top,width,height
```

Toutes les valeurs sont des flottants, dans le repère de l'arène — **1000 × 1000 par
défaut** (`ARENA_WIDTH` / `ARENA_HEIGHT` dans `src/main.h`), indépendamment de la
résolution d'affichage.

---

## `[TimingPoints]`

Définit la conversion millisecondes ↔ beats. Format osu! à 8 champs, dont **trois
seulement sont lus** :

```
offset,beatLength,meter,sampleSet,sampleIndex,volume,uninherited,effects
   ↑       ↑                                              ↑
  lu       lu                                             lu
```

| Champ | Index | Description |
|---|---|---|
| `offset` | 0 | Position du point de timing, en millisecondes |
| `beatLength` | 1 | Durée d'un beat, en millisecondes (`60000 / BPM`) |
| `uninherited` | 6 | **Seules les lignes valant `1` sont retenues.** Les autres sont ignorées. |

Les champs 2, 3, 4, 5 et 7 sont des reliquats d'osu! sans effet. `Song::save()` écrit
systématiquement `,4,2,1,60,1,0` pour les combler.

Plusieurs points de timing sont possibles : `Song::getCumulativeNBeats` cumule les beats
segment par segment, ce qui gère les changements de tempo.

---

## `[Checkpoints]`

Points de reprise après un échec. Une phase par ligne :

```
timestamp,beat
```

| Champ | Type | Description |
|---|---|---|
| `timestamp` | flottant (**secondes**) | Position de reprise dans l'audio |
| `beat` | flottant | Beat auquel l'état de jeu est réinitialisé |

⚠️ Le `timestamp` est en **secondes** alors que `[TimingPoints]` est en **millisecondes**.

En pratique le `timestamp` est placé légèrement **avant** le beat correspondant, pour
laisser au joueur une mesure de reprise avant que les mécaniques redémarrent.

Le nombre de checkpoints détermine le nombre de phases affichées à l'écran d'échec
(« FAIL - Phase 3/7 »).

---

## `[Objects]`

Une mécanique par ligne, le premier champ étant son type.

```
TYPE,champ1,champ2,...,<cible>[,<cible2>]
```

Après chargement, les objets sont **triés par beat croissant**, l'ordre du fichier n'a
donc pas d'importance.

### Champs communs

| Champ | Description |
|---|---|
| `beat` | Beat de résolution de la mécanique (flottant, toujours en position 1) |
| `active` | Durée du télégraphe **en beats** : combien de temps la zone est annoncée avant de se résoudre |
| `nbShare` | Nombre de joueurs devant être dans la zone. La validation est une **égalité stricte** : `nbIn == nbShare` |
| `debuff` | Debuff appliqué à la résolution (voir table plus bas), `0` pour aucun |
| `debuffDuration` | Durée du debuff, en beats |

> ⚠️ `nbShare` est une **constante inscrite dans chaque objet**. C'est ce qui rend une
> chorégraphie dépendante d'un effectif précis : écrite pour 4 joueurs, elle est
> infaisable à 2 ou à 8.

### Les 19 types d'objets

Tous les types de mécaniques concrètes du moteur sont sérialisables — la couverture est
complète. `<cible>` désigne un bloc de 7 champs ou plus, décrit à la section suivante.

#### Zones de dégâts

| Type | Champs |
|---|---|
| `SPREAD` | `beat, nbShare, radius, active, debuff, debuffDuration, <cible>` |
| `DONUT` | `beat, nbShare, distMin, distMax, active, debuff, debuffDuration, <cible>` |
| `CONE` | `beat, nbShare, width, distance, active, debuff, debuffDuration, <centre>, <ancre>` |
| `NOPEZONE` | `beat, nbShare, width, height, active, <cible>` |

`SPREAD` est un disque de rayon `radius`. `DONUT` est une couronne entre `distMin` et
`distMax`. `CONE` est un secteur d'angle `width` et de portée `distance`, orienté du
`<centre>` vers l'`<ancre>`. `NOPEZONE` est un rectangle.

#### Liens

| Type | Champs |
|---|---|
| `TETHER` | `beat, minDist, active, inward, continu, <ancre1>, <ancre2>` |
| `TETHERINDICATOR` | `beat, active, color, <ancre1>, <ancre2>` |

`inward` et `continu` sont des booléens (`0` / `1`). `inward` inverse la contrainte : le
lien doit être raccourci au lieu d'être étiré. `TETHERINDICATOR` est purement visuel.

#### Entités et effets

| Type | Champs |
|---|---|
| `MOVE` | `beat, speed, isInstant, <entité>, <destination>` |
| `DEBUFF` | `beat, debuffType, duration, <cible>` |
| `ACTIVATE` | `beat, val, radius, color, <cible>` |
| `TEXTINDICATOR` | `beat, active, color, texte, <cible>` |
| `DISPLAYIMAGE` | `beat, chemin, active, <cible>` |

`ACTIVATE` fait apparaître ou disparaître un totem (`val` : `1` = actif). `color` est un
entier RGBA non signé (ex. `4285098751`).

#### Arène

| Type | Champs |
|---|---|
| `ADDARENA` | `beat, x, y, width, height` |
| `REMOVEARENA` | `beat, index` |
| `CLEARARENA` | `beat` |
| `MOVEARENA` | `beat, speed, <cible>` |
| `ROTATEARENA` | `beat, angle, speed` |
| `ZOOMARENA` | `beat, val, speed` |
| `SNAPARENA` | `beat, active, <cible>` |

> 🐛 `MOVEARENA` est actuellement **cassé à l'écriture** : il manque une virgule avant la
> cible (voir [ROADMAP.md](../ROADMAP.md), annexe 3). Latent — aucune chorégraphie ne
> l'utilise.

#### Fin de map

| Type | Champs |
|---|---|
| `ENDMAP` | `beat` |

**À placer dans toute chorégraphie.** En son absence, `Game::loadFromFile` émet
`Warning : no EndMap` et déduit la fin de la durée du fichier audio, ce qui décale
l'écran de fin.

---

## Les cibles

Une cible occupe **7 champs**, et peut en référencer une autre de façon récursive.

```
timing,type,team,pos.x,pos.y,id,NULL
timing,type,team,pos.x,pos.y,id,TARGET,<cible imbriquée>
```

Le dernier champ vaut `NULL` (pas de cible imbriquée) ou le littéral `TARGET`, suivi
immédiatement des 7 champs de la cible imbriquée — et ainsi de suite sans limite de
profondeur.

| Champ | Description |
|---|---|
| `timing` | Quand la position est évaluée |
| `type` | Comment la cible est désignée |
| `team` | `0` = joueurs, `1` = totems |
| `pos.x`, `pos.y` | Coordonnées, **ou** paramètres de séquence (voir ci-dessous) |
| `id` | Index de l'entité visée, pour `type = 1` |

### `timing` — `TargetTiming`

| Valeur | Nom | Comportement |
|---:|---|---|
| `0` | `TARGET_ONINIT` | Position figée à l'apparition de la mécanique |
| `1` | `TARGET_ONBEAT` | Position réévaluée au moment de la résolution |
| `2` | `TARGET_FOLLOW` | Position suivie en continu — la zone poursuit sa cible |

### `type` — `TargetType`

| Valeur | Nom | Signification |
|---:|---|---|
| `0` | `TARGET_POS` | Position absolue, lue dans `pos.x` / `pos.y` |
| `1` | `TARGET_ENTITY` | Entité d'index `id` dans l'équipe `team` |
| `2` | `TARGET_RANDOMSEQUENCE` | Entité tirée d'une séquence aléatoire partagée |
| `3` | `TARGET_CLOSEST` | Entité la plus proche de la cible imbriquée |
| `4` | `TARGET_FURTHEST` | Entité la plus éloignée de la cible imbriquée |

⚠️ Les types `3` et `4` **exigent une cible imbriquée** (`TARGET,...`) : c'est par rapport
à elle que la distance est calculée. Avec `NULL`, la résolution renvoie `nullptr`.

### `TARGET_RANDOMSEQUENCE` : `pos` change de sens

Pour `type = 2`, les champs `pos.x` et `pos.y` ne sont **pas des coordonnées** :

- `pos.x` — index de la séquence aléatoire
- `pos.y` — rang à lire dans cette séquence

Une séquence est une permutation aléatoire des entités, **calculée par le serveur et
diffusée à tous les clients**, ce qui garantit que tout le monde voit la même
répartition. Deux objets pointant la même séquence avec des rangs différents désignent
donc deux entités distinctes — c'est le mécanisme d'attribution de rôles.

```
Séquence 0, rang 0  →  2,0,0,0.000000,0.000000,0,NULL
Séquence 0, rang 1  →  2,0,0,0.000000,1.000000,0,NULL
```

---

## Table des debuffs

`DebuffType`, défini dans `src/System/Debuff.h:16`.

| Valeur | Nom | |  Valeur | Nom |
|---:|---|---|---:|---|
| `0` | `DEBUFF_NONE` | | `6` | `DEBUFF_HAATO` |
| `1` | `DEBUFF_ROOT` | | `7` | `DEBUFF_GAADO` |
| `2` | `DEBUFF_CRITICAL` | | `8` | `DEBUFF_EYE1` |
| `3` | `DEBUFF_SUDDENDEATH` | | `9` | `DEBUFF_EYE2` |
| `4` | `DEBUFF_MASK1` | | `10` | `DEBUFF_EYE3` |
| `5` | `DEBUFF_MASK2` | | `11` | `DEBUFF_EYER` |

Les valeurs `6` à `11` sont spécifiques à des chorégraphies précises (Third Eye ya!,
Doggy god's street) et affichent des icônes dédiées.

---

## Pièges

**Aucun échappement.** Le séparateur est la virgule, et rien ne la protège. Une virgule
dans un `texte` de `TEXTINDICATOR` ou dans un `chemin` de `DISPLAYIMAGE` décale tous les
champs suivants et corrompt la ligne.

**Aucune validation.** Un type inconnu est ignoré en silence ; un champ manquant produit
un accès hors bornes, donc un plantage ou pire. Le parseur fait confiance à son entrée.

**Les lignes vides sont tolérées**, ainsi que les fins de ligne Windows (`\r`).

**Les flottants sont écrits avec six décimales** par `std::to_string`. C'est verbeux mais
sans conséquence : la relecture par `std::stof` est exacte à la précision utile.

**Le `Difficulty` n'a aucun effet mécanique.** Deux chorégraphies de difficultés
différentes sont deux fichiers distincts, sans lien entre eux dans le moteur actuel.

---

## Générer un `.mm` depuis le code existant

Tant que les chorégraphies vivent dans `src/MapsCode.cpp`, l'export se fait par la
console de débogage du client (`console()` dans `MusicMech_Client/main.cpp`) :

```
>> save
```

Cette commande appelle `Game::load()` puis `Game::save("output.txt")`. Le fichier
`output.txt` à la racine du dépôt est un vestige de cette manipulation.

⚠️ Avant de s'en servir pour la migration, corriger les bugs 1 à 3 de l'annexe de la
[feuille de route](../ROADMAP.md) : sans quoi l'en-tête est perdu et le rechargement
plante sur le premier `TEXTINDICATOR`.
