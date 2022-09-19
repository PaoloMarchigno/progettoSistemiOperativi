### MIDI KEYBOARD
per la realizzazione di questo progetto ho sfruttato come base il programma sulla keyboard messo a disposizione sul repository

### COSA HO FATTO
ho costruito in arduino una piccola tavola con 7 pulsanti (ogni pulsante rappresenta una nota diversa) collegata propriamente con i pin a (da 22 a 28), a livello di codice ho gestito la durata della nota  con un contatore globale nel while(1) e un array che permette il salvataggio dei tempi al premere del pulsante, l'identificazione della note è anche essa gestita tramite array di valori. Purtroppo non sono riuscito a trovare librerie per far suonare davvero il programma.  
### QUALE PROBLEMA RISOLVE 
in realtà non lo so. 
### COME FARLO GIRARE 
portarsi all'interno della cartella "ProgettoSistemiOperativi"  ed eseguire: 
  $make keyboard.hex
e successivamente : 
  $cutecom
