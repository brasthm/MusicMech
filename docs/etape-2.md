# Étape 2 — Variantes classique / expert

> ✅ **Terminé.** Feuille de route détaillée initialement préparée pour planifier
> l'étape 2, désormais implémentée. Contexte : `ROADMAP.md`, étape 2.

---

## 1. État constaté (vérifié dans le code)

- `rc/Beatmaps/beatmap_list.txt` : format `id|fichier.mm`, **une seule ligne, un seul
  `.mm` par identifiant**.
- `SongData::mmpath` est une **chaîne unique** (`src/System/SongData.h`). Le champ
  `Difficulty:` est lu mais purement décoratif.
- La chaîne réseau `mode` circule déjà client → serveur :
  - création de lobby : `Client::requestLobbyCreation(name, beatmap, mode)` → état TCP 10
  - changement de beatmap : `Client::requestBeatmapChange(beatmap, mode)` → état TCP 25
  - côté serveur, `mode` est converti par `std::stoi(mode)` pour fixer `Lobby::limit`
    (`src/Network/Server.cpp:738` et `:1234`).
- **L'interface est déjà partiellement implémentée** dans `src/BeatmapSelection.cpp` :
  - `saucisse2` (second carrousel) est construit, coloré et rempli avec `addData("2P", "2 Players")`
    / `addData("4P", "4 Players")` ;
  - mais son `update` et son `draw` sont **commentés** (`//saucisse2.update(...)`,
    `//saucisse2.draw(...)`) ;
  - le gestionnaire de la touche `W` (et du bouton manette 2) est **vide** ;
  - la ligne d'aide annonce déjà `"W: change mode"`.
- Le serveur et le client partagent la même classe `SongDatabase` (tout `src/` est
  compilé dans les deux exécutables), donc la logique de variante ne s'écrit qu'une fois.

---

## 2. Décisions à valider avant de coder

### D1 — Format de `beatmap_list.txt`

Une ligne par musique, **N colonnes `.mm` séparées par `|`** :

```
<id>|<variante1.mm>|<variante2.mm>|...
```

