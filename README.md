# 1. Methoden zur Laufzeitanalyse

## 1.1. Laufzeitmessung

Die Zeitmessung intern wird via `Timer::Timer` realisiert.

## 1.2. Profiling

### 1.2.1 Profiling mit `gprof`

### 1.2.2 Profiling mit `perf`

### 1.2.3 Profiling mit `valgrind`

### 1.2.4 Profiling mit `gperftools`

### 1.2.5 Profiling mit `callgrind`

# 2. Benchmarking

## 2.1 Optimize `const bool for DEBUG_MODE`

## 2.2 Use only primitive data types

## 2.3 Pre-Calculation of `threshold` for `SatelliteNetwork::getSatellitesWithHighestCorrelation`

## 2.4 Use double-sequence storage for `Satellite::crossCorrelate`

# 3. Benchmarking mit [perfbench.com](https://perfbench.com/)