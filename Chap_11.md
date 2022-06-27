Chapitre 11 : Algorithme du texte
===
# 1. Recherche dans un texte
## 1.1. Introduction
### 1.1.1. Problème
Étant donné un texte (un fichier / une chaîne de caractère) $t$ et un motif (une chaîne de caractère) $x$, on veut trouver une / toutes les occurrences de $x$ dans $t$ (on veut les positions (indices)).

---

### 1.1.2. Algorithme naïf
On teste toutes les positions dans $t$ pour déterminer si ce sont des positions d'occurrences de $x$.

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
Cet algorithme fait partie d'une famille d'algorithmes, dits de `fenêtre glissante` : on fait glisser une fenêtre sur le texte en notant toutes les positions auxquelles la fenêtre contient le motif.

<p align="center">
<img src="Pictures/Chap_11_G1.png" alt="drawing" width="300">
</p>

Le côté naïf de cet algorithme vient du fait que l'on fait systématiquement glisser la fenêtre d'un rang, quel que soit son contenu. En analysant les raisons de l'échec d'une comparaison, on peut espérer décaler la fenêtre de plusieurs rangs.

## 1.2. Algorithme de Boyer-Moore
### 1.2.1. Introduction
L'algorithme de Boyer-Moore est une algorithme de fenêtre glissante, mais la comparaison entre le contenu de la fenêtre et le motif se fait de la droite vers la gauche, afin de repérer en cas d'échec le caractère le plus à droite qui ne correspond pas au motif. À partir de cette position qui entraîne l'échec de la comparaison, on peut calculer un décalage pour la fenêtre. En pratique, le décalage est précalculé pour toutes les positions du motif et il existe de nombreuses variantes suivant la manière dont le décalage est calculé.

---

### 1.2.2. Algorithme de Boyer-Moore-Horspool
Dans cette variante, si la comparaison de $x_0\dots x_{m-1}$ et $t_i\dots t_{i+m-1}$ (la fenêtre) échoue à l'indice $j$, i.e. $x_{j+1}\dots x_{m+1}=t_{i+k+1}\dots t_{i+m+1}$ et $x_j\not =t_{i+j}$, on cherche à aligner $t_{i+m-1}$ avec son occurrence la plus à droite dans $x$ (sauf $x_{m-1}$)

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
Pour toute lettre $a$, on note $\mathrm d(a)$ le décalage à effectuer pour aligner cette lettre avec son occurrence la plus à droite dans $x$ (sauf la dernière lettre) en cas d'échec d'une comparaison avec une fenêtre dont la dernière lettre est $a$ :

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
       - $i$ est la position d'une occurrence de $x$
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

