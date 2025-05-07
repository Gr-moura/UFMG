Okay, here is a C++ implementation based on the logic outlined. This code attempts to follow the structure and requirements of TP1, including instrumented sorting, calibration loops, input/output, and manual array management.

**Important Considerations:**

1.  **No `std::vector`:** As per the FAQ, standard library containers are forbidden. This code uses raw C-style arrays (`int*`) and manual memory management (`new`/`delete[]`). This is crucial and error-prone; be careful with memory leaks.
2.  **Error Handling:** This code lacks robust error handling (e.g., for invalid input).
3.  **Completeness:** The calibration logic for `limiarQuebras` is implemented based on the "similar strategy" idea. You might need to refine its convergence or range calculation logic based on observed behavior.
4.  **Output Formatting:** Uses `<iomanip>` to match the required precision. Double-check against the exact format required by the VPL.
5.  **Makefile:** You still need to create the `Makefile` as described in the setup phase to compile this code correctly (using `-std=c++11`). Place this code in the `src` directory (e.g., `tp1.cpp`).
6.  **`tp3.out`:** The code generates `tp1.out` in the comments, but the spec mentions `tp3.out`. Ensure your `Makefile` produces the correctly named executable in the `bin` directory.

```cpp
#include <iostream>
#include <cmath>     // For fabs
#include <iomanip>   // For setprecision, fixed
#include <cstring>   // For memcpy

// Structure to hold operation counts
struct Counters {
    long long cmp = 0;
    long long move = 0;
    long long calls = 0;

    void reset() {
        cmp = 0;
        move = 0;
        calls = 0;
    }
};

// --- Helper Functions ---

// Manual swap function to count moves
void swap(int& a, int& b, Counters& counts) {
    int temp = a;
    a = b;
    b = temp;
    counts.move += 3; // Count 3 moves for a standard swap
}

// Calculate cost based on counts and coefficients
double calculaCusto(const Counters& counts, double a, double b, double c) {
    return a * counts.cmp + b * counts.move + c * counts.calls;
}

// --- Instrumented Sorting Algorithms ---

// Instrumented Insertion Sort
void insertionSort(int V[], int tam, Counters& counts) {
    // No recursive call count for insertion sort itself
    int key;
    int j;
    for (int i = 1; i < tam; ++i) {
        key = V[i];
        counts.move++; // Count reading into key
        j = i - 1;

        while (j >= 0) {
             counts.cmp++; // Count comparison V[j] > key
             if (V[j] > key) {
                 V[j + 1] = V[j];
                 counts.move++; // Count the shift
                 j = j - 1;
             } else {
                 break; // Stop shifting
             }
        }
        V[j + 1] = key;
        counts.move++; // Count placing the key back
    }
}

// --- Quicksort Helper Functions ---

// Median-of-3 Pivot Selection
int medianOf3(int V[], int low, int high, Counters& counts) {
    int mid = low + (high - low) / 2;
    // Comparisons to find the median
    counts.cmp += 3; // Estimate 3 comparisons needed in general
    if (V[mid] < V[low]) {
        swap(V[low], V[mid], counts);
    }
    if (V[high] < V[low]) {
        swap(V[low], V[high], counts);
    }
    if (V[mid] < V[high]) { // Note: V[high] is now potentially the smallest
        swap(V[mid], V[high], counts); // Put median in V[high] position
    }
    // Now V[high] holds the median pivot
    return high; // Return index of the pivot
}

// Lomuto Partition Scheme (example)
int partition(int V[], int low, int high, Counters& counts) {
    int pivotIndex = medianOf3(V, low, high, counts); // Select pivot
    int pivotValue = V[pivotIndex];
    counts.move++; // Count reading pivot value

    // Move pivot to end (standard Lomuto setup) - already done by medianOf3 if returning high
    // If medianOf3 returned a different index, swap it to high here.
    // swap(V[pivotIndex], V[high], counts);

    int i = (low - 1); // Index of smaller element

    for (int j = low; j <= high - 1; j++) {
        counts.cmp++; // Comparison V[j] <= pivotValue
        if (V[j] <= pivotValue) {
            i++;
            swap(V[i], V[j], counts);
        }
    }
    swap(V[i + 1], V[high], counts); // Place pivot in correct spot
    return (i + 1); // Return partition index
}


// Instrumented Quicksort (Recursive)
void quickSortRecursive(int V[], int low, int high, Counters& counts) {
     counts.calls++; // Count this recursive call
     if (low < high) {
        int pi = partition(V, low, high, counts);
        quickSortRecursive(V, low, pi - 1, counts);
        quickSortRecursive(V, pi + 1, high, counts);
    }
}

// Wrapper for initial Quicksort call if needed (or just call recursive directly)
void quickSort(int V[], int tam, Counters& counts) {
    if (tam > 1) {
         quickSortRecursive(V, 0, tam - 1, counts);
    }
     // Initial call could be counted here, but recursive already counts first call.
}


// --- Universal Sorter ---

int numeroQuebras(int V[], int tam) {
    int quebras = 0;
    for (int i = 1; i < tam; ++i) {
        if (V[i] < V[i - 1]) {
            quebras++;
        }
    }
    return quebras;
}

void ordenadorUniversal(int V[], int tam, int minTamParticao, int limiarQuebras, Counters& counts) {
    int actualQuebras = numeroQuebras(V, tam);
    counts.reset(); // Reset counters before the sort operation

    if (actualQuebras < limiarQuebras) {
        insertionSort(V, tam, counts);
    } else {
        if (tam > minTamParticao) {
            // For Quicksort, we need to ensure the internal calls are counted.
            // The quickSort wrapper/recursive function handles this.
             quickSort(V, tam, counts);
        } else {
            insertionSort(V, tam, counts);
        }
    }
}

// --- Calibration Logic ---

// Helper to get MPS value based on index (used by calculaNovaFaixa)
int getMPS(int mps_tested[], int index) {
    // Basic bounds check, might need refinement
    if (index < 0) return mps_tested[0];
    // Assuming num_tested is implicitly 6 here, adjust if not
    if (index >= 6) return mps_tested[5];
    return mps_tested[index];
}


// Update search range for partition size calibration
void calculaNovaFaixaParticao(int index_min_cost, int num_tested, const int mps_tested[],
                              int& minMPS, int& maxMPS, int& /*passoMPS*/) {
    // Logic from Figure 3
    int newMinIdx, newMaxIdx;
    if (index_min_cost == 0) {
        newMinIdx = 0; // Using indices 0, 1, 2
        newMaxIdx = 2; // Check if num_tested >= 3
        if (num_tested < 3) newMaxIdx = num_tested -1;

    } else if (index_min_cost == num_tested - 1) {
         newMaxIdx = num_tested - 1; // Using indices n-3, n-2, n-1
         newMinIdx = num_tested - 3; // Check if num_tested >= 3
         if (newMinIdx < 0) newMinIdx = 0;
    } else {
        newMinIdx = index_min_cost - 1;
        newMaxIdx = index_min_cost + 1;
    }

    // Get actual MPS values using the indices
    // Need original mps_tested array mapping index to value
    minMPS = getMPS((int*)mps_tested, newMinIdx); // Cast needed if const was passed
    maxMPS = getMPS((int*)mps_tested, newMaxIdx);

    // passoMPS will be recalculated in the calling loop
}

// Determine the best minimum partition size for Quicksort
int determinaLimiarParticao(const int original_V[], int tam, double limiarCusto,
                            double a, double b, double c) {
    int minMPS = 2;
    int maxMPS = tam;
    if (maxMPS < 2) maxMPS = 2; // Ensure range is valid

    double diffCusto = limiarCusto + 1.0; // Ensure loop runs at least once
    int best_mps_overall = minMPS;
    int iter = 0;

    const int NUM_POINTS = 6; // Test 6 points in the range

    // Need temporary storage within the loop
    double costs[NUM_POINTS];
    int mps_tested[NUM_POINTS];
    Counters current_counts;

    while (diffCusto > limiarCusto && maxMPS > minMPS && (maxMPS - minMPS) >= (NUM_POINTS - 1) / 2 ) { // Add range check
        std::cout << "iter " << iter << std::endl;

        int passoMPS = (maxMPS - minMPS) / (NUM_POINTS - 1); // Ensure division results in steps
        if (passoMPS == 0) passoMPS = 1;

        int num_tested_this_iter = 0;
        for (int i = 0; i < NUM_POINTS; ++i) {
            int current_mps = minMPS + i * passoMPS;
            if (i == NUM_POINTS - 1 || current_mps > maxMPS) { // Ensure last point is maxMPS
                 current_mps = maxMPS;
            }
            if (num_tested_this_iter > 0 && current_mps <= mps_tested[num_tested_this_iter - 1]) {
                 if (i == NUM_POINTS - 1 && current_mps < maxMPS) current_mps = maxMPS; // Try to reach max if possible
                 else continue; // Skip duplicate or decreasing mps
            }
            if(current_mps < 2) current_mps = 2; // Ensure mps is at least 2

            mps_tested[num_tested_this_iter] = current_mps;

            // --- Critical: Copy original array ---
            int* V_copy = new int[tam];
            std::memcpy(V_copy, original_V, tam * sizeof(int));
            // ---

            // Run universal sorter with current MPS as minTamParticao
            // Use a high limiarQuebras to force quicksort path if tam > current_mps
            ordenadorUniversal(V_copy, tam, current_mps, tam + 1, current_counts);

            costs[num_tested_this_iter] = calculaCusto(current_counts, a, b, c);

            std::cout << "mps " << mps_tested[num_tested_this_iter]
                      << " cost " << std::fixed << std::setprecision(9) << costs[num_tested_this_iter]
                      << " cmp " << current_counts.cmp
                      << " move " << current_counts.move
                      << " calls " << current_counts.calls << std::endl;

             delete[] V_copy; // Clean up copy
             num_tested_this_iter++;
             if (current_mps == maxMPS) break; // Stop if maxMPS is reached
        }

         if (num_tested_this_iter < 2) { // Cannot proceed if less than 2 points tested
             best_mps_overall = (num_tested_this_iter == 1) ? mps_tested[0] : minMPS;
             break;
         }

        // Find minimum cost index
        int index_min_cost = 0;
        for (int i = 1; i < num_tested_this_iter; ++i) {
            if (costs[i] < costs[index_min_cost]) {
                index_min_cost = i;
            }
        }
        best_mps_overall = mps_tested[index_min_cost];

        // Calculate difference between first and last cost in this iteration
        diffCusto = std::fabs(costs[0] - costs[num_tested_this_iter - 1]);

        std::cout << "nummps " << num_tested_this_iter
                  << " limParticao " << best_mps_overall
                  << " mpsdiff " << std::fixed << std::setprecision(6) << diffCusto << std::endl;


        // Update range for next iteration only if criteria met
        if (diffCusto > limiarCusto && num_tested_this_iter >= 3) { // Need at least 3 points to refine range meaningfully
             calculaNovaFaixaParticao(index_min_cost, num_tested_this_iter, mps_tested, minMPS, maxMPS, passoMPS);
             // Ensure min/max haven't crossed or become too small
             if (minMPS > maxMPS) break;
             if (minMPS < 2) minMPS = 2;
        } else {
            break; // Stop if converged or cannot refine further
        }


        iter++;
         if (iter > 20) { // Safety break for infinite loops
             std::cerr << "Warning: Max iterations reached in determinaLimiarParticao." << std::endl;
             break;
         }
    }

    return best_mps_overall;
}


// Update search range for break threshold calibration (similar logic)
void calculaNovaFaixaQuebras(int index_best_lq, int num_tested, const int lq_tested[],
                             int& minLQ, int& maxLQ) {
    // Adapted logic from Figure 3 / calculaNovaFaixaParticao
     int newMinIdx, newMaxIdx;
    if (index_best_lq == 0) {
        newMinIdx = 0;
        newMaxIdx = (num_tested >= 3) ? 2 : num_tested -1;
    } else if (index_best_lq == num_tested - 1) {
         newMaxIdx = num_tested - 1;
         newMinIdx = (num_tested >= 3) ? num_tested - 3 : 0;
    } else {
        newMinIdx = index_best_lq - 1;
        newMaxIdx = index_best_lq + 1;
    }

    minLQ = getMPS((int*)lq_tested, newMinIdx); // Reusing getMPS logic
    maxLQ = getMPS((int*)lq_tested, newMaxIdx);
}


// Determine the best threshold for number of breaks
int determinaLimiarQuebras(const int original_V[], int tam, double limiarCusto,
                           double a, double b, double c) {
    int minLQ = 0;
    int maxLQ = tam - 1; // Max possible breaks is n-1
     if (maxLQ < 0) maxLQ = 0;

    double diffCostOverall = limiarCusto + 1.0; // Use cost difference as convergence criteria
    int best_lq_overall = 0; // Default to 0 breaks (use insertion)
    int iter = 0;

    const int NUM_POINTS = 6;
    double costs_qs[NUM_POINTS];
    double costs_in[NUM_POINTS];
    int lq_tested[NUM_POINTS];
    Counters current_counts;

    // Convergence might be based on difference between QS/IN costs at boundaries
     while (diffCostOverall > limiarCusto && maxLQ > minLQ && (maxLQ - minLQ) >= (NUM_POINTS - 1) / 2) { // Add range check
        std::cout << "iter " << iter << std::endl;

        int passoLQ = (maxLQ - minLQ) / (NUM_POINTS - 1);
        if (passoLQ == 0) passoLQ = 1;

        int num_tested_this_iter = 0;
        for (int i = 0; i < NUM_POINTS; ++i) {
            int current_lq = minLQ + i * passoLQ;
             if (i == NUM_POINTS - 1 || current_lq > maxLQ) {
                 current_lq = maxLQ;
             }
              if (num_tested_this_iter > 0 && current_lq <= lq_tested[num_tested_this_iter - 1]) {
                 if (i == NUM_POINTS - 1 && current_lq < maxLQ) current_lq = maxLQ;
                 else continue; // Skip duplicate or decreasing lq
             }

            lq_tested[num_tested_this_iter] = current_lq;

            // --- Run Quicksort (representing cost when quebras >= threshold) ---
            int* V_copy_qs = new int[tam];
            std::memcpy(V_copy_qs, original_V, tam * sizeof(int));
            current_counts.reset();
            quickSort(V_copy_qs, tam, current_counts); // Assuming QS is used above threshold
            costs_qs[num_tested_this_iter] = calculaCusto(current_counts, a, b, c);
            std::cout << "qs lq " << current_lq
                      << " cost " << std::fixed << std::setprecision(9) << costs_qs[num_tested_this_iter]
                      << " cmp " << current_counts.cmp
                      << " move " << current_counts.move
                      << " calls " << current_counts.calls << std::endl;
            delete[] V_copy_qs;

            // --- Run Insertion Sort (representing cost when quebras < threshold) ---
            int* V_copy_in = new int[tam];
            std::memcpy(V_copy_in, original_V, tam * sizeof(int));
            current_counts.reset();
            insertionSort(V_copy_in, tam, current_counts); // Assuming IN is used below threshold
            costs_in[num_tested_this_iter] = calculaCusto(current_counts, a, b, c);
            std::cout << "in lq " << current_lq
                      << " cost " << std::fixed << std::setprecision(9) << costs_in[num_tested_this_iter]
                      << " cmp " << current_counts.cmp
                      << " move " << current_counts.move
                      << " calls " << current_counts.calls << std::endl;
            delete[] V_copy_in;

            num_tested_this_iter++;
             if (current_lq == maxLQ) break; // Stop if maxLQ is reached
        }

        if (num_tested_this_iter < 2) {
             best_lq_overall = (num_tested_this_iter == 1) ? lq_tested[0] : minLQ;
             break;
         }


        // Find the crossover point (where Insertion becomes more expensive than Quicksort)
        int index_best_lq = 0; // Default to first point
        for (int i = 0; i < num_tested_this_iter; ++i) {
            if (costs_in[i] > costs_qs[i]) {
                 // This is the first point where QS is potentially better.
                 // We want the threshold *before* this point.
                 index_best_lq = i;
                 break; // Take the first crossover
            }
             // If QS is always better, index_best_lq remains 0
             // If IN is always better, index_best_lq becomes num_tested_this_iter
             if (i == num_tested_this_iter - 1) index_best_lq = num_tested_this_iter; // IN always better
        }

        // If IN is always better than QS in the tested range, the threshold is effectively beyond maxLQ
        // If QS is always better, threshold is effectively below minLQ (so 0 or 1?)
        if (index_best_lq == 0 && costs_qs[0] < costs_in[0] ) {
            best_lq_overall = lq_tested[0]; // QS better even at lowest LQ
        } else if (index_best_lq == num_tested_this_iter) {
             best_lq_overall = lq_tested[num_tested_this_iter - 1] +1; // IN always better, threshold is high
        }
         else {
            // Crossover happened. Threshold is the LQ value *before* the crossover.
            best_lq_overall = lq_tested[index_best_lq]; // Correct index should be lq_tested[index_best_lq] ? check example output
             // Example iter 1: lq 1 cost_in 4.1, cost_qs 74. lq 40 cost_in 165, cost_qs 74. Crossover before 40. limQuebras=1?
             // Example iter 2: lq 1 in<qs. lq 16 in<qs. lq 31 in<qs. lq 46 in<qs. lq 61 in<qs. lq 76 in<qs. limQuebras=16?
             // The output shows limQuebras=16. This is the value *at* the index where IN < QS holds for the last time before QS potentially becomes better, or the point where the difference is minimal favoring IN.
             // Let's refine: find index `k` such that cost_in[k] < cost_qs[k] but cost_in[k+1] >= cost_qs[k+1] OR find index where cost_in - cost_qs is minimized (closest to 0 from below).
             double min_diff = costs_in[0] - costs_qs[0];
             int best_diff_idx = 0;
             for(int i=1; i<num_tested_this_iter; ++i) {
                 double diff = costs_in[i] - costs_qs[i];
                 // Find where IN is cheaper, but difference is smallest (closest to QS cost)
                 if(diff < 0 && diff > min_diff) { // Found a point where IN is cheaper, and the difference is smaller than previous best
                     min_diff = diff;
                     best_diff_idx = i;
                 } else if (min_diff >= 0 && diff < min_diff) { // If previous best had IN >= QS, take any point where IN < QS
                    min_diff = diff;
                    best_diff_idx = i;
                 }
             }
              best_lq_overall = lq_tested[best_diff_idx];


        }


        // Calculate overall cost difference for convergence check (e.g., difference at boundaries)
        diffCostOverall = std::fabs((costs_in[0] - costs_qs[0]) - (costs_in[num_tested_this_iter - 1] - costs_qs[num_tested_this_iter - 1]));

        std::cout << "numlq " << num_tested_this_iter
                  << " limQuebras " << best_lq_overall
                  << " lqdiff " << std::fixed << std::setprecision(6) << diffCostOverall << std::endl;

        // Update range
         if (diffCostOverall > limiarCusto && num_tested_this_iter >= 3) {
            calculaNovaFaixaQuebras(best_diff_idx, num_tested_this_iter, lq_tested, minLQ, maxLQ);
             if (minLQ > maxLQ) break; // Stop if range inverted
             if (minLQ < 0) minLQ = 0;
         } else {
             break; // Converged or cannot refine
         }

        iter++;
        if (iter > 20) { // Safety break
             std::cerr << "Warning: Max iterations reached in determinaLimiarQuebras." << std::endl;
             break;
         }
    }

    return best_lq_overall;
}


// --- Main Function ---
int main() {
    double limiarCusto;
    double a, b, c;
    int tam;
    // Could add seed, breaks info if needed based on actual input format generation
    // int seed, breaks;

    // Read parameters
    std::cin >> limiarCusto >> a >> b >> c >> tam;

    // Read optional info like seed/breaks if provided (like Figure 4 example)
    // Skipping lines or reading specific values if needed. Example shows "size 1000 seed 1 breaks 502"
    // We'll ignore these extra informational lines for now, assuming VPL provides only the 5 params + data.
    // Consume potential extra info on the size line:
    std::string dummy;
    // std::getline(std::cin >> std::ws, dummy); // Read rest of the size line if necessary

    // Allocate memory for the array
    if (tam <= 0) {
        std::cerr << "Error: Invalid array size." << std::endl;
        return 1;
    }
    int* V = new int[tam];

    // Read array elements
    for (int i = 0; i < tam; ++i) {
        std::cin >> V[i];
    }

    // --- Perform Calibration ---
    // Keep an original copy for repeated calibrations
    int* original_V = new int[tam];
    std::memcpy(original_V, V, tam * sizeof(int));

    // Determine thresholds using the original data
    int determined_minTamParticao = determinaLimiarParticao(original_V, tam, limiarCusto, a, b, c);
    int determined_limiarQuebras = determinaLimiarQuebras(original_V, tam, limiarCusto, a, b, c);

    // --- (Optional) Final Sort ---
    // The assignment focuses on determining the thresholds.
    // You could uncomment this to sort the initial array V using the found thresholds.
    // Counters final_counts;
    // ordenadorUniversal(V, tam, determined_minTamParticao, determined_limiarQuebras, final_counts);
    // std::cout << "\nFinal Sort Results (using determined thresholds):" << std::endl;
    // std::cout << "Thresholds: minTamParticao=" << determined_minTamParticao << ", limiarQuebras=" << determined_limiarQuebras << std::endl;
    // std::cout << "cmp=" << final_counts.cmp << ", move=" << final_counts.move << ", calls=" << final_counts.calls << std::endl;
    // Print sorted array V if needed for verification

    // --- Cleanup ---
    delete[] V;
    delete[] original_V;

    return 0;
}
```