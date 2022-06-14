Chapitre 11 : Algorithme du texte
===
# 1. Rechercherche dans un texte
## 1.1. Introduction
### 1.1.1. Problème
Étant donné un texte (un fichier / une chaîne de caractère) $t$ et un motif (une chaîne de caractère) $x$, on veut trouver une / toutes les occurences de $x$ dans $t$ (on veut les positions (indices)).

---

### 1.1.2. Algorithme naïf
On test toutes les positions dans $t$ pour déterminer si ce sont des positions d'occurences de $x$.

```ocaml
let recherche_naive (x:string) (t:string) : int list =
	let l = ref [] in
	let n = String.length t and m = String.length x in
	for i=0 to n-m do
		let j = ref 0 in
		while !j < m and x.[!j] = t.[i+!j] do
			incr j
		done;
		if !j = m then l := i := !l
	done;
	!l
```
**Complexité :**
Dans le pire cas, la boucle while va s'arrêter au dernier indice de x (exemple : $t=a^n=\underbrace{a\dots a}_{n\text{ fois}}$ et $x=a^{n-1}b$)

$\rightarrow\mathcal O ((n-m+1)m) =\mathcal O(nm)$ si $n$ est petit devant $m$.

---

### 1.1.3. Remarque
Cet algorithme fait partie d'une famille d'algorithmes, dits de `fenêre glissante` : on fait glisser une fenêtre sur le texte en notant toutes les positions auxquelles la fenêtre contient le motif.

<p align="center">
<img src="Pictures/Chap_11_G1.png" alt="drawing" width="300">
</p>

Le côté naïf de cet algorithme vient du fait que l'on fait systématiquement glisser la fenêtre d'un rang, quel que soit son contenu. En analysant les raisons de l'échec d'un comparaison, on peut espérer décaler la fenêtre de plusieurs rangs.

## 1.2. Algorithme de Boyer-Moore
### 1.2.1. Introduction
L'algorithme de Boyer-Moore est une algorithme de fenêtre glissante, mais la comparaison entre le contenu de la fenêre et le motif se fait de la droite vers la gauche, afin de repérer en cas d'échec la caractère le plus à droite que ne correspond pas au motif. À partir de cette position qui entraîne l'échec de la comparaison, on peut calculer un décalage pour la fenêtre. En pratique, le décalage est précalculé pour toutes les positions du motif et il existe de nombreuses variantes suivant la manière dont le décalage est calculé.

---

### 1.2.2. Algorithme de Boyer-Moore-Horspool
Dans cette variante, si la comparaison de $x_0\dots x_{m-1}$ et $t_i\dots t_{i+m-1}$ (la fenêre) échoue à l'indice $j$, i.e. $x_{j+1}\dots x_{m+1}=t_{i+k+1}\dots t_{i+m+1}$ et $x_j\not =t_{i+j}$, on cherche à aligner $t_{i+m-1}$ avec son occurrence la plus à droite dans $x$ (sauf $x_{m-1}$)

<p align="center">
<img src="Pictures/Chap_11_G2.png" alt="drawing" width="300">
</p>

**Exemple :**
$x=aababab$ et 

$\begin{array}{ll}t=&aabbbababacaabbaba
\\
&\begin{array}{ll}aaba&bab
\\
&\begin{array}{ll}a&ababa
\\
&\begin{array}{ll}aababa&b
\\
&aababab
\end{array}
\end{array}
\end{array}
\end{array}$

> À compléter

**Algorithme :**
Pour toute lettre $a$, on note $\mathrm d(a)$ le décalage à effectuer pour alogner cette lettre avec son occurrence la plus à droite dans $x$ (sauf la dernière lettre) en cas d'échec d'une comparaison avec une fenêtre dont la dernière lettre est $a$ :

