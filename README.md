# Párhuzamos algoritmusok beadandó

## <a href="https://github.com/nsbalint/ParallelAlgorithms/tree/main/Beadand%C3%B3%201">1.Beadandó: Egyesítési rendezés</a>

Egyesítési rendezés pthread használatával. Felhasználatól bekér egy tetszőleges tömb méretet, majd hogy hány szálon szeretné, hogy lefusson a program.

### Futtatás:
    make

## <a href="https://github.com/nsbalint/ParallelAlgorithms/tree/main/Beadand%C3%B3%202">2.Beadandó: Szummaszámítás omp, pthread használatával és szekvenciális számítással</a>
Egy user által bekért szám 1:n-ig történő összeadása. A user adja meg ezenkívűl a szálak számát is amit a program használni fog. A program Openmp-t és Pthread-et is használ, statisztika mutatja, hogy nagyobb számoknál az OpenMP ami a leggyorsabb számítási idővel rendelkezik.
### Futtatás:
    make

## <a href="https://github.com/nsbalint/ParallelAlgorithms/tree/main/Beadand%C3%B3%203">3.Beadandó: Gauss-elimináció</a>
Gauss elimináció kiszámítása. Terminálból a lefordítás után, a user argumentumként adhatja meg a mátrix nagyságát, egy szövegfájlt amiben az értékeket, és a számítás gyorsaságát letárolja a rendszer, legutolsó sorban pedig az optimizációként, hogy hány szálon fusson az adott program.

### Futtatás terminálból:
  javac GaussElimination.java
  java GaussElimination.java <mátrix nagysága> <kimenő fájl neve> <szálak száma>



