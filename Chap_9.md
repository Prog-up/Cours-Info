Chapitre 9 : Bases de données
===
# 1. Concepts élémentaires
## 1.1. Introduction aux bases de données

---
### 1.1.1. Introduction
De nombreuses applications infomratiques manipulent de grandes quatités de données qui doivent être organsées et stockées de sorte qu'il est possible de les traiter efficacement pour :
- en ajouter
- en retirer
- en extraire de l'information

Ce traitement doit pouvoir se faire de manière concurente tout en préservant l'intégrité des données.

---
### 1.1.2. Système de gestion de bases de données (SGBG) et paradigme logique
Préserver l'intégriter des données est une tache complexe dans un contexte d'accès concurrents donc le traitement des données sera confié à un outil appelé `SGBD` dont le rôle est de recevoir les requêtes des utilisateurs :
- moddification des données
- extraction d'information à partir de ces données

Et de les traduire en des opérations effectuées sur la base de données. C'est au SGBD de garantir la cohérence des données au fur et à mesure des opérations réalisése. Les requêtes prennent en général la forme d'un description du résultat attendu sans indication sur la manière de calculer. C'est le SGBD qui implémente la recherche du résultat.

C'est le principe du `paradigme logique` : un programme est une description des propriétés que doit satisfaire le résultat. Un résultat est un jeu de paramètres qui satisfait les propiétés. Il n't a pas aucune indication sur la manière de claculer les résultats.

Pour que cela fonctionne, la plupart des SGBD s'appuient sur un modèle introduit dans les années 1970, appelé `modèle relationnel`.

---
### 1.1.3. Le modèle relationnel
- Le `modèle relationnel` est un modèle mathématique basé sur la théorie des ensembles et la logique des prédicats et qui présente les bases de données comme des objets qui définissent des relations entre des blocs d'information. C'est un modèle abstrait qui s'exprime indépendamment des implémentations possible et qui crouvre donc de nombreux SGBD.
- Dans ce modèle, une base de données est vue comme un ensemble de relations. Ces relations sont aussi appelées tables car on peut les représenter par des tableaux à double entrée dont les colonnes correspondent à un type d'information particulier. Ces colonnes sont appelées les attributs de la relation.

  **Exemple :**
  Dans une système d'information d'une bibliothèque, on peut avoir une table `Document` dont les attributs sont :
  - le titre
  - l'auteur
  - le genre
  - la date de parution
  - le nombre de pages
  - etc

- Chaque attribut est associé à un domaine qi correspond à l'ensemble des valeurs possibles par l'attribut. Ce domaine permet de choisir un type pour implémenter concrètement la base de données.

  Étant donné une relation $\mathrm{R}$ dont les attributs sont $\mathrm{A}_1\dots \mathrm{A}_n$ associés aux domaines $\mathrm{D}_1\dots \mathrm{D}_n$, on appelle `schéma relationnel` de $\mathrm{R}$ l'association des attributs et des domaines notée $\mathrm{R}(\mathrm{A}_1:\mathrm{D}_1,\dots,\mathrm{A}_n:\mathrm{D}_n)$.

  **Exemple :**
  Pour la table `Document` :
  - le titre et l'auteur sont des *données textuelles*
  - le genre est trié d'une *énumération finie* (roman, poésie, théâtre ...)
  - la date de parution est une *date*
  - le nombre de pages est un *entier*

  d'où le schéma relationnel : 
  ```
  Document(titre:texte, auteur:texte, genre:enum(roman...), date_de_parution:date, nombre_de_pages:entier)
  ```

  Le domaine "texte" peut être par exemple associé au type string des chaînes de caractères et le domaine entier au type int.

