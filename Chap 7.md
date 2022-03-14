# **Chapitre 7 : Élément d'algorithmes**
# Intro
A la manière de la recherche d'un élément dans un ABR, on s'intéresse à la décomposition d'un problème en un ou plusieurs sous-problèmes.

**On distingue plusieurs méthodes selon :**
- le type de problème à résoudre ;
- la manière dont on décompose le problème ;
- la manière dont on reconstruit la solution au problème à partir de celles des sous-problèmes. 

**Nous étudierons :**
- la méthode `diviser pour régner` ;
- la programmation dynamique ;
- les algorithmiques gloutons.

# Diviser pour régner
## Méthode et premiers exemples
### Méthode
**La méthode `diviser pour régner` se décompose en 3 étapes :**
- Diviser le problème en un ou plusieurs sous-problèmes `disjoints` ;
- Résoudre les sous-problèmes, soit récursivement, soit directement si le sous-problème est assez simple ;
- Reconstruire la solution au problème initial à partir de celles des sous-problèmes.

### Remarque
On retrouve l'idée des principes d'induction, où l'on utilise l'hypothèse d'induction (la solution à un sous-problème) pour démontrer la propriété sur une instance plus grande (le problème initial).

### Complexité des algorithmes *diviser pour régner*
**Cette méthode donne une relation de récurrence de la forme :**

$\mathcal C(n) = C_{\text{décomposition}}(n) + \sum_{p\ \text{sous-problèmes}} \mathcal C(\lvert p\rvert) + C_{\text{reconstruction}}(n)$

(ici, $\lvert p\rvert$ désigne la taille du problème $p$).

L'enjeux est de trouver des manières peu coûteuses de décomposer / reconstruire et d'obtenir peu de sous-problèmes assez petits pour avoir une complexité meilleure que celle de la résolution naïve du problème.

### Exemple : Tri fusion
(chap 1, 3.1.4)

**Problème :** 
On veut trier une liste.

**Algorithme :**
- Diviser : on décompose la liste en 2 listes de tailles égales à une unité près ;
- Résoudre : on trie récursivement les 2 listes, sauf si elles sont de taille $\le 1$ (déjà triées)
- Reconstruire : on fusionne les 2 listes triées en une liste.

**Récurrence :**
$\mathcal C(n) = \mathcal O(n) + \mathcal C(\lfloor\frac n 2\rfloor) + \mathcal C(\lceil\frac n 2\rceil) + \mathcal O(n)$.

Donc $\mathcal O(n \log n)$.

### Exemple : Exponentiation rapide
(TD_04)

**Problème :** 
Calcul de $x^n$.

**Algorithme :**
- Diviser : on veut calculer $x^{\frac n 2}$ ;
- Résoudre : appel récursif, ou si $\frac n 2 = 0$, on renvoit 1 ;
- Reconstruire : si $n \equiv 0\ [2]$, on calcule $x^{\frac n 2} \times x^{\frac n 2}$, sinon on calcule $x \times x^{\frac n 2} \times x^{\frac n 2}$.

**Récurrence :**
$\mathcal C(n) = \mathcal O(1) + \mathcal C(\frac n 2) + \mathcal O(1)$.

Donc $\mathcal O(\log n)$.

### Exemple : Recherche dichotomique
(TD_06)

**Problème :** 
On veut déterminer si une valeur apparaît dans un tableau trié.

**Algorithme :**
- Diviser : on s'intéresse à la moitié gauche ou droite du tableau selon la comparaison de la valeur recherchée avec l'élément au milieu du tableau ;
- Résoudre : appel récursif sauf si le sous-tableau est de taille $\le 1$ ou si l'élément au milieu est la valeur recherché ;
- Reconstruire : la solution au sous-problème est la solution au problème initial.

**Récurrence :**
$\mathcal C(n) = \mathcal O(1) + \mathcal C(\frac n 2)$.

Donc $\mathcal O(\log n)$.

### Exemple : Tri rapide (colle 01)
**Problème :** 
Trier une liste.

**Algorithme :**
- Diviser : on choisit un élément `pivot` et a réparti la liste en 2 sous-listes (celles des éléments) $<$ au pivot et celle des éléments $>$ pivot) et on compte le nombre d'occurrences du pivot ;
- Résoudre : appel réc sauf si la liste est de taille $\le 1$ ;
- Reconstruction : on concatène les 2 sous-listes triées (dans le bon ordre) en plaçant entre les 2 le nb d'occurrence du pivot.

**Récurrence :**
$\mathcal C(n) = \mathcal O(1) + \mathcal C(q) + \mathcal C(r) + \mathcal O(p + q)$

