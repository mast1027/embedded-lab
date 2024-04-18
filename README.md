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

## 2.2 Use only primitive data types

## 2.3 Pre-Calculation of `threshold` for `SatelliteNetwork::getSatellitesWithHighestCorrelation`

## 2.4 Use double-sequence storage for `Satellite::crossCorrelate`

# 3. Benchmarking mit [perfbench.com](https://perfbench.com/)