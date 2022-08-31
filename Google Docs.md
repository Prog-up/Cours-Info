# Chapitre 1 : Bases de programmation


[TOC]



# 



1. 
1. Introduction

## 1.1 Définition (paradigmes de programmation)

Les langages de programmation peuvent répondre à différentes approches de la programmation appelées paradigmes qui conditionnent la manière dont on écrit un programme.

**Principaux paradigmes :**



* impératif : les programmes sont des séquences d’instructions qui affectent l'état de la machine (mémoire).
* déclaratif : les programmes sont constitués de déclarations/définitions qui ne sont pas conditionnées par l’état de la machine.

**Il se décline en paradigme :**



* fonctionnel : les objets déclarés sont des fonctions (au sens mathématique, que l’on peut appeler sur des arguments pour obtenir un résultat).
* logique : les objets déclarés sont des prédicats logiques (des contraintes), le résultat d’un programme est l’ensemble des valeurs qui satisfait les contraintes.


## 1.2. Langages au programme

OCaml : développé à Inria à partir des années 1980, particulièrement adapté à la programmation fonctionnelle (mais adapté aussi aux programmation impératives et orientés objet).

C : développé par Bell Labs à partir des années 1970, sont fonctionnement est impératif.



2. 
2. Programmation fonctionnelle

## 2.1. Bases de langage OCaml



        1. 
2.1.1. Déclarations
Une déclaration permet d’associer une valeur à un nom, écrit de façon permanente (déclaration globale) sert temporairement (déclaration locale). La valeur est donnée par une expression (objet de base en OCaml).

**Syntaxe :**



* liaison globale : `let &lt;nom>=&lt;expression>`
* liaison locale : `let &lt;nom>=&lt;expression> in &lt;expression>`

**Exemples :**

`let n = 10+2;;` -> réponse d’OCaml :	val n : int = 12

`let n = 5 in n*n;;` ->			val _ : int = 25

`n*n;;` ->					val _ : int 144

`let x = let n = sin n*n;;` ->		val x : int 25

**Remarque :** 

On appelle variable un nom associé à une valeur. C’est la valeur de l’expression au moment de la déclaration qui donne la valeur de la variable.



**Exemples :**


```
let a = 1;;
let b = a+1;;
let a = 2;; (*ici on définit une nouvelle variable en écrasant le nom a*)
```


**Déclaration simultanée : **


```
let <nom>=<expression> and <nom>=<expression>
```


**Exemples :**


```
let a = 3 and b = 2 in a+b;; mais pas let x = 1 and y = x+1;;
```


Car x n’est pas déclaré au préalable.

⚠ `let x = 1 in let y = x+1;;` -> interdit car on définit une variable locale par/avec une variable globale, mais l’inverse fonctionne.



        2. 
2.1.2. Expressions
Les expressions sont construites par combinaison de variables, de constantes (0, 1, …) de fonctions et de constructions syntaxiques renvoyant une valeur (liaison locale par exemple). Chaque expression est associée à un type qui décrit la nature de sa valeur et qui est automatiquement reconnu.

**Les types de base sont :**



* unit : il est associé à une unique valeur, void notée ()
* int : les entiers (bornés). Pour les construire, on peut utiliser des constantes :
    * des constantes : 0, 1, 2 …
    * les entiers minimal et maximal : 
        * min_int
        * max_int
    * des fonctions : +, -, *, / (quotient dans la division euclidienne), mod (reste dans la division euclidienne)

**Exemples :**

`2*5/3;;` -> = 3

`5/3*2;;` -> = 2

`(1+3) mod 2;;` -> = 0

`1+3 mod 2;;` -> = 2



* float : « les réels »
* constantes : 3,14159 ; 1,789e3
* fonctions : +. ; *. ; -. ; /. ; ** (⚠ pas de point, fonction puissance) ; sqrt (√), log (logarithme népérien), exp, sin, cos, tan, asin, acos, atan…

⚠ Ne pas oublier le point :

2.5 *. 2. mais pas 2.5 *. 2



* char : les caractères, notés entre ‘’ (exemple : ‘a’, ‘b’…)
* string : les chaînes de caractères, notées entre “ ” (exemple : “abc”, “a”…)

**Fonctions utiles :**



* ^ : concaténation (exemple : “bon” ^ “jour”->“bonjour”)
* String.length : longueur (exemple : String.length“”->=0)
* float_of_int : converti float en int
* int_of_float : converti int en float
* les couples : si t1 et t*2 sont des types, t1*t2 est le type des couples dont la première composante est de type t1 et la seconde est de type t2 (exemple : 1, 3.) est de type int + float.

**Fonctions :**



* fst, snd : pour obtenir les composantes
* boal : les valeurs de vérité
* constantes : true, false
* fonctions : not, && (et), || (ou)

**Évaluation paresseuse :**



* exp 1 && exp 2 n’évolue pas exp 2 si exp 1 s’évalue à false
* exp 1 || exp 2 n’évolue pas exp 2 si exp 1 s’évalue à true
* comparaison : = ; &lt;> (négation de =) ; &lt; ; > ; ≤ ; ≥

Ces fonctions de comparaison peuvent être utilisées sur tous les types : on parle de polymorphisme. 

**Exemple : **


```
"chameau" ≤ "chat" (*ordre lexicographique*)
```




        3. 
2.1.3. Filtrage par motif
Le filtrage permet de tester la valeur d’une expression et de renvoyer une valeur différente selon le cas dans lequel on se trouve.

**Syntaxe :**


```
match <expression> with
|<motif> -> <expression>
|<motif> -> <expression>
```


La valeur de l’expression est comparée aux motifs dans l’ordre et on s’arrête au premier qui correspond.

**Motifs :**



* constantes
* nom : on fait une déclaration locale associant le nom à la valeur de l’expression.
* _ : n’importe quelle valeur est autorisée
* combinaisons de motifs :
    * via des constructions syntaxiques (exemple : (a, _))
    * motifs gardés : on associe un motifs à une expression booléenne : 

        &lt;motif> when &lt;expression>


**Exemples :**


```
match x with
|0. -> 0.
|_ -> 1./.x
match x with
|y when y < 0 -> -y
|_ -> x
(*calcul de valeur absolue*)
```




**Remarque : **

On peut réunir des motifs pour renvoyer la même valeur à condition qu’ils contiennent les mêmes noms.

**Exemples :**


```
match (a,b)|(0, x) -> 0
|(x, y) -> x + y
```


On peut imbriquer les filtrages :


```
match (a, b) with
|(x, 0) |(0, x) -> begin match with x with
|0 ->-1
|_ ->0
end
|(x, y) ->x + y
```


On peut utiliser le filtrage pour récupérer les composantes d’un couple :


```
match x with
|(a, b) -> ... 
```


On préfère : `let (a, b) = x in ... `

 ⚠ On fait attention à couvrir tous les cas possibles avec des motifs.



        4. 
2.1.4. Fonctions
Déclarations similaires aux variables, en ajoutant les paramètres.

**Syntaxe : **


```
let <nom fonction> <nom paramètre> = <expression>
```


**Exemple :** 


```
let f x = x + 1;; définit f : f(x) = x + 1
```


**Application :** 


```
f 2 ou bien f(2)
```


⚠ `f2*3	(f2)*3	f(2+3)`

La valeur de l’argument est calculée avant le calcul dans la fonction (passage par valeur). 

**Plusieurs paramètres : **


```
let g x y = x + y
```


On dit que cette fonction est curryfiée (du nom de Haskell Curry).

**Version décurryfiée : **


```
let g (x, y) = x + y
```


Les fonctions currifiées sont dites d’ordre supérieur, c’est-à-dire qu’elles renvoient des fonctions par application partielle avec arguments.

**Exemple : **

g est la fonction f(y) = 1 + 1 -> elle est égale à f 1



**Type d’une fonction : **

Les types des paramètres séparés par des flèches suivis du type du résultat.

**Exemple : **

g est de type int -> int -> int

**Fonctions anonymes : **

fonctions sans nom

**Syntaxe : **


```
fonction <nom> -> <expression>
```


⚠ Un seul paramètre est autorisé

**Exemple : **


```
let g : function x -> function y -> x+y 
(*s'abrège en*) 
let g = function x y -> x+y
```


**Remarque : **

La fonction est compatible avec le filtrage

**Exemple : **


```
function
|0. -> 1
|x -> sin x/.x
```


Il est possible de préciser le type des paramètres et du résultat d’une fonction.

**Syntaxe : **


```
let <nom> (<nom paramètre> : <type>) : <type-res> = ...
```



<table>
  <tr>
   <td><code>let test0(n:int):bool=</code>
   </td>
   <td>
   </td>
   <td rowspan="2" >} où let test 0 : int -> bool : function n -> n = 0
   </td>
  </tr>
  <tr>
   <td><code>   match x with \
   |0 -> true \
   |_ -> false;;</code>
   </td>
   <td>} où n ☰ 0 
   </td>
  </tr>
</table>


Lorsque l’on peut utiliser n’importe quel type (polymorphisme), on le dénote par suivie d’une lettre (d’abord a, puis b … ).

**Exemple :**


```
let compare (x : 'a) (y : 'a) : int =
   match y with
   |t when t = x -> 0
   |t when t < x -> 1
   |_ -> -1;;
```



### 


### 2.1.5. Commentaires

En Ocaml, on écrit les commentaires entre (* et *)


## 2.2. Récursivité


### 2.2.1. Motivation

On veut dessiner une spirale

**Problème :**

Calculer les coordonnées des angles est fastidieuse

**Idée :**



* tracer le 1er segment
* tracer une spirale de largeur l - Δ, tournée de 90°

**Algorithme :**

Spirale(l, Δ) :

	Si l &lt;= 0 alors Stop

	Sinon

		Tracer un segment de longueur l

		Tourner de 90°

		Spirale(l - Δ, Δ)

**Remarque :**

C’est un algorithme qui fait référence à lui-même.


### 2.2.2. Intro informelle

Un objet (algorithmique, structure de données, image…) est récursif en la définition de cet objet fait appel : un objet de même nature.

**Exemples :**



* Processus paramétré dont la définition : fait appel à ce même processus avec des paramètres plus simple (ex : suite récurrente) ;
* Image contenant en elle-même des images similaires (ex : spirale, fractales, par exemple, le triangle de Sierpinski).


### 2.2.3. Fonction récursive en OCaml

On utilise le mot-clé rec pour indiquer qu’une fonction peut faire référence à elle-même, placée juste après le let dans une déclaration de la fonction (même pas une déclaration locale).

**Exemple :**

Calcul récursif de la factorielle en remarquant que n! = n*(n-1)!

let rec fact (n : int) : int = n * fact (n - 1);;

**⚠ On termine par :**

Résultat de fact 10 : Stack overflow doing evaluation (logique récurrence ?)

Il faut un cas de base pour que la fonction s’arrête, ici 0! = 1


```
let rec fact (n : int) = (*en rappel n >= 0*)
   match n with
   |0 -> 1
   |_ -> n * fact (n - 1);;
```



### 2.2.4. Caractéristiques d’un algorithme récursif :



* Un ou plusieurs appels récursif, généralement sur des données de &lt;< taille>> inférieure (taille définie en cas par cas) ;
* Une ou plusieurs conditions d’arrêt, appelées cas de base, où le résultat est calculé sans appel récursif.

**Exemple :**

Calcul des nombres de façon de construire une barrière de longueur n en utilisant des élément de longueur 2 ou 3 noté f(n).

**Cas de base : **



* si n &lt;= 1, f (n) = 0 (impossible)
* si n = 2 ou 3, f (n) = 1 : on utilise l'élément de longueur correspondante.

**Cas général :** 



* si n > 3, on choisit le 1er élément (de longueur 2 ou 3) pris en compte le nombre de façons de construire la longueur restante : f (n) = f (n - 2) + f (n - 3)

**Code : **


```
let rec f (n : int) : int = (*on suppose n >=O*)
   match n with
   |0 |1 -> 0
   |2 |3 -> 1
   |_ -> f(n-2) + (f(n-3))
```



### 2.2.5. Première structure récursive en OCaml : les listes 

**Avertissement : **

Les listes OCaml sont très différentes des listes Python :



* Les listes OCaml sont homogène (tous les éléments sont de même type) ;
* On ne peut accéder directement qu’à la tête de la liste, tel que le 1er élément ;
* On ne peut pas modifier une liste, seulement en créer de nouvelles.

**Schéma des listes : **

Chaque éléments d’une liste possède, en plus de la valeur de la donnée, un &lt;<pointeur>> vers l’élément suivant de la liste (liste simplement chaînée)

Les listes sont de taille finie -> on utilise un marqueur de finir nil (contraction nilil)

Une liste OCaml est soit la liste vide, soit un élément (la tête) associé à une liste contenant le reste des éléments (la queue).

**Code OCaml :**



* type de liste : c’est un type polymorphe, paramétré par un seul type (listes homogènes)
* le type s’écrit ‘a liste
* nil : la liste vide est représenté par []
* association d’un élément et d’une liste : constructeur &lt;<cons>>, noté :: de manière infixe (exemple : x :: [], a<sub>0</sub> :: a<sub>1</sub> :: … :: [])
* sucre syntaxique : on peut écrire [a<sub>0</sub> ; a<sub>1</sub> ; … ; an]
* déconstruction :
    * on accède à la tête par la fonction List.hd (pour head)
    * on accède à la queue par la fonction List.tl (pour tail)
* On utilise plutôt le filtrage pour déconstruire une liste.

**Exemple : **

Calcul de longueur


```
let rec longueur (l : '- list) : int =
   match l with
   |[] -> 0
   |t :: q -> 1 + longueur q;;
```


(En OCaml : List_length)

Comme pour les couples, on peut déconstruire les listes dans une liaison locale :


```
let t :: q = l in ... 
```


Mais c'est fortement déconseillé : contrairement aux couples, il a un autre cas (nil) et OCaml protestera.

**Gammes :**

Test d'appartenance : List.mem : ‘a -> ‘a list -> bool

**Exemple :**


```
let rec mem (x : 'a) (l : 'a list) : bool =
   match f with
   |[] -> false
   |_ when x List_hd l -> true
   |_ -> mem x (List.th l);;
```


**Forme canonique :**


```
let rec mem (x : 'a) (l : 'a list) : bool =   
   match l with
   |[] -> false
   |t :: q -> x = t || mem x q (*⚠ évaluation paresseuse*)
   |t : _ when t = x -> true
   |_ :: q -> mem x q;;
```


**Concaténation :**

On a l'opérateur infixe @

**Exemples :**

[1 ; 2]@[3 ; 4 ; 5] vaut [1 ; 2 ; 3 ; 4 ; 5]


```
let rec concat (l1 : 'a list) (l2 : 'a list) : 'a list =
   match l1 with
   |[] -> l2
   |t :: q -> t :: (concat t l2);;
```


**Test booléens :**



* List-exist : (‘a -> bool) -> bool (test s’il existe un élément qui satisfait la propriété) ;
* List-for-all : (‘a -> bool) -> ‘a list (test si tous les éléments satisfait la propriété) ;
* List-filter : (‘a -> bool) -> ‘a list (renvoie uniquement les éléments qui satisfait la propriété).

**Application point par point :**



* List.map : (‘a -> ‘b) -> ‘a list -> ‘b list)
* List.map f [a<sub>0</sub> ; a<sub>1</sub> ; … ; a<sub>n</sub>] = [fa<sub>0</sub> ; fa<sub>1</sub> ; … ; fa<sub>n</sub>]


### 2.2.6. Cas particuliers de récursivité

**Récursivité croisée/mutuelle :** 

La récursivité peut survenir non pas quand un algorithme s’appelle lui-même, mais quand plusieurs algorithmes dépendent les uns des autres.

**Syntaxe :**


```
let rec f1 args1 = code1
and f2 args2 = code2
...
and fn argsn = coden
```


**Exemple : **Test de parité


```
let rec pair (n : int) : bool : (*n ≥ 0*)
   match n with
   |0 -> true
   |1 -> false
   |_ -> impair (n - 1)
   and impair (n : int) : bool :
      match n with
      |0 -> false
      |1 -> true
      |_ -> pair (n-1);;
```


**Récursivité terminale :** 