L'idée de Boyer et Moore est d'aligner plutôt la caractère qui provoque l'échec de la comparaison avec son occurrence la plus à droite dans $x$ (sauf la dernière lettre).

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
       - Occurrence de $x$ à la position $i$
       - $i\leftarrow i+1$
   - Sinon :
       - $i\leftarrow i+\max(1,\mathrm d(t_{i+j}-(m-1-j))$

**Complexité :**
Dans le pire cas $\mathcal O(mn)$ avec le même exemple qu'en 1.2.2.

---

### 1.2.4. Algorithme de Boyer-Moore
La version complète de l'algorithme de Boyer-Moore utilise une seconde fonction de décalage.

Celle de 1.2.3. correspond à la règle du mauvais caractère : si un caractère de la fenêtre fait échouer la comparaison avec le motif, on essaie de l'aligner avec sa dernière occurrence dans le motif (sauf la dernière lettre).

Il y a aussi la règle du bon suffixe : lorsqu'un caractère fait échouer la comparaison, on a réussi à lire un suffixe de $x$ dans la fenêtre. On peut essayer d'aligner ce suffixe dans le texte avec son occurrence la plus à droite dans $x$ à condition qu'elle soit précédée d'un caractère différent.

<p align="center">
<img src="Pictures/Chap_11_G5.png" alt="drawing" width="300">
</p>

$\mathrm d_2(j) =$ longueur du plu court suffixe de $x$ qui a $x_{j+1}\dots x_{n-1}$ comme suffixe  et préfixe et qui n'est pas précédé dans $x$ de $x_j$.

Si un tel suffixe n'existe pas, on peut chercher le plus long suffixe de $u$ qui est préfixe de $x$ et l'aligner avec le $u$ de la fenêtre

<p align="center">
<img src="Pictures/Chap_11_G6.png" alt="drawing" width="300">
</p>

$\mathrm d_2(j) =$ longueur du plus court mot $w$ qui a $u$ comme préfixe et $x$ comme suffixe.

**Remarque :**
- $|w|\le |u|+|x|$
- $\mathrm d_2(j)\ge 1+m-j-1,\forall j$

L'algorithme de Boyer-Moore utilise le décalage maximal entre ceux calculés à partir de $\mathrm d$ et $\mathrm d_2$.

**Remarque :**
Si on trouve une occurrence de $x$ (u=x), alors on tombe dans le deuxième cas du calcul de $d_2$ : on cherche le plus long suffixe de $x$ qui est aussi préfixe de $x$, que l'on appelle le bord de $x$ (on note $\mathrm d_2(-1)$.

**Algorithme :**
- $i\leftarrow 0$
- Tant que $i\le n-m$ :
   - $j\leftarrow m-1$
   - Tant que $j\ge 0$ et $x_j=t_{i+j}$ :
       - $j\leftarrow j-1$
   - Si $j=-1$ :
       - Occurrence de $x$ à la position $i$
       - $i\leftarrow i+\mathrm d_2(j)-m$
   - Sinon :
       - $i\leftarrow i+\max(\mathrm d(t_{i+j})-(m-1-j),\mathrm d_2(j)-(m-j-1))$

**Exemple :**

> Insert ex

**Complexité :**
On admet que $d_2$ peut être précalculée en temps $\mathcal O(m)$.

Dans le pire des cas, la recherche est encore en $\mathcal O(nm)$ (exemple : $x=a^m$$ et $t=a^n$).

**Remarque :**
Il existe une version plus complexe avec un prétraitement qui permet une complexité $\mathcal O(n+m)$ `H.P.`

## 1.3. Algorithme de Karp-Rabin
### 1.3.1. Principe
L'idée de l'algorithme de Karp-Rabin est d'éviter les comparaisons en temps linéaire entre le motif et le contenu d'une fenêtre en utilisant une fonction de hachage. On parle d'empreinte pour désigner le haché d'une chaîne de caractères par la fonction de hachage choisie et on compare les empreintes du motif et du contenu de la fenêtre. Pour contrer le problème des collisions, un cas d'égalité des empreintes on compare aussi les deux chaînes de caractères.

**Algorithme :**
Entrée : texte $t=t_0\dots t_{n-1}$, motif $x=x_0\dots x_{m-1}$ (+$h$ la fonction de hachage choisie à l'avance)

Pseudo-code :
- $h_x\leftarrow\mathrm h(x_0\dots x_{m-1})$
- $h_t\leftarrow\mathrm h(t_0\dots t_{m-1})$
- Pour $i$ de $0$ à $n-m$ :
 - Si $h_x=h_t$ et (paresseux) $x_0\dots x_{m-1}=t_0\dots t_{m-1}$ :
   - Occurrence de $x$ à la position $i$
 - Si $i<n-m$ :
   - $h_t\leftarrow\mathrm h(t_{i+1}\dots t_{i+m})$

---

### 1.3.2. Choix de la fonction de hachage
**Plusieurs contraintes :**
- On doit pouvoir comparer des empreintes en temps constant : en pratique, les empreintes sont des entiers machines donc ce n'est pas un problème.
- Il doit y avoir peu de collisions `avec le haché du motif`
- On doit pouvoir calculer l'empreinte de la fenêtre à l'itération suivante sans lire tous ses caractères (sinon on retrouve la complexité de l'algorithme naïf).

On peut par exemple utiliser une fonction de hachage déroulante, i.e. une fonction $h$ telle qu'il est possible de calculer en temps constant $\mathrm h(u_1\dots u_m)$ à partir de $\mathrm h(u_0\dots u_{m-1})$.

> Insert Graph 1)

**Exemple :**
On considère que les caractères sont codés sur un octet, i.e. on les assimile à des entiers compris entre $0$ et $m-1$ (avec $r=2^8$). On peut voir une chaîne de caractères de longueur $m$, comme l'écriture en base $r$ d'un entier compris entre $0$ et $r^m-1$.

$$\mathrm P(u_0\dots u_{m-1})=\sum^{n-1}_{i=0}u_ir^{m-1-i}=u_0r^{m-1}+u_1r^{m-2}+\dots+u_{m-1}$$

On choisit un nombre premier $p$ et on définit $\mathrm h(u)=\mathrm P(u)\text{mod }p$

$$\begin{array}{lll}
   \mathrm h(u_0\dots u_{m-1})&=\displaystyle\sum^{m}_{i=1}u_ir^{m-1-i+1}\text{mod }p
   \\
   &=\displaystyle(\sum^{m-i}_{i=1}u_ir^{m-i}+u_m)\text{mod }p
   \\
   &=\displaystyle(r(\sum^{m-1-i}_{i=1}u_ir^{m-i}-u_or^{n-1})+u_m)\text{mod }p
   \\
   &=(r(\mathrm h(u_0\dots u_{m-1})-u_or^{n-1})+u_m)\text{mod }p
\end{array}$$

$$\delta(u_0,u_m):e\mapsto(r(e-u_0r^{n-1})+u_m)\text{mod }p$$

**Remarque :**
Si on précalcule $r^{m-1}$ alors $\delta(u_0,u_m)$ est bien calculable en temps constant.

Complexité du précalcul : $\mathcal O(\log m)$ avec l'exponentiation rapide (modulo).

---

### 1.3.3. Implémentation en OCaml
```ocaml
let hash (r:int)(p:int)(s:string):int=
   let e = ref O in
   for i=0 to String.length s-1 do
       e := (r*!e+(Char.code s.[i])) mod p (*schéma de Horner*)
   done;
   !e

let delta (r:int)(p:int)(rm:int)(u0:char)(un=char)(e:int):int=
   (r*(e-(Char.code u0)*rm)+Char.code um)mod p

let harp_rabin (t:int)(x:string):int=
   let n = String.length t and m=String.length x in
   let l = ref[] in
   let r = 256 and p = Ox7fffffff in (*p=(2^31)-1*)
   let rm = fast_exp_mod r (n-1) p in (*(r^n-1) mod p*)
   let hx = hash r p x and e = ref (hash r p (String.sub 0 m t)) in
   for i=0 to n-m do
       if hx=!e && x=String.sub i m t
       then l := i::!l;
       if i<n-m then e := delta r p rm t.[i] t.[i+m] !e
   done;
   !l
```

---

### 1.3.4. Etude de la complexité
- Complexité de l'initialisation :
 - calcul de $rm$ : $\mathcal O(\log m)$
 - calcul de $hx$ et $e=\mathrm h(t_0\dots t_{n-1})$ : $\mathcal O(m)$
 - $\mathcal O(m)$ au total pour l'initialisation
- Complexité de la boucle :
 - à chaque itération : 1 comparaison et 1 calcul de delta en $\mathcal O(1)$
 - en cas d'égalité d'empreintes : 1 extraction + comparaison de chaîne d taille $m$ : $\mathcal O(m)$
 - Au total : $\mathcal O(m)+(n-m)\times\mathcal O(1)+\#\text{égalités d'empreintes}\times\mathcal 0(m)=\mathcal O(n+m\#\text{égalités d'empreintes})$
 - Avec $t=a^n$ et $x=a^m$, on a égalité à chaque itération et on obtient une complexité $\mathcal O((n-m)m)$

Exemple de ce cas où le pire cas est atteint sans occurrence de $x$ dans $t$ : $x=aa$, $t=arar\dots ar$

$p=17$ et $r=26$

$\mathrm h(aa)=0=\mathrm h(ar)=\mathrm h(ra)$

**Remarque :**
Dans la publication de Karp et Rabin, l'idée est de choisir un nombre premier $p$ au hasard parmi un ensemble prédéfini pour limiter le risque de collision.

**Admis :**
Si on choisit deux chaînes de taille $m$ aléatoirement uniformément, la probabilité de collision avec la fonction de hachage choisie est de l'ordre de $\frac{1}{p}$ ($<10^{-9}$ si $p=2^{31}-1$).

**Attention :**
En pratique, les chaînes étudiées ne sont pas du tout choisies uniformément.

---

### 1.3.5. Extension à la recherche de plusieurs motifs
Même si cet algorithme est moins efficace que l'algorithme de Boyer-Moore pour la recherche d'un seul motif, il devient plus intéressant pour la recherche de Plusieurs motifs car on peut l'adapter pour éviter de lancer une recherche par motif. En choisissant une structure d'ensemble adaptée, il est possible de vérifier en temps constant si l'empreinte d'une sous-chaîne est égale à l'empreinte des motifs (test d'appartenance).

$\rightarrow$ Il suffit de remplacer le test d'égalité d'empreintes par un test d'appartenance à l'ensemble des empreintes des motifs (précalculées) dans l'algorithme de Karp-Rabin.

# 2. Algorithmes de compression

## 2.1. Contexte

### 2.1.1. Principe
On dispose d'un texte (en fait, d'un fichier, quel que soit son contenu, puisque c'est une séquence finie d'octets) et on souhaite réduire l'espace mémoire qu'il occupe via un changement d'encodage. On s'intéresse ici à la compression sans perte, i.e. on doit pouvoir retrouver l'intégralité de l'information initiale à partir du texte compressé. Formellement, on note $\Sigma$ l'ensemble des symboles authorisés dans le texte, appelé alphabet (en pratique $\Sigma=\{0;1\}$) et $\Sigma^*$ l'ensemble des séquences des séquences finies d'éléments de $\Sigma$. On Cherche alors une fonction de $\Sigma^*$ dans $\Sigma^*$, nommée compression, telle qu'il existe decompression : $\Sigma^*\rightarrow\Sigma^*$ tel que $\forall t\in\Sigma^*\mathtt{decopression}(\mathtt{compression}(t))=t$.

