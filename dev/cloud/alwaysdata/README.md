# Procedure à suivre pour créer une cles SSH sur le serveur AlwaysData

## Etape 1 :

Générer la clé en local.
		
		$ mkdir -p $HOME/.ssh
		$ chmod 0700 $HOME/.ssh
		$ ssh-keygen -t ed25519 -f $HOME/.ssh/id_ed25519
		
		(tips : vous pouvez indiquez une passphrase vide pour pouvoir vous connecter directement sans la rentrer)

## Etape 2 :

Déclarer la clés publique (.pub) sur le serveur.

		$ ssh-copy-id -i $HOME/.ssh/id_ed25519.pub track-chip@ssh-track-chip.alwaysdata.net

## Etape 3 :

Se connecter au serveur en ssh.

		$ ssh track-chip@ssh-track-chip.alwaysdata.net