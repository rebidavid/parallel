# Párhuzamos algoritmus beadandó

A féléves beadandóban megírt kódok célja két 3x3-as mátrix összeadása volt, ahol a munka elosztása több szálon történik.
Szabadon választott techonlógiának az Opencl-t választottam.

##Pthread
Meghatároztam a mátrix méretét (MATRIX_SIZE) és a szálak számát (NUM_THREADS) előredefiniált makrókkal.
ThreadData striktúrában tárolom a szál adatait, az A,B és az eredmény mátrixra mutató pointereket.
A matrixAddition függvény megkapja a szál adatait, kiszámítja a kezdő és vég sorait a mátrixnak, végrehajtja az összeadást.
A main függvény deklarálja az A, B és eredmény mátrixokat, a szálakat és a hozzá tartozó adatokat és kiírja a mátrixok tartalmát.

##OpenMP
Meghatároztam a mátrix méretét (MATRIX_SIZE) előredefiniált makrókkal.
A printMatrix függvény kiírja a mátrix tartalmát.
Az '#pragma omp parallel for' direktívával párhuzamosítja a következő for ciklusokat.
A 'collapse(2)' paraméterrel a két egymásba ágyazott for ciklust együtt párhuzamosítja.
A for ciklusokban végrehajtja a mátrixösszeadást és az eredményt elhelyezi a result mátrixban.
Kiírja az A és B mátrixokat, valamint az eredmény mátrixot a printMatrix függvénnyel.

##OpenCL
Meghatároztam a mátrix méretét (MATRIX_SIZE) előredefiniált makrókkal.
A printMatrix függvény kiírja a mátrix tartalmát.
A main függvény deklarálja a szükséges OpenCL változókat,meghatározza a mátrixösszeadást elvégző kernel függvényt.
Létrehozza az A, B és eredmény mátrixokat, valamint a hozzájuk tartozó OpenCL buffer objektumokat, futtatja a kernel függvényt a clEnqueueNDRangeKernel függvénnyel.
Kiírja az A és B mátrixokat, valamint az eredmény mátrixot a printMatrix függvénnyel.