Une fonction est récursive terminale si un résultat est le résultat d’un appel récursif sans calcul supplémentaire. Cela permet des optimisations dans la gestion des appels de fonction (cf le cours sur la mémoire des programmes).

**Exemple : **calcul de la somme 

<p id="gdcalert1" ><span style="color: red; font-weight: bold">>>>>>  gd2md-html alert: equation: use MathJax/LaTeX if your publishing platform supports it. </span><br>(<a href="#">Back to top</a>)(<a href="#gdcalert2">Next alert</a>)<br><span style="color: red; font-weight: bold">>>>>> </span></p>

 en terminale : fonction terminale


```
let rec somme (n : int) : int =
   match n with
   |0 -> 0
   |_ -> n + somme (n-1);;
```


**Problème : **somme 500 000 -> « Stack overflow during execution (looping recursion?) »

**Réécriture de manière terminale :**


```
let somme-term (n : int) : int =
   let rec aux (n : int) (acc : int) : int = 
   (*calcule acc +k=0nkk*)
      match n with
      |0 -> rec
      |_ -> aux (n - 1) (acc + n)
   in aux n 0;;
```


Ici, l’accumulation est calculée avant l’appel récursif (passage par valeur) : on économise l’espace mémoire.

**Attention :**

La récursivité n’est qu’un outil comme un autre : on ne l’utilise pas s’il y a plus efficace

let somme-non-rec(n : int) : int = n * (n + 1).


# 3. Efficacité et sûreté des programmes


## 3.1. Complexité


### 3.1.1. Intro

La notion de complexité est une mesure de l’efficacité des programmes/algorithmes.

On distingue complexité temporelle (mesure du temps de calcul) et complexité spatiale (mesure de l’espace mémoire utilisé).

**Attention :**

Ces notions sont très floues : 



* Complexité spatiale : doit-on tenir compte de la mémoire cache ? De l’espace mémoire alloué par le système d’exploitation mais non utilisé) ;
* Complété temporelle : compte-on le temps utilisé par le système pour gérer les appels de fonction ?

Est-ce pertinent de distinguer les temps d’exécution de l’addition de de la multiplication ?

On s’intéresse en général à l’ordre de grandeur de ces quantités et pour la complexité temporelle plutôt au nombre d'opérations élémentaires effectuées.

**Exemple :**


```
let rec max (l:int list) : int =
   match l with
   |[] -> min_int
   |t::q -> match max q with
      |m when m < t -> t
      |m -> m;;
```


**Opérations élémentaires :** 

Décomposition d’une liste en tête est queue/comparaison sur les entiers.

**Complexité temporelle :** 

3 comparaisons élémentaires + 1 appel récursif.

Donc pour chaque élément on a 3 opérations et pour le dernier appel récursif (sur []) on a une seule opération.

Si la liste a n éléments, on a donc 3n + 1 opérations élémentaires.

**Remarques : **



* La complexité dépend de la taille des paramètres ; 
* Les constantes sont en général difficiles à déterminer ; 
* On s’intéresse plutôt à l’ordre de grandeur de la complexité pour de grandes valeurs de la taille des paramètres : on parle de complexité asymptotique.


### 3.1.2. Notation de Bachmann – Landau

Soit (u<sub>n</sub>)

<p id="gdcalert2" ><span style="color: red; font-weight: bold">>>>>>  gd2md-html alert: equation: use MathJax/LaTeX if your publishing platform supports it. </span><br>(<a href="#">Back to top</a>)(<a href="#gdcalert3">Next alert</a>)<br><span style="color: red; font-weight: bold">>>>>> </span></p>

<sub>ℕ</sub>, (v<sub>n</sub>)

<p id="gdcalert3" ><span style="color: red; font-weight: bold">>>>>>  gd2md-html alert: equation: use MathJax/LaTeX if your publishing platform supports it. </span><br>(<a href="#">Back to top</a>)(<a href="#gdcalert4">Next alert</a>)<br><span style="color: red; font-weight: bold">>>>>> </span></p>

<sub>ℕ</sub> des suites d’entiers positifs.

On dit que : 



* u est dominé par v, noté un = O(v<sub>n</sub>), s’il existe c > 0 de N ∈ ℕ tel que pour tout n ≥ N, 

    u<sub>n</sub> ≤ cv<sub>n</sub>

* u détermine v, noté un = Ω(v<sub>n</sub>), s’il existe c > 0 et N ∈ ℕ tel que pout tout n ≥ N, cv<sub>n</sub> ≤ u<sub>n</sub>
* u est de l’ordre de v, noté u<sub>n</sub> = O(v<sub>n</sub>), si un = O(b<sub>n</sub>) et u<sub>n</sub> = Ω(v<sub>n</sub>)

**Proposition (admise) :** règle de calcule



* 

<p id="gdcalert4" ><span style="color: red; font-weight: bold">>>>>>  gd2md-html alert: equation: use MathJax/LaTeX if your publishing platform supports it. </span><br>(<a href="#">Back to top</a>)(<a href="#gdcalert5">Next alert</a>)<br><span style="color: red; font-weight: bold">>>>>> </span></p>

 ⚠ la base du log n’est pas importante
* 

<p id="gdcalert5" ><span style="color: red; font-weight: bold">>>>>>  gd2md-html alert: equation: use MathJax/LaTeX if your publishing platform supports it. </span><br>(<a href="#">Back to top</a>)(<a href="#gdcalert6">Next alert</a>)<br><span style="color: red; font-weight: bold">>>>>> </span></p>



