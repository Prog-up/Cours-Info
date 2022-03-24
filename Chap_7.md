**Chapitre 7 : Élément d'algorithmes**
===
# 1. Introduction
A la manière de la recherche d'un élément dans un ABR, on s'intéresse à la décomposition d'un problème en un ou plusieurs sous-problèmes.

**On distingue plusieurs méthodes selon :**
- le type de problème à résoudre ;
- la manière dont on décompose le problème ;
- la manière dont on reconstruit la solution au problème à partir de celles des sous-problèmes.

**Nous étudierons :**
- la méthode `diviser pour régner` ;
- la programmation dynamique ;
- les algorithmes gloutons.

# 2. Diviser pour régner
## 2.1. Méthode et premiers exemples

---
### 2.1.1. Méthode
**La méthode `diviser pour régner` se décompose en 3 étapes :**
- Diviser le problème en un ou plusieurs sous-problèmes `disjoints` ;
- Résoudre les sous-problèmes, soit récursivement, soit directement si le sous-problème est assez simple ;
- Reconstruire la solution au problème initial à partir de celles des sous-problèmes.

---
### 2.1.2. Remarque
On retrouve l'idée des principes d'induction, où l'on utilise l'hypothèse d'induction (la solution à un sous-problème) pour démontrer la propriété sur une instance plus grande (le problème initial).

---
### 2.1.3. Complexité des algorithmes *diviser pour régner*
**Cette méthode donne une relation de récurrence de la forme :**

$\mathcal C(n) = C_{\text{décomposition}}(n) + \sum_{p\ \text{sous-problèmes}} \mathcal C(\lvert p\rvert) + C_{\text{reconstruction}}(n)$

(ici, $\lvert p\rvert$ désigne la taille du problème $p$).

L'enjeux est de trouver des manières peu coûteuses de décomposer / reconstruire et d'obtenir peu de sous-problèmes assez petits pour avoir une complexité meilleure que celle de la résolution naïve du problème.

---
### 2.1.4. Exemple : Tri fusion
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

---
### 2.1.5. Exemple : Exponentiation rapide
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

---
### 2.1.6. Exemple : Recherche dichotomique
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

---
### 2.1.7. Exemple : Tri rapide (colle 01)
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

---
## 2.2. Application : Calcul de la médiane

---
### 2.2.1. Problème
On veut calculer la médiane d'une liste de  valeurs distinctes, c'est-à-dire l'élément de rang $\lfloor\frac{n}{2}\rfloor$ où le rang d'un élément est le nombre d'éléments qui lui sont strictement inférieurs.

---
### 2.2.2. Solution naïve
On trie la liste et on renvoie l'élément au milieu.

**Complexité :**
$\mathcal O(n \log (n))$ (ex : avec le tri fusion).

