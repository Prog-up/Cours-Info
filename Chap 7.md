**Chapitre 7 : Élément d'algorithmes**
===
# Introduction
A la manière de la recherche d'un élément dans un ABR, on s'intéresse à la décomposition d'un problème en un ou plusieurs sous-problèmes.

**On distingue plusieurs méthodes selon :**
- le type de problème à résoudre ;
- la manière dont on décompose le problème ;
- la manière dont on reconstruit la solution au problème à partir de celles des sous-problèmes. 

**Nous étudierons :**
- la méthode `diviser pour régner` ;
- la programmation dynamique ;
- les algorithmes gloutons.

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
- Résoudre : appel récursif, ou si $\frac n 2 = 0$, on renvoie 1 ;
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
- Reconstruction : on concatène les 2 sous-listes triées (dans le bon ordre) en plaçant entre les 2 le nombre d'occurrence du pivot.

**Récurrence :**
$\mathcal C(n) = \mathcal O(1) + \mathcal C(q) + \mathcal C(r) + \mathcal O(p + q)$

où
$
   \left|
      \begin{array}{l}
         \text{p est le  nombre d'occurrences du pivot}
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
On veut calculer la médiane d'une liste de  valeurs distinctes, c'est-à-dire l'élément de rang $\lfloor\frac{n}{2}\rfloor$ où le rang d'un élément est le nombre d'éléments qui lui sont strictement inférieur.

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

**Dans le pire cas :** 
Comme pour le tri rapide $\mathcal O(n^2)$, par exemple si on choisit le $1^{er}$ élément comme pivot et si le tab est trié et $i=n-1$.

**Dans le meilleur cas :** 
Le pivot est l'élément de rang i ~> $\mathcal O(n)$.

**Conclusion :** 
Le choix du pivot est déterminant. On peut se rapprocher du meilleur cas de tri rapide en choisissant un pivot près de la médiane. On peut s'approcher de la médiane (que l'on cherche à calculer), à moindre coût à l'aide de l'algorithme de la médiane des médianes.
### Algorithme de la médiane des médianes
**Idée :** 
On regroupe les éléments de la liste en petits paquets (de taille constante) dont on peut calculer les médianes naïvement, et on choisit comme pivot la médiane de ces médianes, calculée récursivement.

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
  
   Donc une récurrence avec la même démonstration qu'une analyse conclut : $\mathcal C(n)\le c'n$.

Donc l'algorithme de la médiane des médianes permet de déterminer la médiane en temps linéaire.

---
> Mail prof à propos de l'avancée du TIPE
## 2.3. Application  : couveture de points par des segments de même longueur
### 2.3.1. Problème
Étant donné $n$ points $x_1, ..., x_n$ sur la droite réelle et $k\in \mathbb{N}^*$, on veut déterminer la longueur l minimale tele qu'il exite une couverture de $x_1, ..., x_n$ par $k$ segments de longeur $l$.

$k$ segments $[l_1;r_1] ... [l_k;r_k]$ forment une couverture de $x_1 ... x_n$ ssi $\forall i\in [|1, |], \exist j\in [|1;k|], x_i\in [|l_j;r_j|]$ ...

### 2.3.2. Remarque
Ceci est un problème d'optimisation : on cherche à minimiser/maximiser une certaine qunatité en respectant des contraintes. On peut en général associer à un problème d'optimisation un problème de décision, c'est-à-dire un problème où l'on se pose la question de l'existance d'un obet vérifiant des contraintes.

**Ici :**
Étant donné $x_1, ..., x_n$, $k$ et $l$ existe-t-il une coiverture  de $x_1, ..., x_n$ par $k$ segments de longueur $l$ ?

### 2.3.3. Résolution par dichotomie de problème d'optimisation
**Idée :**
On suppose que l'on sait résoudre le problème de décision et on procède à une recherche dichotomoique du $l$ minimal pour lequel l'algorithme de résolution du problème de décision répond "oui".

On sait que $L=\frac{max_{i; j} (x_i; x_j)}{k}$ permet de construire une couverture, donc on cherhce $l$ dans $[0; L]$.

On procède à une recherche dichotomique dans un tableau virtuel (on ne le construit pas) qui à chaque $i\in [|0; L|]$ ... associe la réponse au problème de décision pour $l=i$.

### 2.3.4. Résolution du problème de décision
**Idée :**
On s'intéresse au problème de décision dual suivant : étant donné $n$ segments $[l_1;r_1]...[l_n;r_n]$ et $k\in \mathbb{N}^*$, peut-on choisir $k$ points $x_1, ..., x_k$ tel que $\forall i\in [|1;n|]$ ..., $\exist j\in [|1:k|]$ tel que $x_j\in [l_i;r_i]$ ?

Cela permet de résoudre le problème initial : si $\exist [l_1;r_1]...[l_r;r_r]$ couverture de $x_1, ..., x_n$ par des segments de longueur $l$, alors on a une solution au problème dual pour les intervalles $[x_1-l;x_1]...[x_n-l;x_n]$ ($x_i\in [l_j;r_j]$ ssi $l_j\in [x_i-l;x_i]$).

**Résolution du problème dual :**
Soit $[l_1;r_1]...[l_r;r_r]$ $n$ segments et $k\in \mathbb{N}^*$.

On traite les segments par extrémité droite croissante :

**Algorithme :**

$P\leftarrow\empty$

Trier et renuméroter les segments par $r_i$ croissant

$P\leftarrow r_1$

$P\leftarrow P$u{$p$} ...

Pour $i$ de $2$ à $n$

  Si $l_i > p$

  $p\leftarrow r_i$

  $P\leftarrow Pu{p}$ ...

Si $\lvert P\rvert\le k$ succès, sinon échec.

