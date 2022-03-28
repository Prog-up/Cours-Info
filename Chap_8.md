Chapitre 8 : Logique
===
# 1. Introduction
La logique est un domaine mathématique dont l'objet d'étude est l'ensemble des propriétés que l'on peut exprimer, leur valeur de vérité et la notion de démonstration. La logique propose un cadre formel pour manipuler ces notions, où l'on distingue la syntaxe, i.e. la manière d'exprimer les propriétés de la sémantique,i.e. des interprétations que l'on peut donner à la syntaxe.

Les démonstrations, vues en tant qu'objets mathématiques, ne seront étudiées qu'en MPI.

# 2. Syntaxe des formules logiques
## 2.1. Logique propositionnelle

---
### 2.1.1. Introduction
On décompose les propriétés que l'on cherche à exprimer pour faire ressortir leur structure logique. Les énoncés que l'on ne peut pas décomposer sont appelés atomes. En logique propositionnelle, on abstrait les atomes en des variables dites propositionnelles.

---
### 2.1.2. Définition : formules de la logique propositionnelle
Soit $V$ un ensemble de variables propositionnelles. On définit inductivement l'ensemble $\mathcal{F}$ des formules de la logique proportionnelle par :

$\dfrac{x\in V}{x\in\mathcal{F}}$
$\dfrac{\varphi\in\mathcal{F}}{\neg\varphi\in\mathcal{F}}$
$\dfrac{\varphi_1\in\mathcal{F}\;\varphi_2\in\mathcal{F}}{\varphi_1\vee\varphi_2\in\mathcal{F}}$
$\dfrac{\varphi_1\in\mathcal{F}\;\varphi_2\in\mathcal{F}}{\varphi_1\wedge\varphi_2\in\mathcal{F}}$
$\dfrac{\varphi_1\in\mathcal{F}\;\varphi_2\in\mathcal{F}}{\varphi_1\rightarrow\varphi_2\in\mathcal{F}}$

On appelle :
- $\neg$ la négation
- $\vee$ la disjonction
- $\wedge$ la conjonction
- $\rightarrow$ l'implication

On appelle aussi équivalence le symbole $\leftrightarrow$ définit par $\varphi_1\leftrightarrow\varphi_2=(\varphi_1\rightarrow\varphi_2)\wedge(\varphi_2\rightarrow\varphi_1)$

---
### 2.1.3. Remarque
Malgré leur nom, les symboles de la définition précédente n'ont aucune signification. Le sens des symboles tient du domaine de la sémantique. On parle ici de syntaxe abstraite. On peut utiliser une autre représentation pour les syntaxes abstraites, appelée grammaire, qui s'écrit comme suit :

$\varphi::=x|\neg\varphi|\varphi_1\vee\varphi_2|\varphi_1\wedge\varphi_2|\varphi_1\rightarrow\varphi_2$ où x parcourt $\vee$.

L'étude précise des grammaires relève du programme de MPI.

---
### 2.1.4. Vocabulaire
Les symboles $\neg,\vee,\wedge,\rightarrow$ et $\leftrightarrow$ sont appelés connecteurs logiques. Ce sont eux qui définissent la structure logique des énoncés. Le nombre d'arguments d'un connecteur logique est appelé son arité.

---
### 2.1.5. Représentation des formules
On représente généralement les formules de manière linéaire en ajoutant des parenthèses pour désambiguïser la lecture.

Par exemple, $p\vee q\wedge r$ peut se lire :
- $p\vee (q\wedge r)$
- $(p\vee q)\wedge r$

Par convention, la négation est prioritaire sur les autres connecteurs, donc $\neg p\vee q$ se lit $(\neg p)\vee q$ et pas $\neg(p\vee q)$.

En raison de leur définition inductive, les formules ont une représentation arborescente naturelle : chaque règle d'inférence utilisée définit un symbole de tête / connecteur principal qui est la racine du sous-arbre correspondant.

**Exemple :**
$p\rightarrow(\neg q\vee r)$ est représentée par :

<p align="center">
 <img src="Pictures/Screenshot_20220328-165927__02.jpg" alt="drawing" width="300">
</p>

**Remarque :**
On obtient un arbre (binaire) dont les nœuds internes sont les connecteurs logiques et les nœuds externes sont les atomes. L'arité d'un connecteur est l'arité du nœud correspondant.

L'écriture linéaire de la formule correspondant au parcours en profondeur infixe, en adoptant une représentation préfixe pour les nœuds d'arité 1.

On pourrait envisager d'utiliser les parcours préfixe / postfixe pour représenter les formules.

