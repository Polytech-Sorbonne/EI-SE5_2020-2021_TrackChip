# Altimètre BMP180

## BUS I2C
```
Deux fils (SDA, SCL) tirés à 5V.

I2C utilise des séquences de 8 bits (MSB first = Big Endian)

Start - slave_addr - A - slave_reg - A - Data - A - Stop

Start	: SDA drops low, SDC still high
ACK	: le slave tire la ligne SDA à zéro
Stop 	: SDA low -> high ; SCL high
```

## Librairie utilisée
```
https://bitbucket.org/christandlg/bmp180mi/src/master/
```

## UML
```
Cette librairie possède le diagramme UML suivant :
		BMP180MI 
		   |
		   |
	     BMP180TwoWire 
		   |
		   |
	       BMP180I2C

On se contente donc de modifier la classe fille BMP180I2C
```

## Packager la librairie modifiée
```
Créer un lien symbolique du dossier bmp180/ dans Arduino/libraries :
$ cd ~/Arduino/libraries
$ ln -s /path/to/bmp180
```