**Objectif :**
$\mathcal O(n)$ (optimal puisqu'on doit bien lire tous les élément)

---
### 2.2.3. Généralisation et algorithme "diviser pour régner"
On s'intéresse au problème suivant : trouver l'élément de rang i, où il est un paramètre.

**Algorithme :**
On s'inspire du tri rapide
- Diviser : on choisit un pivot p et on détermine les listes $l_<$ et $l_>$ des éléments strictement inférieurs/supérieurs à p ;
- Résoudre : cela dépend de la taille de $l_<$
  - si $\lvert l_<\rvert > i$, alors on cherche l'élément de rang i dans $l_<$
  - si $\lvert l_<\rvert = i$, alors p est l'élément de rang i
  - si $\lvert l_<\rvert < i$, alors on cherche l'élément de rang $i-\lvert l_<\rvert -1$ dans $l_>$ ;
- Reconstruire : l'élément de rang i est le résultat de la résolution du sous-problème.

**Récurrence :** $\mathcal C(n) = \mathcal O(n) +C_{\text{choix du pivot}}(n) + \left\{
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

---
### 2.2.4. Algorithme de la médiane des médianes
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
## 2.3. Application  : couverture de points par des segments de même longueur

---
### 2.3.1. Problème
Étant donné $n$ points $x_1, ..., x_n$ sur la droite réelle et $k\in \mathbb{N}^*$, on veut déterminer la longueur $l$ minimale telle qu'il existe une couverture de $x_1, ..., x_n$ par $k$ segments de longueur $l$.

$k$ segments $[l_1;r_1] ... [l_k;r_k]$ forment une couverture de $x_1, ..., x_n$ ssi $\forall i\in [\![1; n]\!]$, $\exists j\in [\![1;k]\!]$, $x_i\in [\![l_j;r_j]\!]$

---
### 2.3.2. Remarque
Ceci est un problème d'optimisation : on cherche à minimiser/maximiser une certaine quantité en respectant des contraintes. On peut en général associer à un problème d'optimisation un problème de décision, c'est-à-dire un problème où l'on se pose la question de l'existence d'un objet vérifiant des contraintes.

**Ici :**
Étant donné $x_1, ..., x_n$, $k$ et $l$ existe-t-il une couverture  de $x_1, ..., x_n$ par $k$ segments de longueur $l$ ?

---
### 2.3.3. Résolution par dichotomie de problème d'optimisation
**Idée :**
On suppose que l'on sait résoudre le problème de décision et on procède à une recherche dichotomique du $l$ minimal pour lequel l'algorithme de résolution du problème de décision répond "oui".

On sait que $L=\frac{max_{i; j} (x_i; x_j)}{k}$ permet de construire une couverture, donc on cherche $l$ dans $[0; L]$.

On procède à une recherche dichotomique dans un tableau virtuel (on ne le construit pas) qui à chaque $i\in [\![0; L]\!]$ associe la réponse au problème de décision pour $l=i$.

---
### 2.3.4. Résolution du problème de décision
**Idée :**
On s'intéresse au problème de décision dual suivant : étant donné $n$ segments $[l_1;r_1],...,[l_n;r_n]$ et $k\in \mathbb{N}^*$, peut-on choisir $k$ points $x_1, ..., x_k$ tel que $\forall i\in [\![1;n]\!]$, $\exists j\in [\![1:k]\!]$ tel que $x_j\in [l_i;r_i]$ ?

Cela permet de résoudre le problème initial : si $\exists [l_1;r_1],...,[l_r;r_r]$ couverture de $x_1, ..., x_n$ par des segments de longueur $l$, alors on a une solution au problème dual pour les intervalles $[x_1-l;x_1],...,[x_n-l;x_n]$ ($x_i\in [l_j;r_j]$ ssi $l_j\in [x_i-l;x_i]$).

**Résolution du problème dual :**
Soit $[l_1;r_1],...,[l_r;r_r]$ $n$ segments et $k\in \mathbb{N}^*$.

On traite les segments par extrémité droite croissante :

**Algorithme :**

$
  \begin{aligned}
    &P\leftarrow\varnothing
    \\
    &\text{Trier et renuméroter les segments par }r_i\text{ croissant}
    \\
    &P\leftarrow r_1
    \\
    &P\leftarrow P\cup\{p\}
    \\
    &\text{Pour }i\text{ de }2\text{ à } n
  \end{aligned}
$

$
  \begin{aligned}
         \text{Si }l_i > p
        \\
        & p\leftarrow r_i
        \\
        & p\leftarrow r_i
        \\
        & P\leftarrow P\cup\{p\}
  \end{aligned}
$

Si $\lvert P\rvert\le k$ succès, sinon échec.

**Correction :**
Tous les segments sont rencontrés par un point de P.

**Invariant de boucle :**
Au début du tour indice $i$, tous les segments jusqu'à l'indice $i-1$ sont rencontrés et $p=max(P)=r_j$ pour un certain $j<i$.

$\rightarrow$ Initialement : $P=\{r_1\}=\{p\}$ donc $p=max(P)=r_1$ avec $1<2$ et $r_1\in [l_1;r_1]$ donc $[l_1;r_1]$ est rencontré par un élément de P.

$\rightarrow$ Conservation de l'invariant : on suppose l'invariant vrai au début du tour i, en particulier $p=max(P)=r_j$ pour $j<i$.
- Si $l_i\le p$, comme $j<i$,$r_j\le r_i$ donc $l_i\le p\le r_i$ et il est inutile de rajouter un points pour $[l_i;r_i]$. De plus, $p=max(P)=r_j$ avec $j<i+1$.
- Si $l_i<p$, il faut un point supplémentaire : $P\cup\{r_i\}$ rencontre bien $[l_i;r_i]$ et $p=r_i=max(P\cup\{r_i\})$ avec $i<i+1$.

**Optimalité :**
En notant $P=\{p_1, p_2, ..., p_{f}\}$ on montre par récurrence finie que $\forall i\in [|1;\lvert p\rvert|]$, il exite $P_{opt}$ optimal rencontrant tous les segments et contenant {$p_1, ..., p_i$}.

**Initialisation :**
$i=1$

On considère $P_{opt}$ une solution optimale

Si $p_1\notin P_{opt}$, on s'intéresse à min $P_{opt}$, qui est nécessaire pour rencontrer les segments $[l_1;r_1],...,[l_j;r_j]$ pour un certain j.

$\forall k\le j$, on remarque que $l_k\le min(P_{opt})\le r_1\le r_k$ donc $P_{opt}\backslash\{min(P_{opt})\}\cup\{r_1\}$ convient.

**Hérédité :**
Par hypothèse de récurrence, $\exists P_{opt}$ qui rencontre $[l_1;r_1],...,[l_n;r_n]$ et qui contient $\{p_s|s\in[\![1;i]\!]\}$.

On numérote les éléments de $P_{opt}$ : $popt_1,...,popt_{\rvert P_{opt}\lvert}$, si $popt_{i+1}\not ={p_{i+1}}$, on utilise le même raisonnement que ci-dessous pour montrer que tous les intervalles pour lesquels $popt_{i+1}$ est nécessaire sont rencontrés par $p+1$.

Pour la même raison, on peut remplacer $popt_{i+1}$ par $p_{i+1}$.

**Remarque :**
On a utilisé un algorithme glouton pour résoudre le problème dual (cf.4.)

---
### 2.3.5. Analyse de complexité
- Résolution du problème dual : $\mathcal O (n \log n)$ à cause du tri ;
- Conversion du problème de décision en son dual : $\mathcal O (n)$ pour la construction des $[x_i-l;x_i]$ ;
- Recherche par dichotomie : calcul des diamètre $D=max_{i, j}(x_i-x_j)$ en $\mathcal O (n)$ puis $\mathcal O (\log(\frac{D}{k}))$ itérations ;
- Au total : $\mathcal O (n \log (n) \log(\frac{D}{k}))$.

# 3. Programmation dynamique
## 3.1. Méthode

---
### 3.1.1. Introduction
Si les sous-problèmes ne sont pas disjoints, la méthode `diviser pour régner` donne des algorithmes dont la complexité est mauvaise, parce que l'on est amené à résoudre plusieurs fois le même sous-problème.

**Exemple :**
Calcul des coefficients binomiaux avec le triangle de Pascal :

$$\dbinom{n}{p}=\dbinom{n-1}{p}+\dbinom{n-1}{p-1}$$

l'implémentation naïve de cette formule donne une complexité

$
  \mathcal C (n, p)
  \\
  =\mathcal C (n-1, p)+\mathcal C(n-1, p-1)
  \\
  =...
  \\
  =\mathcal O (\binom{n}{p})\rightarrow$ exponentiel dans le pire cas $(p=\frac{n}{2})
$.

---
### 3.1.2. Approche descendante de la programmation dynamique
On stocke les valeurs calculées pour les retrouver en temps constant si on en a encore besoin. On parle de mémorisation.

**Exemple**
```OCaml
let binom_memorised (n:int) (p:int):int=
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
**Complexité temporelle / spatiale :**
$\mathcal O (np)$

---
### 3.1.3. Approche ascendante
On adopte un point de vue impératif en inversant l'ordre dans lequel les sous-problèmes sont considérés. On commence pour les cas de base et on construit progressivement la solution au problème global.

**Remarque :**
On doit faire attention aux dépendances entre les valeurs calculées car elles ne sont plus gérées par la pile d'exécution.

**Exemple : Triangle de Pascal**

$\dbinom{i}{j}=\dbinom{i-1}{j}+\dbinom{i-1}{j-1}\rightarrow$ on remplit la matrice ligne par ligne.

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

**Complexité spatiale / temporelle :**
$\mathcal O (np)$

On peut faire mieux en complexité spatiale : $\mathcal O (p)$

Un seul tableau de taille $p$ suffit, on utilise la formule sur le tableau de la droite vers la gauche.

---
### 3.1.4. Exemple : Nombres de Delannay
Nombre de chemins distincts que peut prendre une dame sur un échiquier pour aller du coin inférieur gauche au coin supérieur droit en n'utilisant que des déplacements par rangée / colonne croissante, en fonction des dimensions de l'échiquier.

- Si $i\not ={0}$ et $j\not ={0}$ : $D(i,j)=\underbrace{D(i, j-1)}_{\rightarrow}+\underbrace{D(i-1,j)}_{\uparrow}+\underbrace{D(i-1,j-1)}_{\nearrow}$
- Si $i=0$ ou $j=0$ : $D(i,j)=1$

Par programmation dynamique, on calcul $D(n,p)$ en $\mathcal O (np)$ en temps et $\mathcal 0 (p)$ en espace (2 rangées suffisent).

---
## 3.2. Application aux problèmes d'optimisation

---
### Introduction
Un problème d'optimisation est un problème dans lequel on veut maximiser ou minimiser une valeur sans certaines contraintes L'objectif est de déterminer les paramètres permettant d'atteindre l'optimum. La méthode de la programmation dynamique s'applique à de nombreux problèmes d'optimisation.Pour appliquer cette méthode, le problème doit avoir une certaine propriété, appelée propriété de sous-structure optimale : si l'on dispose d'une solution optimale au problème, alors cette solution induit une solution optimale à une ou plusieurs sous-problèmes.

Par exemple, si un plus court chemin de A à B passe par C, alors le sous-chemin de A à C est bien un plus court chemin de A à C.

---
### 3.2.2. Exemple : Chemin de poids maximum sur un échiquier
On reprend le problème vu en 3.1.4. mais on ne cherche plus à déterminer le nombre de chemin, mais plutôt on suppose que les cases de l'échiquier contiennent des poids et on veut trouver un chemin qui maximise la somme des poids des cases parcourues.

**On modélise le problème à l'aide d'une matrice de poids :**

$\begin{bmatrix}
 31 & 21 & 12 & 26 & 34
 \\
 37 & 21 & 34 & 26 & 10
 \\
 2 & 39 & 12 & 49 & 47
\end{bmatrix}$chemin de poids max.

Une recherche exhaustive n'est pas raisonnable : le nombre de chemins à tester pour une matrice $n\times p$ est le nombre de Delannay $D(n, p)$. Or, $D(n, p)\ge\binom{n+p}{p}$

(en interdisant les pas diagonaux, il faut $n$ pas verticaux et $p$ pas horizontaux pour passer d'un coin à l'autre. Un chemin est donc caractérisé par l'emplacement de ses pas horizontaux).

Vérifions que ce problème satisfait la propriété de sous-structure optimale :
- Si un chemin de poids max de $(0,0)\ge (n-1,p-1)$ passe par $(i,j)$, alors le sous-chemin de $(0,0)$ à $(i,j)$ est de poids max.
- Sinon, on complète un chemin de poids max de $(0,0)$ à $(i,j)$ par le sous-chemin de $(0,0)$ à $(n-1,p-1)$ et on obtient un chemin valide de $(0,0)$ à $(n-1,p-1)$ qui contredit l'optimalité du chemin initial.

La propriété de sous-chemin optimale correspond en fait à une récurrence sur le poids max $w_{i,j}$ d'un chemin de $(0,0)$ à $(i,j)$ : on note $M=(m_{i,j})_{i,j}$, la matrice définissant le problème.


Alors : $w_{i,j}=(m_{i,j})_{i,j}+\left\{
 \begin{array}{l}
   0\text{ si }i=j=0
   \\
   w_{0,j-1}\text{ si }i=0\text{ et }j\not =0
   \\
   w_{i-1,0}\text{ si }i\not =0\text{ et }j=0
   \\
   max(w_{i,j-1},w_{i-1,j},w_{i-1,j-1})\text{ si }i\not =0\text{ et }j\not =0
 \end{array}\right.
$

On peut calculer $w_{n-1,p-1}$ par programmation dynamique.

On adopte l'approche ascendante de la programmation dynamique : on remplit la matrice $W=(m_{i,j})_{i,j}$, soit par :
- ligne croissante (et colonnes croissantes)
- colonnes croissantes (et lignes croissantes)
- anti-digonales, i.e. par $i+j$ croissant

**Exercice : Code**

**Complexité :**
$\mathcal O(n,p)$, en espace aussi, mais on peut optimiser l'espace requis car il suffit de connaître une ligne / colonne pour remplir la suivante ~> $\mathcal O(min(n,p))$ en espace.

**Remarque :**
On n'a calculé que le poids maximal, pas un chemin réalisant ce poids. Deux possibilités :
1. Lors du remplissage de la matrice, on détermine en plus de $w_{i,j}$ un prédécesseur de $(i,j)$ sur un chemin de poids max de $(0,0)$ à $(i,j)$. On détermine un tel prédécesseur en gardant un couple qui réalise le maximum dans la formule de récurrence.
2. On détermine la matrice $W$ puis on retrouve un chemin de poids max en partant de la case $(n-1,p-1)$, en déterminant un prédécesseur à  l'aide des valeurs de $N$ puis en calculant récursivement un chemin vers ce prédécesseur.

---
### 3.2.3. Exemple : Produit de matrices
On cherche à minimiser le nombre de multiplications nécessaires au calcul du produit de matrices.

- Si $A$ et $B$ sont de taille $n\times p$ et $p\times q$, on peut calculer $AB$ à l'aide de $npq$ multiplications à l'aide de la définition :

$$(AB)_{i,j}=\sum_{k=1}^p a_{i,k}b_{k,j}$$

- Si $A$, $B$ et $C$ sont de taille $2\times 5$, $5\times 8$ et $8\times 6$, on peut calculer $ABC$ de 2 façons :
 - $(AB)C$ ~> 176 multiplications ($2\times5\times8+2\times8\times6$)
 - $A(BC)$ ~> 300 multiplications ($5\times8\times6+2\times5\times6$)

On veut donc trouver un parenthésage optimal du produit $A_0,...,A_{n-1}$ où $\forall i\in[\![0;n-1]\!], A_i$ est de taille $t_i\times t_{i+1}$

Ce problème vérifie la propriété de sous-structures optimale : si $(A_0,...,A_k)(A_{k+1},...,A_{n-1})$ est un parenthésage optimal, on a bien des parenthésages optimaux des produits $A_0,...,A_k$ et $A_{k+1},...,A_{n-1}$.

On observe qu'il faudra résoudre les sous-problèmes suivants : optimisation du parenthésage des produits $A_i,...,A_j$.

$\forall 0\le i\le j\le n-1$, on note $m_{i,j}$ le nombre minimal de multiplication nécessaires au calcul de $A_i,...,A_j$.

Si $\underbrace{(A_i,...,A_k)}_{\text{matrice de taille }t_i\times t_{k+1}}\times\underbrace{(A_{k+1},...,A_j)}_{\text{matrice de taille }t_{k+1}\times t_{j+1}}$ est un parenthésage optimal, alors $m_{i,j}=m_{i,k}+m_{k+1,j}+t_i+t_{k+1}t_{j+1}$.

On retrouve alors la relation de récurrence : $m_{i,j}\left\{\begin{array}{l}
 0\text{ si }i=j
 \\
 min
 \\
 k\in[\![i;j-1]\!]
\end{array}\right.(m_{i,k}+m_{k+1,j}+t_i+t_{k+1}t_{j+1})$ si $i<j$.

Comment remplir la matrice $M=(m_{i,j})_{i,j}$ ?

On peut remplir la matrice par diagonales, i.e. par $j-1$ croissant

**Exercice : Code**

**Complexité :**
$\mathcal O(n^3)$ en temps, $\mathcal O(n^2)$ en espace.

Comment représenter un parenthésage optimal $\pi_{i,j}$ de $A_i,...,A_j$ ?

Si le parenthésage s'écrit $(A_i,...,A_k)(A_{k+1},...,A_j)$, il suffit de retenir $k$ et les parenthésages $\pi_{i,k} et \pi_{k+1,j}$.

**Remarque :**
C'est un ABR.

# 4. Algorithmes gloutons
## 4.1. Méthode

---
### 4.1.1. Introduction
La programmation dynamique est une méthode utilise pour résoudre de nombreux problèmes, mais les implémentations nécessites en général d'allouer une grande quantité de mémoire. L'approche des algorithmes gloutons est similaire à celle de la programmation dunamique dans sa version descendante. La différence principale dans le fait qu'on ne résout pas plusieurs sous-problèmes poiur garder ensuite la meilleure solution : on choisit à l'avance le sous problème à résoudre. Le choix du sous-problème se fait à l'aide d'une heuristique, i.e. d'une stratégie de décision locale permettent de faire un choix rapide.

---
### 4.1.2. Exemple : Problème du rendu de monnaie
On doit rendre une somme $n$ à l'aide de pièces / billets dont la valueyr appartient à une ensemble $S$.

**Objectif :**
Minimiser le nombre de pièces / billets utilisées.

- **Résolution par prog dynamique :** on va noter $f(n,S)$ le nombre minimal de pièces / billets nécessaires pour atteindre $n$ avec des pièces / billets de valeur prise dans $S$ et on note $S=\{c_1,...,c_k\}$.
  
  On remarque que $\forall i\in \llbracket 1,k\rrbracket,f(n,S)\le \min(\underbrace{f(n,S)\\{c_i}}_{\text{on utilise pas }c_i},1+f(n-c_i,S))$...

  On peut remplir la matrice $F=(f_{i,j})_{i,j}$, où $\forall i,j, f_{i,j}=f(i,\{c_1,...,c_j\})$ 
  
  ~> algo en $\mathcal O(nk)\rightarrow$ complexité exponentielle

  **Explication :**
  - paramètres du problème : $n$ et $S=\{c_1,...,c_k\}$
  - taille des paramètres : $\mathcal O(\log n)$ et $k$
  - $\mathcal O(nk)=\mathcal O(\underbrace{2^{\log_2 n}}_{\text{exponentiel en }\log n}k)$

- **Algo glouton :**
  
  **Idée :** on utilise autant que possible la plus grosse prièce $\le n$ dans l'idée qu'il faudrait utiliser plusieurs petites prièces pour compenser l'absence d'une telle prièce.

  **Algo :** Trier $S$ par ordre d'écroissant et renuméroter en $\{c_1',...,c_k'$


  $\begin{aligned}{}
  \text{Pour }i\text{ de 1 à }k :
  \\
  &\text{Utiliser }c_i\text{ autant que possible, i.e. }\lfloor\frac{n}{c_i'}\rfloor\text{ fois}
  \\
  &n\leftarrow n-c_i'\times\lfloor\frac{n}{c_i'}\rfloor
  \\
  \text{Si }n\not = 0\text{, échec }
\end{aligned}$

  **Complexité :** $\mathcal O(k\log k)$

  **Exemple : n = 48**
  - dans le système européen, $S=\{1,2,5,10,20\}\rightarrow$ solution $2\times 20+5\times 2+1$
   
    on peut démontrer que l'algo est optimal et qu'il réussi toujours dans ce système

  - dans le système britanique antérieur à 1971 : $S=\{1,3,6,12,24,30\}\rightarrow$ solution : $30+12+6$, optimum : $2\times 24$

---
### Remarque
Cet exemple démontre qu'un algo glouton ne fournit pas forcazment toujours une solution optimale. Il faut donc pouvoir démontrer l'optimalité d'un algo glouton lorsque l'on souhaite l'utiliser. Il existe un cadre théorique donnant une condition suffisante d'optimalité, appelé théorie des matroïdes (**H.P.**). Nous avons vu en **2.3.4.** une autre méthode de démonstration : on montre par récurrence qu'il existe une solution optimale qui fait les mêmes choix que l'algo glouton et on montre aussi que l'algo glouton fournit uen solution, ce qui implique que toute solution optimale faisant les mêmes choix donne la même solution.

---
## 4.2. Application
Ordonnancement de tâches unitaires avec pénalité de retard.

---
### 4.2.1 Description du problème
On considère un ensemble de $n$ tâches $T=\{t_s,...,t_{n-1}\}$ qui nécessitent chacune une unité de temps pour être réalisées. À chaque tâche $t\in T$ est associée une date limite $f(t)\in \llbracket 0,n-1 \rrbracket$ et une pénalité $p(t)\in\mathbb{N}$ si la date limite n'est pas respectée.

On appelle ordonnancement des tâches une fonction $d$ : $T\rightarrow\llbracket O,n-1\rrbracket$ qui associe à chaque $t\in T$ la date limite $d(t)$ à laquelle la date est réalisée. $d$ doit être une bijection (on n'effectue qu'une tâche à chaque instant et toutes les tâches sont traitées).

Un ordonnancement $d$ définit 2 ensembles :
- $T^+=\{t\in T,d(t)\le f(t)\}$ l'ensemle des tâches réalisées à temps
- $T^-=\{t\in T,d(t)>f(t)\}$ l'ensemle des tâches réalisées en retard.

La pénalité associée à d est $P(d)=\displaystyle\sum_{t\in T} p(t)$

**Objectif :**
Déterminer $d$ minimisant $P(d)$

**Exemple :**
$ | 1 | 2 | 3 | 4 | 5 | 6
|:---:|:---:|:---:|:---:|:---:|:---:|
| f |$...

donne $P(d)(t_0)+p(t_3)=3+2=5$

---
### 4.2.2. Algo glouton
On remarque que les pénalités de retard ne dépendant pas de la durée du retard. Ce qui compte est donc l'ordonancement des tâches de $T^+$. On cherche donc à construire $T^+ ... T$ tq on peut trouver un ordonencement qui traite dans les délais les éléments de $T^+$ et tq $P(T^+)=\displaystyle\sum_{t\in T^+} p(t)$ est maximal.

**Heuristique :**
On sélectionne en priorité les tâches de pénalité maximale que l'on planifie le plus tard possible.

**Algo :**
Trier les tâches par pénalité décroissante et les renommer $t_0,...,t_{n-1}$

$T^+\leftarrow\empty$

Marquer toutes les dates de $\llbracket 0,n-1\rrbracket$ comme disponibles

$
\begin{aligned}
  \text{Pour }i\text{ de 0 à }n-1
  \\
  &\text{S'il existe une date}j\le f(t_i)\text{ disponible}
  \\
  &&\text{Ajouter }t_i\text{ à }T^+
  \\
  &&\text{Marquer le plus grand }j\le f(t_i)\text{disponible comme occupé par }t_i
\end{aligned}
$

À la fin, placer les tâches non sélectionnées aux dates restantes.

**Complexité :**
- le tri se fait en $\mathcal O(n\log n)$
- la recherche d'un temps $j\le f(t_i)$ disponible dépend de la structure de données utilisée pour représenter l'ensemble des dates disponibles.

Avec un tableau de booléens, on parcourt les dates jusqu'à en trouver une disponible ou jusqu'à exhaustion des dates ~> recherche linéaire $\rightarrow\mathcal O(n^2)$ au total

Avec un ABR équilbré contenant les dates disponibles : Exo : étant donné une date $d$, on peut trouver le plus grand élément de l'ABR inférieur ou égal à $d$ $\rightarrow\mathcal O(n\log n)$ au total

---
### Preuve d'optimalité

**Lemme 1 :**
Soit $T$ un ensemble de tâches et $t$ une tâche $\in T$ de pénalité maximale

Alors $\exists T^+ ... T$ dont on peut planifier les éléments dans les délais, tq $P(T^+)$ est maximal et tq $t\in T^+$

**Démonstration :**
On considère $T^+$ optimal.

Si $t\notin T^+$. S'il reste une date $d\le f(t)$ non occupée par des tâches de $T^+$, alors $T^+\cup\{t\}$ contredit l'optimalité de $T^+$.

Donc il existe une tâche $t'\in T^+$ planifiée à une date $d\le f(t)$.

Or, $p(t')\le p(t)$ donc $T'=(T^+...\{t'\})\cup \{t\}$ est aussi une solution optimale.

En effet, on peut traiter toutes les tâches de $T'$ dans les délais et $P(T')=P(T^+)-p(t')+p(t)\ge P(T^+)$

**Lemme 2 :**
On considère $T^+ ... T$ optimal contenant une tâche $t$ de pénalité maximale associée à la date $j$.

On construit le sous-prolème sans $t$ ni date $j$ ainsi :

$T'=T ... \{t\}$

$\forall t'\in T', f'(t')=\left\{\begin{array}
  f(t')\text{ si } f(t')<j
  \\
  f(t')-1\text{ sinon}
\end{array}\right.$

Alors $T^+ ... \{t\}$ est optimal pour $T'$

**Démonstration :**
Tout ordonnancement de $T'$ corresopnd à ordonnancement de $T$ et réciproquement en décalant les temps postérieurs à $j$ pour insérer la tâche de $t$. Si on dispose de $d'$ pour $T'$, alors $d$, définie par $d(t')=...$ donne un ordonnancement de même pénalité.

S'il existait $T^{++}$ optimal pour $T'$ avec $P(t^{++}>P(T^+ ... \{t\}=P(T^+)-p(t)$ alors $T^{++}\cup \{t\}$ donnerait une solution optimale pou rT qui contredit l'optimalité de $T^+$.

**Théorème :**
L'algo glouton donne une solution optimale

**Démonstration :**
Par récurrence sur $n$ :
- $n=1$, trivial
- hérédité : on note $T=\{t_0,...,t_n\}$ ordonné par pénalité décroissante

  Par le lemme 1, il existe une solution optimale $T^-+$ contenant $t_0$
  
  Par le lemme 2, $T^=+ ... \{t_0\}$ est optimale pour $T ... \{t_0\}$ avec les délais décalés

  Par hypothèse de récurrence, l'algo glouton est optiml pour $T ... \{t_0\}$ avce les délais décalés $\rightarrow$ ensemble $T$

  On peut décaler l'odonnancement pour insérer $t_0$ et obtenir une solution pour $T$
  ...














> Aide exos prof