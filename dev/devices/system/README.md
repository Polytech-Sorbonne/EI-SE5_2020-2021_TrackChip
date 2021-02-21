# Classe track_chip
Classe encapsulant les librairies pour les différents périphériques.
(Communication, capteurs, position etc ...)

# Précaution lors de l'upload du code 
Il faut débrancher le broche TX du GPS pour pouvoir téléverser le code depuis l'IDE arduino.
C'est parce que ce gps utilise le même port série que le calbe USB utilisé pour téléverser.

# Architecture du code 
* On utilise la liaison _Serial_ pour imprimer des caractères sur la liaison USB

* Le gps communique avec la liaison _Serial1_ sur les broches RX0 et TX0 de l'ESP32
	+ BAUDE=9600 par défaut

* Le wisol communique avec la liaison _Serial2_ sur les broches RX2 et TX2 de l'ESP32 
	+ BAUDE=9600 par défaut

# examples/class_system/
Ce dossier instancie un code example utilisant la classe track_chip
(En cours de développement)

# examples/bare_system/
Ce dossier instancie un code example utilisant les libairies sans la classe track_chip 