---

### 2.1.2. Remarque
On ne peut pas avoir $\forall t\in\Sigma^*|\mathtt{compression}(t)|<|t|$.

En effet, la condition $\mathtt{decompression}\circ\mathtt{compression}=\mathtt{id}$ impose que compression soit injective. Mais dans ce cas, on aurait une fonction injective de l'ensemble des textes d'une taille donnée vers l'ensemble des textes de taille strictement inférieure : impossible car le cardinal du second ensemble est strictement inférieur à celui du premier.

Il existe donc toujours des textes dont la version compressée est plus grande que la version décompressée. L'important est alors de trouver des algorithmes qui compressent efficacement les textes qui sont pertinents pour l'utilisateur.

---

### 2.1.3. Algorithmes au programme
On va étudier l'algorithme de Huffman, qui exploite des données sur la fréquence d'apparition des caractères dans le texte pour déterminer un encodage, et l'algorithme de Lempel-Ziv-Welch, qui ne nécessite pas la connaissance de l'intégralité du texte pour calculer un encodage car il construit incrémentalement un dictionnaire de codes pour les motifs apparaissants dans le texte.

## 2.2. Algorithme de Huffman

### 2.2.1. Principe
L'idée principale de cet algorithme est d'associer un code plus court aux caractères les plus fréquents pour diminuer la taille du texte.