Exemple (pour test, avant l'étape 5) :

```
30328|Bruno Mars - The Lazy Song [classique].mm|Bruno Mars - The Lazy Song [expert].mm
```

- Le format actuel `id|fichier.mm` (1 seule variante) **doit rester valide** : une ligne
  à 2 colonnes = une seule variante. Pas besoin de migrer les 13 lignes tout de suite.
- Libellé de la variante : lire une nouvelle clé d'en-tête **`Variant:`** dans le `.mm`
  (ex. `Variant:Classique` / `Variant:Expert`). Si absente, retomber sur le nom de
  fichier sans l'extension.

### D2 — Codage réseau du `mode`

Garder les signatures existantes `(name, beatmap, mode)` et **encoder les deux
informations dans `mode`** :

```
<effectif>:<indexVariante>   ex. "4:0", "8:1"
```

- `effectif` = `Players:` de la variante choisie (c'est déjà ce qui est envoyé aujourd'hui).
- `indexVariante` = position dans le vecteur de variantes de la chanson.

Le serveur coupe sur `:`, utilise la partie gauche pour `limit` et la droite pour choisir
le `.mm`. Aucun changement de signature côté `Client`.

> Alternative plus « propre » mais plus invasive : ajouter un 4ᵉ champ `variant` aux
> paquets 10 et 25. Rejeté pour l'instant : la feuille de route globale demande le
> minimum suffisant, et `mode` est le canal prévu à cet effet.

---

## 3. Découpage en tâches

### T1 — Modèle de données (`src/System/SongData.h`, `SongData.cpp`)

- Remplacer `SongData::mmpath` (string) par un vecteur de variantes :

  ```cpp
  struct SongVariant {
      std::string mmpath;    // chemin relatif du .mm
      std::string label;     // "Classique", "Expert"…
      std::string difficulty;// Difficulty: du .mm
      std::string nbPlayers; // Players: du .mm
  };
  std::vector<SongVariant> variants;
  ```

- Garder les champs `name/artist/image/vignette/id/songpath/preview` en tête de chanson
  (lus une seule fois sur la **première** variante, identiques pour les autres).
- `SongDatabase` :
  - parser N colonnes ; pour chaque variante, ouvrir le `.mm` et lire l'en-tête
    (`Variant:`, `Difficulty:`, `Players:`) jusqu'à `[TimingPoints]` ;
  - ajouter `selectedVariant_` + `getSelectedVariant()` / `setSelectedVariant(int)` ;
  - `getSelectedPath()` → `"Beatmaps/" + id + "/" + variants[selectedVariant_].mmpath` ;
  - `getCurentNbPlayers()` → `variants[selectedVariant_].nbPlayers`.

**Critère :** compile, et `getSelectedPath()` retourne le bon fichier selon la variante.

### T2 — Interface de sélection (`src/BeatmapSelection.cpp`)

- Remplacer les `addData("2P", ...)` / `addData("4P", ...)` par les libellés de variantes
  lus depuis `songs` (`Classique` / `Expert`).
- Décommenter `saucisse2.update(elapsedTime)` et `saucisse2.draw(window)`.
- Câbler la touche `W` (et bouton manette 2) pour basculer `saucisse2.left()/right()`.
- Quand le carrousel s'arrête (`!saucisse2.isMoving()`), appeler
  `songs->setSelectedVariant(saucisse2.getIndex())` et rafraîchir `difficultyText` /
  `nbPlayers`.
- Initialiser `saucisse2` sur `songs->getSelectedVariant()` (actuellement pré-positionné
  sur le nombre de joueurs).
- Mettre à jour la ligne `info` (`W` = variante, `Z` = aléatoire).

**Critère :** le second carrousel est visible, on navigue entre deux variantes au clavier
et à la manette, l'affichage Difficulté/Joueurs se met à jour.

### T3 — Codage/décodage du `mode` (`RoomCreation.cpp`, `RoomMenu.cpp`, `Server.cpp`, `Lobby.h`)

- Côté client, aux deux points d'envoi, remplacer `getCurentNbPlayers()` par :

  ```cpp
  songs.getCurentNbPlayers() + ":" + std::to_string(songs.getSelectedVariant())
  ```

  - `src/RoomCreation.cpp` (création, appel `request(...)`) ;
  - `src/RoomMenu.cpp:229` (changement de beatmap).

- Côté serveur :
  - état 10 (`Server.cpp:738`) : couper `mode` sur `:`, `limit = stoi(gauche)`,
    stocker `variant = stoi(droite)` ;
  - état 25 (`Server.cpp:1234`) : idem, en plus de l'existant ;
  - ajouter un champ public `sf::Uint8 variant` (ou `int`) à `Lobby`
    (`src/Network/Lobby.h`).

**Critère :** un salon créé avec « 4:1 » reçoit `limit=4` et `variant=1`.

### T4 — Chargement côté serveur (`Server.cpp` état 20)

Au démarrage de partie (`Server.cpp:961`), avant `load(...)` :

```cpp
songs_.setSelectedById(lobbies_[lobbyIndex].beatmap);
songs_.setSelectedVariant(lobbies_[lobbyIndex].variant);
lobbies_[lobbyIndex].load(songs_.getSelectedPath());
```

**Critère :** le serveur charge le `.mm` de la bonne variante (log `Mechanics number`
cohérent).

### T5 — Propagation aux autres clients

- État 41 « GET LOBBY CONTENT » (`Server.cpp:1365-1367`) : ajouter `variant` après
  `beatmap` dans le paquet.
- `Client::requestLobbyInfo` (`Client.cpp:665-675`) : lire ce champ et le stocker dans
  `Lobby` (le même `Lobby` est partagé client/serveur via `Network/Lobby.h`).
- Appliquer la variante reçue :
  - `RoomMenu.cpp` (bloc de refresh, ~ligne 375) : en plus de `setSelectedById(...)`,
    appeler `songs->setSelectedVariant(client->getCurrentLobby().variant)` ;
  - `LobbySelection.cpp:261` (à l'entrée d'un salon) : idem.

**Critère :** un joueur non-créateur qui rejoint un salon affiche la bonne variante, et la
voit changer quand le créateur la modifie.

### T6 — Vérification de bout en bout

1. Compiler les deux cibles (voir `README.md`).
2. Créer une chanson de test avec **deux `.mm`** dans un dossier (copier un `.mm`
   existant, ajouter `Variant:Classique` / `Variant:Expert` et deux `Players:` distincts
   si besoin) et ajouter sa ligne multi-colonnes à `beatmap_list.txt`.
3. Scénario : sélectionner la variante dans le carrousel → créer un salon → lancer →
   vérifier côté client (`Mechanics number`) et côté serveur (mêmes logs) que le bon
   `.mm` est chargé.
4. Tester le changement de variante par le créateur et sa propagation au second client.

---

## 4. Points de vigilance

- **`SongDatabase` unique côté serveur** : `setSelectedById` / `setSelectedVariant`
  doivent être appelés **juste avant** `load()`, jamais à la création du lobby, sinon
  deux lobbies se marchent dessus (pattern déjà en vigueur aujourd'hui).
- **`saucisse2` n'a que 2 emplacements** (1 grand + 1 petit, `nbRight_ = 1`). Parfait
  pour 2 variantes ; à revoir si on veut plus de 2 variantes un jour.
- **Rétro-compatibilité du format** : une ligne `id|fichier.mm` (une seule variante) doit
  continuer de fonctionner, avec `selectedVariant_ = 0` par défaut.
- **`getCurentNbPlayers()`** est utilisé ailleurs (pré-positionnement du carrousel,
  couleur du `beatmapFond` dans `RoomCreation`) : vérifier que ces usages suivent bien la
  variante sélectionnée après T1/T2.
- Le champ `mode` est aussi affiché/lu dans `RoomCreation` (texte « NP ») : aucun conflit
  attendu, mais ne pas oublier qu'il ne contient plus seulement un entier.
