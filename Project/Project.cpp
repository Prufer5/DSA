/*
    Autori:     Grossi Mara, 159901
                Toneatto Jessica, 153425
*/

#include <iostream>
#include "Utility.h"
#include "SortingFunctions.h"
#include <fstream>
using namespace std;

int main()
{
    statistics cs_times[100];
    statistics quick_times[100];
    statistics insertion_times[100];
    statistics quick_3_ways_times[100];

    double Tmin = getResolution() * ((1 / MRE) + 1);
    ofstream file;

    // apertura file 

    file.open("Results_n.csv");
    file << "n,CountingSort,sd_CS,QuickSort,sd_QS,InsertionSort,sd_IS,QuickSort3Ways,sd_QS3W" << endl;

    for(int i = 0; i < 100; i++)    // genero 100 campioni con m fissato e n che varia 
    {
        size_t n = generateParameters(100, B_n, i);

        cs_times[i] = measure(n, 100000, countingSort, Tmin);
        quick_times[i] = measure(n, 100000, quickSort, Tmin);
        insertion_times[i] = measure(n, 100000, insertionSort, Tmin);
        quick_3_ways_times[i] = measure(n, 100000, quickSort_3_ways, Tmin);

        file << n << "," 
             << cs_times[i].time << "," << cs_times[i].sd << "," 
             << quick_times[i].time << "," << quick_times[i].sd << ","
             << insertion_times[i].time << "," << insertion_times[i].sd << ","
             << quick_3_ways_times[i].time << "," << quick_3_ways_times[i].sd << endl;
    }

    file.close();

    file.open("Results_m.csv");
    file << "m,CountingSort,sd_CS,QuickSort,sd_QS,InsertionSort,sd_IS,QuickSort3Ways,sd_QS3W" << endl;

    for(int i = 0; i < 100; i++)    // genero 100 campioni con n fissato e m che varia
    {
        int m = generateParameters(10, B_m, i);

        cs_times[i] = measure(10000, m, countingSort, Tmin);
        quick_times[i] = measure(10000, m, quickSort, Tmin);
        insertion_times[i] = measure(10000, m, insertionSort, Tmin);
        quick_3_ways_times[i] = measure(10000, m, quickSort_3_ways, Tmin);

        file << m << "," 
             << cs_times[i].time << "," << cs_times[i].sd << "," 
             << quick_times[i].time << "," << quick_times[i].sd << ","
             << insertion_times[i].time << "," << insertion_times[i].sd << ","
             << quick_3_ways_times[i].time << "," << quick_3_ways_times[i].sd << endl;
    }

    file.close();

    return 0;
}