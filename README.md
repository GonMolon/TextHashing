# TextHashing
College project to learn and experiment with hashing applied to similarity-level detection in text files.


Instrucciones para la ejecución del programa

Compilar el código fuente: make. -> Crea varios ejecutables, y los deja en el directorio /exp.
      
Dentro del directorio /exp hay cuatro ejecutables:
   
       
       - generator.exe: genera una permutación aleatoria de las palabras de un fichero. 
            Parámetros (fichero_entrada fichero_salida [-w palabras por linea][-s seed]):
            
              ·fichero_entrada: documento con el que crearemos la permutación.
              ·fihcero_salida: documento en el que habrá la permutación aleatoria del fichero_entrada.
              ·-w palabaras por linea: número de palabras por linea que contendrá el fichero de salida.
              ·-s seed: semilla a partir de la cual se generarán números aleatorios.
       
       
       - SimCalculator.exe: programa principal que calcula el coeficiente de similaridad entre documentos, 
         con jaccard y minhash. 
            Parámetros (fichero1 fichero2 modo), dependiendo del modo puede tener más parametros:
            
              ·fichero1 y fichero2: documentos a comparar.
              ·modo, puede ser uno de los siguientes:
                  + all: ejecuta todos los possibles modos.
                  + jaccard: hace el cálculo a partir de guardar k-shingles como strings en un conjunto para cada fichero.
                  + jaccard_hash: realiza el cálculo almacenando k-shingles como hashes de 4 bytes en un conjunto para cada
                    fichero. 
                  + jaccard_roll: igual que jaccard_hash pero usando rolling hash para hacer los hashes.
                  + minhash: calcula la similitud haciendo las signaturas minhash de cada documento. Necesita un parámetro
                    adicional (número de funciones de hash utilizadas por el minhash.)
                  + minhash_roll: igual de minhash pero usando rolling hash para hacer los hashes. Necesita un parámetro
                    adicional (número de funciones de hash utilizadas por el minhash.)
                    En todos los modos excluiendo all, puedes poner como parámetro el tamaño de los shingles con el que
                    quieras que se ejecute el programa. En los modos de minhash también puedes poner como parametro una seed   
                    para generar la funciones de hash.
           Las instrucciones del ejecutable se pueden encontrar ejecutando el programa con el parametro help    
           (./SimCalculator.exe help | less).
         
         
       - lsh.exe: programa que aplica el algoritmo de LSH a un conjunto de documentos dado. 
              Parámetros (PATH_PATTERN k t min seed):
              
                ·PATH_PATTERN: path del directorio contenedor de los documentos que se quieren analizar,
                 el programa cojerá todos los archivos .txt del directorio.
                ·k: tamaño de los shingles.
                ·t: número de funciones de hash.
                ·min: coeficiente mínimo para que dos documentos sean comparables. (valor entre 0 y 1).
                ·seed: semilla que se usará para generar las funciones de hash que generarán las signatures.
              
       
       - seed_gen.exe: usado por el script que genera los experimentos. Genera un entero aleatorio.       
              
            
