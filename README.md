# Calcolo fattori correttivi esperimento Cavendish

Nella repository sono presenti due file per calcolare i valori di fc1 ed fc2 per correggere gli errori sistematici nel calcolo di G.

Per compilare, da dentro la cartella clonata:
```shell
  cmake -S ./src -B ./release -DCMAKE_BUILD_TYPE=Release
  cmake --build release
```
*Il secondo comando potrebbe richiedere un po' di tempo a finire, in quanto, per ottimizzare l'uso di memoria durante l'esecuzione del programma, è stato preferito eseguire una parte dei calcoli durante la compilazione

Per eseguire, poi:
```shell.
  /release/correzione_fc1
  /release/correzione_fc2
```

I risultati dei calcoli saranno stampati a schermo e scritti nella cartella ./output

Per cambiare i parametri usati durante il calcolo (b, d, M, R, H o il numero di suddivisioni del cilindro) basta modificare le costanti definite a inizio programma dentro i files in ./src