$$\mathrm d(a)=\left\{\begin{array}{ll}
	|u| \text{ si } u \text{ est le plus petit affixe non vide de } x \text{tel que } au \text{ est un suffixe de }x
	\\
	|x| \text{ si } u \text{ n'existe pas, i.e. si } x \text{ ne contient pas } a \text{ ou alors seulement en dernière position}
\end{array}\right.$$

**Pseudo-code :**
- $i\leftarrow 0$
- Tant que $i\le n-m$ :
	- $j\leftarrow m-1$
	- Tant que $j\ge 0$ et $x_j=t_{i+j}$ :
		- $j\leftarrow j+1$
	- Si $j=-1$ :
		- $i$ est la position d'une occurence de $x$
		- $i\leftarrow i+1$
	- Sinon :
		- $i\leftarrow i+\mathrm d(t_{i+n-1})$

**Précalcul de $\mathrm d$ :**
Pour toute lettre $a$, $\mathrm d(a)\leftarrow m$

Pour $i$ de $0$ à $m-2$ : $\mathrm d(x_i)\leftarrow m-1-i$

> Insert G3

**Complexité :**
- Précalcul : $\mathcal O(|A|+m)$ où $A$ est l'alphabet, i.e. l'ensemble des symboles possibles dans un texte
- Algorithme : Dans le pire cas, on décale toujours d'un rang (exemple : $t=a^n$ et $x=ba^{m-1}$)$\rightarrow$ même complexité que l'algorithme naïf.

En pratique, c'est plus efficace : $\mathcal O(n)$ en moyenne (admis).

---

### 1.2.3. Algorithme de Boyer-Moore (simplifié)
L'algorithme de Boyer-Moore-Horspool ne tient pas compte de ce qu'il se passe lors de la lecture de la fenêtre, mais seulement de son dernier caractère.

**Par exemple :**
Si $x=aababab$ et la fenêtre vaut $aabcbab$, le décalage calculé vaut 2 alors que l'absence de $c$ dans $x$ permet un décalage de 4 rangs.

L'idée de Boyer et Moore est d'aligner plutôt la caractère qui provoque l'échec de la comparaison avec son occurence la plus à droite dans $x$ (sauf la dernière lettre).

Plus précisément, si $x_j\not =t_{i+j}$ et $x_{j+1}\dots x_{m-1}=t_{i+j+1}\dots t_{i+m-1}$, alors on décale la fenêtre de $\mathrm d(t_{i+j})-(m-1-j)$

<p align="center">
<img src="Pictures/Chap_11_G3.png" alt="drawing" width="300">
</p>

**Attention :**
Cela ne fait pas toujours progresser la recherche

<p align="center">
<img src="Pictures/Chap_11_G4.png" alt="drawing" width="300">
</p>

$\rightarrow$ on obtient un décalage négatif ! Dans ce cas, on décale seulement d'un rang par sécurité.

**Exemple :**

> À compléter 3) -> feuille note

**Algorithme :**
- $i\leftarrow 0$
- Tant que $i\le n-m$ :
	- $j\leftarrow m-1$
	- Tant que $j\ge 0$ et $x_j=t_{i+j}$ :
		- $j\leftarrow j-1$
	- Si $j=-1$ :
		- Occurence de $x$ à la position $i$
		- $i\leftarrow i+1$
	- Sinon :
		- $i\leftarrow i+\max(1,\mathrm d(t_{i+j}-(m-1-j))$

**Complexité :**
Dans le pire cas $\mathcal O(mn)$ avec le même exemple qu'en 1.2.2.

---

### 1.2.4. Algorithme de Boyer-Moore
La version complète de l'algorithme de Boyer-Moore utilise une seconde fonction de décalage.

Celle de 1.2.3. correspond à la règle du mauvais caractère : si un caractère de la fenêtre fait échouer la comparaison avec le motif, on essaie de l'aligner avec sa dernière occurence dans le motif (sauf la dernière lettre).

Il y a aussi la règle du bon suffixe : lorsqu'un caractère fait échouer la comparaison, on a réussi à lire un suffixe de $x$ dans la fenêtre. On peut essayer d'aligner ce suffixe dans le texte avec son occurence la plus à droite dans $x$ à condition qu'elle soit précédée d'un caractère différent.

<p align="center">
<img src="Pictures/Chap_11_G5.png" alt="drawing" width="300">
</p>

$\mathrm d_2(j) =$ longueur du plu court suffixe de $x$ qui a $x_{j+1}\dots x_{n-1}$ comme suffixe  et préfixe et qui n'est pas précédé dans $x$ de $x_j$.

Si un tel suffixe n'existe pas, on peut chercher le plus long suffixe de $u$ qui est préfixe de $x$ et l'aligner avec le $u$ de la fenêtre

<p align="center">
<img src="Pictures/Chap_11_G6.png" alt="drawing" width="300">
</p>

$\mathrm d_2(j) =$ longueur du plu court mot $w$ qui a $u$ comme préfixe et $x$ comem suffixe.

**Remarque :**
- $|w|\le |u|+|x|$
- $\mathrm d_2(j)\ge 1+m-j-1,\forall j$

L'algorithme de Boyer-Moore utilise le décalage maximal entre ceux calculés à partir de $\mathrm d$ et $\mathrm d_2$.

**Remarque :**
Si on trouve une occurence de $x$ (u=x), alors on tombe dans le deuxième cas du calcul de $d_2$ : on cherche le plus long suffixe de $x$ qui est aussi préfixe de $x$, que l'on appelle le bord de $x$ (on note $\mathrm d_2(-1)$.

**Algorithme :**
- $i\leftarrow 0$
- Tant que $i\le n-m$ :
	- $j\leftarrow m-1$
	- Tant que $j\ge 0$ et $x_j=t_{i+j}$ :
		- $j\leftarrow j-1$
	- Si $j=-1$ :
		- Occurence de $x$ à la position $i$
		- $i\leftarrow i+\mathrm d_2(j)-m$
	- Sinon :
		- $i\leftarrow i+\max(\mathrm d(t_{i+j})-(m-1-j),\mathrm d_2(j)-(m-j-1))$