**Exemple :**
$abaabc$ nécessite 12 bits avec un code de taille fixe (3 lettres $\leadsto$ 2 bits par caractère) mais seulement 9 bits avec un code de taille variable (exemple : $a=0,b=10,c=11$).

**Remarque :**
Pour pouvoir décompresser sans ambiguïté un encodage taille variable, on ne peut pas encoder un caractère avec un préfixe du code d'un autre caractère. On appelle cela un code préfixe.

L'algorithme de Huffman est un algorithme qui, étant donné un texte, produit un code préfixe optimal pour la compression de ce texte, en termes de la taille du texte compressé.

---

### 2.2.2. Représentation de l'encodage des symboles
On s'intéresse uniquement à des encodages binaires. Un code peut être représenté à l'aide d'un arbre binaire (strict) : dans cet arbre, les caractères sont placés aux feuilles et le chemin de la racine vers une feuille donne le code du caractère correspondant (descendre à gauche correspond au bit 0 et descendre à droite au bit 1).

**Exemple :**
Le code de $a=0$, $b=10$, $c=11$ est représenté par :

```mermaid
flowchart TB
   id0(( )) --- id1((a)) & id2(( ))
   id2 --- id3((b)) & id4((c))
```
Donne $a=00$, $b=01$, $c=10$ et $d=11$

$\rightarrow$ pour avoir un code optionnel, l'arbre doit être binaire strict

**Remarque :**
La longueur du code d'un caractère est la profondeur de la feuille correspondante dans l'arbre représentant l'encodage. Déterminer un code préfixe optimal revient à chercher un minimum pour $\varphi(t)=\sum_{x\in\text{feuilles}(t)}\mathrm f(x)\times\mathrm p(x,t)$ où :
- $\mathrm p(x,t)$ est la profondeur de la feuille $x$ dans l'arbre $t$ ;
- $\mathrm f(x)$ est la fréquence du caractère $x$ dans le texte.

---

