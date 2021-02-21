# TrackChip, le traqueur autonome ! 
L'objectif de ce projet est double :
* Développer un traqueur autonome de précision ~10m (partie Device)
* Récupérer ces informations sur un client WEB (partie Cloud)

### Device
Le device en lui-même est basé sur un micro-controleur ESP32, entouré des périphériques suivant :
* Altimètre BMP180
* GPS ADA746
* Module Sigfox BRKWS01
* Batterie LIPO 1050mAh
* Régulateur de tension 5V Polulu U1V11F5

```
Les sources des bibliothèques des périphériques ainsi que du PCB sont disponibles dans le dossier /devices du git.
```
### Site Web
Le site internet possède les fonctionnalitées suivantes :
* Position de l'utilisateur
* Position du traqueur
* Calcul de la différence d'altitude
* Calcul du trajet en voiture pour rejoindre le traqueur
* Historique des positions du traqueur

```
Les sources du serveur, de la base de donnée et du site Web sont disponibles dans la partie cloud/ du git.
```

# Notice d'utilisation
Le système dans son ensemble possède le comportement suivant :
* Le device utilise le GPS quand il reçoit un signal
* Le device utilise le scrapping WiFi quand le GPS est indisponible
* La position est envoyée sur notre serveur via le réseau SigFox
* Les informations sont accessibles sur notre site via un client Web. 

### Device
Le device s'allume et s'éteint avec le boutton ON/OFF sur le côté de sa boîte protectrice.
Il envoie alors sa position toutes les 5 minutes.
```
Le programme faisant fonctionner le device peut-être modifié et téléversé avec l'IE Arduino.
Il faut simplement s'assurer que les librairies utilisées sont bien visibles en les ajoutant dans ~/Arduino/lib.
```

### Réseau SigFox
Le device envoie ses données sur un backend web en utilisant le réseau SigFox.
Ce backend redirigie ensuite ces informations sur notre serveur grâce à une fonction de callback.
On accède au backend via l'URL suivant :
```
https://backend.sigfox.com/auth/login
```

### Serveur
Le serveur est un ensemble de programmes gérant le site Web ainsi que la base de donnée. 
Il peut être hebergé sur une machine locale, ou bien sur internet via un VPS.
Afin d'avoir accès aux nombreux service de géolocalisation (carte, itinéraire, etc), nous avons utilisé différentent APIs fournit par Google.
Ces APIs nécéssitent une clés pour pouvoir y accéder que vous devrez générer en créant d'abord un compte Google Cloud Platform. 
Puis en copiant, collant votre clés à la place de la notre dans le fichier dev/cloud/php/map.php à la ligne 44 dans le lien du script.
En local, on peut lancer le site avec les commandes suivantes :
```
$ cd /path/to/sources
$ php -S 127.0.0.1.:8888
```

### Site Web
Nous avons choisi d'utiliser l'hébergeur always-data pour notre site.
Cela donnait un URL du type :
```
https://track-chip.alwaysdata.net/
```

