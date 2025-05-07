Okay, let's modify the implementation for Extra Point 2 (in-memory caching) to avoid using `std::vector` and rely entirely on manual dynamic array management.

**1. Define the Storage Structure and Global Variables:**

```cpp
#include <iostream> // Keep necessary includes
#include <cmath>
#include <iomanip>
#include <cstring>
// DO NOT include <vector>

struct CalibrationResult {
    // Context (The Key)
    double coeff_a;
    double coeff_b;
    double coeff_c;
    int size_range_key;   // An integer representing the size category
    int breaks_range_key; // An integer representing the breaks category

    // Results
    int determined_limP;
    int determined_limQ;

    // Constructor for convenience (optional but helpful)
    CalibrationResult() : coeff_a(0), coeff_b(0), coeff_c(0),
                         size_range_key(-1), breaks_range_key(-1),
                         determined_limP(-1), determined_limQ(-1) {} // Default constructor

    CalibrationResult(double a, double b, double c, int sk, int bk, int lp, int lq)
        : coeff_a(a), coeff_b(b), coeff_c(c), size_range_key(sk), breaks_range_key(bk),
          determined_limP(lp), determined_limQ(lq) {}
};

// --- Global Variables for Manual Memory Management ---
CalibrationResult* g_calibrationMemory = nullptr; // Pointer to the dynamic array
int g_memoryCapacity = 0;                   // Allocated capacity
int g_memoryCount = 0;                      // Number of items currently stored
// --- End Global Variables ---
```