### 2.2.3. Encodage et décodage
On considère un arbre binaire $t$ représentant un code préfixe et on suppose que l'on travaille sur l'alphabet des octets (type char).
- Pour décoder une séquence de bits, il suffit de descendre dans l'arbre selon les bits lus et, lorsque l'on atteint une feuille, de produire le caractère correspondant et poursuivre la lecture en repartant de la racine.

   **Code :**
   ```ocaml
   type arbre = Feuille of char |Noeud of arbre * arbre
   ```

   On représente un bit par un booléen (false pour 0 et true pour 1).

   ```ocaml
   let decode (l:bool list) (t:arbre):char list =
      let rec aux (l:bool list) (a:arbre):char list =
          match l, a with
          |_, Feuille c -> c::aux l t (*Attention à l'ordre*)
          |[], _ -> []
          |b::q, Noeud(g,l) -> if b then aux q d else aux q g
      in aux l t
   ```

   **Complexité :**
   $\mathcal O(\#\text{bits dans le texte compressé})$

- Pour un texte, étant donné un arbre représentant un encodage pour chacun des caractères du texte, on ne veut pas parcourir l'arbre à chaque caractère pour déterminer son code. On calcule donc d'abord une table d'encodage associant à chaque caractère son code. On peut la calculer avec un unique parcours de l'arbre :

   ```ocaml
   let codes (t:arbre):bool list array =
      let a = Array.make 256 [] in (*on travaille sur les octets*)
      let rec aux (t:arbre) (acc:bool list):unit =
          match t with
          |Feuille c -> a.(Char.code c) <- List.rev acc (*chemin accumulé à l'envers*)
          |Noeud(g,d) -> aux g (false::acc); aux d (true::acc)
      in aux t [];
      a
   ```

   **Complexité :**
   Chaque noeud interne est traité en $\mathcal O(1)$ et chaque feuille $x$ est traité en $\mathcal O(\mathrm p(x,t))$


En notant $n$ le nombre de caractères encodés ($n\le |\Sigma|$), il y a $n$ feuilles et $n-1$ nœuds internes car l'arbre est binaire strict (cf Chap 6.1.1.10). La hauteur de l'arbre est comprise entre $\lceil \log_2(n) \rceil$ et $n$.

Dans la complexité est en $\Omega(n\log n)$ et en $\mathcal O(n^2)$.

Une fois la table d'encodage calculée, il suffit de remplacer chaque caractère par son code :

```ocaml
let encode (l:char) (t:arbre):bool list =
   let a = codes t in
   List.flatten (List.map (fun c -> a.(Char.code c)) l)
```

---

### 2.2.4. Arbre de Huffman
Il reste à déterminer comment calculer un arbre représentant un code préfixe adapté à la compression d'un arbre donné. L'algorithme de Huffman est un algorithme glouton déterminant un arbre optimal. Cet algorithme part d'une forêt de feuilles et les fusionne 2 à 2 jusqu'à l'obtention d'un unique arbre. La fusion de deux arbres est la construction d'un nouveau nœud dont les arbres sont les fils.

**Exemple :**

$~~~~~~~~~~a~b~c\\~~~~~~~~~~~~~\Downarrow$
```mermaid
flowchart TB
   id0((a))
   id(( ))--- id1((b)) & id2((c))
```
$~~~~~~~~~~~~~\Downarrow$

```mermaid
flowchart TB
   id0(( )) --- id1((a)) & id2(( ))
   id2 --- id3((b)) & id4((c))
```

L'idée du choix glouton est la suivante : la fusion incrémente la longueur du code des feuilles des deux arbres concernés donc les arbres contenant les caractères les moins fréquents doivent subir le plus de fusion donc être fusionnés en priorité.

On généralise la fonction $\mathrm f$ de 2.2.2. aux arbres en définissant $\displaystyle\mathrm f(t)=\sum_{x\in\text{feuilles}(t)}\mathrm f(x)$.

**L'algorithme de Huffman s'écrit alors ainsi :**
Entrée : texte $s$
Pseudo-code :
- $\mathrm{occ}\leftarrow$ table des occurrences des caractères de $s$
- $F\leftarrow$ ensemble des feuilles $c$ où $c$ est tel que $\mathrm{occ}(c)>0$
- Tant que $|F|\ge 2$ :
   - Extraire $t_1$ de $F$ tel que $\mathrm f(t_1)$ est minimale
   - Extraire $t_2$ de $F$ tel que $\mathrm f(t_2)$ est minimale
   - $F\leftarrow F\bigcup$
   - $F \leftarrow F \cup \{\mathtt{fusion}(t_1, t_2)\}$
- Renvoyer l'unique élément de $F$

**Implémentation :**
La forêt $F$ se comporte comme une file de priorité min où la priorité d'un arbre $t$ est $f(t)$.

On suppose donné un type \texttt{fp} associé aux primitives suivantes :
- $\texttt{create : unit -> fp}$ qui crée une file de priorité vide ;
- $\texttt{add : arbre -> int -> fp -> unit}$ qui insère un arbre avec la priorité (entière) donnée dans la file ;
- $\texttt{take\_min : fp -> arbre * int}$ qui extrait un arbre de priorité min et qui renvoie aussi sa priorité ;
- $\texttt{size : fp -> int}$ qui renvoie la taille de la file.

**Code :**
```ocaml
let huffman (s:char list):arbre =
   let occ = Array.make 256 0 in (*on travaille sur des octets*)
   List.iter (fun c -> occ.(Char.code c) <- 1 + occ.(Char.code c)) s;
   let f = create () in
   for i = 0 to 255 do
      if occ.(i) <> 0 then
         add (Feuille(Char.chr i)) occ.(i) f
   done;
   while size f > 1 do
      let t1, f1 = take_min f in
      let t2, f2 = take_min f in
      add (Noeud(t1, t2)) (f1 + f2) f
   done;
   fst (take_min f)
```

**Complexité :**
On note $\mathrm n(s)$ le nombre de caractères distincts de $s$.
- Comptage des occurences : $\mathcal O(s)$
- Création de la file : avec une implémentation par tas : $\mathcal O(\mathrm n(s)\underbrace{\log\mathrm n(s)}_{\text{une insertion en }\mathcal O(\mathrm n(s))})$
- Une itération de la boucle : $\mathcal O(\log\mathrm n(s))$, il y a $\mathcal O(\mathrm n(s))$ itérations.

**Au total :** $\mathcal O(|s|+\mathrm n(s)\log(\mathrm n(s)))=\mathcal O(|s|)$ car $\mathrm n(s)\le 256$ car on travaille sur des octets.

---

### 2.2.5. optimalité de l'arbre de Huffman
**Rappel :**
On cherche à trouver un arbre $t$ minimisant $\displaystyle\varphi(t)=\sum_{x\in\text{feuille}(t)}\mathrm f(x)\mathrm p(x,t)$ où $\mathrm f(x)$ est la fréquence d'apparition de $x$ dans le texte et $\mathrm p(x,t)$ la profondeur de $x$ dans t.

On généralise $\mathrm f$ aux arbres par $\displaystyle\mathrm f(t)=\sum_{x\in\text{feuille}(t)}\mathrm f(x)$ et $\varphi$ aux forêts par $\displaystyle\varphi(F)=\sum_{t\in F}\varphi(t)$.

**Lemme :**
En notant $F'$ la forêt obtenue après un tour de boucle appliqué à $F$, i.e. $F'=(F\setminus\{t_1;t_2\})\cup\{\text{Noeud}(t_1;t_2)\}$ où $t_1$ et $t_2$ sont 2 éléments de $F$ qui minimisent $f$.

On a : $\varphi(F')=\varphi(F)+\mathrm f(t_1)+\mathrm f(t_2)$.

**Démonstration :**

$\begin{array}{ll}
   \varphi(F')&=\displaystyle\sum_{t\in F'}\varphi(t)
   \\
   &=\displaystyle\underbrace{\sum_{t\in F}\varphi(t)}_{\varphi(F)}-\varphi(t_1)-\varphi(t_2)+\varphi(\text{Noeud}(t_1,t_2))
\end{array}$

Or, $\begin{array}{ll}
   \varphi(\text{Noeud}(t_1,t_2))&=\displaystyle\sum_{x\in\text{feuille}(t_1)et \bigcup\text{Feuille}(t_2)}\mathrm f(x)\mathrm p(x,\text{Noeud}(t_1,t_2))
   \\
   &=\displaystyle\sum_{x\in\text{feuille}(t_1)}\mathrm f(x)\underbrace{\mathrm p(x,\text{Noeud}(t_1,t_2)})
\end{array}$

> À compléter

d'où $\varphi(F')=\varphi(F)+\mathrm f(t_1)+\mathrm f(t_2)$

**Proposition :**
Si les lettres les moins fréquentes à $a$ et $b$ sont soeur dans l'arbre et de profondeur maximale.

**Démonstration :**
On considère un arbre optimal $t_{\text{opt}}$ et on note $c$ et $d$ deux feuilles soeurs de profondeur maximale dans $t_{\text{opt}}$ (possible car $t_{\text{opt}}$ est binaire strict).

Sans perte de généralité, suppose $\mathrm f(a)\le\mathrm f(b)$ et $\mathrm f(c)\le\mathrm f(d)$.

Par définition de $a$ et $b$, on sait que $\mathrm f(a)\le\mathrm f(c)$ et $\mathrm f(b)\le\mathrm f(d)$.

En échangeant dans $t_{\text{opt}}$ la feuille $a$ et la feuille $c$, on obtient $t$ tel que :
$\begin{array}{ll}
\varphi(t)&=\varphi(t_{\text{opt}})-\mathrm f(a)\mathrm p(a,t_{\text{opt}})-\mathrm f(c)\mathrm p(c,t_{\text{opt}})+\mathrm f(a)\mathrm p(c,t_{\text{opt}})+\mathrm f(c)\mathrm p(a,t_{\text{opt}})
\\
&=\varphi(t_{\text{opt}})+(\underbrace{\mathrm f(a)-\mathrm f(c)}_{\le 0})(\underbrace{\mathrm p(c,t_{\text{opt}})-\mathrm p(a,t_{\text{opt}})}_{\ge 0})
\end{array}$

Donc $\varphi(t)\le\varphi(t_{\text{opt}})$.

En échangeant de même les feuilles $b$ et $d$ dans $t$, on otient $t'$ avec $a$ et $b$ feuilles soeursde profondeur maximale et tel que $\varphi(t')\le\varphi(t)\le\varphi(t,t_{\text{opt}})$ donc tel que $t'$ est optimal.


