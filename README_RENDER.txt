DEPLOIEMENT PUBLIC SUR RENDER

Cette version est préparée pour Render avec Docker :
- Docker installe Python et g++ ;
- le moteur C++ est compilé automatiquement sous Linux ;
- Gunicorn démarre Flask sur le port fourni par Render.

ETAPES :
1. Décompressez ce dossier.
2. Créez un compte sur https://github.com/ puis un nouveau dépôt (repository) public.
3. Dans GitHub, faites Add file > Upload files et envoyez tous les fichiers et dossiers contenus dans DarlyRevise_Studio.
   Le Dockerfile doit être à la racine du dépôt, au même niveau que app.py.
4. Sur https://render.com/, créez un compte et connectez GitHub.
5. Cliquez New > Web Service, puis choisissez le dépôt.
6. Choisissez Runtime = Docker et le plan Free si proposé.
7. Laissez le Dockerfile à la racine (ne renseignez pas de commande Python manuelle).
8. Cliquez Deploy.
9. Quand le statut devient Live, ouvrez l'URL *.onrender.com affichée par Render et partagez-la.

A SAVOIR :
- Sur le plan gratuit, le service s'endort après 15 minutes sans visite ; la première visite suivante peut prendre environ une minute.
- Ce prototype utilise un moteur C++ heuristique, pas une IA générative réelle.
