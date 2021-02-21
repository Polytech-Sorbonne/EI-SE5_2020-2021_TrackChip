Guide Utilisation librairie Wisol
developpée pour module Wisol Sigfox et ESP32 
Pour utiliser la librairies :
compresser le dossier wisol au format .zip puis ajouter depuis l'IDE: sketch > include library

Pour utiliser l'example sans mdofications :
TX (wisol) -> RX2 (esp32)
RX (wisol) -> TX2 (esp32)
+ (wisol) -> 3.3V (esp32)
- (wisol) -> GND (esp32)