**Théorème :**
L'algorithme de Hoffman renvoie un arbre optimal.

**Démonstration :**
On procède par récurrence sur le nombre de caractères distincts dans le texte :
- si le texte est écrit à l'aide d'un unique caractère : il n'y a qu'un seul arbre possible donc l'algorithme est optimal ;
- si l'algorithme est optimal pour les textes à $n$ caractères distincts, considérons un texte à $n+1\ge 2$ caractères distincts. Notons $a$ et $b$ les deux caractères les moins fréquents dans ce texte.

La première étape de l'algorithme de Huffman consiste à fusionner les feuilles associées à $a$ et $b$. Cela revient à considérer un nouveau texte où $a$ et $b$ sont remplacées par un nouveau caractère $z$ dont la fréquence d'apparition est donc $\mathrm f(a)+\mathrm f(b)=\mathrm f(\text{Noeud}(a,b))$.

Ce nouveau texte ayant $n$ caractères distincts, on sait que l'algo de Huffman produit un arbre $t_{\text{opt}}$ optimal pour ce texte par hypothèse de récurrence.

L'arbre $t$ obtenu par l'algorithme de Huffman pour le texte initial est $t_{\text{opt}}$ où la feuille associée à $z$ est remplacée par le $\text{Noeud}(a,b)$.

$\varphi(t)=\varphi(t_{\text{opt}})+\mathrm f(a)+\mathrm f(b)$ (même démonstration que le lemme).

On sait qu'il existe une solution optimale $t_{\text{opt}}'$ tel que $a$ et $b$ sont des feuilles soeurs de profondeur maximale.

On construit $t'$ en remplaçant dans $t_{\text{opt}}'$ $\text{Noeud(a,b)}$ par $\text{Feuille}(z)$.

Donc $\varphi(t_{\text{opt}}')=\varphi(t')+\mathrm f(a)+\mathrm f(b)\ge\varphi(t_{\text{opt}})+\mathrm f(a)+\mathrm f(b)=\varphi(t)$ donc $t$ est optimal.

---