**Correction :**
Tous les segments sony rencontrées par un points de P.

Invariant de boucle : au début du tour indice $i$, tous les segments jusqu'à l'indice $i-1$ sont rencontrés et $p=max(P)=r_j$ pour un certain $j<i$.

$\rightarrow$ Initialement : $P={r_1}={p}$ ... donc $p=max(P)=r_1$ avec $1<2$ et $r_1\in [l_1;r_1]$ donc $[l_1;r_1]$ est rencontré par un élément de P.

$\rightarrow$ Conservation de l'invariant : on suppose l'invariant vrai au début du tour i, en particulier $p=max(P)=r_j$ pour $j<i$. 
- Si $l_i\le p$, comme $j<i$,$r_j\le r_i$ donc $l_i\le p\le r_i$ et il est inutile de rajouter un points pour $[l_i;r_i]$. De plus, $p=max(P)=r_j$ avec $j<i+1$.
- Si $l_i<p$, il faut un point supplémentaire : $Pu{r_i}$ ... rencontre bien $[l_i;r_i]$ et $p=r_i=max(Pu{r_i})$ ... avec $i<i+1$.

**Optimalité :**
En notant $P={p_1, p_2, ..., p_{f}}$ ... on montre par récurrence finie que $\forall i\in [|1;\lvert p\rvert|]$, il exite $P_{opt}$ optimal rencontrant tous les segments et contenant {$p_1, ..., p_i$}.

**Initilalisation :**
$i=1$ On considère $P_{opt}$ une solution optimale

Si $p_1\notin P_{opt}$, on s'intéresse à min $P_{opt}$, qui est nécessaire pour rencontrer les segments $[l_1;r_1]...[l_j;r_j]$ pour un certain j.

$\forall k\le j$, on remarque que $l_k\le min(P_{opt})\le r_1\le r_k$ donc $P_{opt}\ {min}(P_{opt}U{r_1}$ ... convient.

**Hérédité :**
...

**Remarque :**
On a utilisé un algorithme glouton pour résoudre le problème dual (cf.4.)

### 2.3.5. Analyse de compléxité
- Résolution du problème dual : $\mathcal O (n \log n)$ à cause du tri ;
- Convertion du rpoblème de décison en son dual : $\mathcal O (n)$ pour la construction des $[x_i-l;x_i]$ ;
- Recherche par dichotomie : calcul des diamètre $D=max_{i, j}(x_i-x_j)$ en $\mathcal O (n)$ puis $\mathcal O (\log(\frac{D}{k}))$ itérations ;
- Au total : $\mathcal O (n \log (n) \log(\frac{D}{k}))$.

# 3. Programmation dynamique
## 3.1. Méthode
### Introduction
Si les sous-problèmes ne sont pas disjoints, la méthode `diviser pour régner` donne des algorithmes dont la complexité est mauvaise, parce que l'on est amené à résoudre plusieurs fois le même sous-problème.

**Exemple :**
Calcul des coefficients binomiaux avec le triangle de Pascal : ... l'implémentation naïve de cette formule donne une complexité $\mathcal C (n, p)=\mathcal C (n-1, p)+\mathcal C(n-1, p-1)=...=\mathcal O (...)\rightarrow$ exponentiel dans le pire cas $(p=\frac{n}{2})$.

### Approche descandante de la programmation dynamique
On stoque les valeurs calculées pour les retrouver en temps constant si on en a encore besoin. On parle de mémorisation.

**Exemple**
```OCaml
let binom_memorised (n:int) (j:int):int=
   let t = Array.make_matrix (n+1) (p+1) (-1) in
   let rec aux (i:int) (j:int):int=
      if t.(i).(j)<>-1 then t.(i).(j)
   else
      if j=0||i=j then begin
         t.(i).(j)<-1;
         1
      end else begin
         t.(i).(j)<- aux (i-1) j + aux (i-1) (j-1);
         t.(i).(j)
      end
   in aux n p;;
```
**Complexité temporelle / spaciale :** 
$\mathcal O (np)$

### 3.1.3. Approche ascendante
On adopte un point de vue impératif en inversant l'odre dans lequel es sous-problèmes sont considérés. On commence pour les cas de base et on construit progressivement la solution au problème global.

**Remarque :**
On doit faire attention aux dépendances entre les valeurs calculées car elles ne sont plus gérées par la pile d'exécution.

**Exemple : Triangle de Pascal**
... $\rightarrow$ on remplit la matrice ligne par ligne.

```OCaml
let binom_ascending (n:int) (p:int):int=
   let t = Array.make_matrix (n+1) (p+1) 1 in
   for i = 2 to n do
      for j = 1 to min (i-1) p do
         t.(i).(j)<-t.(i-1).(j)+t.(i-1).(j-1)
      done
   done
   t.(m).(p)
```

**Comléxité spatiale / temporelle :**
$\mathcal O (np)$

On peut faire mieux en complexité spaciale : $\mathcal O (p)$ un seul tableau de taille $p$ suffit
...
on utilise la formule sur le tableau de la droite vers la gauche.

### 3.1.4. Exemple : Nombres de Delannay
Nombre de chemins distincts que peut prendre une dame sur un échiquier pour aller du coin inférieur gauche au coin supérieur droit en n'utilisant que des déplacements par rangée / colonne croissante, en fonction des dimentions de l'échiquier.

$D(i,j)=D(i, j-1)+D(i-1,j)+D(i-1,j-1)$

Si $i\not ={0}$ et $j\not ={0}$ : $D(i,j)=1$ si $i$ ou $j=0$.

Par programmation dynamique, on calcul $D(n,p)$ en $\mathcal O (np)$ en temps et $\mathcal 0 (p)$ en espace (2 rangées suffisent).