**2. Keep Key Generation Functions:** (These don't change)

```cpp
// Example function to map size to a range key
int getSizeRangeKey(int tam) {
    if (tam <= 100) return 0;
    if (tam <= 1000) return 1;
    if (tam <= 10000) return 2;
    return 3; // 10001+
}

// Example function to map breaks (as percentage) to a range key
int getBreaksRangeKey(int breaks, int tam) {
    if (tam <= 0) return 0; // Avoid division by zero
    double break_percentage = static_cast<double>(breaks) / tam * 100.0;
    if (break_percentage <= 5.0) return 0;
    if (break_percentage <= 20.0) return 1;
    if (break_percentage <= 50.0) return 2;
    return 3; // 51%+
}
```

**3. Implement Manual Memory Lookup Function:**

```cpp
// Searches the manual memory array for a matching context.
// Returns true if found, false otherwise. Fills foundLimP/Q if found.
bool findInMemoryManual(double a, double b, double c, int size_key, int breaks_key,
                        int& foundLimP, int& foundLimQ) {
    for (int i = 0; i < g_memoryCount; ++i) {
        const auto& entry = g_calibrationMemory[i];
        // Use a tolerance for comparing doubles
        if (std::fabs(entry.coeff_a - a) < 1e-9 &&
            std::fabs(entry.coeff_b - b) < 1e-9 &&
            std::fabs(entry.coeff_c - c) < 1e-9 &&
            entry.size_range_key == size_key &&
            entry.breaks_range_key == breaks_key)
        {
            foundLimP = entry.determined_limP;
            foundLimQ = entry.determined_limQ;
            return true; // Found a match
        }
    }
    return false; // No match found
}
```

**4. Implement Manual Add to Memory Function (with Resizing):**

```cpp
// Adds a new result to the manually managed dynamic array
void addToMemoryManual(double a, double b, double c, int size_key, int breaks_key,
                       int limP, int limQ) {

    // Check if resize needed
    if (g_memoryCount >= g_memoryCapacity) {
        int newCapacity = (g_memoryCapacity == 0) ? 10 : g_memoryCapacity * 2; // Start with 10, then double
        CalibrationResult* newMemory = new CalibrationResult[newCapacity];

        // Copy existing data if there is any
        if (g_calibrationMemory != nullptr) {
            for (int i = 0; i < g_memoryCount; ++i) {
                newMemory[i] = g_calibrationMemory[i]; // Copy constructor needed or direct assignment
            }
            delete[] g_calibrationMemory; // Delete old array
        }

        g_calibrationMemory = newMemory; // Point to the new array
        g_memoryCapacity = newCapacity;  // Update capacity
    }

    // Add new entry at the end
    g_calibrationMemory[g_memoryCount] = CalibrationResult(a, b, c, size_key, breaks_key, limP, limQ);
    g_memoryCount++; // Increment the count of items
}
```

**5. Modify `main` Function Logic:**

```cpp
// ... (Keep all previous includes - EXCEPT <vector> - and functions: Counters, swap, calculaCusto, sorts, numeroQuebras, ordenadorUniversal, calibration functions, etc.) ...

// ... (Define CalibrationResult struct, global memory variables, key functions, findInMemoryManual, addToMemoryManual) ...


int main() {
    double limiarCusto;
    double a, b, c;
    int tam;

    // Read parameters
    std::cin >> limiarCusto >> a >> b >> c >> tam;

    if (tam <= 0) {
        std::cerr << "Error: Invalid array size." << std::endl;
        return 1;
    }
    int* V = new int[tam];

    // Read array elements
    for (int i = 0; i < tam; ++i) {
        std::cin >> V[i];
    }

    // Keep an original copy for repeated calibrations
    int* original_V = new int[tam];
    std::memcpy(original_V, V, tam * sizeof(int));

    // --- Adaptive Logic ---
    int determined_minTamParticao = -1; // Initialize to indicate not set
    int determined_limiarQuebras = -1;

    // 1. Calculate context keys for the current run
    int current_breaks = numeroQuebras(original_V, tam);
    int size_key = getSizeRangeKey(tam);
    int breaks_key = getBreaksRangeKey(current_breaks, tam);

    // 2. Check memory using the manual array function
    bool found = findInMemoryManual(a, b, c, size_key, breaks_key,
                                    determined_minTamParticao, determined_limiarQuebras);

    if (found) {
        std::cout << "--- Using Cached Calibration Results ---" << std::endl;
        std::cout << "Cached minTamParticao: " << determined_minTamParticao << std::endl;
        std::cout << "Cached limiarQuebras: " << determined_limiarQuebras << std::endl;
        std::cout << "--------------------------------------" << std::endl;
        // WARNING: This still skips the calibration runs and their detailed output logs,
        // which might cause issues with VPL testing if it expects those logs.
    } else {
        std::cout << "--- Running Calibration ---" << std::endl;
        // 3. Calibrate if not found
        determined_minTamParticao = determinaLimiarParticao(original_V, tam, limiarCusto, a, b, c);
        determined_limiarQuebras = determinaLimiarQuebras(original_V, tam, limiarCusto, a, b, c);

        // 4. Store the new result in the manual memory array
        addToMemoryManual(a, b, c, size_key, breaks_key, determined_minTamParticao, determined_limiarQuebras);
        std::cout << "--- Stored New Calibration Result (In-Memory) ---" << std::endl;
    }

    // --- (Optional) Final Sort using determined thresholds ---
    // ... (code to potentially sort V using the thresholds) ...

    // --- Cleanup ---
    delete[] V;
    delete[] original_V;

    // *** Crucial: Clean up the manually managed memory ***
    delete[] g_calibrationMemory;
    g_calibrationMemory = nullptr; // Prevent dangling pointer issues
    g_memoryCount = 0;
    g_memoryCapacity = 0;
    // *** End Cleanup ***

    return 0;
}
```

**Key Changes:**

1.  Removed `#include <vector>`.
2.  Introduced global variables `g_calibrationMemory`, `g_memoryCapacity`, `g_memoryCount`.
3.  Created `findInMemoryManual` which iterates through `g_calibrationMemory` up to `g_memoryCount`.
4.  Created `addToMemoryManual` which handles checking capacity, reallocating using `new[]`, copying old data, `delete[]`ing the old array, and then adding the new element and incrementing the count.
5.  Added cleanup code at the end of `main` to `delete[] g_calibrationMemory`.

This version achieves the in-memory caching without relying on `std::vector`, but remember the **important warning** about potentially failing VPL tests if they strictly require the full calibration output logs on every run.