### 2.2.6. Aspects partiques
- **Lecture / écriture :** en pratique, on lit et on écrit dans un fichier octet par octet.

  Or, le codage calculé par l'algorithme de Huffman n'est pas de taille fixe donc on aurait plutôt besoin de lire / écrire bit par bit.

  Un solution simple pour l'écriture consiste à accumuler les bits en attendant d'en avoir assez. Il suffit d'un entier pour implémenter cet accumulateur : si $n=\langle b_1\dots b_k\rangle_2$ avec $k<8$, on peut ajouter le bit $b_{k+1}$ en calculant $\langle b_1\dots b_kb_{k+1}\rangle_2=2n+b_{k+1}$.

  **Problème n°1 :**
  S'il n'y a pas assez de bits pour construire un octet en fin de fichier.

  **Solution n°1 :**
  On complète avec des 0 à la fin pour finir l'octet (cela s'appelle du padding).

  **Problème n°2 :**
  Comment ne pas confondre ces 0 avec le code d'un caractère ?

  **Solution n°2 :**
  On ajoute un octet supplémentaire en fin de fichier qui représente le nombre de 0 ajouté.

  Pour la décompression, il faut déterminer quand on arrive à l'avant-dernier octet pour savoir qu'il faut lire l'octet suivant afin de connaître le nombre de 0 à ignorer dans cet avant-dernier octet. Pour cela, on peut lire le fichier avec 2 octets d'avance pour repérer la fin du fichier, ou alors on peut déterminer à l'avance la taille du fichier et compter le nombre d'octets lus.

- **Stockage de l'arbre :** la connaissance de l'arbre de Huffman est nécessaire pour pouvoir décompresser le fichier. Il faut donc pouvoir le stocker sous la forme d'un fichierqui sera transmis avec le fichier compressé.

  La transformation de l'arbre en fichier s'appelle sérialisation de l'arbre.

  Comme l'arbre de Huffman est binaire strict, il est aisé de le sérialiser : on définit $\text{repr}(t)$ par induction structurelle sur $t$ :

  - $\text{repr}(\text{Feuille},c)=0\underbrace{\text{code}(c)}_{\text{octet représentant }c}$

  - $\text{repr}(g,d)=1\text{ repr}(g)\text{ repr}(d)$

  ```ocaml
  let rec output_tree (f:out_channel) (t:arbre) : unit =
     match t with
     |Feuille c -> output.byte f 0 ; output_byte f (Char.code c)
     |Noeud (g,d) -> output_byte f 1; output_tree f g; output_tree f d

  let rec input_tree (f:in_channel) : arbre = (*désérialisation*)
     match input_byte f with
     |0 -> Feuille(Char.chr (input_byte f))
     |_ -> let g = input_tree f in
           let d = input_tree f in
           Noeud (g,d)
  ```

  **Remarque :** 
  La sérialisation est bien-sûr plus générale que son application aux arbres binaires. contrainte importante : il faut connaître a priori l'encodage utilisé dans la sérialisation pour être capable de désérialiser.

  Il existe des formats standards pour la sérialisation, qui peuvent être générique, par exemple le format JSON, ou bien dédiés à certaines applications, comme le format DIMACS CNF ou le langage DOT pour représenter les graphes.

  **Exemple :**
  ```
  graph G {
    a -- b -- c;
    a -- d;
  }
  ```

  $~~~~~~~~~~~~~\Downarrow$

   G=
   ```mermaid
   graph
      a --- b --- c
      a --- d
   ```

## 2.3. Algorithme de Lempel-Ziv-Welch (LZW)

### 2.3.1. Introduction
L'algorithme de Huffman a 2 inconvénients principaux :
- il est nécessaire de connaître à l'avance l'intégralité du texte pour construire l'encodage ;
- le texte compressé ne suffit pas pour effectuer la décompression, il est nécessaire de l'accompagner par un fichier représentant l'arbre d'encodage.

L'algorithme de LZW répond à ces 2 problèmes :
- il est possible de compresser un flux de données via la construction incrémentale d'un dictionnaire de codes pour les motifs apparaissant dans le texte ;
- il n'y a pas besoin d'informations supplémentaires pour décompresser car il est possible de reconstruire le dictionnaire à la volée lors de la lecture du flux compressé.

---

### 2.3.2. Principe
On construit incrémentalement le dictionnaire en garantissant que pour chaque motif introduit, tous ses préfixes sont déjà présents dans le dictionnaire. En particulier, le dictionnaire est initialé en stockant son code pour chaque caractère posible (via la table ACII). Les codes choisis pour les motifs sont consécutifs et ne dépendent que de l'ordre d'apparition des motif dans le texte. C'est ce qui permet de reconstruire le dictionnaire lors de la décompression en fonction de l'ordre d'apparition des codes.

---

### 2.3.3. Compression
On note :
- $t_0,\dots,t_{n-1}$ le texte
- $d\leftarrow$ dictionnaire construit à partir de la table ASCII (entier entre 0 et 255 associé à chaque caractère, i.e. octet possible)
- $m\leftarrow t_0$
- Pour $i$ de $1$ à $n-1$ :
  - Si $\mathrm d(mt_i)$ est défini :
    - $m\leftarrow mt_i$
  - Sinon :
    - Produire $\mathrm d(m)$ en sortie
    - Ajouter $mt_i$ à $\mathrm d(\text{avec le dernier code dans }d\text{ plus 1})$
    - $m\leftarrow t_i$$
