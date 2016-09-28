# WestWorldWithMessaging

## Membres du groupe
Nicolas BLANC - Code permanent : *BLAN30039307* </br>
Charles GAGNON- Code permanent : *GAGC30099600*

## Descriptif du projet
Mettre en place des automates pour manipuler des IAs simples.

### Ajout
- Ajout d'un soulard `Classe Drunk` qui intéragit avec le mineur dans le saloon.
- Ajout d'un enfant `Classe MinersChild` qui intéragit avec le mineur, mais aussi la femme du mineur.
- Les entités sont executé en parallèle, le programme est threadé, et seul une entité à la fois peut écrire sur la console, les messages ne sont donc pas mélangés `Classe MessageThread`

## Difficulté
- Il a fallu faire plusieurs tests avant de mettre en place les threads correctement. Et l'ajout d'une classe pour afficher les messages car ceux-ci peuvent être écris tous en même temps
- Une erreur sur l'ordinateur de Nicolas BLANC non résolue, `Erreur C1083 : Impossible d'ouvrir le fichier source : '..\..\Common\Time\CrudeTimer.cpp' : No such file or directory	WestWorldWithMessaging`
 