où
$
   \left|
      \begin{array}{l}
         \text{p est le  nombre d'occurences du pivot}
         \\
         \text{q est le nombre d'éléments < pivot}
         \\
         \text{r est le nombre d'éléments > pivot}
      \end{array}
      \right.
$

Avec un choix déterministe en temps constant du pivot (ex : le premier élément), on a :
- $\mathcal O(n^2)$ dans le pire cas ;
- $\mathcal O(n\log n)$ dans le meilleur cas.

## Application : Calcul de la médiane
### Problème
On veut calculer la médiane d'une liste de  valeurs distinctes, c'est-à-dire l'élément de rang $\lfloor\frac{n}{2}\rfloor$ où le rang d'un élément est le nb d'élément qui lui sont stric inférieur.

### Solution naïve
On trie la liste et on renvoie l'élément au milieu.

**Complexité :** 
$\mathcal O(n \log (n))$ (ex : avec le tri fusion).

**Objectif :** 
$\mathcal O(n)$ (optimal puisqu'on doit bien lire tous les élément)/

### Généralisation et algorithme "diviser pour régner"
On s'intéresse au problème suivant : trouver l'élément de rang i, où i est un paramètre.

**Algorithme :** 
On s'inspire du tri rapide
- Diviser : on choisit un pivot p et on détermine les listes $l_<$ et $l_>$ des éléments strictement inférieurs/supérieurs à p ;
- Résoudre : cela dépend de la taille de $l_<$
   - si $\lvert l_<\rvert > i$, alors on cherche l'élément de rang i dans $l_<$
   - si $\lvert l_<\rvert = i$, alors p est l'élément de rang i
   - si $\lvert l_<\rvert < i$, alors on cherche l'élément de rang $i-\lvert l_<\rvert -1$ dans $l_>$ ;
- Reconstruire : l'élément de rang i est le résultat de la résolution du sous-problème.

**Récurrence :** $\mathcal C(n) = \mathcal O(n) +C_{\text{choix du pivot}}(n) + \left|
      \begin{array}{l}
         \mathcal C(q)
         \\
         \text{ou}
         \\
         \mathcal O(1)
         \\
         \text{ou}
         \\
         \mathcal C(r)
      \end{array}
      \right.
$ selon la taille de $l_<$, avec les notations de 2.1.7.

**Dans le pire cas :** comme pour le tri rapide $\mathcal O(n^2)$, par exemple si on choisit le $1^{er}$ élément comme pivot et si le tab est trié et $i=n-1$.

**Dans le meilleur cas :** le pivot est l'élément de rang i ~> $\mathcal O(n)$.

**Conclusion :** le choix du pivot est déterminant. On peut se rapprocher du meilleur cas de tri rapide en choisissant un pivot près de la médiane. On peut s'approcher de la médiane (que l'on cherche à calculer), à moindre coût à l'aide de l'algorithme de la médiane des médianes.
### Algorithme de la médiane des médianes
**Idée :** on regroupe les élément de la liste en petits paquets (de taille constante) dont on peut calculer les médianes naïvement, et on choisit comme pivot la médiane de ces médianes, calculée récursivement.

**Complexité :** $\mathcal C(n) = \underbrace{\mathcal O(n) + \mathcal C{\dfrac n 5}}_{\text{calcul du pivot}} + \underbrace{\mathcal O(n)}_{\text{division}} + \underbrace{f(n)}_{\text{éventuel appel récursif}}$

On peut majorer la valeur de $f(n)$ en majorant les tailles des listes $l_<$ et $l_>$.

On s'intéresse à $l_<$ (le cas $l_>$ se traite de manière similaire).

Observons le $\frac{n}{5}$ médianes des paquets. Parmi celles-ci, il y en a à la moitié qui sont inférieures à p.

Dans le pire cas : tous les éléments des $\frac{n}{10}$ paquets de ces médianes sont inférieurs à p.

Dans les autres paquets, il y a au plus 2 élément inférieur à p (car la médiane et les 2 éléments qui lui sont supérieur soit inférieur à p).

Au total, il y a au plus $5\times{\frac{n}{10}}+2\times{\frac{n}{10}}=\frac{n}{2}+\frac{n}{5}=\frac{7n}{10}$ éléments dans $l_<$.

Donc $\mathcal C(n)\le \mathcal C(\frac{n}{5})+\mathcal C(\frac{7n}{10})+\mathcal O(n)$.

En pratique, sous les approximations, on montre qu'il existe $\mathcal c>0$, tel que $\forall n ,\mathcal C(n)\le cn + C(\lfloor\frac n 5\rfloor) + C(7\lfloor\frac n {10}\rfloor + 4)$.

Montrons que $\mathcal C(n)=\mathcal O(n)$, i.e. qu'il existe $\mathcal c'>0$ et $N\in \mathbb{N}$ tel que $\forall n >= N, \mathcal C(n) \le \mathcal c'n$.

**On procède par analyse puis synthèse :**
- Analyse :

   $
   \begin{array}{rcll}
         C(n) &\le& cn + C(\lfloor\frac n 5\rfloor) + C(7\lfloor\frac n {10}\rfloor) + 4
         \\
         &\le& cn + c'\lfloor\frac n 5\rfloor + c'\frac n {10} + 4
         \\
         &\le& cn + \dfrac{c'n}{5} + c'\frac{7n}{10} + 4
         \\
         &\le& cn + c'\frac{9n}{10} + 4
         \\
         &\le& c'n & \text{dès que}\ cn \le c'\frac n {10} - 4
   \end{array}
$
   
   Or, $cn \le \mathcal C'(\frac{n}{10}-4)$ ssi $\frac{10cn}{n-40}\le c'$ (si $n>40$) et $\frac{n}{n-40}\le 2$ si $n\ge 80$.
- Synthèse : on choisit $N=800$ et $c'=20c$

   $\forall n \ge N, \frac{n}{n-40}\le 2$ donc $\frac{10cn}{n-40}\le 20c = c'$
  
   Donc un récurrente avec la même démonstration qu'une analyse conclut : $\mathcal C(n)\le c'n$.

   Donc l'algorithme de la médiane des médianes permet de déterminer la médiane en temps linéaire.