<table>
  <tr>
   <td>
   </td>
   <td rowspan="3" >
{
   </td>
   <td>

<p id="gdcalert6" ><span style="color: red; font-weight: bold">>>>>>  gd2md-html alert: equation: use MathJax/LaTeX if your publishing platform supports it. </span><br>(<a href="#">Back to top</a>)(<a href="#gdcalert7">Next alert</a>)<br><span style="color: red; font-weight: bold">>>>>> </span></p>


   </td>
  </tr>
  <tr>
   <td>
<ul>

<li>

<p id="gdcalert7" ><span style="color: red; font-weight: bold">>>>>>  gd2md-html alert: equation: use MathJax/LaTeX if your publishing platform supports it. </span><br>(<a href="#">Back to top</a>)(<a href="#gdcalert8">Next alert</a>)<br><span style="color: red; font-weight: bold">>>>>> </span></p>


</li>
</ul>
   </td>
   <td>

<p id="gdcalert8" ><span style="color: red; font-weight: bold">>>>>>  gd2md-html alert: equation: use MathJax/LaTeX if your publishing platform supports it. </span><br>(<a href="#">Back to top</a>)(<a href="#gdcalert9">Next alert</a>)<br><span style="color: red; font-weight: bold">>>>>> </span></p>


   </td>
  </tr>
  <tr>
   <td>
   </td>
   <td>

<p id="gdcalert9" ><span style="color: red; font-weight: bold">>>>>>  gd2md-html alert: equation: use MathJax/LaTeX if your publishing platform supports it. </span><br>(<a href="#">Back to top</a>)(<a href="#gdcalert10">Next alert</a>)<br><span style="color: red; font-weight: bold">>>>>> </span></p>


   </td>
  </tr>
</table>




* Si un = O(w<sub>n</sub>) et v<sub>n</sub>=O(w<sub>n</sub>), alors u<sub>n</sub> + v<sub>n</sub> = O(w<sub>n</sub>) 
* Si un = O(v<sub>n</sub>) alors u<sub>n</sub>w<sub>n</sub> = O(v<sub>n</sub>w<sub>n</sub>)

**Exemple :**

u<sub>n</sub> = O(u<sub>n</sub>)

O(1) = O(n) ⚠ Abus de notation


### 3.1.4. Complexité dans le pire cas

On s'intéresse en général, étant donnée un taille d’entrée, à la valeur maximale de la complexité pour les entrées de cette taille

**Remarque :**

« complexité » dénote « complexité temporelle dans le pire cas »

**Vocabulaire :**



* O(1) : on dit que le programme s'exécute en temps/espace constant

**Exemple :**

somme-non-rec (cf 2.2.6)



* O(n) : on parle de complexité linéaire

**Exemple :**


```
let rec recherche (x : 'a)(b : 'a list) : int = 
(*renvoie la position de x dans l (0 pour la tête), -1 si x n'apparaît pas*)
   match l with
   |[] -> -1
   |t ::_ when t = x -> 0
   |_::q -> match recherche x q with
      |-1 -> -1
      |n -> n + 1
```


**Pire cas :** x n’apparaît pas, on va au bout de la liste.

Pour chaque élément, on effectue un nombre fini borné (≤ 5) de comparaisons.

L’appel sur [] (liste vide), nécessite une seule comparaison.

Complexité n ≤ C(n) ≤ 5n + 1 ≤ 6n pour n ≥ 1 donc C(n) = O(n)



* O(n²) : on parle de complexité quadratique (on parle aussi de complexité polynomiale lorsque la complexité est en O(

<p id="gdcalert10" ><span style="color: red; font-weight: bold">>>>>>  gd2md-html alert: equation: use MathJax/LaTeX if your publishing platform supports it. </span><br>(<a href="#">Back to top</a>)(<a href="#gdcalert11">Next alert</a>)<br><span style="color: red; font-weight: bold">>>>>> </span></p>

)où ⍺ > 0.

**Exemple : **suppression des doublons d’une liste


```
let rec suppr.doublons(l : 'a list) : 'a list =
   match l with 
   |[] -> []
   |t::q when List.mem t q -> supr.doublons q
   |t::q -> suppr.doublons q;;
```


**Pire cas :** il n’y a pas de doublons : la fonction parcourt toute la queue à chaque appel, sachant que au i ème appel récursif, la queue est de taille n – i donc la complexité est de l’ordre de 

<p id="gdcalert11" ><span style="color: red; font-weight: bold">>>>>>  gd2md-html alert: equation: use MathJax/LaTeX if your publishing platform supports it. </span><br>(<a href="#">Back to top</a>)(<a href="#gdcalert12">Next alert</a>)<br><span style="color: red; font-weight: bold">>>>>> </span></p>





* O(log n) : on parle de complexité logarithmique

Exemple : recherche dichotomique dans un tableau (on verra ça plus tard)



* O(n log n) : on parle de complexité quasi-linéaire

Exemple : complexité optimale pour le tri d’une liste par comparaison (on verra ça plus tard)



* O(a<sup>n</sup>) pour a > 0 : on parle de complexité exponentielle

Exemple : vérification par force brute de la satisfiabilité d’une forme logique à n variables (on verra ça plus tard)

**Remarque : **on utilise la même terminologie pour O car on se contente en général de majorer la complexité.

Impact sur le temps de calcul : on considère un programme qui s’exécute en 1s pour une entrée de taille n à la complexité donnée


<table>
  <tr>
   <td>O(n)
   </td>
   <td>Temps pour 10m
   </td>
   <td>Temps pour 100m
   </td>
  </tr>
  <tr>
   <td>O(1)
   </td>
   <td>1s
   </td>
   <td>1s
   </td>
  </tr>
  <tr>
   <td>O(log n)
   </td>
   <td>1,003s
   </td>
   <td>1,007s
   </td>
  </tr>
  <tr>
   <td>O(n)
   </td>
   <td>10s
   </td>
   <td>1m40s
   </td>
  </tr>
  <tr>
   <td>O(n log n)
   </td>
   <td>14,7s
   </td>
   <td>3m13s
   </td>
  </tr>
  <tr>
   <td>O(n²)
   </td>
   <td>1m 40s
   </td>
   <td>2h46m40s
   </td>
  </tr>
  <tr>
   <td>O(2<sup>n</sup>)
   </td>
   <td>10^19 années
   </td>
   <td>10^289 années
   </td>
  </tr>
</table>



### 3.1.4. Relation de récurrence

Relation de la forme : C(n) = C(n - 1) + a n



On résout directement : C(n) = C(n - 1) + a n

				= C(n - 2) + a(n - 1) + a n

				= … (par récurrence)

				= C(1) + a(somme de n à k = 1 de k)

				= C(1) + ((n - 1)(n + 2)) / 2

				= O(n²)

**Exemple :** tri par insertion : on construit une liste triée en insérant un à un les éléments


```
let rec insert (x : 'a) (l : 'a list) : 'a list =
   (*on insère x dans l triée par ordre croissant*)
   match l with
   |[] -> [x]
   |t::q when t ≤ x -> t::(insert x q)
   |_ -> x::l;;
```


**Pire cas :** on parcourt toute la liste (n est le plus grand l) -> O(n)


```
let rec tri-insertion (l: 'a list) : 'a list =
   match l with
   |[] -> []
   |t::q -> insert t (tri-insertion q);;
```


Pour une liste de taille n, on obtient C(n) = C(n-1) + O(n) = 0(n²)

dont C(n-1) -> appel en q et O(n) -> décomposition de l + insertion

⚠ On manipule des migration, i.e. des “inégalités de récurrence”

**Pire cas atteint :** si la liste est triée par ordre décroissant.

**Meilleur cas :** O(n) si l est triée par ordre croissant.

Relation de la forme C(n) = 2(n/2) + f(n)

**Remarque :**



* L’ordre de grandeur va dépendre de celui de f(n) ; 
* n n’est pas toujours pair -> il faudrait considérer C(n) ≤ 2C([n/2])+f(n) en utilisant la croissance de la complexité ; 
* En pratique, cela ne change pas l’ordre de grandeur.

**Exemple :** Tri fusion

On coupe la liste en 2 listes de même longueur (à une unité près), que l’on tri récursivement, avant de les fusionner (exemple d’algo diviser pour régner)


```
let rec partition (l : 'a list) : 'a list * 'a list (*couple de listes*) =
   match with
   |[] -> []
   |[t] -> [t], []
   |a::b::q-> let (l1, l2) = partition q in 
      (a ::l1, b::l2);;
(*a = tête, b::q = queue (b = tête de la queue, q = queue de la queue)*)
```


C(n) = C(n – 2) + a = O(n) avec 7 ≥ a ≥ 5



**Par récurrence :** C(n-2) + a = C(n mod 2) + a[n/2]


```
let rec fusion (l1 : 'a list) (l2 : 'a list) : 'a list =
   (*fusionne 2 listes triées pour renvoyer une liste triée*)
   match l1, l2 with
   |[], _ -> l2
   |_, [] -> l1
   |t1::q1, t2::q2 when t1 ≤ t2 -> t1::fusion q1 l2
   |t1::q1, t2::q2 -> t2::fusion l1 q2;;
```


C(n<sub>1</sub>, n<sub>2</sub>) = max(C(n<sub>1</sub>, n<sub>2</sub> – 1) + constante, (C<sub>1</sub> – 1, n<sub>2</sub>) + constante)

**Pire cas :** 

On parcours tous les éléments des deux listes -> C(n<sub>1</sub>, n<sub>2</sub>)=O(n<sub>1</sub> + n<sub>2</sub>)


```
let rec tri-fusion (l : 'a list) : 'a list =
   match l with
   |[] |[_] -> l (*cas de liste vide et liste contenant un unique élément*)
   |_ -> let (l1, l2)=partition de l in
      fusion (tri-fusion l1) (tri-fusion l2);;
```


C(n) = 2C(n/2) + O(n)

dont 2C(n/2) -> tri de l1 et l2 et O(n) -> partition + fusion de deux listes de longueur n/2

**En réalité :** 

C(n) = C([n/2])+C([n/2])+O(n)

**Intuition :** 

n =2^p

C(n) = 2 C(n / 2) + a n

	= 2 (2 C(n / 4) + a (n / 2) + a n

	= 4 C(n / 4) + 2 a n

	= 2<sup>n</sup> C(n / 2<sup>n</sup>) + 2 a n

	= … 

= 2<sup>k</sup> C(n / 2<sup>k</sup>) + k a n 

= … 

= 2<sup>p</sup> C(1) + p a n

	= (p a + 1) n

	= (log<sub>2</sub>(n) a + 1) n

	= O(n log n)

((n = 2<sup>p</sup>) -> (log2(n) = log2(n) (2<sup>p</sup>) = p)

On veut montrer qu’il existe C > 0, N ∈ ℕ tel que pour tout n ≥ N, C(n) log n

N > 1 car log 1 = 0 &lt; C(1)

C(2) = 2 C(1)+ a 2 ≤ 2 c log 2 pour c assez grand

C(3) = C(1) + 2C(2) + a 3 ≤ 3 c log 3 pour c assez grand

**Par récurrence :** C(n) ≤ C([n / 2]) + C([n / 2]) + a n

			≤ [n / 2] c log([n / 2]) + [n / 2] c log([n / 2]) + a n

			≤ n c log([n / 2]) + a n 

			≤ n c log(n + 1 - n c log(2) + a n

			≤ n c log n pour c assez grand

**Confère cours prof sur Moodle :** [Étude de la complexité du tri fusion](https://documentcloud.adobe.com/link/track?uri=urn:aaid:scds:US:a246b1be-f6d0-4d34-b465-1033e340b0df)


### 3.1.5. Complexité spatiale

Il peut être intéressant d’utiliser une solution plus coûteuse en mémoire pour gagner en complexité temporelle. On parle de comparaisons tempo-mémoire.

**Précision :** 

La complexité spatiale est l’espace mémoire utilisée <span style="text-decoration:underline;">en plus</span> de celui occupé par les paramètres.

**Exemple : **

Calcul du n<sup>ème</sup> terme de la suite de Fibonacci : F<sub>0</sub>=F<sub>1</sub> = 1 et F<sub>n+2</sub>=F<sub>n+1</sub>+F<sub>n</sub>

**Solution naïve :**

let rec fibo (n : int) : int =

	match n with

	|0 |1 -> 1

	|_ -> fibo (n - 1) + fibo(n - 2);;

**Espace :** O(1) (en négligeant la pile)

**Temps :** C(n+2) = C(n+1)+C(n)

-> On retrouve la récurrence de la suite de Fibonacci

-> C(n)=O(Fn)=O(θ<sup>n</sup>) avec θ nombre d’or

-> complexité exponentielle

**Mémorisation : **

On retient les termes pour éviter de les recalculer

let fibo (n:int):int=

	let rec aux (n:int):int list=

		match n with

		|0 -> [1]

		|1 -> [1 ; 1]

		|_ -> let l = aux(n-1) in

			let f1 = List.hd l in

			let f2=List.hd(List.tl l) in

			f1+f2)

		in List.hd(aux n)

(*exemple de programmation dynamique)

**Espace : **O(n)

**Temps : **C(n) = C(n-1) + a = O(n)

**Optimisation : **

On ne garde que les 2 derniers termes

let fibo (n:int) :int=

	let rec aux(n:int):int*int=

		match n with

		|0 |1 -> (1, 1)

		|_ -> let (a, b) = aux(n-1) in

			(a+b, a)

	in fst (aux n)

**Espace : **O(n)

**Temps : **O(n)


### 


### 3.1.6. Complexité en moyenne

Lorsqu’il y a une grosse différence entre la complexité dans le pire cas et celle dans le meilleur cas, on s'intéresse à la moyenne des complexités pour toutes les entrées d'une table donnée.

**Exemple : **retour sur la fonction recherche

let rec recherche (x :’a) (l :’a list) : int=

	match l with

	|[]-> -1

	|t ::_ when t = x -> 0

|_::q -> match recherche x q with

		|-1-> -1

		|n – 1 -> n+ 1

**Pire cas : **O(n)

**Meilleur cas: **O(1)

**Problème : **Il y a une infinité de listes de taille n

**Restriction : **

On cherche un élément de la liste en supposant l élément tiré aléatoirement uniformément -> n p possibilités.

On cherche l’élément de position i : on affecte i+1 fois un nombre constant c d’opérations -> moyenne 1/n… (INCOMPLET)

**Conclusion : **

On est plus souvent proche du pire cas, que du meilleur.


## 3.2. Spécification et tests


### 3.2.1. Rappels

Lors de la déclaration d’une fonction, il est possible de préciser la signature, i.e. le type de ses paramètres et de son résultat.

Lorsque le code d’une fonction s’appuie sur des hypothèses concernant ces paramètres (qui ne sont pas garanties par la signature), il est recommandé de les préciser en commentaire.

**Exemple :**

let rec somme ( n : int ) : int =

	(*on suppose n positif*)

	match n with

	|0 -> 0

	|_ -> n + somme(n-1);;


### 3.2.2. Spécification d'une fonction

Fournir la spécification d’une fonction, c’est préciser quelles sont les données attendues en paramètres (type et hypothèses) et expliquer ce qu’elle calcule (type et nature du résultat vis à vis des paramètres en entrée).

**Remarque**

Il n’y a pas vraiment de standard pour l’écriture d’une spécification, le plus important c’est d’être précis.

**Exemple**

Fonction insert :



* paramètres : 	+ élément w de type ‘a

			+ liste l triée de type ‘a list



* résultat : liste triée contenant x et tous les éléments de l*)

let rec insert (x :’a) (l :’a list) : ‘a list = …


### 3.2.3. Motivation des test



* Le typage en OCaml permet de vérifier statiquement la cohérence de l’écriture des expressions (statique = qui se passe avant l’exécution du code) ; 
* Les tests sont une manière dynamique de vérifier que l’exécution d’un programme se passe bien (dynamique = qui se passe pendant l’exécution du code) ; 
* Faire des tests permet de détecter les erreurs du programmeur et de l’utilisateur.

**Exemple :** erreur de l’utilisateur

L’utilisateur ne fournit pas un paramètre qui vérifie la spécification (contrainte de type ou de valeur). Il y a des fonctions de lecture qui permettent d’interrompre le programme pour demander des valeurs à son utilisateur :



* read_int : unit -> int
* read_float : unit -> float
* read_line : unit -> string

(utilisation comme fonction sans arguments : let a = read_int();;)

**Erreur**

Si on exécute somme(read_int()) et si l’utilisation écrit :



* -2 -> « Stack overflow... »
* 2.3 -> « Exception : Failure ‘’int_of_string’’ »

**Exemple :** erreur pour le programmeur



* Faute de frappe (+1 ou lieu de +2) ; 
* Incompréhension sur le résultat d’une fonction.

**Exemple :**

Que calcul x mod 3 ? Le reste de la division euclidienne de x par 3 si x est positif.

Si x est négatif, le résultat est négatif : le reste moins 3.


### 3.2.4. Détecter une erreur pour détecter un erreur

**Il faut pouvoir :**



1. exprimer des contraintes : expression booléenne ;
2. vérifier que les contraintes sont satisfaites , i.e. qu’elles s’évaluent en true.

**Possibilité :** expression conditionnelle.

**Syntaxe :** if &lt;expression> then &lt;expression> else &lt;expression>

La première expression doit être de type bool, l’expression conditionnelle s'évalue en la valeur de l’expression après « then » si ce booléen s’évalue en true et celle de la dernière expression sinon 

Les deux expressions (branches then et else doivent être de même type. 

Si la branche then est de type unit, la branche else est facultative

if b then e est équivalent à if b then e else ()


### 3.2.5. Signaler une erreur

Pour signaler une erreur, on peut interroger l’exécution du programme pour effectuer l’erreur ou bien poursuivre en renvoyant une valeur par défaut représentant l’absence de résultat.

**Exemple**

List.hd [] -> « Exception : Failure « hd » »

On peut réécrire hd let hd (l :’a list) (default : ‘a) : ‘a =

	match l with

	|[] -> defaut

	|t ::_ -> t;;

**Problème :** changement de type de la fonction.



* On n’a pas toujours une valeur par défaut à fournir (exemple : division par 0 : tout entier est un quotient valide) ; 
* Type option : on peut signaler l’absence de résultat grâce au type ‘a option (polymorphe) qui a 2 constructeurs : 
    * None : qui représente l’absence de valeurs ; 
    * Some : ‘a -> ‘a option (Some x représente la valeur de x).

**Exemple :**

let rec quotient (a : int) (b : int) : int option = (*on suppose a ≥ O et b ≥ 0*)

	if b = 0 then None

	if a &lt; b then Some 0

	else match quotient (a-b) b with

		|None -> None

		|Some q -> Some (1+q)

**Problème :**

Les types options se propagent très vite et sont fastidieux à manipuler)

**Exceptions :** On a vu le message « Exception : Failure ... »

C’est le résultat de l’application de la fonction failwith, qui prend une chaîne de caractères en entrée qui interrompt le programme.

**Exemple :**

let rec quotient (a:int) (b:int):int =

	if b = 0 then failwith ‘’Division par O’’

	else if a &lt; b then 0

	else 1+ quotient (a-b) b

**Remarque :**

Si et seulement si le résultat de la fonction failwith est de type int.

En fait, failwith est de type string -> ‘a

Failure est un cas particulier d’exception :



* On déclare une exception grâce à la syntaxe exception &lt;nom> [of &lt;type>] (le nom commence par une majuscule et la partie entre [] est un argument optionnel) ; 
* Un exception est de type exn ; 
* On soulève une exception grâce à raise &lt;nom>, ce qui interrompt le programme et affiche « Exception : &lt;nom> » ; 
* raise est de type exn -> ‘a -> failwith s est équivalent à raise (Failure s).

**Remarque :**

Les expressions conditionnés, les type option et les exceptions ne sont pas spécifiques à la gestion d’erreur.

En particulier, on peut rattraper une exception pour poursuivre l’exécution autrement.

**Syntaxe : **

try &lt;expr> with

	|&lt;nom> ->&lt;expression>

	|&lt;nom> ->&lt;expression>

	…

	|&lt;nom> ->&lt;expression>

Les exceptions non rattrapés remontent jusqu’à l’utilisateur.


### 3.2.6 Un cas particulier : les assertions

Une assertion s’écrit assert &lt;expr>, où l’expression est de type bool.

Si l’expression s’évalue en :



* false, l’expression Assert_failure est soulevée ; 
* true, le résultat est (), donc de type unit.

**Usage : **

On évalue l’assertion puis on exécute le reste du code, i.e. on exécute des instructions l’une après l’autre.

On utilise une nouvelle construction syntaxique : la séquences

**Syntaxe :**

&lt;expression> ; &lt;expression> ; … ; &lt;expression>

&lt;expression> ; … ; &lt;expression n-1> sont de type unit

le type de la séquence et le type de l’expression &lt;expression>

**Exemple :**

let rec somme (n : int) : int =

	assert (n >= 0) ;

	if n = 0 then O else n + somme (n-1);;


### 3.2.7. Corriger des erreurs

Exécuter des tests permet de détecter une erreur mais aussi la portion de code qui est fautive

L’outil le plus simple pour déterminer d’où vient la faute et comment la corriger c’est l’usage d’affichage localisé en combinaison d’un jeu de tests (couvrant l’ensemble des probabilités pour l’exécution d’un programme).

**Fonction d’affichage :**



* print_int : int -> unit
* print_float : float -> unit
* print_string : string -> unit
* print_newline : init -> unit

(print_newline() affiche le caractère retour à la ligne)

Ce sont des instructions à utiliser au sein de séquences.

On aborde la propagation impérative.



**Remarque :**

Les instructions en OCaml sont des expressions de type unit et affectant l’état de la machine.

On dit qu’elles produisent des effets de bord et elles sont par conséquent appelées expressions impures (par opposition à purement fonctionnelle).


# 4. Programmation impérative


## 4.1. Bases du langage C


### 4.1.1. Expressions

Comme en Ocaml, les expressions sont construites par combinaison de variables, de constantes, de fonctions et de différentes constructions syntaxiques pouvant renvoyer une valeur. Les expressions sont également associées à des types.

**Les types de base sont :**



* void : un type vide qui joue un rôle similaire à unit en Ocaml ;
* int : les entiers, constructibles via de constantes (0, 1, …) ou des fonctions (+, -, *, / (quotient dans la divisions euclidienne), % (reste dans la division euclidienne) ;
* double : les nombres flottant (même si float existe également) :
    * On peut utiliser des constantes (3,14159 ou 1.789e3) ou des fonctions (+, -, *, /) ;
    * Remarque : inutile d’ajouter un . comme en Ocaml.
* char : les caractères, noté entre ‘ (ex : ‘a’, ‘b’, …) ;
* bool : les valeurs de vérité :
    * Les constantes booléenne sont true et false ;
    * Les fonctions booléennes sont :
        * La négation : !&lt;expression> ;
        * La conjonction : &lt;expression> && &lt;expression> (évaluées de manières paresseuses) ;
        * La disjonction : &lt;expression> || &lt;expression> (évaluées de manières paresseuses) ;
        * Les comparaisons : ==, !=, &lt;, >, &lt;=, >=.


### 4.1.2. Instructions

Elles désignent des ordres à exécuter, qui ont un effet sur l’état de la machine (sa mémoire). On dit qu’elles produisent des effets de bord.

**Exemples d’instructions :**



* **La déclaration** : on déclare une variable en précisant son type, son nom et facultativement sa valeur.

**Syntaxe :**

&lt;type> &lt;nom> [=&lt;expression>] ; (le point virgule est obligatoire à la fin d’une instruction)

**Exemple :**


```
	int x = 42;
	double z;
```



    **Déclaration simultanée :** 


    On peut déclarer plusieurs variables de même type en les séparant par des virgules.

**Exemple :**


```
	int x, y;
	int i = 0, j;
```



    **Constantes :** 


    Par défaut, on peut modifier des variables. Pour interdire la modification d’une variable, on utilise le mot clé const.


    **Exemple :**


```
	const double x = 3.4;
```



    La valeur est obligatoire ici.



* **Affectation :** pour modifier la valeur d’une variable, on utilise l’instruction d’affectation.

**Syntaxe :** 

&lt;nom> = &lt;expression>;

 ⚠ ne pas confondre l’égalité (==) et l’affectation (=).



* **L'incrémentation** (Hors Programme) : on peut ajouter 1 à la valeur d’une variable entière grâce à l’opérateur d’incrémentation.

    **Syntaxe : **


    &lt;nom> ++;


    Les propriétés de cet opérateur sont Hors Programme.


    **Remarque :**


    Il existe aussi un opérateur de décrémentation (&lt;nom> --)


    -> avec nos restrictions, c’est équivalent d’écrire i ++ ou i = i + 1 ou i += 1.

* **L’assertion :** on écrit assert( &lt;expressions> ) ;
* **Entrées/sorties :** On peut afficher une chaîne de caractère grâce à la fonction printf

**Exemple :** 


```
	printf("bonjour\n"); /*\n = retour à la ligne*/
```



    On peut afficher la valeur d’une expression grâce à une chaîne de format contenant des codes :



* %d pour les entiers ;
* %f pour les flottants ;
* %lf pour les double;
* %c pour les caractères ;
* %s pour les chaînes de caractères.

	

	**Exemple :**


```
      printf("%d", x + 1);
	printf("%d et %j", x + 1, 4.5);
```



    Pour demander une valeur à l’utilisateur, on utilise la fonction scanf avec la chaîne de format adaptée.


    **Exemple :** 


```
	scanf("%d", &x);
```



    (%d : on attend un entier)


    (& : opérateur pour obtenir l’adresse mémoire de la variable, déclaré au préalable)


    (x : variable dans laquelle on veut stocker la valeur)


### 4.1.3. Structures de contrôle



* **Instruction conditionnelle :**

	Syntaxe : if (&lt;expression>) &lt;instruction> [else &lt;instruction>]

	Exemple :


```
	if (b) x = x + 2;
	if (a && !b)
		x = x + 2;
	else
		y = 2 + x;
```



    Pour exécuter plusieurs instructions dans une branche d’une instruction conditionnelle, on délimite un bloc par des accolades


    **Exemple :**


```
	if (b) {
		x = x + 2;
		y = 2 * y;
	}
```




* **Itérations :** la programmation itérative est un cas particulier de la programmation impérative.

    **Principe :** on répète le même bloc d’instructions un certain nombre de fois :

* boucles conditionnelles : on répète les instructions tant qu’une condition est satisfaite.

	**Syntaxe :** 

while (&lt;expression>) &lt;instruction/bloc>

	**Exemple : **


```
	while (x % 7 != 0)
		x--;
```




* **Boucles inconditionnelles/boucles for**

    On répète les instructions un nombre déterminé de fois. En C, le nombre d’itérations est conditionné par trois expressions.


    **Syntaxe :** for (&lt;expression1>; &lt;expression2>; &lt;expression3>) &lt;instruction/bloc>

* &lt;expression1> est l’initialisation, exécutée avant la boucle ;
* &lt;expression2> est une condition. Les itérateurs s’arrêtent lorsqu’elle n’est plus satisfaite ;
* &lt;expression3> est une instruction exécutée entre chaque itération (souvent l’incrémentation d’un compteur).

    **Exemple :**


    ```
	for(i=0; i<0; i++){
		x=x*2 ;
		y=y/2*i ;
	}
```



    **Remarque :** i doit être déclaré avant et vaudra 10 à la fin de l'exécution.


    On peut également déclarer un compteur de boucle qui sera supprimé à la fin de l'exécution.


    ```
	for(int i = 0; i < 10; i ++) {...}
```


* Interruption des itérations : on peut interrompre une boucle avec l'interaction break.


### 4.1.4. Fonctions



* **Déclaration :** on utilise la syntaxe suivante :

    &lt;type_res> &lt;nom_fonction> (&lt;type-arg<sub>1</sub>> &lt;nom-arg<sub>1</sub>>, …, &lt;type-arg<sub>n</sub>> &lt;nom-arg<sub>n</sub>>) &lt;bloc>


    **Exemple :** 


    ```
	double moyenne (double x, double y, double z) {
		return (x+y+z)\3;
	}
```



    L’instruction return [&lt;expression>]; permet de sortir de la fonction en renvoyant la valeur de l’expression.


    Si le type de retour est void, on n’utilise pas d’expression et le return est facultatif.

* Usage pour appliquer une fonction à des arguments on utilise la syntaxe &lt;nom> (&lt;expression>, … &lt;expression>)

    Les arguments sont passés en valeur.


    Si le type de retour est void, on peut voir l’appel de fonction comme une instruction (exemple : f(x, y);)

* **Fonction main :** c’est la fonction principale d’un programme (-> elle est obligatoire si on veut exécuter du code).

    Elle est sans paramètres (pour l’instant) et son type de retour est int. Par défaut, la valeur de retour est 0.


    On écrit donc


    ```
	int main() {
		<bloc>
		return 0;
	}
```


* **Variables locales :** les variables déclarées dans un bloc sont limitées à ce bloc.

    Pour déclarer une variable locale, on la déclare en dehors de toute fonction.



### 4.1.5. Tableaux

On se limite pour l’instant aux tableaux statiques, i.e. dont la taille est fixée d'avance pour une expression littérale.



* **Déclaration :** on utilise la syntaxe &lt;type> &lt;nom> [&lt;taille>];
* **Initialisation :** on peut initialiser le contenu du tableau à l’aide d’une boucle ou bien au moment de la déclaration à l’aide de la syntaxe &lt;type> &lt;nom> [&lt;taille>] = {&lt;expression>, …, &lt;expression>};

    **Exemple :**


    ```
	int tab[z];
	int t[3]={0, 1, 2};
```


* **Accès et écriture : **on accède à une case d’un tableau par son indice (entre 0 et la largeur mais i - 1)

    **Syntaxe :** &lt;nom>[&lt;indice>] (indice = expression arbitraire)


    si t[0] ou t[i + 1]


    Pour écrire dans une case, on utilise l'instruction d'affectation.


    **Exemple :**


    ```
	t[0]=2;
	for (int i = 0; i<n; i++){
		t[i]=2*i;
	}
```


* **Tableaux multidimensionnels :** ce sont des tableaux de tableaux.

    **Exemple :**


    ```
	int t [20][10];
	for (int i = 0; i<20; i++){
		for(int j = 0; j<10, j++){
			t[i][j] = +j;
		}
	}
```


* **Chaînes de caractères :** ce sont des tableaux de caractères qui contiennent obligatoirement le caractère spécial ‘\O’ qui délimite la fin de la chaîne.

    ⚠ entrées : on écrit scanf(“%s”, &lt;nom>)



### 4.1.6. Transtypage

Les conversions de type sont implicites

**Exemple :** 1 + 2.5 est correct

On peut écrire une conversion explicite grâce à la syntaxe (&lt;type>)&lt;expression>.

Cas particuliers pour les chaînes de caractères : fonctions atoi pour les entiers et les atoi pour les flottants.


### 4.1.7. Les commentaires

Ils s’écrivent entre /* et */

Pour ceux qui tiennent sur une ligne, on peut seulement les précéder de //.


## 4.2. Programmation impérative en Ocaml


### 4.2.1. Rappel

Les instructions Ocaml sont des expressions de type unit, dites impures car elles produisent des effets de bord.

Tous les objets vus jusqu’ici sont immuables, i.e. on ne peut pas changer leur valeur. Il existe toutefois des objets mutables en Ocaml.


### 4.2.2. Références

Les instructions affectent la mémoire de la machine, mais on ne souhaite pas manipuler directement les adresses mémoires. On préfère pour cela associer un identifiant à un emplacement mémoire, via la déclaration d'une référence.

**Syntaxe :**

ref &lt;expression> est une référence à un emplacement mémoire qui contient la valeur de l’expression. Pour la manipuler, on lui donne un nom à l’aide d’une déclaration (locale ou globale).

**Exemple :**


```
let x = ref [1, 2, 3, 4]
```


Le type des références est ‘a ref où ‘a désigne le type de la valeur stockée.

Il faut distinguer le contenu (la référence) du contenu (la valeur référencée), que l’on obtient à l’aide de l’opérateur de déréférencement : 

Si &lt;nom> est une référence, !&lt;nom> est la valeur contenue dans la référence.

On peut modifier le contenu d’un référence grâce à une affectation

**Syntaxe :**


```
<nom> := <expression>
```


**⚠ Ne pas confondre :**


<table>
  <tr>
   <td>
   </td>
   <td>Affectation
   </td>
   <td>Test d'égalité
   </td>
   <td>Négation
   </td>
   <td>Déréférencement
   </td>
  </tr>
  <tr>
   <td>Ocaml
   </td>
   <td>:=
   </td>
   <td>=
   </td>
   <td>not
   </td>
   <td>!
   </td>
  </tr>
  <tr>
   <td>C
   </td>
   <td>=
   </td>
   <td>==
   </td>
   <td>!
   </td>
   <td>(plus tard)
   </td>
  </tr>
</table>


**Exemple :**


```
let x = ref 0 in (*ou let x:int ref = ref 0 in*)
x := 2;
x := !x + 3;
!x (*- : int = 5*)
```


Comme en C, on dispose d’opérateurs d’incrémentation et de décrémentation (sur int ref) :


```
let x = ref 0 in 
incr x;
!x (*- : int = 1*)

let x ref 2 in
decr x;
!x (*- : int = 1*)
```



### 4.2.3. Boucles

Ce sont des instructions, donc des expressions de type unit.

**Boucles conditionnelles :**


```
while <expression1> do <expression2> done
```


Où &lt;expression1> est de type unité (le corp de la boucle).

**Boucles inconditionnelles : **

Beaucoup plus contraintes qu’en C : une boucle for en Ocaml déclare un indice de boucle (de type int) qui varie par pas  de 1 entre une valeur initiale et une valeur finale (incluses).

**Syntaxe :**


```
for <nom> = <expression1> to <expression2> do <expression3> done
```




* Où &lt;expression<sub>1</sub>> et &lt;expression<sub>2</sub>> sont de type int et &lt;expression<sub>3</sub>> de type unit ;
* &lt;nom> est un identifiant uniquement dans &lt;expression<sub>3</sub>> ;
* “équivalent” en C : 

    ```
	for (int <nom> = <expression1>; <nom> <= <expression2>; <nom>++){
   		<expression3>
	}
```



On peut aussi écrire des boucles descendantes :


```
for <nom> = <expression1> downto <expression2> do <expression3> done
```



### 4.2.4. Tableaux

Le type des tableaux dont les éléments sont de type ‘a est ‘a array (les tableaux sont homogènes).



* **Création de tableaux :**
    * directement : `[|&lt;expression<sub>1</sub>>; &lt;expression<sub>2</sub>>; ...; &lt;expression<sub>n</sub>>|]` (tableau vide : [||])
    * à l’aide de la fonction Array.make : int -> ‘a -> ‘a array

        **Exemple : **


        Array.make 5 0. est le tableau [|0.; 0.; 0.; 0.; 0.|]

    * Par les matrices (i.e. les tableaux de tableaux), on utilise Array.make_matrix : 

        int -> int -> ‘a -> ‘a array array


        **Exemple : **


        ```
		Array.make_matrix 2 3 0 (*vaut [| [|0; 0; 0|]; [|0; 0; 0|] |]*)
```


    * à l’aide de la fonction Array.init : int -> (int -> ‘a) -> ‘a array

        **Exemple : **


        ```
		Array.make_matrix 2 3 0 (*vaut [| [|0; 0; 0|]; [|0; 0; 0|] |]*)
```


* **Lectures/écriture :** on accède aux éléments par indice (entre 0 et la longueur moins 1)

    **Syntaxe : **


    &lt;nom>.(&lt;expression>) où &lt;nom> est le nom du tableau et &lt;expression> représente l’indice (de type int)


    Pour modifier une case d’un tableau, on écrit &lt;nom>.(&lt;expression<sub>1</sub>>) &lt;- &lt;expression<sub>2</sub>>


    où &lt;expression<sub>1</sub>> est l’indice de la case et &lt;expression<sub>2</sub>> la valeur à stocker.


    Accès dans une matrice : par accès successifs : &lt;nom>.(&lt;expression<sub>1</sub>>).(&lt;expression<sub>2</sub>>)...

* Longueur : on utilise la fonction Array.length : ‘a array -> int

    ⚠ pour les matrices 	Array.length m est le nombre de lignes


    			Array.length m.(0) est le nombre de colonnes

* **Copie :** on copie un tableau existant grâce à Array.copy : ‘a array -> ‘a array

    **Exemple **: 


    ```
	Array.copy [|0; 0; 0|] renvoie [|0; 0; 0|]
```



⚠ Nouveau tableau ;


    ⚠ La copie est superficielle.


    **Exemple **:


```
	let t = Array.make_matrix 2 3 0;;
	let t' = Array.copy t;;
	t'.(0).(1) <- 2;;
	t;;
```



    renvoie [| [|0; 2; 0|]; [|0; 0; 0|] |]


    Pour créer une copie indépendante (deep copy) : il faut appliquer Array.copy à chaque élément


    **Exemple **:


```
	let t' = Array copy t;;
	for i = 0 to Array.length t -1 do
	t'.(i) <- Array.copy t.(i)
	done;;
```



    ou bien 


```
	let t' = Array.init (Array.length t)(function, i -> Array.copy t.(i));;
```




* **Fonctions à savoir coder :**
    * Array.mem : ‘a -> ‘a array -> bool (test d'appartenance)
    * Array.exists : (‘a -> bool) -> ‘a array -> bool (existence d’un élément satisfaisant un propriété)
    * Array.for_all : (‘a -> bool) -> ‘a array -> bool (universalité d’une propriété sur les éléments du tableau)
    * Array.map : (‘a -> b’) -> ‘a array -> ‘b array (image point à point à une fonction)
    * Array.iter : (‘a -> unit) -> ‘a array -> unit pour appliquer successivement une instruction à chaque élément d’un tableau (dans l’ordre)

        **Exemple : **


        ```
		Array.iter (function x -> print_int x; print_newline())
```



        Affiche les éléments du tableau d’entiers t (un par ligne)


        **Remarque : **


        La fonction List.iter existe.



### 4.2.5. Chaînes de caractères

Comme en C, on peut accéder aux caractères d’une chaîne par indice

Syntaxe : 


```
<nom>.[<expression>]
```


**Remarque :** 

Il existe une fonction String.make : int -> char -> string

⚠ Contrairement au C, les chaînes de caractères ne sont pas des tableaux de caractères i.e. les types string et char array sont distincts.

En particulier, depuis Ocaml 4.06, les chaînes de caractères sont immuables.

Autre différence essentielle entre OCaml et C : le typage :

On dit que le typage d’OCaml est fort et que celui de C est faible

⚠ Il n’y a pas de définition universellement reconnue des typages faible/fort.

**Intuition : **

Un typage fort apporte des garanties de sécurité vis-à-vis du programme en imposant des conditions plus strictes.

**Exemple :**



* Conversions de types implicites (impossible en OCaml, possible en C) ;
* Accès aux cases d’un tableau non vérifié en C.


# Chapitre 2 : Représentation et stockage de l’information


[TOC]



# 1. Mémoire d’un programme compilé


## 1.1. Organisation de la mémoire


### 1.1.1. Distinction statique/dynamique

Le stockage des objets manipulés par un programme est géré de 2 manières différentes selon leurs nature :



* **Statiquement :** lorsque le compilateur dispose de l’information suffisante pour prévoir de la place pour ces données, elle peut être réservée à l’avance.
* **Dynamiquement :** lorsque la taille des objets n’est connue que lors de l’exécution du programme, le programme doit faire une demande d’allocation pour obtenir l’espace en mémoire.

**Exemple :**



* Les variables globales/locales constantes ou dont la taille est fixée (ex : type int/char) sont gérées statiquement ;
* Les tableaux dont la taille dépend de l’état du programme au moment de l’exécution (exemple : “Array.make n 0” où n est un variable dépendant des calculs antérieurs) sont gérés dynamiquement.
* **Allocation statique :** plusieurs zones de mémoire sont utilisées selon la nature de l’objet :
    * Les variables globales initialisées sont stockées dans le binaire donc chargé en mémoire avec le binaire dans une zone spécifique qui l’accompagne (int x = 3) ;
    * Les variables globales non initialisées sont allouées et placés en mémoire au moment du chargement du binaire qui ne contient que leur déclaration (int x) ;
    * Les variables locales et les paramètres des fonctions sont placés dans une zone mémoire spécifique appelée pile, utilisée dynamiquement afin de ne réserver l’espace qu’au moment de l’appel de la fonction ou de l’exécution du bloc.
* **Allocation dynamique : **on utilise une zone spécifique appelée tas (les détails spécifiques aux langages C et OCaml seront vus en 1.2).

    **Schéma :**


<table>
  <tr>
   <td>
code binaire
   </td>
   <td>
   </td>
  </tr>
  <tr>
   <td>variables globales initialisées
   </td>
   <td>
   </td>
  </tr>
  <tr>
   <td>variables globales non initialisées
   </td>
   <td>
   </td>
  </tr>
  <tr>
   <td>tas
<p>
↓
   </td>
   <td>
   </td>
  </tr>
  <tr>
   <td>↑
<p>
pile
   </td>
   <td>
   </td>
  </tr>
</table>


**Commande :** objdump \
(écrire un programme prog.c, puis gcc -c prog.c, puis objdump -x prog.o)


### 1.1.2. Portée syntaxique d’un identificateur

**Définition :**

La portée syntaxique d’un identificateur est la zone de texte d’un programme dans laquelle il est possible d’y faire référence sans erreur à la compilation

**Exemple :**


<table>
  <tr>
   <td>1
   </td>
   <td><code>int a = 1;</code>
   </td>
   <td>Identificateur
   </td>
   <td>Portée
   </td>
   <td>
   </td>
  </tr>
  <tr>
   <td>2
   </td>
   <td><code>int f (int x) {</code>
   </td>
   <td>a
   </td>
   <td>1 - 9
   </td>
   <td>1 -> int x = x; possible /!\ comportement non spécifié
   </td>
  </tr>
  <tr>
   <td>3
   </td>
   <td><code>  int y = x + a;</code>
   </td>
   <td>x
   </td>
   <td>2 - 5
   </td>
   <td>
   </td>
  </tr>
  <tr>
   <td>4
   </td>
   <td><code>  return y;</code>
   </td>
   <td>y
   </td>
   <td>3 - 5
   </td>
   <td>
   </td>
  </tr>
  <tr>
   <td>5
   </td>
   <td><code>}</code>
   </td>
   <td>f
   </td>
   <td>2 - 9
   </td>
   <td>2 - > récursivité autorisée
   </td>
  </tr>
  <tr>
   <td>6
   </td>
   <td><code>int y () {</code>
   </td>
   <td>z
   </td>
   <td>7 - 9
   </td>
   <td>
   </td>
  </tr>
  <tr>
   <td>7
   </td>
   <td><code>  int z = 3;</code>
   </td>
   <td>g
   </td>
   <td>6 - 9
   </td>
   <td>6 - > récursivité autorisée
   </td>
  </tr>
  <tr>
   <td>8
   </td>
   <td><code>  return z + f(z);</code>
   </td>
   <td>
   </td>
   <td>
   </td>
   <td>
   </td>
  </tr>
  <tr>
   <td>9
   </td>
   <td><code>}</code>
   </td>
   <td>
   </td>
   <td>
   </td>
   <td>
   </td>
  </tr>
</table>


/!\ La portée est associée aux identificateurs, pas aux variables

Exemple :


<table>
  <tr>
   <td>1
   </td>
   <td><code>int f() {</code>
   </td>
   <td>Portées de i : 2 - 5 et 6 - 8
   </td>
  </tr>
  <tr>
   <td>2
   </td>
   <td><code>  int i = 3;</code>
   </td>
   <td>
   </td>
  </tr>
  <tr>
   <td>3
   </td>
   <td><code>  return i;</code>
   </td>
   <td>
   </td>
  </tr>
  <tr>
   <td>4
   </td>
   <td><code>}</code>
   </td>
   <td>
   </td>
  </tr>
  <tr>
   <td>5
   </td>
   <td><code>int g () {</code>
   </td>
   <td>
   </td>
  </tr>
  <tr>
   <td>6
   </td>
   <td><code>  int i = 5;</code>
   </td>
   <td>
   </td>
  </tr>
  <tr>
   <td>7
   </td>
   <td><code>  return i + 1;</code>
   </td>
   <td>
   </td>
  </tr>
  <tr>
   <td>8
   </td>
   <td><code>}</code>
   </td>
   <td>
   </td>
  </tr>
</table>



<table>
  <tr>
   <td>1
   </td>
   <td><code>int f() {</code>
   </td>
   <td>Portée de i : 2 - 8 
   </td>
  </tr>
  <tr>
   <td>2
   </td>
   <td><code>  int i = 3;</code>
   </td>
   <td>mais phénomène de masquage dans les lignes : 
   </td>
  </tr>
  <tr>
   <td>3
   </td>
   <td><code>  for (int i = 0; j &lt; 3; j + 1) {</code>
   </td>
   <td>4 - 6
   </td>
  </tr>
  <tr>
   <td>4
   </td>
   <td><code>    int i = 4;</code>
   </td>
   <td>{int i = 3}
   </td>
  </tr>
  <tr>
   <td>5
   </td>
   <td><code>    i = i + j;</code>
   </td>
   <td>i = i + 1
   </td>
  </tr>
  <tr>
   <td>6
   </td>
   <td><code>  }</code>
   </td>
   <td>
   </td>
  </tr>
  <tr>
   <td>7
   </td>
   <td><code>  return i;</code>
   </td>
   <td>
   </td>
  </tr>
  <tr>
   <td>8
   </td>
   <td><code>}</code>
   </td>
   <td>
   </td>
  </tr>
</table>


**Remarque :**

Les mêmes principes s’appliquent en Ocaml sauf qu’il est impossible de faire référence à une variable non initialisée.

Pour ces 2 langages, la portée est statique. En python, la portée est dynamique.

**Exemple :**


```
if cond :
  x = 2
```



### 1.1.3. Durée de vie d’une variable

**Définition :**

La durée de vie d’une variable correspond à la période de l'exécution du programme depuis sont allocation jusqu’à la libération de la mémoire associée.

**Remarque :**

La plupart du temps, la durée de vie d’une variable correspond à la portée de son identificateur.

En C, il est possible de définir des variables, dites statiques, dont la durée de vie dépasse la portée (H.P.).


### 1.1.4. Gestion de la pile

La pile sert au stockage des variables locales et des paramètres des fonctions. Son remplissage évolue en fonction de l’exécution du programme en “empilant” les zones créées et en "dépilant" les zones libérées à la manière de la structure de données appelée pile (cf plus tard).

**Remarque :**

On peut utiliser les registres du processeur pour stocker certaines données. On suppose ici que ce n’est pas le cas.

Lors d’un appel de fonction, on ajoute sur la pile d'exécution un bloc de mémoire (stack frame) correspondant au bloc d’activation de la fonction, qui contient :



* les paramètres de la fonction ;
* l’adresse de retour, indiquant la position à laquelle doit reprendre l’exécution du programme après l’exécution de la fonction ;
* un espace pour le résultat de la fonction, qui sera transmise
* de l’espace pour les variables locales ;
* l’adresse du bloc précédent, permettant de dépiler le bloc d’activation après l’exécution de la fonction.

**Exemple :**


```
int f (int a, int b) {
  int c = 3;
  c = c + b;
  c = c * a;
  return c;
}
int main () {
  int x = f(10, 12);
  return 0;
}
```




<p id="gdcalert12" ><span style="color: red; font-weight: bold">>>>>>  gd2md-html alert: inline image link here (to images/image1.png). Store image on your image server and adjust path/filename/extension if necessary. </span><br>(<a href="#">Back to top</a>)(<a href="#gdcalert13">Next alert</a>)<br><span style="color: red; font-weight: bold">>>>>> </span></p>


![alt_text](images/image1.png "image_tooltip")


/!\ La pile est limitée : s’il y a trop d’appels de fonction imbriqués, l’empilement des blocs d’activation dépassera la capacité de la pile (Stack overflow)

**Exemple :**

Une fonction récursive sans cas de base (boucle infinie) ou qui font trop d'appels récursifs


```
let rec somme (n : int) : int =
  match n with
  |0 -> 0
  |n -> n + somme (n - 1);;
```



```
let sum n =
  let aux n acc =
    match n with
    | 0 -> acc
    | _ -> aux (n - 1) ( acc + n)
  in aux n 0;;
```


Optimisation pour les fonctions récursives terminales en OCaml. Elle n'est pas garantie en C et ne peut pas être faite en Python.


## 1.2. Gestion de la mémoire en OCaml et en C


### 1.2.1. Gestion de la mémoire en OCaml

En OCaml, la gestion de la mémoire est gérée automatiquement, les allocations dynamiques sont réalisées de manière transparente (comme toutes les déclarations). La mémoire est également libérée automatiquement grâce à un programme appelé “ramasse-miette” / ”glaneur de cellules” (garbage collector) qui détecte quand un bloc de mémoire peut être libéré et qui réorganise le tas pour le compacter.


### 1.2.2. Principe de la gestion de la mémoire en C

Contrairement à OCaml, les allocations dynamiques en C sont gérées par le programmeur qui doit réclamer explicitement l’allocation d’un bloc mémoire sur le tas d’une taille donnée et qui doit signaler plus tard au système que la mémoire peut être libérée. Il faut impérativement libérer la mémoire allouée. Dans le cas contraire, on parle de fuite mémoire et le système peut devenir inutilisable faute de mémoire disponible.

En C, on fait référence aux zones de mémoires par leur adresse.


### 1.2.3. Pointeurs

Les pointeurs sont des objets qui représentent des adresses en mémoire. A la manière des références en OCaml, le type des pointeurs est paramétré par le type de la valeur contenue dans le bloc mémoire qu’ils adressent / sur laquelle ils pointent.

**Syntaxe :**

&lt;type> * est le type des pointeurs qui pointent sur une valeur de type &lt;type>.

**Déclaration :**

Comme pour les autres variables.

**Exemple :**


```
int *p;
double **q;
```


**Remarque :**

On peut placer l'étoile contre le type ou contre le nom de la variable ou même séparée des deux par des espaces.

/!\ `int *p, a;` déclare un pointeur sur entier p et un entier a.

**Opérateur d’adressage :**

C’est `&` (Rappel : scanf prend une adresse en argument).

**Exemple :**


```
int a = 2;
int *p = &a;
```


**Opérateur de déréférencement : **

C’est `*`.

Exemple :

Après l’exemple précédent *p vaut 2.

On peut voir le déréférencement de p comme une variable dont on peut modifier la valeur.

**Exemple :**


```
*p = 3;
printf ("%d\n", a); (*affiche 3*)
```



<table>
  <tr>
   <td>
   </td>
   <td>
   </td>
   <td>
   </td>
  </tr>
  <tr>
   <td>
   </td>
   <td>p = adresse
   </td>
   <td>
   </td>
  </tr>
  <tr>
   <td>
   </td>
   <td>a = 3 ← adresse
   </td>
   <td>
   </td>
  </tr>
  <tr>
   <td>Pile
   </td>
   <td>
   </td>
   <td>
   </td>
  </tr>
</table>


→ on peut utiliser les pointeurs pour écrire des fonctions qui renvoient plusieurs résultats.

**Idée :**

On écrit une fonction de type void qui prend en paramètre des pointeurs sur les cases mémoires où l’on souhaite récupérer le résultat.

**Exemple :**


```
void min_max(int x, int y, int *min, int *max) {
  if (x <= y) {
    *min = x;
    *max = y;
  } else {
    *min = y;
    *max = x;
  }
}
min_max(x, y, &x, &y);
```



<table>
  <tr>
   <td>max = adresse
   </td>
   <td rowspan="4" >}min_max
   </td>
  </tr>
  <tr>
   <td>min = adresse
   </td>
  </tr>
  <tr>
   <td>y = 2
   </td>
  </tr>
  <tr>
   <td>x = 3
   </td>
  </tr>
  <tr>
   <td>y = 3
   </td>
   <td>adresse y
   </td>
  </tr>
  <tr>
   <td>x = 2
   </td>
   <td>adresse x
   </td>
  </tr>
</table>


**Chaîne de format : **%p


### 1.2.4. Allocation dynamique en C

**On dispose de 2 fonctions :**



* **Allocation : **on utilise la fonction malloc, de prototype

    ```
     void *malloc(size_t size)
```



     \
où void est un pointeur sur rien (on ne connaît pas le type de la valeur sur laquelle le pointeur pointe), size_t est le type représentant une table et size est le nombre d’octets à réserver.


    → on utilise le transtypage pour choisir le type du pointeur


    **Exemple :**


    ```
     char *t = (char*) malloc(n);
```



    En cas d’échec de l’allocation, malloc renvoie un pointeur particulier, noté NULL.


    Pour déterminer le nombre d’octets à allouer, on utilise la fonction sizeof qui prend en paramètre un type ou un objet et renvoie sa taille..


    **Exemple :**


    ```
     int *t = (int*) malloc (n* sizeof(int));
```


* **Libération de la mémoire :** on utilise la fonction free, de prototype

    ```
     void free(void *ptr)
```



    où le 1er void est une instruction et le 2nd peut prendre n’importe quel pointeur (par transpitage)


    **Exemple :**


    free(t);


<table>
  <tr>
   <td>
/!\ <code>int a;</code>
   </td>
   <td><code>char *a = malloc(8);</code>
   </td>
   <td>provoquent des erreurs
   </td>
  </tr>
  <tr>
   <td><code>free(&a);</code>
   </td>
   <td><code>free(a);</code>
   </td>
   <td>
   </td>
  </tr>
  <tr>
   <td>
   </td>
   <td><code>free(a);</code>
   </td>
   <td>
   </td>
  </tr>
</table>




* **Protection mémoire :** un programme s'exécute dans un environnement mémoire constitué de plusieurs zones, appelées segments, et ne peut écrire que dans certaines d’entre elles.

    Le système protège l'intégralité de la mémoire grâce à une erreur (“segmentation fault” ou “segmentation violation”) en cas d’accès interdit.


    **Exemple :**


    On ne peut pas écrire à l’adresse 0 ni dans le segment du code.


<table>
  <tr>
   <td>
<code>int *a = 0;</code>
   </td>
   <td><code>int min(){</code>
   </td>
  </tr>
  <tr>
   <td><code>printf("%d", *a);</code>
   </td>
   <td><code>int *a = (int*) (&main);</code>
   </td>
  </tr>
  <tr>
   <td>
   </td>
   <td><code>*a = 0;</code>
   </td>
  </tr>
  <tr>
   <td>
   </td>
   <td><code>return 0;</code>
   </td>
  </tr>
  <tr>
   <td>
   </td>
   <td><code>}</code>
   </td>
  </tr>
</table>



### 1.2.5. Tableaux

En C, on peut voir un tableau comme un pointeur sur sa première case.

**Exemple :**


<table>
  <tr>
   <td>int *p, tab[5];
   </td>
   <td>est équivalent à
   </td>
   <td>int *p, tab[5];
   </td>
  </tr>
  <tr>
   <td>p = tab;
   </td>
   <td>
   </td>
   <td>p = &tab[0];
   </td>
  </tr>
</table>


**H.P. :** Dans ce contexte, p + i (ou tab + i) est l’adresse de la case d’indice i.

**Exemple :**


```
int t[5] = {A, 2, 3, 4, 5};
for(int i = 0, i < 5; i++){
  printf("%d\n", *(t + i));
}
/*affiche les éléments de t*/
```


Allocation dynamique d’un tableau

**Exemple :**


```
int *t = (int*) malloc (n *sizeof (int)); 
/*alloue un tableau de n entiers*/
```


Pour un tableau en paramètre d’une fonction

/!\ la taille n’est pas vérifiée

**Exemple :**


```
void f(int t[6]) {
  t[0]++;
  t[1]++;
}
```


Fonctionne aussi pour un tableau de taille 2. En fait, on pouvait écrire “int t[]”.

→ il est recommandé de passer la taille du tableau en argument.

**Exemple :**


```
void print_tab(int *t, int n) /* ou bien int t[], int n*/ {
  for (int i = 0; i < n: i ++) {
    printf("%d\n", t[i]);
  }
}
```


Allocation d’une matrice à n lignes et m colonnes : 2 possibilités :



1. On alloue un tableau de tableaux ;
2. On linéarise la matrice.

    ```
     int **mat = (int **) malloc (n*sizeof(int*));
     for (int i = 0 ; i < n ; i ++) {
       mat[i] = (int*) malloc(m* sizeof(int));
     }
```



    → à la libération, appeler free sur chaque ligne avant de l’appeler sur mat

1. `int *mat = (int*) malloc(n* m* sizeof(int));`

    Accès : au lieu de mat[i][j], on écrit mat [j + m* i]


    Libération : un seul appel à free.



### 1.2.6. Arguments de la fonction main

On peut passer des arguments au programme via la ligne de commande exécutée dans le terminal pour le lancer (cela permet par exemple de mettre en place un système d’options ou passer un fichier en paramètre pour que le programme traite les données du fichier). Ces arguments sont obtenus comme paramètre de la fonction main sans la forme d’un tableau de chaînes de caractères.

**Prototype de main :** `int main(int argc, char* argv[])`

où int argc est le nombre d’éléments écrit sur la ligne de commande <span style="text-decoration:underline;">y compris</span> le nom du programme et char* argv[] est le tableau des éléments.

→ argv[0] est le nom du programme et argv[1] … argv[argc - 1] sont les arguments du programme.

En OCaml, le point d’entrée du programme n’est pas une fonction main prenant des arguments, mais une expression de type unit. On récupère les arguments du programme grâce au module Sys : Sys.argv est un objet de type string array équivalent au argv du langage C.


# 2. Systèmes de fichiers


## 2.1. Organisation


### 2.1.1. Arborescence de fichiers

Les données qui sont stockées sur l'ordinateur sont répartis dans des unités cohérentes appelées fichiers. Les fichiers ne sont pas en vrac dans la mémoire mais organisés grâce aux répertoires / dossiers, représentant un groupe de fichiers. Cette structure organisée est appelée l'arborescence des fichiers.

**Exemple :**


```
/
├── bin
│   └── ls
├── dev
├── etc
├── home
│   ├── Alice
│   │   └── toto.txt
│   └── bob
└── media

```



* **bin :** exécutables permettant de démarrer le système et commandes de terminal ;
* **dev :** interfaces vers des périphérique ;
* **ect : **les fichier de configuration du système ;
* **home :** répertoires personnels des utilisateurs ;
* **media :** les données des périphériques de stockage que l’on dit “monter” (brancher).

Chaque élément de l'arborescence est décrit par un chemin indiquant comment naviguer dans l'arborescence pour accéder aux fichiers.

**Un chemin peut être :**



* **Absolu :** c’est la suite des répertoires à traverser depuis la racine.

    **Exemple :**


    /home/Alice/toto.txt

* **Relatif :** c’est la suite des répertoires à traverser depuis le répertoire courant.

    **Exemple :**


    Depuis home, Alice/toto.txt


    **Problème : **


    Comment faire depuis bin ?


    → ../home/Alice/toto.txt


    **Symboles :**

* . : désigne le répertoire courant ;
* .. : désigne le répertoire parent (ex : depuis Alice, ../.. est la racine) ;
* ~ : désigne le répertoire personnel de l’utilisateur (répertoire par défaut).


### 2.1.2. Manipulation de fichiers depuis un programme

Chaque langage a sa propre syntaxe pour les lectures et écrire dans des fichiers :



* **Ocaml :** il faut ouvrir un canal de communication / un flux de données avant de pouvoir lire / écrire dans le fichier. Il faut penser à refermer ce canal.
    * **Type : **
        * in_channel : pour la lecture
        * out_channel : pour l’écriture
    * **Ouverture d’un canal :** on utilise les fonctions :
        * open_in : string -> in_channel
        * open_out : string -> out.channel
    * La chaîne de caractère en argument est un fichier (relatif / absolu) vers le fichier.
    * **Fermeture d’un canal :** on utilise les fonctions :
        * close_in : in_channel -> unit
        * close_out : out_channel -> unit
    * **Ecriture / lecture :** on écrit dans un fichier via un canal grâce à la fonction :
        * output_string : out_channel -> string -> unit
        * Exemple :

            ```
               let oc = open_out "/home/Aice/toto.txt" in
               output_string pc "bonjour\n";
               close_out oc
```



On lit via la fonction input_line : in_channel -> string qui lit une ligne du fichier et renvoie sur le caractère de retour à la ligne.

S’il n’y a plus de ligne à lire, la fonction soulève l'exception End_of_file.

**Exemple :**


```
let ic = open_int "/home/Aice/toto.txt" in
try
  while true do
    lit s = input_line ic in
    Printf.printf "%s\n" s
  done
with
  |End_of_file -> close_in ic
```




* **C :** les flux de données sont manipulés via des pointeurs :
    * **Ouverture :** On utilise la fonction fopen, de prototype

        FILE* fopen(char path[], char mode[])


        où path désigne un chemin vers le fichier et mode est le mode d'ouverture.


        “r” pour la lecture ou “w” pour l’écriture (autres modes H.P.).

    * **Fermeture :** on utilise la fonction fclose, de prototype

        void fclose (FILE* file)

    * **Ecriture / lecture :** pour l’écriture, on utilise la fonction fprintf équivalente à printf avec un argument supplémentaire de type FILE* (en 1ère position).

        **Exemple : **


        ```
          fprint(file, "%p\n", file);
          fprintf(file, "%d", x + y);
```



    On lit grâce à la fonction fscanf, qui fonctionne comme scanf avec argument supplémentaire que fprintf.


    On peut tester la valeur de retour de fscanf pour savoir si on a atteint la fin du fichier (valeur spéciale EOF)


    **Exemple :**


    ```
     FILE* file = fopen(« toto.txt », « r ») ;
     if(file == NULL) {
       printf(« échec de l'ouverture\n ») ;
       assert false ;
     }
     char s[81] ;
     while (fscanf(file, «%s », s)!= EOF)
       printf(«%s\n », s) ;
     fclose(file) ;
```



    **Remarque :**


    `printf` et `scanf` sont les équivalents de `fprintf` et `fscanf` où l’on utilise le flux standard

* **stdir :** flux d’entrée standard ;
* **stdout :** flux de sortie standard ;
* **stderr :** flux d’erreur standard, souvent égal à stdout.

OCaml dispose aussi des flux standards, de même nous. Il y a aussi une fonction :

`Print.fprintf` en OCaml


### 2.1.3. Implémentation de l’arborescence de fichiers

Dans les exemples précédents, on a accédé au contenu des fichiers de manière séquentielle.

En pratique, la mémoire est organisée en blocs auxquels on peut accéder : 



* directement, via leur adresse en mémoire ; 
* séquentiellement : on parcourt les blocs successifs à partir d’un bloc de départ.

Les accès séquentiels sont en général plus rapides que les accès directs. Dans l’idéal, les fichiers seraient donc stockés dans des blocs contigus. Seulement, il y a un problème de fragmentation de la mémoire : les modifications successives de l’arborescence (création / suppression / redimensionnement des fichiers) laissent des plages de blocs inutilisables. De plus, la gestion des blocs dépend du système de fichiers utilisé : le système d’exploitation n’applique pas la même stratégie pour éviter la fragmentation selon le système de fichiers. Nous allons voir le principe de l’allocation indexée, utilisée dans le système type UNIX.

Un fichier est en fait un nom associé à un nœud (inode) qui est une structure codée dans un / plusieurs blocs de mémoire et contenant les métadonnées du fichier (cf 2.1.4.) et les adresses des différents blocs contenant les données du fichier.

Cela résout le problème de fragmentation (tout bloc est utilisable en mettant à jour le nœud d’index du fichier concerné) sans trop réduire les performances des accès aux fichiers.

Un répertoire est alors une liste de nœuds d’index associés à des noms. La séparation du nom des autres métadonnées est importante pour pouvoir partager les blocs de mémoire associés à un fichier entre plusieurs noms, vus comme des « raccourcis ».

Il y a deux manières de procéder :



* le lien physique : on crée deux noms <span style="text-decoration:underline;">pour le même nœud d’index</span>.

    Il y a des restrictions : pas de lien physique vers le répertoire ni vers un autre système de fichier.

* le lien symbolique un lien symbolique est un nouveau fichier, donc un nœud d’index différent, ne contenant dans ces données que le chemin vers le fichier auquel il fait référence. Les restrictions des liens physiques ne s’appliquent pas aux liens symboliques.


### 2.1.4. Attributs de fichiers

Les attributs en métadonnées qui sont stockés dans le nœud d’index d’un fichier fournissant des informations sur le fichier. Dans la norme POSIX, on y trouve en particulier : 



* la taille du fichier (en octets) ; 
* le nombre de blocs alloués ; 
* le nombre de liens physique vers le nœud d’index ; 
* le numéro de nœud d’index ; 
* les identifiants de l’utilisateur propriétaire et du groupe du fichier ; 
* des données d’horodatage concernant les accès et modifications du fichiers ; 
* des droits d’accès au fichier, identifiant les opérateurs autorisés sur ce fichier selon l’utilisateur.

Il y a 3 catégories d’utilisateurs : 



* le propriétaire du fichiers ; 
* les membres du groupe de fichiers ; 
* les autres.

Pour chaque catégorie, il est possible d’autoriser / d’interdire 3 opération : 



* la lecture du fichier ; 
* l’écriture du fichier ; 
* l’exécution du fichier en tant que programme exécutable.

Cas particuliers pour les répertoire : 



* l’accès en lecture permet de lister le contenu du répertoire ; 
* l’accès en écriture permet de créer / supprimer / renommer les fichiers contenus dans le répertoire (nécessite l’accès en exécution) ; 
* l’accès en exécution permet de traverser le répertoire, ie d’accéder au contenu du répertoire pour les fichiers pour lesquels on a des droits d’accès.




## 2.2. Manipulation depuis le terminal


### 2.2.1. Navigation dans l’arborescence de fichiers



* **Se retrouver :** l’environnement du terminal est placé dans un répertoire “courant”. On utilise la commande pwd, pour “print working directory”, pour déterminer le répertoire courant ;
* Pour connaître le contenu d’un répertoire, on utilise la commande ls, pour “list”.  \
**Deux options :**
    * **Sans argument : **la commande liste le contenu du répertoire courant ;
    * **On peut donner un argument :** un chemin relatif / absolu vers un répertoire et la commande liste alors le contenu de ce répertoire. \
**Exemple :** \
ls/home/Alice \
ls Bureau (si le répertoire courant est un répertoire d’utilisateur) \
ls ../tp  \
**<code>? \
├── ws \
└── tp</code></strong>
* <strong>Se déplacer : </strong>on utilise la commande cd, pour “change directory”, pour changer de répertoire courant :
    * <strong>Sans argument :</strong> cette commande déplace le répertoire courant vers le répertoire utilisateur.
    * On peut choisir le répertoire courant en donnant un chemin vers le répertoire \
<strong>Exemple :</strong> \
cd ../.. \
cd ~ (équivalant à cd) \
cd Bureau


### 2.2.2. Modifications de l’arborescence de fichiers



* **Création de fichiers :**
    * **Fichiers :** on peut utiliser un éditeur de texte (ex : commande emacs) \
On peut également créer un fichier vide à l’aide de la commande touch, qui prend en argument un chemin vers le fichier à créer. \
**Exemple : \
**touch DS/ds_03.tex \
touch toto.txt \
Si le fichier existe déjà, la commande modifier les métadonnées d’horodatage.
    * **Répertoire :** on crée un répertoire à l’aide de la commande mkdir, pour “change directory”. \
Elle prend également en argument un chemin. \
**Exemple : \
**mkdir /tmp/test
    * **Copie : **on peut copier un fichier / un répertoire à l’aide de la commande cp pour “copy”, qui prend en argument un chemin vers le fichier / répertoire à copier et un chemin vers la destination \
**Exemple :** \
cp toto.txt ~/Bureau \
cd toto.txt ~/Bureau/bla.txt \
cp bla.txt bli.txt \
Pour les répertoires, on doit utiliser l’option -r, pour “recursive”. \
cp -r /tmp/home/Alice/Documents (copie le dossier dans Documents) \
cp -r /tmp/home/Alice/Documents/copie.tmp (copie et renomme en copie.tmp)
* **Suppression : **
    * **Fichier :** on supprime un fichier grâce à la commande rm, pour “remove”, qui prend en argument un chemin vers le fichier à supprimer. \
**Exemple :** \
rm /tmp/toto.txt \
On peut donner plusieurs chemins pour supprimer plusieurs dossiers, et on dispose du symbole * qui représente n’importe quelle chaîne de caractères. \
**Exemple :** \
rm *.ml (supprime tous les fichiers du répertoire courant dont l'extension est .ml)
    * **Répertoires : **on supprime un répertoire vide à l’aide de la commande rmdir, pour “remove directory”. Plutôt que de vider le répertoire pour utiliser rmdir, on utilise l’option -r de rm.
* **Déplacement :** on déplace un fichier répertoire à l’aide de la commande mv, pour “move”, prenant les mêmes arguments que cp. \
/!\ Pas d’option -r


### 2.2.3. Gestion des systèmes de fichiers



* **Ajout d’un système de fichiers :** on utilise la commande mount (on parle de montage) qui prend en argument un chemin vers le périphérique, et un chemin vers le répertoire qui contiendra l’arborescence du périphérique. Sans argument, la commande mount liste les points de montage. \
**Exemple :** \
mount /dev/sdc1 Documents/ma_clé_USB
* **Démontage :** on utilise la commande umount, qui prend un chemin vers le point de montage.


### 2.2.4. Gestion des droits



* Exécuter une commande en tant qu'administrateur, on préfixe la commande par la commande sudo, pour “super user do” \
**Exemple :** \
L’utilisateur doit faire partie du groupe sudo.
* **Gérer les droits des fichiers/répertoires : **on représente les droits d’accès par une chaîne de caractères rwx (utilisation) rwx (groupe) rwx (autres), en plaçant des - pour les droits non attribués. \
**Exemple :** \
rwx rw- r-- \
(Le propriétaire à tt les droits, ceux du groupe ne peuvent pas l’exécuter et les autres peuvent uniquement le lire). \
On peut aussi charger cette chaîne à l’aide de la commande chmod, pour “change mode”, qui peut être utilisée de 2 manières :
    * On modifie les droits d’une catégorie (u pour utilisateur, g pour groupe, o pour les autres) par ajout (+), supprimer (-), en définition (=) de droits. \
**Exemple : ** \
chmod u + rm &lt;chemin du fichier> \
chmod o = r &lt;chemin>
    * On utilise une représentation numérique des droits (4 pour la lecture, 2 pour l’écriture et 1 pour l’exécution) que l’on somme pour chaque catégorie. \
**Exemple :** \
chmod 7 5 1 &lt;chemin> (7 = u ; 5 = g ; o = 1)


### 2.2.5. Création de liens

On utilise la commande ln, pour “link”, qui prend les mêmes arguments que les commandes cp et mv. Par défaut, le lien est physique. Pour obtenir un lien symbolique, on utilise l’option -s.

**Exemple :**

ln -s /dev/sdl ~/Documents/data

ln tp/macros.tex td/


### 2.2.6. Redirections

On peut rediriger les flux d’entrée / sortie des programmes :



* **Rediriger la sortie vers un fichier :** on utilise > pour la sortie standard et 2> pour la sortie d’erreur. \
**Exemple :** \
./prog 2> erreur.log \
echo bonjour > /tmp/hello.txt \
On utilise >> er 2>> pour ajouter à la fin sans écraser.
* **Rediriger l’entrée vers un fichier :** on utilise &lt; \
**Exemple :** ls > contenu.txt \
sort &lt;contenu.txt> contenu_triée.txt
* **Rediriger la sortie d’un programme vers l’entrée d’un autre : **on utilise un tube (pipe) dénoté par |. \
**Exemple :** \
ls | sort >contenu_triée.txt \
ls | grep “.nl$”


# 3. Représentation de l’information : types numériques


## 3.1. Représentation des entiers


### 3.1.1. Introduction

En machine, les données sont stockées sous forme linéaire, ie sous la forme de suites de 0 et de 1. Cela fonctionne car de nombreux types d’information peuvent être encodées par des entiers, qui eux même ont plusieurs représentations dont la représentation binaire.


### 3.1.2. Base de numérotation 

**Définition :**

Soit b ∈ ℕ \ {0 ; 1}. Alors ∀n ∈ ℕ, il existe une unique suite (n<sub>k</sub>)|k ∈ ℕ tel que ∀k ∈ ℕ, n<sub>k</sub> ∈⟦0, b - 1⟧, (n<sub>k</sub>)<sub>k</sub> ∈ ℕ stationne ultimement en 0 et 

<p id="gdcalert13" ><span style="color: red; font-weight: bold">>>>>>  gd2md-html alert: equation: use MathJax/LaTeX if your publishing platform supports it. </span><br>(<a href="#">Back to top</a>)(<a href="#gdcalert14">Next alert</a>)<br><span style="color: red; font-weight: bold">>>>>> </span></p>

où p est tel que ∀k > p, n<sub>k</sub> = 0

On appelle représentation en base b la suite (finie) n<sub>p</sub> … n<sub>0</sub> et on note n = &lt;n<sub>p</sub> … n<sub>0</sub>><sub>k</sub>.

**Démonstration :**



* **Unicité :** On suppose l'existence d’un tel développement 

<p id="gdcalert14" ><span style="color: red; font-weight: bold">>>>>>  gd2md-html alert: equation: use MathJax/LaTeX if your publishing platform supports it. </span><br>(<a href="#">Back to top</a>)(<a href="#gdcalert15">Next alert</a>)<br><span style="color: red; font-weight: bold">>>>>> </span></p>

. On remarque que 

<p id="gdcalert15" ><span style="color: red; font-weight: bold">>>>>>  gd2md-html alert: equation: use MathJax/LaTeX if your publishing platform supports it. </span><br>(<a href="#">Back to top</a>)(<a href="#gdcalert16">Next alert</a>)<br><span style="color: red; font-weight: bold">>>>>> </span></p>

avec 0 &lt;= n<sub>0</sub> &lt; b donc n<sub>0</sub> est récursivement le reste dans la division euclidienne de n par b. On note 

<p id="gdcalert16" ><span style="color: red; font-weight: bold">>>>>>  gd2md-html alert: equation: use MathJax/LaTeX if your publishing platform supports it. </span><br>(<a href="#">Back to top</a>)(<a href="#gdcalert17">Next alert</a>)<br><span style="color: red; font-weight: bold">>>>>> </span></p>

le quotient (aussi uniquement déterminé) et on recommence → on montre par récurrence que les n<sub>k</sub> sont uniquement déterminés.
* **Existence :** \
Si n = 0 : (0)<sub>k</sub> in ℕ convient
* Si n > 0 : On définit les suites (n<sub>k</sub>)<sub>k∈ℕ</sub> et (N<sub>k</sub>)<sub>k∈ℕ</sub> par  \
	N<sub>0</sub> = n \
	∀ k ∈ ℕ :  \
		n<sub>k</sub> est le reste dans la division euclidienne de N<sub>k</sub> par b \
		N<sub>k</sub> + 1 est le quotient dans la division euclidienne de N<sub>k</sub> par b \
Par définition ∀  k ∈ ℕ, n<sub>k</sub> ∈⇾⟦0, b - 1⟧ \
n = N<sub>0</sub> = N<sub>1</sub> x b = n<sub>0</sub> = (N<sub>2</sub> x b + n<sub>1</sub>)b + n<sub>0</sub> = N<sub>2</sub> x b<sup>2</sup> + n<sub>1</sub> x b + n<sub>0</sub>  \
-> une récurrence (finie) permettra de démontrer 

<p id="gdcalert17" ><span style="color: red; font-weight: bold">>>>>>  gd2md-html alert: equation: use MathJax/LaTeX if your publishing platform supports it. </span><br>(<a href="#">Back to top</a>)(<a href="#gdcalert18">Next alert</a>)<br><span style="color: red; font-weight: bold">>>>>> </span></p>

quand on aura montré que (n<sub>k</sub>)<sub>k</sub> ∈ ℕ stationne en 0 à partir d’un certain rang. \
Soit k ∈ ℕ : \
	N<sub>k</sub>  = b x N<sub>k+1</sub> + n<sub>k</sub> et b > 1 \
	donc 2 N<sub>k+1</sub> ≤ b N<sub>k+1</sub> ≤ N<sub>k</sub> \
	donc par récurrence, 2<sup>k</sup> N<sub>k</sub> ≤ N<sub>0</sub> = n \
	donc, pour k tel que 2<sup>k</sup> > n, N<sub>k</sub> = 0 et ∀ p ≥ k + 1, n<sub>p</sub> = 0 \
**Exemple :** \
b = 10 -> représentation décimale \
b = 2 -> représentation binaire \
b = 16 -> représentation hexadécimale : on utilise comme &lt;<chiffres>> les symboles 0, …, 9, a, …, f \


<table>
  <tr>
   <td>
décimal
   </td>
   <td>binaire
   </td>
   <td>hexadécimal
   </td>
  </tr>
  <tr>
   <td>17
   </td>
   <td>10001
   </td>
   <td>11
   </td>
  </tr>
  <tr>
   <td>15
   </td>
   <td>1111
   </td>
   <td>f
   </td>
  </tr>
  <tr>
   <td>0
   </td>
   <td>0
   </td>
   <td>0
   </td>
  </tr>
</table>



### 3.1.3. Remarque

Il y a aussi la représentation unaire (base 1)



* Les algorithmes vus en primaire s’adaptent à toutes les bases
* En pratique, on ne peut pas représenter tous les entiers : il y a un nombre maximal de chiffres. Si le résultat d’une opération doit utiliser plus de chiffres, il est tronqué (ce qui revient à faire des calculs modulos b ^ p où p est la taille maximale). On appelle cela un dépassement de capacité (overflow en anglais).
* La gestion des entiers négatifs nécessite un choix de représentation :
    * **Types en C**
        * **Taille fixée explicitement : **
            * int8_t, int32_t, int64_t pour les entiers relatifs
            * unit8_t, unit32_t, unit64_t pour les entiers naturels \
On parle d’entiers non signés (unsigned)
        * **Si la taille importe peu : **int et unsigned int (dont la taille est en général 32 bits)


### 3.1.4. Entiers signés



* **Solution naïve : **on utilise un bit de signe (0 pour positif, 1 pour négatif) \
Problème :
    * 0 à 2 représentations
    * les algos usuels ne fonctionnent plus sur 8 bits : les entiers entre -2<sup>7</sup> + 1 et 2<sup>7</sup> - 1

4 + (-2) = 2 mais &lt;00000100><sub>2</sub> + &lt;100000010><sub>2</sub> = &lt;10000110><sub>2</sub> \
			4		       -2			-6



* **Complément à 2 :** sur p bits, entiers entre - 2<sup>p - 1</sup> et 2<sup>p - 1</sup> - 1 représentés de manière unique. \
Idée : on note ~= le complémentaire de n (en inversant les bits) \
Alors n + “n avec au dessus ~ : ~n” = &lt;1…1> _ 2 3 ^ p - 1 \
				        p bits \
donc ~n + 1 = 2 ^ p - n "modulo (à remplacer par formule)” - n [2 ^p]
    * Si n >= 0, on le représente normalement
    * Si n &lt; 0, on le représente pour ~n + 1 ie 2 ^ p - |n|

	**Exemple :**

	6+(-6) = 0 et &lt;00000110><sub>2</sub> + &lt;11111010><sub>2</sub> = &lt;10000000><sub>2</sub> = &lt;000000000><sub>2</sub> (overflow)


### 3.2.1. Idée

On s’inspire des bases de numération pour les entiers et on représente séparément parties entières et parties décimales :

&lt;x<sub>p</sub>…x<sub>0<strong>. .</strong></sub>x<sub>-1</sub>… x<sub>-q</sub>><sub>b</sub> = sum from k = -q to p of x _ k times b ^ k

**Exemple :**

&lt;4.35>**10** = 4 x 10<sup>0</sup> + 3 x 10<sup>-1</sup> + 5 x 10<sup>-2</sup>

&lt;10.11><sub>2</sub> = 2<sup>1</sup> + 2<sup>-1</sup> + 2<sup>-2</sup> = &lt;2.75><sub>10</sub>

**Remarque :**

Une telle représentation n’est pas nécessairement finie.

On appelle nombre décimal (resp. dyadique) un nombre dont la représentation en base 10 (resp. 2) est finie.

**Calcul de la représentation :**

Soit x ∈ ]0 ; 1[. On veut écrire x sous la forme {0.x<sub>−1</sub> x<sub>−2</sub> . . .}<sub>b</sub> .

On remarque que b · x = {x<sub>−1</sub> . x<sub>−2</sub> x<sub>−3</sub> . . .}<sub>b</sub> donc x<sub>−1</sub> = ⎣bx⎦

Comme x − ⎣bx⎦ = {0 . x<sub>−2</sub>x<sub>−3</sub> . . .}<sub>b</sub>, on peut recommencer.

**Exemple :**

{0.7}<sub>10</sub> en base 2 ?

2 × 0.7 = 1.4 → 1

2 × 0.4 = 0.8 → 0

2 × 0.8 = 1.6 → 1

2 × 0.6 = 1.2 → 1

2 × 0.2 = 0.4 → 0

{0.10110 0110 0110 . . .}<sub>2</sub>

**Remarque :**

Pour utiliser cette représentation, on fixe les nombres de chiffres avant et après la virgule. On parle de représentation en virgule fixe.


### 3.2.2. Représentation en virgule flottante

**On s’inspire de la représentation scientifique des nombres x = (-1)<sup>1</sup> n times 2<sup>e</sup> où :**



* s in {0, 1} est le bit de signe
* n in [1, 2[ est la mantisse
* e in ℤ est l’exposant

**Remarque :**

On ne peut pas représenter 0



* La représentation binaire de n est de la forme &lt;1, m<sub>-1</sub>m<sub>-2</sub> …><sub>2</sub> ;
* On fait des erreurs d’arrondi si n n’est pas dyadique.

**Norme IEEE - 754 **établie en 1985, elle définit une convention sur la représentation des nombres en virgule flottante.


<table>
  <tr>
   <td>
   </td>
   <td>#bits
   </td>
   <td>Signe
   </td>
   <td>Exposant
   </td>
   <td>Mantisse
   </td>
   <td>
   </td>
  </tr>
  <tr>
   <td>Simple précision
   </td>
   <td>32
   </td>
   <td>1
   </td>
   <td>8
   </td>
   <td>23
   </td>
   <td>-> float en C
   </td>
  </tr>
  <tr>
   <td>Double précision
   </td>
   <td>64
   </td>
   <td>1
   </td>
   <td>11
   </td>
   <td>52
   </td>
   <td>-> double en C / float en OCaml
   </td>
  </tr>
</table>


**Convention :**



* On ne stocke pas la partie entière de la mantisse ;
* L’exposant e est représenté par l’écriture binaire de e + 2<sup>p - 1</sup> - 1 où p est le nombre de bits d'exposant. \
/!\ pas de complément à 2

**Exemple :**

En simple précision 0 10000010 1100…0



* s = 0 -> nombre positif
* e = &lt;10000010><sub>2</sub> - 2<sup>7</sup> + 1 = 130 - 127 = 3
* m = &lt;1.11><sub>2</sub> = &lt;1.75><sub>10</sub>

    x = + 1.75 x 2<sup>3</sup> = 14


**Remarque :**

En raison des erreurs d’approximation, on ne teste jamais l’égalité de 2 flottants.  \
On compare plutôt la valeur absolue de leur différence à l’erreur liées à la précision.

**Exemple :**



* En simple précision l’erreur est de l’ordre de 2<sup>e</sup> times 2<sup>-23</sup> -> on compare à 10<sup>-7</sup> \
(où 2<sup>-23</sup> est le dernier bit de mantisse)
* En double précision, on compare à 10<sup>-12</sup>

**Cas particuliers de la norme IEEE - 754 :**



* Si les bits d’exposant ne sont pas 0…0 ou 1…1, on parle de forme normalisée ;
* Si les bits de mantisse sont 1…1 ;
    * Si les bits de mantisse sont 0…0 : cela encode +-oo selon le signe ;
    * Si au moins  un bit de mantisse vaut 1, cela encode NoN (mot or number).
* Si les bits d’exposant sont 0..0, on parle de forme dénormalisée ;

Le nombre représenté est alors avec p bits d’exposant et q bits de mantisse : (-1)<sup>8</sup> x 8 x 2<sup>e</sup>

où e = 2 - 2<sup>p-1</sup> et m = {0 x m<sub>-1</sub>…m<sub>-q</sub>}<sub>2</sub>.


# Chapitre 3


## Vérification de programme


[TOC]



# 


# 1.Terminaison


## 1.1. Définition (terminaison)

On dit qu’un programme / algorithme termine s’il n’exécute qu’un nombre fini d’opérations quelle que soit l’entrée.


## 1.2. Remarque

Le nombre d’opérations peut être arbitrairement grand en fonction de l’entrée (pas de majorant commun à toutes les entrées).



<p id="gdcalert18" ><span style="color: red; font-weight: bold">>>>>>  gd2md-html alert: equation: use MathJax/LaTeX if your publishing platform supports it. </span><br>(<a href="#">Back to top</a>)(<a href="#gdcalert19">Next alert</a>)<br><span style="color: red; font-weight: bold">>>>>> </span></p>




## 1.3. Exemple

**Montrons que les 2 fonctions suivantes terminent :**


```
let is_prime (n : int) : bool =
  let res = ref true in
  for i = 2 to n - 1 do
    if n mod i = 0 then
      res := false
    done;
  !red
```


-> boucle exécutée n - 2 fois 

+ uniquement des opérations élémentaires qui terminent.


```
let count_prime (n : int) : int =
  let res = ref 0 in
  for i = 2 to n do
    if is_prime i then incr res
  done;
  !res
```


-> boucle exécutée n - 1 fois



* chaque appel à is_prime termine
* des opérations élémentaires qui terminent



**Conclusion :**

Une boucle inconditionnelle termine dès que les opérations qui la composent terminent.

/!\ Une boucle for en C est une boucle while déguisée.

**Rappel :** for (c<sub>1</sub>; c<sub>2</sub>; c<sub>3</sub>) c<sub>4</sub> équivaut à :


```
{ c1;
  while (c2) {
    c4;
    c3;
  }
}
```


-> La difficulté dans les preuves de terminaisons réside dans les boucles while et les fonctions récursives.


## 1.4. Définition (variant)

Un variant est une quantité entière positive au début de chaque itération (appel récursif et telle que sa valeur décroît strictement au cours de l’itération).

**Généralisation :**

On peut autoriser les quantités négatives strictement croissantes


## 1.5. Théorème

Une boucle composée d'opérations qui terminent et admettent un variant termine.

**Démonstration :**

Il n’existe pas de suite strictement décroissante d’entiers positifs.


## 1.6. Exemple


```
while (a > 0 && b > 0) {
  if(a % 2 == 0) {
    a = a + 1;
    b = b - 3
  } else {
    a = a - 2
    b = b + 1
}
```




* si a &lt;= 0 ou b &lt;= 0, on n’entre pas dans la boucle ;
* si a > 0 et b > 0 :
    * a est un variant à partir de la 2ème itération (a pair -> a + 1  impair puis des soustractions avec 2 conservant la parité)
    * a + b est un variant


## 1.7. Cas des fonctions récursives


```
let rec is_even (n : int) : bool =
  match n with
  |0 -> true
(*|1 -> false*)
  |_ -> is_even (n - 2)
```




* la variant “nature” (n) peut devenir négatif si on oublie un cas d’arrêt :
    * Trouver une quantité strictement décroissante ne suffit pas, il faut vérifier que l’on atteint toujours un cas d’arrêt.&lt;3

En cas de doute, on peut toujours écrire une fonction récursive comme une boucle while. On parle de dérécursivation (H.P. dans sa généralité), simple dans le cas des fonctions récursives terminales.


```
let is_even (n : int) : bool =
  let m = ref n in
  while !m <> 0 && !m <> 1 do
    m := !m - 2
  done;
  !m = 0
```



# 2. Correction


## 2.1. Définition (correction)

On dit qu’un algorithme / programme est correct vis-à-vis d’une spécification si, quelle que soit l’entrée, il termine et renvoie un résultat qui respecte la spécification.

On parle de correction totale par contraste avec la correction partielle, définie comme suit : un programme / algorithme est partiellement correct vis-à-vis d’une spécification si, quelle que soit l'entrée <span style="text-decoration:underline;">telle que l’algorithme termine</span>, le résultat renvoyé respecte la spécification.


## 2.2. Exemples


```
let rec somme (n : int) : int = if n = 0 then 0 else n + somme (n - 1)
```


-> partiellement correct


```
let rec somme (n : int) : int =
  assert (n >= 0);
  if n = 0 then 0 else n + somme (n - 1) (* uwu *)
```


-> termine bien dans tous les cas <span style="text-decoration:underline;">mais</span> ne renvoie pas de résultat dans le cas n &lt; 0.


## 


## 2.3. Définition (invariant)

Un invariant est un prédicat portant sur les variables du programme qui est satisfait avant d’entrer dans la boucle / au début du 1er appel (récursif) et tel que l’exécution d’une itération conserve sa véracité.


## 2.4. Remarque

L’objectif est de trouver un invariant tel que sa véracité en sortie de boucle garantit la spécification.


## 2.5. Exemple :


```
let suplog2 (n : int) : int =
  let k = ref 0 in
  let p = ref 1 in
  while !p < n do
    incr k;
    p := 2 * !p
  done;
  !k
```




* Terminaison :  n - !p est un variant
* Correction : on montre que I(k, p) = 2<sup>k - 1</sup> 2n et p = 2<sup>k</sup>

**I est un invariant :**



* avant d’entrer dans la boucle I(0, 1) = 2<sup>-1</sup> &lt; n et 1 = 2<sup>0</sup> -> Ok
* si I (k p! est vrai au début d’une itération : on veut montrer I (k + 1, 2p) \
I (k + 1, 2p) = <span style="text-decoration:underline;">2<sup>k</sup> &lt; n</span> et 2p = <span style="text-decoration:underline;">2<sup>k + 1</sup></span> -> vrai car p = 2<sup>k</sup> d’après I (k, p) \
		-> vrai car 2<sup>k</sup> = p &lt; n puisque la condition de boucle était vraie au début de l’itération

I en sortie de boucle démontrer la correction : on a I(k, p) = 2<sup>k - 1</sup> &lt; n et p = 2<sup>k</sup> et la condition de boucle est fausse, ie p >= n donc 2<sup>k - 1</sup> &lt; n &lt;= 2<sup>k</sup>

/!\ Cette démonstration est fausse

**Exemple :**

n = &lt;011…1><sub>2</sub> (type d’entier signés)

	-> nombre de bits de type int

p : &lt;0…01><sub>2</sub> puis &lt;0…010><sub>2</sub> puis … puis &lt;01…0><sub>2</sub> &lt; n

Or, si p = &lt;01…0><sub>2</sub>, alors 2 * p &lt; 0 &lt; n

-> il peut y avoir des dépassements de capacité -> il faut en tenir compte dans la spécification ou bien détecter l’overflow dans le calcul.


## 2.6. Exercice

Suite de Fibonacci (F<sub>n</sub> | n 

<p id="gdcalert19" ><span style="color: red; font-weight: bold">>>>>>  gd2md-html alert: equation: use MathJax/LaTeX if your publishing platform supports it. </span><br>(<a href="#">Back to top</a>)(<a href="#gdcalert20">Next alert</a>)<br><span style="color: red; font-weight: bold">>>>>> </span></p>

ℕ) :


```
int fibo(int n) {
  int x = 1, y = 1;
  for (int i = 0, i < n - 1, i++) {
    y = x + y;
    x = y - x;
  }
  return y;
}
```


I (i, x, y) = y = F<sub>i+1</sub> et x = F<sub>i</sub>

&lt;3


# 3. Graphes de flot de contrôle


## 3.1. Motivation

En pratique, il est difficile de trouver des invariants pour démontrer la correction d’un programme. Il est possible de démontrer des propriétés sur un programme à l’aide d’outils qui analysent le code sans l’exécuter (on parle d’analyse statique), mais ils ne permettent pas de tout démontrer : on fait en général des tests.

_“Program testing can be used to show the presence of bugs, but never to show their absence!”_ - Edsger W. Dÿkstra

_“Beware of bugs in the above code; I have only proved it correct, not tried it.”_ - Donald E. Knuth

Le choix des tests est particulièrement important pour ne pas “manquer” une erreur.  \
Une analyse de la structure du code peut aider à les concevoir.


## 3.2. Graphe de flot de contrôle

Définition : Un graphe de flot de contrôle est un graphe représentant la structure d’un programme Il possède un point d’entrée et un point de sortie correspondant à l’entrée et à la sortie du programme. Ses sommets sont de deux natures : il y a des blocs d’instructions élémentaires et des nœuds de décision étiquetés par une condition et correspondant aux branchements dans l’exécution des programmes. Les arcs du graphe relient les nœuds correspondant à des blocs d'instruction et branchements consécutifs.

**Construction :**



* les instructions élémentaires consécutives sont réunies dans le même bloc

    E**xemple :**


<table>
  <tr>
   <td colspan="3" >
En C :
   </td>
   <td colspan="3" >En OCaml :
   </td>
  </tr>
  <tr>
   <td>E ->
   </td>
   <td>int x = 1;
<p>
int y = 2;
<p>
x = x + y;
<p>
y = x - y;
<p>
x = x - y;
   </td>
   <td>-> S
   </td>
   <td>E ->
   </td>
   <td>let a = f 2 in
<p>
(a, g a)
   </td>
   <td>-> S
   </td>
  </tr>
</table>




* une instruction conditionnelle crée un branchement

    `if b then c1 else c2` ~> 


    

<p id="gdcalert20" ><span style="color: red; font-weight: bold">>>>>>  gd2md-html alert: inline image link here (to images/image2.png). Store image on your image server and adjust path/filename/extension if necessary. </span><br>(<a href="#">Back to top</a>)(<a href="#gdcalert21">Next alert</a>)<br><span style="color: red; font-weight: bold">>>>>> </span></p>


![alt_text](images/image2.png "image_tooltip")


* une boucle crée également un branchement :

    `while (b) { \
  c \
}` ~>


    

<p id="gdcalert21" ><span style="color: red; font-weight: bold">>>>>>  gd2md-html alert: inline image link here (to images/image3.png). Store image on your image server and adjust path/filename/extension if necessary. </span><br>(<a href="#">Back to top</a>)(<a href="#gdcalert22">Next alert</a>)<br><span style="color: red; font-weight: bold">>>>>> </span></p>


![alt_text](images/image3.png "image_tooltip")



    On pourra voir une boucle for comme une boucle while


    `for (c1; c2; c3) { \
  c4 \
}` ->


    

<p id="gdcalert22" ><span style="color: red; font-weight: bold">>>>>>  gd2md-html alert: inline image link here (to images/image4.png). Store image on your image server and adjust path/filename/extension if necessary. </span><br>(<a href="#">Back to top</a>)(<a href="#gdcalert23">Next alert</a>)<br><span style="color: red; font-weight: bold">>>>>> </span></p>


![alt_text](images/image4.png "image_tooltip")



    On peut adapter cela enn OCaml en écrivant une condition qui porte sur la variable de la boucle


    `for i = a to b do c done` ~>


    

<p id="gdcalert23" ><span style="color: red; font-weight: bold">>>>>>  gd2md-html alert: inline image link here (to images/image5.png). Store image on your image server and adjust path/filename/extension if necessary. </span><br>(<a href="#">Back to top</a>)(<a href="#gdcalert24">Next alert</a>)<br><span style="color: red; font-weight: bold">>>>>> </span></p>


![alt_text](images/image5.png "image_tooltip")



**Exemple :**


    Calcul du PGCD par soustractions successives


```
     while (p != q)
       if (p > q)
         p = p - q;
       else
         q = q - p;
     return p; ~>
```




<p id="gdcalert24" ><span style="color: red; font-weight: bold">>>>>>  gd2md-html alert: inline image link here (to images/image6.png). Store image on your image server and adjust path/filename/extension if necessary. </span><br>(<a href="#">Back to top</a>)(<a href="#gdcalert25">Next alert</a>)<br><span style="color: red; font-weight: bold">>>>>> </span></p>


![alt_text](images/image6.png "image_tooltip")



## 3.3. Chaînes et exécutions

Une exécution du programme correspond à un chemin dans son graphe de flot de contrôle.

**Exemple :**

PGCD avec p = 6 et q = 10, on obtient le chemin :

E -> W -> I -> C2 -> W -> I -> C1 -> W -> I -> C2 -> W -> R -> S

Un chemin ne correspond pas forcément à une exécution

**Exemple :**

`if b then x = 0; \
if != x &lt;> 0 then y := 1 / !x;` ~>



<p id="gdcalert25" ><span style="color: red; font-weight: bold">>>>>>  gd2md-html alert: inline image link here (to images/image7.png). Store image on your image server and adjust path/filename/extension if necessary. </span><br>(<a href="#">Back to top</a>)(<a href="#gdcalert26">Next alert</a>)<br><span style="color: red; font-weight: bold">>>>>> </span></p>


![alt_text](images/image7.png "image_tooltip")


Le chemin E -> I1 -> X -> I2 -> Y -> S ne correspond à aucune exécution.

On appelle chemin faisable un chemin qui correspond à (au moins) une exécution.

**Le principe de la conception de tests à l’aide du graphe der flot de contrôle est le suivant :**



1. On choisit un ensemble de chemins selon un critère de couverture fixé à l’avance
2. On élimine les chemins infaisable
3. Pour chaque chemin restant, on étudie les conditions qui portent sur les entrées du programme pour que l'exécution correspondante au chemin. On choisit alors une entrée comme cas de test pour que l’exécution correspondante au chemin. On choisit alors une entrée comme cas de test.


## 3.4. Critère de couverture

Pour couvrir tous les cas possibles, le critère le plus évident est de prendre tout les chemins possibles.

Par exemple pour le graphe en 3.3. , on a les chemins suivants :

E -> I1 -> X -> I2 -> Y -> S \
         |               |-> S \
         |-> I2 -> Y -> S \
               |-> S

Cependant, dès qu’il y a un boucle, il y a une infinité de chemins dans le graphe.

**Remarque :**

On peut avoir une infinité de chemins faisables même si le programme se termine (ex : une boucle dont le nombre d’itérations dépend d’une variable d’entrée)

On peut affaiblir ce critère en considérant tous les chemins de longueur au plus k (fixé) ou tous les chemins qui vont parcourir la boucle au plus k fois.

**On peut choisir d’autres critères, comme**



* **la couverture de toutes les instructions du programme :** on choisit un ensemble de chemins tels que chaque sommet est couvert par au moins un chemin.

    Exemple :


    `if (x != 0) x = 1; \
y = 1 / x; `~>


    

<p id="gdcalert26" ><span style="color: red; font-weight: bold">>>>>>  gd2md-html alert: inline image link here (to images/image8.png). Store image on your image server and adjust path/filename/extension if necessary. </span><br>(<a href="#">Back to top</a>)(<a href="#gdcalert27">Next alert</a>)<br><span style="color: red; font-weight: bold">>>>>> </span></p>


![alt_text](images/image8.png "image_tooltip")



    Le chemin E -> I -> X -> Y -> S satisfait le critère mais ne concerne pas la division par 0.

* **la couverture de toutes les branches : **on choisit un ensemble de chemins tels que pour chaque nœud de décision, les deux branches issues de ce nœud sont couvertes par au moins un chemin.

    **Exemple :**


    `if a &lt; 2 && b = a  then x := 2 - a else x := a - 2` ~>


    

<p id="gdcalert27" ><span style="color: red; font-weight: bold">>>>>>  gd2md-html alert: inline image link here (to images/image9.png). Store image on your image server and adjust path/filename/extension if necessary. </span><br>(<a href="#">Back to top</a>)(<a href="#gdcalert28">Next alert</a>)<br><span style="color: red; font-weight: bold">>>>>> </span></p>


![alt_text](images/image9.png "image_tooltip")



    Le critère est satisfait par l’ensemble des chemins {E -> I -> V -> S ; E -> I -> F -> S}


    Ces chemins sont faisable (a = b = 1 et a = b = 3)


    La couverture des branches implique la couverture des instructions mais pas nécessairement la couverture de toutes les possibilités (il manque le cas où a != b).


    Il est possible de rajouter comme contrainte le choix de tests couvrant toutes les valeurs possibles par des sous-conditions, mais le nombre de tests devient exponentiel en le nombre de sous-conditions.


    **Remarque :**


    Il n’est pas forcément intéressant de considérer toutes les valeurs pour les sous-conditions (ex : évaluation paresseuse des opérateurs booléens).



## 3.5. Détection des chemins infaisable et choix des tests

Afin de déterminer si un chemin est faisable et, le cas échéant, de choisir un test concret le réalisant, on peut donc calculer un "condition de chemin“ en fonction de la valeur des entrées par exécution symbolique. Cette condition réunit les contraintes qui portent sur les entrées pour que l’exécution corresponde au chemin. 

**On suit les étapes suivantes :**



1. On donne une valeur symbolique aux variables d’entrées.
2. On initialise la condition de chemin à vrai
3. On suit le chemin
    * si le nœud est un bloc d’instructions : on exécute ces instructions sur les valeurs symboliques. 
    * si le nœud est un nœud de décision : on remplace la condition de chemin par la conjonction de cette condition et de la condition du nœud (ou de sa négation suivant la branche suivie par le chemin) où l’on a remplacé les variables par leur valeur symbolique.

**Exemple :**

Suite de Syracuse

`while (x != 1) { \
 if (x %2 == 0) { \
    x = x / 2; \
  } else { \
    x = 3 * x + 1 \
  } \
} `~>



<p id="gdcalert28" ><span style="color: red; font-weight: bold">>>>>>  gd2md-html alert: inline image link here (to images/image10.png). Store image on your image server and adjust path/filename/extension if necessary. </span><br>(<a href="#">Back to top</a>)(<a href="#gdcalert29">Next alert</a>)<br><span style="color: red; font-weight: bold">>>>>> </span></p>


![alt_text](images/image10.png "image_tooltip")



<table>
  <tr>
   <td>Chemin
   </td>
   <td>E ->
   </td>
   <td>W ->
   </td>
   <td>I ->
   </td>
   <td>X1 ->
   </td>
   <td>W ->
   </td>
   <td>S
   </td>
  </tr>
  <tr>
   <td>x
   </td>
   <td>x<sub>0</sub>
   </td>
   <td>_
   </td>
   <td>_
   </td>
   <td>x<sub>0</sub> / 2
   </td>
   <td>_
   </td>
   <td>_
   </td>
  </tr>
  <tr>
   <td>Condition de chemin
   </td>
   <td>vrai
   </td>
   <td>x<sub>0</sub> ≠ 1
   </td>
   <td>x<sub>0</sub> ≠1
<p>
x<sub>0</sub> ≡ 0 [2]
   </td>
   <td>_
   </td>
   <td>x<sub>0</sub> ≠ 1
<p>
x<sub>0</sub> ≡ 0 [2]
<p>
x<sub>0</sub> / 2 = 1
   </td>
   <td>_
   </td>
  </tr>
</table>


Le chemin est faisable avec l’entrée x = 2.


<table>
  <tr>
   <td>Chemin
   </td>
   <td>E ->
   </td>
   <td>W ->
   </td>
   <td>I ->
   </td>
   <td>X2 ->
   </td>
   <td>W ->
   </td>
   <td>S
   </td>
  </tr>
  <tr>
   <td>x
   </td>
   <td>x<sub>0</sub>
   </td>
   <td>_
   </td>
   <td>_
   </td>
   <td>3x<sub>0</sub> + 1
   </td>
   <td>_
   </td>
   <td>_
   </td>
  </tr>
  <tr>
   <td>Condition de chemin
   </td>
   <td>vrai
   </td>
   <td>x<sub>0</sub> ≠ 1
   </td>
   <td>x<sub>0</sub> ≠1
<p>
x<sub>0</sub> ≡ 1 [2]
   </td>
   <td>_
   </td>
   <td>x<sub>0</sub> ≠ 1
<p>
x<sub>0</sub> ≡ 1 [2]
<p>
3x<sub>0</sub> + 1 = 1
   </td>
   <td>_
   </td>
  </tr>
</table>


Le chemin est infaisable : x<sub>0</sub> ≡ 1 [2] et 3x<sub>0</sub> + 1 = 1, contradiction (x0 impair donc 3x<sub>O</sub> + 1 pair).

Chapitre 5 : Ordres et inductions



1. Ensembles ordonnés

1.1. Vocabulaire

1.1.1. Définition (relation d’ordre)

Soit E un ensemble : une rel	tion &lt;= sur E est une relation d’ordre sur elle est :



* réflexive : 1
* antisymétrique 2
* transitive : 3

On appelle ensemble ordonné tout couple (E, &lt;=) où &lt;= est une relation d’ordre E

1.1.2. Exemple

setN, setZ, setR avec l’ordre &lt;= habituel

(P(E), <span style="text-decoration:underline;">C</span>) où A &lt;= B ssi 4 :



* réflexivité : 5
* antisymétrique 6
* transitive : 7

…



* réflexivité : 8
* antisym : 9
* trans : 10

1.1.3. Définition (ordre stricte)

Soit (E, &lt;=) un ensemble ordonné

L'ordre strict &lt; associé à &lt;= est défini par 11

1.1.4. Remarque

Un ordre strict n’est pas un ordre (il n’est pas réflexif)

1.1.5. Définition (prédécesseur, successeur)

Soit (E, &lt;=) un ensemble ordonné et xy in E



* x n’est pas prédécesseur (resp successeur) de y ssi x&lt;y (resp y&lt;x)
* x n’est pas prédécesseur (resp successeur) de y ssi x&lt;y (resp y&lt;x) et n’existe pas d’élément Z in E tel que x&lt;z&lt;y (resp y&lt;z&lt;x)

1.1.6. Représentation graphique d’un ensemble ordonné

Soit (E, &lt;=) un ensemble ordonné fini

On représente (E, &lt;=) par son diagramme de HAsse qui est un graphe dont les sommets sont les éléments de E et tel que qu’un arc x -> y existe si x est un prédécesseur de y.

Exemple (P({x, y, z}), &lt;=) :

12

1.1.7. Définition (ordre total)

Soit (E, &lt;=) un ensemble ordonné

&lt;= est total ssi 13

On dit alors que E est totalement ordonné

1.1.8. Exemple :

&lt;= sur setN, setZ, setR au total

(P(E), &lt;=) n’est pas toujours total (s’il y a au moins 2 éléments x, y in E, {x} et {y}n’est pas comparable)

14

1.1.9. Défiition (élément minimal/maximal)

Soit (E, &lt;=) un ensemble ordonné et P in P(E)



* Un élé min de P est un élé 15
* Un min pour P est un élé 16

1.1.10. Remarque

LE min, s’il existe, est unique et est min

Si l’ordre est total, être minimal est équivalent à être minimum

Il peut y avoir plusieurs élé minimaux : 17

2 et 3 sont minimaux

1.2. Ordres et inductions bien fondés

1.2.1. Déf (ordre bien fondé)