- Les lignes d'une relation de schéma $\mathrm{R}(\mathrm{A}_1:\mathrm{D}_1,\dots,\mathrm{A}_n:\mathrm{D}_n)$ correspondent aux éléments de la relation $\mathrm{R}$, qui est un sous-ensemle de $\mathrm{D}_1\times\dots\times\mathrm{D}_n$. On appelle don ces éléments des `tuples` ou des `enregistrements`.

  **Exemple :**
  Pour la table `Document` :

  | titre | auteur | genre | date de parution | nombre de pages |
  |:-:|:-:|:-:|:-:|:-:|
  | La cousine Bette | Honoré de Balzac | Roman | 1848 | $\color{green}{240}$ |
  | De la guerre | Carl van Clauservitz | Traité | 1832 | $\color{green}{240}$ |
  | Cyrano de Bergerac | Edward Rostant | Théâtre | 1897 | $280$ |

  **Remarque :**
  Certains enregistrements peuvent coïncider pour certains attributs et on veut une manière efficace de les distinguer
  - On appelle `clé candidate` un ensemble minimal (pour l'inclusion) d'attributs permettent de caractériser de manière unique chaque enregistrement, i.e. tel qu'il n'existe pas deux enregistrements qui coïncident sur tous les attributs de la clé.

  **Exemple :**
  Pour la table Document, {titre, auteur} devrait convenir.

  Il peut y avoir plusieurs clés candidates et on doit en choisir une, appelée `clé primaire`. On souligne dans le schéma relationnel les attributs de la clé primaire pour les repérer efficacement

  **Remarque :**
  On choisit souvent d'ajouter un attribut entier pour numéroter les enregistrements, que l'on choisit comme clé primaire.
  - Dans une relation $\mathrm{R}$, on appelle `clé étrangère` un ensemble d'attributs qui constitue une clé candidate (souvent primaire) d'une autre relation.

  **Exemple :**
  Dans une table `Emprunts` décrivant les emprunts de la bibliothèque, on intègre la clé de la table `Document` pour identifier les documents empruntés.

---
### 1.1.4. Algèbre relationnelle
L'algèbre relationnelle est une théorie mathématique qui décrit les opérations que l'on peut réalister sur une base de données du point de vue du modèle relationnel. Les propriétés qui découlent de cette théorie définissent un fondement rigoureux aux implémentation de SGBD en justifiant les optimisations des requêtes des utilisateurs. Cette théorie est `H.P` mais nous l'étudirons via le langage de requêtes `SQL` (Structured Query Language).

---
## 1.2. Le langage SQL : requête élémentaire

---
### 1.2.1. Gestion du contexte :
- choix de la base de donnée : 
  ```SQL 
  USE <nom_base>;
  ```
- obtention du schéma relationnel d'une table :
  ```SQL
  DESCRIBE <nom_table>;
  ```

**Exemple :**

```SQL
USE bibliotheque;
DESCRIBE Document;
```

Les opérations de création / suppression / modification de bases de données / de tables sont `H.P`.

---
### 1.2.2. Opération de projection
Pour visualiser le contenu d'une table, on utilise la requête :
```SQL
SELECT * FROM <nom_table>;
```
C'est un cas particulier de l'opération de projection qui permet de construire une table ne contenant les valeurs des tuples que pour certains attributs.

**Attention :**
La table construite par une requête est éphémère.

**Syntaxe :**
```SQL
SELECT <attribut_1>,...,<attribut_2> FROM <nom_table>;
```

**Exemple :**
```SQL
SELECT titre, date_de_parution FROM Document;
```

**Remarque :**
Cette requête peut créer une table contenant des doublons qui sont conservés par défault. On utilise le mot-clé `DISTINCT` pour éliminer ces doublons.

**Exemple :**
```SQL
SELECT DISTINCT titre, date_de_parution FROM Document;
```
Les enregistrements du résultat d'une projection sont a priori rangés dans le même ordre que dasn la table initiale.

On peut choisir de les réordonner en utilisant le mot-clé `ORDER BY` suivi d'une liste d'attributs.

L'ordre associé à cette liste est l'ordre croissant lexicographique.

**Exemple :**
```SQL
SELECT * FROM Document;
ORDER BY auteur, date_de_parution;
```

Pour utiliser l'ordre décroissant selon l'un des attributs, on utilise le mot-clé `DESC` après le nom de l'attribut.

**Exemple :**
```SQL
SELECT * FROM Document;
ORDER BY  auteur, date_de_parution DESC;
```

**Attention :**
`DESC` ne porte que sur un seul attribut $\rightarrow$ le répéter si besoin.

Il est aussi possible de renommer les attributs du résultat d'une projection, ce qui peut être nécéssaire dans des opérations plus complexes, faisant intervenir des sous-requête ou plusieurs yables. On utilise pour cela le mot-clé `AS`.

**Exemple :**
```SQL
SELECT titre, auteur, date_de_parution AS date 
FROM Document;
```
On peut combiner tout cela :
```SQL
SELECT titre, date_de_parution AS date 
FROM Document
ORDER BY date DESC, titre;
```