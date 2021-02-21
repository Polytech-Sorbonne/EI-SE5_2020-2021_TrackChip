# KiCad - Architecture

## Librairie
```
Le fichier track_chip.lib contient tout les "symboles" créés pour le projet :
	- ESP32 NodeMCU
	- BMP180
	- ADA746
	- BRKWS01

La librairie contient aussi les symboles déjà présents par défaut dans KiCad, 
afin d'éliminer la dépendance à la version du logiciel.
```

## Schéma
```
Le fichier .sch représente le schéma du circuit électronique du système (Eeschema).
Il instancie les différents symboles de la librairie du projet.
```

## Empreintes

### Dimensions
```
- Largeur typique d'une piste : 1mm
- Largeur typique d'une alimentation : 2mm
- Ecart entre les pastilles : 2.54mm
- Diamètre typique de perçage : 0.8mm
- Diamètre typique de pastille : 1.5mm
```

### Plans de masse
```
Recommendations : faire des plans de masses.
Si il y a un domaine analogique et un domaine numérique, 
faire des plans de masse séparés et les relier avec une piste.
```

## Batterie
```
On utilise un circuit avec chargeur intégré.
```
# Version Sigfox
La version Sigfox utilise un module Wisol pour les communications.
C'est cette version qui a été retenue pour les démonstrations

# Version GSM
La version GSM utilise une carte SIM pour les communications.
Cette version est en cours de développement.