- Produire $\mathrm d(m)$ en sortie

**Rappel :**
Le code ASCII de $a$ est 97 et $b$ est 98.

**Exemple :**
$t=aababaaab$

|$\bold i$|0|1|2|3|4|5|6|7|8|
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
|$\bold m$|$a$|$a$|$b$|$a$|$ab$|$a$|$aa$|$a$|$ab$|
|**Sortie**|97|97|98||257||256||257|

Dictionnaire :
- (aa,256)
- (ab,257)
- (ba,258)
- (aba,259)
- (aaa,260)

**Attention :**
Ce n'est pas un code préfixe donc les codes doivent être de taille fixe pour permettre la décompression.

**Problème :**
Si tous les codes sont sur $k$ bits, le dictionnaire peut contenir au plus $2^k$ entrées donc il y a un risque de saturation.

Pour résoudre ce problème, il y a plusieurs options :
- On efface la dictionnaire lorsqu'il arive à saturation et on repart de zéro comme si on travaillait sur un nouveau fichier. On produit un code spécial pour signaler efficacement. Un code peut donc représenter plusieurs motifs selon sa position dans le texte compressé ;
- On ajoute un bit aux codes, ce qui revient à doubler la taille du dictionnaire (comme un tableau dynamique). Comme l'algorithme de décompression recontruit incrémentalement le dictionnaire, la saturation est détectée et on sait quand il faut lire des codes de taille $k+1$.

---

### 2.3.4. Décompression
On reconstruit le dictionnaire en parallèle de la lecture des codes. Le premier code est nécessairement le code ASCII du premier caractère du fichier. Pour les codes suivants, on a besoin de se souvenir du dernier code lu : notons $c_0$ le dernier code lu et $c_1$ le code en cours de lecture. Le code $c_1$ correspond à un mot de la forme $xs$ où $x$ est un caractère et $s$ un mot potentiellement vide et correspond à un certain mot $u$. Au moment de la production de $c_0$, le motif $m$ vaut $u$ et $m$ est remplacé par le caractère $t_i$ en cours de lecture. Comme ce caractère est le premier du motif associé au prochain code produit, i.e. $c_1$, on sait que $t_i=x$. On sait alors que le motif $ux$ doit être inséré dans le dictionnaire. Ainsi, on effectue les mêmes opérations sur le dictionnaire que l'algorithme de compression, mais avec un temps de retard.

**Exemple :**
||97|97|98||257|256|257|
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
|$\bold i$|0|1|2|3|4|5|
|$\bold u$|$a$|$a$|$b$|$ab$|$aa$|$ab$||

Dictionnaire :
- (aa,256)
- (ab,257)
- (ba,258)
- (aba,259)
- (aaa,260)

Sortie : $aababaaab$

**Problème :**
Comme on construit le dictionnaire avec un temps de retard, il est possible que le dernier code lu ne soit pas encore dans le dictionnaire.

**Exemple n°1 :**
$t=aaa$

|$\bold i$|0|1|2|
|:-:|:-:|:-:|:-:|
|$\bold m$|$a$|$a$|$aa$|
|**Sortie**|97||256|

Dictionnaire :
- (aa,256)

**Exemple n°2 :**
||97|256|
|:-:|:-:|:-:|
|$\bold i$|0|1|
|$\bold u$|$a$||

Dictionnaire : $\varnothing$

Sortie : $a$?

**Remarque :**
Le code qui pose problème vaut nécessairement la taille du dictionnaire donc correspond au dernier code inséré dans le dictionnaire par l'algorithme de compression à ce stade de la lecture.

**Solution :**
En remarquant les notations pécédentes, $c_1=|d|$ est le code inséré dans le dictionnaire par l'algorithme de compression au moment de la production de $c_0$. Donc le motif associé à $c_1$ s'écrit $ux$ où $u$ est associé à $c_0$ et $x$ la lettre lue à ce moment. Or, comme l'algorithme de compression repart du motif $m=x$ au moment de la production de $c_0$, $x$ est la première lettre du motif associé à $c_1$, i.e. $ux$. Comme $u$ est non vide, $x$ est donc aussi la première lettre de $u$ et on peut reconstruire le motif $ux$ associé à $c_1$.

**Algorithme :**
- $d\leftarrow$ dictionnaire construit à partir de la table ASCII
- Produire $\mathrm d(c_0)$ en sortie
- Pour $i$ de 1 à m-1 :
  - Si $c_i<|d|$ :
    - Produire $\mathrm d(c_i)$ en sortie
    - $x\leftarrow$ première lettre de $\mathrm d(c_i)$
  - Sinon (on sait que $c_i=|d|$) :
    - $x\leftarrow$ première lettre de $\mathrm d(c_{i-1})$
    - Produire $\mathrm d(c_{i-1})x$ en sortie
  - Ajouter $\mathrm d(c_{i-1})x$ au dictionnaire

**Code :**
$c_0,\dots,c_{m-1}$