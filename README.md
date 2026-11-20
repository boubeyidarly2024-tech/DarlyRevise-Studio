# DarlyRévise Studio — projet pédagogique

Projet de démonstration d'un site de révision utilisant :
- HTML : structure de l'interface
- CSS : design responsive
- JavaScript : interactions navigateur et appels HTTP
- Python / Flask : serveur web et orchestration
- C++ : moteur local de génération de contenus
- Code::Blocks : édition et compilation du programme C++

## 1. Préparer les logiciels
Installe Python 3, Code::Blocks avec le compilateur MinGW/GCC, et un navigateur récent.

## 2. Compiler le moteur C++ avec Code::Blocks
1. Ouvre `DarlyRevise.cbp` dans Code::Blocks.
2. Choisis la cible `Debug` ou `Release`.
3. Clique sur Build (ou F9).
4. Le programme doit être créé sous `engine/DarlyEngine.exe` (Windows).
   Si Code::Blocks produit un fichier sans `.exe`, vérifie les paramètres de sortie de la cible.

Alternative depuis un terminal MinGW ouvert dans le dossier du projet :
`g++ -std=c++11 engine/main.cpp -o engine/DarlyEngine.exe`

## 3. Installer Python et démarrer le serveur
Ouvre un terminal dans le dossier du projet :

Windows :
`py -m venv .venv`
`.venv\\Scripts\\activate`
`py -m pip install -r requirements.txt`
`py app.py`

macOS / Linux :
`python3 -m venv .venv`
`source .venv/bin/activate`
`python3 -m pip install -r requirements.txt`
`python3 app.py`

## 4. Ouvrir le site
Dans ton navigateur, va sur `http://127.0.0.1:5000`.

Le navigateur sert l'interface HTML/CSS/JavaScript. JavaScript envoie une requête à Flask. Flask lance le programme C++ compilé, lui transmet le cours et récupère le résultat.

## 5. Structure
- `app.py` : serveur Python Flask
- `DarlyRevise.cbp` : projet Code::Blocks
- `engine/main.cpp` : moteur C++
- `templates/index.html` : page web
- `static/style.css` : design
- `static/app.js` : interactions
- `requirements.txt` : dépendance Python

## Limites et sécurité
Ce prototype fonctionne localement et produit des résumés heuristiques et des questions génériques. Ce n'est pas une IA générative et il ne garantit pas l'exactitude pédagogique. Pour une vraie IA, il faudra connecter un fournisseur d'IA depuis le serveur Python, sans exposer la clé API dans le navigateur.

Pour une publication Internet, ne déploie pas directement cette configuration Flask de développement ni un exécutable Windows. Il faut adapter le déploiement à un serveur compatible avec le système d'exploitation cible, sécuriser les entrées, limiter la taille des cours et utiliser un serveur WSGI de production.
