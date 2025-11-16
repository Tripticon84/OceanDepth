# OceanDepths

## But du jeu
OceanDepths est un roguelite textuel d’exploration sous-marine. Vous partez de la base en surface et descendez par paliers de 50 m pour explorer les zones, affronter des créatures, récupérer des perles (monnaie) et améliorer votre équipement.

- Chaque déplacement vers une zone plus profonde consomme de l’oxygène (coût croissant avec la profondeur).
- Explorer une case peut lancer un combat (zones hostiles), ouvrir la boutique (⛵), ou récompenser (zones sûres comme les grottes).
- L’objectif est de progresser le plus profondément possible en gérant santé, oxygène et fatigue.

Contrôles principaux sur la carte:
- Z/Q/D/S + flèches: se déplacer dans la zone et entre les zones
- E: explorer la case
- R: retour surface (base)
- I: inventaire
- S: sauvegarder (depuis la base)
- X: retour au menu

## Installation et exécution
Prérequis:
- Windows: MinGW-w64 (gcc) + make (via MSYS2/Chocolatey) ou équivalent
- macOS/Linux: gcc/clang + make

Compilation:
```bash
# Créer le dossier d’objets (si besoin)
mkdir -p obj
# Compiler
make
```

Exécution:
```bash
./oceandepth    # (ou .\oceandepth.exe sous Windows)
```

Notes:
- Le Makefile compile automatiquement tous les fichiers `src/**/*.c` et crée `oceandepth` à la racine.
- Si vous utilisez PowerShell sans make global, lancez via MSYS2 MinGW64 ou ajoutez `C:\msys64\mingw64\bin` au PATH.

## Sauvegarde/Chargement
- Depuis la carte, appuyez sur `S` à la base pour ouvrir le menu de sauvegarde.
- `Charger partie` est accessible depuis le menu principal.

## Répartition du travail
- Yann:
  - Combats (actions des joueurs)
  - Map (navigation, génération, exploration)
  - Sauvegarde (écran et logique de slots)
  - Monstres (génération/équilibrage)

- Loris:
  - Inventaire
  - Boutique (Shop)
  - Menu (écran titre)
  - Assemblage global des features entre elles

## Structure du projet
- `src/`
  - `menu/`: écran principal
  - `map/`: génération des zones, navigation, règles d’exploration
  - `combat/` et `display_combat/`: logique et affichage des combats
  - `inventory/`: gestion des items et équipements
  - `save/`: sauvegarde/chargement
  - `monster/`: types de monstres et utilitaires
  - `utils/`: fonctions utilitaires (affichage, saisie, aléatoire)
- `docs/displays/`: maquettes ASCII des écrans

Bon jeu !