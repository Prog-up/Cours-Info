# Cours Info
## 2. Ensembles inductifs, indution structurelle
### 2.1. Définition par induction
### 2.1.1. Définition (système de règle d'inférence)
Un système de règle d'inférence est donnée par un ensemble d'assertion (propriétés) et de règles pour démontrer ces assertions (on parle de règle d'inférence). Une règle d'inférence est donnée par un ensemble de $n \in \mathbb{N}$ prémisses (hypothèses de la règle) et par une assertion qu'on appelle la conclusion. On note une telle règle : <u>prémise$_{1}$, premise$_{2}$, ..., prémise$_{n}$</u> : conclusin.

Si n = 0, on parle d'axiome.

### 2.1.2 Exemple
Avec l'assertion : "être un entier naturel" peut définir les règles

(1)

### 2.1.3 Définition (dérivation)
Étant donnéun système de règle d'inférences, assertion est dite dérivable si elle est la conclusion d'un axiome ou d'une règle dot les prémisses sont dérivables.

On appelle (arbre de) dérivation l'ensemble des règles utilisés pour dériver une assertion.

### 2.1.4. Exemple
On ajoute un opérateur + et la règle (2)

On peut alors dériver l'assertion : S (S0) + S0 est un entier naturel

(3)

### 2.1.5. Définition (ensemble indicatif)
Un ensemble indicatif est un ensemble défini par induction, est le plus petit ensemble (au sens de l'incusion) engendré par un système de règles d'inférence (avec l'assertion "appartenir à cet ensemble")

### 2.1.6. Exemple
On définit inductivement l'ensemble Expr des expressions arithmétiques sur les entiers naturels par :

(4)

### 2.1.7. Remarque
On procède de manière analogue à la définition d'un type somme récurcif en OCaml en associant une règle à chaque constructeur de type : si le constructeur n'a pas d'argument, alors il correspond à un axiome, sinon la règle qui  lui correspond à pour prémise l'appartienne des arguments à leurs types respectifs.

```OCaml
type expr =
|Not of int
|Plus of expr * expr
|Moins of expr * expr
|Mult of expr * expr
and nat =
|Zero
|S of nat
```
>prouteuh
