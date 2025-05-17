/*
    Grossi Mara 
*/

#include<iostream>
#include <stdlib.h>
#include <random>
#include <chrono>
#include <vector>
#include<algorithm>
#include "SortingFunctions.h"
using namespace std;
using namespace std::chrono;

#define B_n exp(((log(100000) - log(100)) / 99))
#define B_m exp(((log(1000000) - log(10)) / 99))
#define MRE 0.001   // errore minimo relativo

struct statistics
{
    double time;
    double sd;  // standard deviaton
};

double getResolution();
double getDuration(steady_clock::time_point start_time, steady_clock::time_point end_time);
statistics measure(size_t size, int parameter_range, void (*func)(int*, size_t), double min_time);
int* generateArray(size_t n, int m);
int generateParameters(int A, float B, int i);


// ____________________________________________________________________ Inizializzazione array ____________________________________________________________________

int* generateArray(size_t n, int m)
{
    /* 
        Funzione per la generazione di un array con valori pseudo-casuali mediante l'uso di un generatore con un valore di inizializzazione non deterministico
    */

    random_device rd;
    mt19937 gen(rd());  
    uniform_int_distribution<int> range(1, m);

    int* toOrderArray = (int*) malloc(sizeof(int) * n);
    
    for(int i = 0; i < n; i++)
    {
        toOrderArray[i] = range(gen);
    }

    return toOrderArray;
}


int generateParameters(int A, float B, int i)
{
    /* 
        Funzione che genera i parametri (quelli non fissati) necessari alla creazione dell'array 
    */

    return floor(A * pow(B, i));
}

// _____________________________________________________________________ Misurazione dei tempi ____________________________________________________________________


double getResolution() 
{
    /* 
        Funzione per la stima della risoluzione del clock di sistema
    */

    steady_clock::time_point end_time;
    steady_clock::time_point start_time = steady_clock::now();

    do 
    {
        end_time = steady_clock::now();
    } while (start_time == end_time);

    return getDuration(start_time, end_time);
}


double getDuration(steady_clock::time_point start_time, steady_clock::time_point end_time)
{
    /* 
        Funzione per ottenere la durata di un blocco di codice in base al tempo di inizio e di fine
    */

    typedef duration<double, seconds::period> secs;

    return duration_cast<secs>(end_time - start_time).count();
}


statistics measure(size_t size, int parameter_range, void (*func)(int*, size_t), double min_time)
{
    /*
        Funzione per il calcolo del tempo medio degli algoritmi di sorting.
        Vengono effettuate 10 misurazioni diverse e ne verrà calcolata la media
    */

    int count = 0;
    double mean = 0;
    double sd_sum = 0;
    double runtime = 0;
    double single_meas = 0;
    int* toOrderArray;
    vector<double> times;

    double init_time;

    steady_clock::time_point end_time;
    steady_clock::time_point end_time_init;
    steady_clock::time_point start_time; 

    for(int i = 0; i < 10; i++)
    {
        count = 0;
        start_time = steady_clock::now();
        
        while (true)
        {
            toOrderArray = generateArray(size, parameter_range);

            end_time_init = steady_clock::now();    // fermo il clock per misurare il tempo che ci mette a inizializzare l'array

            func(toOrderArray, size);

            end_time = steady_clock::now();     // fermo il clock per misurare il tempo che ci mette a ordinare l'array

            count++;

            runtime = getDuration(start_time, end_time);
            init_time = getDuration(start_time, end_time_init);

            free(toOrderArray);

            if (runtime >= min_time)
            {
                break;
            }
        }

        single_meas = (runtime - init_time) / count;

        times.push_back(single_meas);
        mean += single_meas;
    }

    mean = mean / 10;

    for(int i = 0; i < times.size(); i++)
    {
        sd_sum += pow(times.at(i) - mean, 2);
    }

    sort(times.begin(), times.end(), less<double>{});

    return statistics{(times.at(4) + times.at(5)) / 2, (sqrt(sd_sum / 10))};
}
 



