# 1. Methoden zur Laufzeitanalyse

## 1.1. Laufzeitmessung

Die interne Laufzeitmessung wird via `Timer::Timer` realisiert. Hierzu werden im Konstruktor die aktuelle Zeit
`std::chrono::high_resolution_clock::now()` gespeichert und im Destruktor die Differenz zur aktuellen Zeit berechnet.

Das Script `./profile.sh` filtert die Ausgabe und speichert die Ergebnisse
in `profiling_data/$SUBFOLDER/$DATE_internal.txt`.

## 1.2. Profiling

### 1.2.1 Profiling mit `gprof`

`gprof` ist ein Profiling-Tool, das in der Regel mit dem GNU-Compiler `gcc` installiert wird. Es kann verwendet werden,
um die Laufzeit von Programmen zu analysieren und zu optimieren. `gprof` erzeugt ein Profiling-File, das die Laufzeit
der Funktionen im Programm aufzeichnet. Dieses Profiling-File kann dann mit dem `gprof`-Tool analysiert werden, um die
Laufzeit der Funktionen zu identifizieren, die am meisten Zeit in Anspruch nehmen.

Die Verwendung von `gprof` ist einfach. Zuerst muss das Programm mit dem `-pg`-Flag kompiliert werden, um das Profiling
zu aktivieren. Dann wird das Programm ausgeführt, um das Profiling-File zu erzeugen. Schließlich wird das Profiling-File
mit dem `gprof`-Tool analysiert, um die Laufzeit der Funktionen zu identifizieren, die am meisten Zeit in Anspruch
nehmen.

Herzu wurde das `CMakeLists.txt`-File um folgende Zeilen erweitert:

```cmake
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -pg")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -pg")
```

Die Analysedatei wird vom Script `./profile.sh`erzeugt und in `profiling_data/$SUBFOLDER/$DATE_gprof_output.txt`
gesichert.

### 1.2.2 Profiling mit `perf`

`perf` ist ein Profiling-Tool, das in der Regel mit dem Linux-Kernel installiert wird. Es kann verwendet werden, um die
Laufzeit von Programmen zu analysieren und zu optimieren. `perf` erzeugt ein Profiling-File, das die Laufzeit der
Funktionen im Programm aufzeichnet. Dieses Profiling-File kann dann mit dem `perf`-Tool analysiert werden, um die
Laufzeit
der Funktionen zu identifizieren, die am meisten Zeit in Anspruch nehmen.

Das Script `./profile.sh` erzeugt die Analysedatei und speichert sie in `profiling_data/$SUBFOLDER/$DATE_perf.data`.
Diese können mittels `perf diff $FILE1 $FILE2` verglichen werden.

### 1.2.3 Profiling mit `valgrind` / `callgrind` und `kcachegrind`

`valgrind` ist ein Framework zur Erstellung von dynamischen Analysewerkzeugen. Es kann Speicherlecks, ungültigen
Speicherzugriff, uninitialisierten Speicher und ähnliche Probleme in C und C++ Programmen erkennen. `valgrind` bietet
verschiedene Tools an, von denen eines Memcheck ist, das am häufigsten für die Speicherfehleranalyse verwendet wird.
`valgrind` ändert den Code der Zielanwendung in Echtzeit, um ihn zu überwachen und zu analysieren, was bedeutet, dass es
das Ausführen der Programme stark verlangsamt.

`callgrind` ist ein Profiling-Tool, das auf der `valgrind`-Infrastruktur aufbaut. Es sammelt unter anderem Informationen
über die Ausführungshäufigkeit von Funktionen, die Aufrufbeziehungen zwischen Funktionen und die Anzahl der ausgeführten
Instruktionen. `callgrind` ist besonders nützlich zur Leistungsoptimierung von Programmen, da es detaillierte Daten
darüber liefert, wo Zeit oder Rechenressourcen verbraucht werden. Die gesammelten Daten werden in einer Datei
gespeichert, die mit Werkzeugen wie `KCachegrind` analysiert werden kann.

`KCachegrind` ist ein Visualisierungstool, das die von `callgrind`
gesammelten Daten liest und grafisch darstellt. Es bietet eine benutzerfreundliche grafische Oberfläche, um die
Profildaten zu durchsuchen und zu analysieren. Mit `KCachegrind` können Entwickler die Aufrufhierarchie von Funktionen
sehen, Hotspots in ihrem Code identifizieren und sogar spezifische Informationen über die Ausführungskosten einzelner
Codezeilen erhalten.

Das Script `./profile.sh` erzeugt die Analysedatei und speichert sie in `profiling_data/$SUBFOLDER/$DATE_callgrind.out`.

# 2. Benchmarking

## 2.1 Optimize `const bool for DEBUG_MODE`

Zuerst wurde die `DEBUG_MODE`-Variable in der `globals.*`-Datei als `const bool` definiert. Dies ermöglicht dem
Compiler,
die Variable zur Kompilierzeit zu optimieren, da sie nicht mehr geändert werden kann.

