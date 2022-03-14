# Chapitre 7 : Élément d'algorithmes


### Exemple : Tri rapide (colle 01)
Problème : trier une liste
Algo :
- Diviser : on choisit un élément `pivot` et a réparti la liste en 2 sous-listes (celles des éléments) < au pivot et celle des éléments > pivot) et on compte le nombre d'occurrences du pivot
- Résoudre : appel réc sauf si la liste est de taille $\le 1$
- Reconstruction : on concatène les 2 sous-listes triées (dans le bon ordre) en plaçant entre les 2 le nb d'occurrence du pivot

Récurrence : ...

## Application : Calcul de la médiane
### Problème
On veut calculer la médiane d'une liste de  valeurs distinctes, c'est-à-dire l'élément de rand ... |_n/2_| où le rang d'un élément est le nb d'élé qui lui sont stric inférieur

### Solution naïve
On trie la liste et on renvoie l'élé au milieu

Complexité : $O(n \log (n))$ (ex : avec le tri fusion)

Objectif : $O(n)$ (optimal puisqu'on doit bien lire tous les élé)
### Généralisation et algorithme "diviser pour régner"
On s'intéresse au problème suivant : trouver l'élé de rang i, où i est un paramètre

Algo : on s'inspire du tri rapide
- Diviser : on choisit un pivot p et on détermine les listes $l_<$ et $l_>$ des éléments strictement inférieurs/supérieurs à p.
- Résoudre : cela dépend de la taille de $l_<$
 - si ... $|l_<| > i$, alors on cherche l'élé de rang i dans $l_<$
 - si $|l_<| = i$, alors p est l'élé de rang i
 - si $|l_<| < i$, alors on cherche l'élé de rang $i-|l_<|-1$ dans $l_>$
- Reconstruire : l'élé de rang i est le résultat de la résolution du sous-problème

Récurrence : ... $C(n) = O(n) +C_{choix du pivot}(n) +$ selon la taille de $l_<$, avec les notations de 2.1.7.

Dans le pire cas : comme pour le tri rapide $O(n^2)$, par exemple si on choisit le $1^{er}$ élé comme pivot et si le tab est trié et $i=n-1$

Dans le meilleur cas : le pivot est l'élé de rang i ~> $O(n)$

Conclusion : le choix du pivot est déterminant. On peut se rapprocher du meilleur cas de tri rapide en choisissant un pivot près de la médiane. On peut s'approcher de la médiane (que l'on cherche à calculer), à moindre coût à l'aide de l'algo de la médiane des médianes.
### Algo de la médiane des médianes
Idée : on regroupe les élé de la liste en petits paquets (de taille constante) dont on peut calculer les médianes naïvement, et on choisit comme pivot la médiane de ces médianes, calculée récursivement
...

Complexité : $C(n) = O(n) + C(\frac{n}{5})+O(n)+f(n)$
...

On peut majorer la valeur de f(n) en majorant les tailles des listes $l_<$ et $l_>$.

On s'intéresse à $l_<$ (le cas $l_>$ se traite de manière similaire)

Observons le $\frac{n}{5}$ médianes des paquets. Parmi celles-ci, il y en a à la moitié qui sont inférieures à p.

Dans le pire cas : tous les éléments des $\frac{n}{10}$ paquets de ces médianes sont inférieurs à p.

Dans les autres paquets, il y a au plus 2 élé inférieur à p (car la médiane et les 2 éléments qui lui sont supérieur soit inférieur à p).

Au total, il y a au plus $5\times{\frac{n}{10}}+2\times{\frac{n}{10}}=\frac{n}{2}+\frac{n}{5}=\frac{7n}{10}$ éléments dans $l_<$.

Donc $C(n)\le C(\frac{n}{5})+C(\frac{7n}{10})+O(n)$

En pratique, sous les approximations, on montre qu'il existe $C>0$, tel que $\forall n ,C(n)\le Cn+$...

Montrons que $C(n)=O(n)$, i.e. qu'il existe $C'>0$ et $N\in \mathbb{N}$ tel que $\forall n >= N, C(n) \le C'n$

On procède par analyse puis synthèse :
- Analyse : $C(n) \le Cn + C()$ ...

   Or, $Cn \le C'(\frac{n}{10}-4)$ ssi $\frac{10Cn}{n-40}\le C'$ (si $n>40$) et $\frac{n}{n-40}\le 2$ si $n\ge 80$
- Synthèse : on choisit $N=800$ et $C'=20C$

   $\forall n \ge N, \frac{n}{n-40}\le 2$ donc $\frac{10Cn}{n-40}\le 20C = C'$
  
   Donc un récurrente avec la même démonstration qu'une analyse conclut : $C(n)\le C'n$

   Donc l'algorithme de la médiane des médianes permet de déterminer la médiane en temps linéaire.


$\left\lfloor\dfrac{2}{3}\right\rfloor$
$\lfloor\frac{2}{3}\rfloor$

$\left| \begin{array}{c} a \\ b \end{array} \right.$