### 2.1.6. Vocabulaire
- Une sous-formule d'une formule $\varphi$ donnée est la formule associée à un sous-arbre de l'arbre représentant $\varphi$.

 On définit inductivement l'ensemble $SF(\varphi)$ des sous-formules de $\varphi$ par :

 $\forall x\in V, SF(x)$ $SF(\neg\varphi)=\{\neg\varphi\}\cup SF(\varphi)$

 $\forall\circ\in\{\vee;\wedge;\rightarrow\},SF(\varphi_1\circ\varphi_2)=\{\varphi_1\circ\varphi_2\}\cup SF(\varphi_1)\cup SF(\varphi_2)$

 **Exemple :**
 $SF(p\rightarrow(\neg q\wedge r))=\{p\rightarrow(\neg q\vee r);\neg q\vee r;p;\neg q;r;q$\}

- La taille $|\varphi|$ d'une formule $\varphi$ est le nombre de connecteurs logiques de la formule, i.e. le nombre de nœuds internes de l'arbre $A_\varphi$ associé à $\varphi$.

 **Proposition :**
 $|\dfrac{|A_\varphi|-1}{2}\le|\varphi|\le|A_\varphi|-1$

 **Démonstration :**
 L'arbre $A_\varphi$ contient au moins une feuille donc $|\varphi|\le|A_\varphi|-1$
  (cas d'égalité pour $\varphi$ de taille $n$ : $\varphi=\underbrace{\neg\neg...\neg}_{\text{n fois}} p$)

 $A_\varphi$ est un arbre binaire ayant |\varphi| noeuds internes, donc il a au plus $|\varphi|+1$ feuilles (Chap 6 1.1.10.) donc $A_\varphi\le|\varphi|+|\varphi|+1=2|\varphi|+1$.

- La hauteur d'une formule est la hauteur de l'arbre associé, i.e. le nombre maximal de connecteurs à traverser pour atteindre une variable proportionnelle.

 **Exemple :**
 La hauteur de $p\rightarrow(\neg q\vee r)$ est 3.

---
## 2.2. Logique du premier ordre
---
### 2.1.1. Définition : langage du premier ordre
Un langage du premier ordre est défini par une signature $\Sigma$, composée de :
- symboles de fonction, chacun muni d'une arité $k\in\mathbb N$. Les symboles de fonction d'une arité 0 sont appelés symboles de constante.
- symboles de prédicat ou de relation, chacun muni d'une arité $k\in\mathbb N$. Les symboles de fonction d'une arité 0 sont appelés symboles de constante propositionnelle.

---
### 2.2.2. Exemple
Le langage de la théorie des ensembles est défini par la signature suivante :
- symboles de fonction :
 - $\empty$ (arité 0)
 - $\{.\}$ (arité 1)
 - $.\cup.$ et $.\cap .$ (arité 2)
 - $.^c$ (arité 1)
- symboles de prédicat :
 - $.=.$, $.\subseteq.$, $.\in.$ (arité 2)

---
### 2.2.3. Définition : termes et formules de la logique du premier ordre
Soit $\Sigma$ une signature et $\vee$ un ensemble de variables. $\Sigma$ et $\vee$ définissent des ensembles de termes et de formules via grammaires suivantes :
- Terme : $t::=x|f(t_1,...,t_k)$
  où
 $\left\{\begin{array}{ll}
   x\text{ parcours }\vee
   \\
   (f,k)\text{ parcourt les symboles de fonction et leur arité}
 \end{array}\right.$

- Formules : $\varphi::=p(t_1,...,t_k)|\neg\varphi|\varphi_1\vee\varphi_2|\varphi_1\wedge\varphi_2|\varphi_1\rightarrow\varphi_2|\forall x.\varphi|\exists x.\varphi$
  où
 $\left\{\begin{array}{ll}
   x\text{ parcours }\vee
   \\
   (p,k)\text{ parcourt les symboles de prédicat et leur arité}
 \end{array}\right.$

On appelle :
- $\forall$ le qualificateur universel
- $\exists$ le quantificateur existentiel

Les atomes de cette logique sont les formules de la forme $p(t_1,...,t_k)$.

$\exists!x,P(x)\equiv\exists x(P(x)\wedge\forall y.(P(y)\rightarrow y=x))$

On parle de logique du 1er ordre car on ne peut quantifier que sur des variables représentant des termes. Si l'on peut quantifier sur des variables représentant des formules, on parle de logique du second ordre.

---
### Exemple
En théorie des ensemble, la formule $(\forall A.\forall B.A\cap B\subseteq A)\wedge\empty\subseteq A$ est représentée de manière arborescente par :

<p align="center">
 <img src="Pictures/Screenshot_20220328-171237__01.jpg" alt="drawing" width="300">
</p>

---
### Remarque
- La logique du premier ordre est aussi appelée calcul des prédicats
- Dans une formule du premier ordre, les variables peuvent être "capturées" par un quantificateur ou indépendantes de toute quantification

 On peut voir une formule comme une propriété des variables indépendantes de toute quantification et donc remplacer ces variables par des termes concrets.

- Le calcul propositionnel est un cas particulier du calcul des prédicats où il n'y a pas que des constantes propositionnelles (les quantificateurs et les termes deviennent inutiles).