Dies is in Commit [0bb55bd](https://github.com/mast1027/embedded-lab/commit/0bb55bd34046d5f741aa47e384e241656bb830c1) zu
sehen.

### Verbesserung

Keine nennenswerte Verbesserung.

`perf`-Vergleich:

```shell
# Event 'cycles:P'
#
# Baseline  Delta Abs  Shared Object      Symbol                                                                      
# ........  .........  .................  ............................................................................
#
               +2.52%  [kernel.kallsyms]  [k] mas_next_slot
    97.22%     +0.26%  embedded_lab       [.] Satellite::crossCorrelate(std::vector<int, std::allocator<int> > const&)
     0.00%     -0.00%  [kernel.kallsyms]  [k] native_write_msr
     2.78%             [kernel.kallsyms]  [k] get_page_from_freelist
```

Interner Vergleich:
`main: 139611 microseconds.` vs. `main: 139392 microseconds.`

## 2.2 Use only primitive data types

Alle nicht primitive Datentypen wurden durch primitive Datentypen ersetzt.

Dies is in Commit [08f257c](https://github.com/mast1027/embedded-lab/commit/08f257c1e818d19ffa321025ddd2494e088eccce) zu
sehen.

### Verbesserung

`perf`-Vergleich:
Kaum Verbesserungen da natürlich die Laufzeitverhältnisse gleich bleiben.

```shell
# Event 'cycles:P'
#
# Baseline  Delta Abs  Shared Object      Symbol                                                                      
# ........  .........  .................  ............................................................................
#
              +99.83%  [kernel.kallsyms]  [k] __kmem_cache_alloc_bulk
     0.00%     +0.17%  [kernel.kallsyms]  [k] native_write_msr
    97.22%             embedded_lab       [.] Satellite::crossCorrelate(std::vector<int, std::allocator<int> > const&)
     2.78%             [kernel.kallsyms]  [k] get_page_from_freelist
```

Interner Vergleich:
`main: 139611 microseconds.` vs. `main: 487 microseconds.` , d.h. eine Verbesserung um `139124 microseconds` und um
Faktor `286` zur initialen Laufzeit bzw. [2.1](#21-optimize-const-bool-for-debug_mode).

Das Einlesen der Quelldatei wurde kaum beeinflusst.

`parseFile` und `crossCorrelate` haben einen massiven Performance-Boost erhalten, vermutlich vom Wechsel
von `std::vector` auf `int[]`.

`gprof`-Vergleich:
Kaum zu berechnen, da die Laufzeit der Funktionen nach den Änderungen bei 0.0 liegt.

## 2.3 Pre-Calculation of `threshold` for `SatelliteNetwork::getSatellitesWithHighestCorrelation`

Die `threshold`-Variable wurde in der `SatelliteNetwork`-Klasse als `double` definiert und im Konstruktor berechnet.

Dies is in Commit [e8531b1](https://github.com/mast1027/embedded-lab/commit/e8531b1fa6f622b8016b34b53fc150f4efb95c82) zu
sehen.

### Verbesserung

`perf`-Vergleich:
Kaum Verbesserungen da natürlich die Laufzeitverhältnisse gleich bleiben.

`gprof`-Vergleich:
Kaum zu berechnen, da die Laufzeit der Funktionen nach den Änderungen bei 0.0 liegt.

Interner Vergleich:
`SatelliteNetwork::getSatellitesWithHighestCorrelation: 9 microseconds`
vs. `SatelliteNetwork::getSatellitesWithHighestCorrelation: 3 microseconds.` , d.h. eine Verbesserung
um `6 microseconds` und um Faktor `3` zur vorherigen Laufzeit bzw. [2.3](#22-use-only-primitive-data-types).

Im Gesamten jedoch kaum nennenswert.

## 2.4 Use double-sequence storage for `Satellite::crossCorrelate`

Das Array `receivedData` wurde verdoppelt um die Laufzeit der `crossCorrelate`-Funktion zu verbessern. Durch die
verdoppelung der Länge des Arrays wird das Berechnen des Shift-Indexes via Modulo-Operationen überflüssig.

Dies is in Commit [7e75d85](https://github.com/mast1027/embedded-lab/commit/7e75d85f3fb20fe539fc4917ce2154d96e8a98b1) zu
sehen.

`perf`-Vergleich:
Kaum Verbesserungen da natürlich die Laufzeitverhältnisse gleich bleiben.

`gprof`-Vergleich:
Kaum zu berechnen, da die Laufzeit der Funktionen nach den Änderungen bei 0.0 liegt.

Interner Vergleich:
`Satellite::crossCorrelate[X]: 9 microseconds.` vs. `Satellite::crossCorrelate[X]: 3 microseconds.` , d.h. eine
Verbesserung um `6 microseconds` und um Faktor `3` zur vorherigen Laufzeit
bzw. [2.4](#23-pre-calculation-of-threshold-for-satellitenetworkgetsatelliteswithhighestcorrelation).

Da dies natürlich für alle 24 Satelliten geschieht verbessert sich die Laufzeit der `crossCorrelate: 242 microseconds.`
vs. `crossCorrelate: 78 microseconds.`. Dies entspricht einer Verbesserung um `164 microseconds` und um Faktor `3.1`.

# 3. Benchmarking mit [perfbench.com](https://perfbench.com/)