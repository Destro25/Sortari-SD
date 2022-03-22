#include <iostream>
#include <random>
#include <chrono>
#include <vector>
#include <algorithm>
using namespace std;
using namespace chrono;
long long getMax(vector<long long> v, int n)
{
    long long mx = v[0];
    for (int i = 1; i < n; i++)
        if (v[i] > mx)
            mx = v[i];
    return mx;
}
void countSort(vector<long long> &v, int n, long long exp, int baza)
{
    int i;
    vector <int> count(baza);
    vector <long long> temp(n);

    for (i = 0; i < n; i++)
        count[(v[i] / exp) % baza]++;

    int poz = 0, apar;
    for(i= 0; i < baza; i++)
    {
        apar = count[i];
        count[i] = poz;
        poz = poz + apar;
    }//retin pozitia de inceput a fiecarei cifre

    for (i = 0; i < n; i++)
    {
        temp[count[(v[i] / exp) % baza]] = v[i];
        count[(v[i] / exp) % baza]++;
    }
    for( i = 0; i < n; i++)
    {
        v[i] = temp[i];
    }
}
void radixsort(vector<long long> &v, int n, int baza)
{
    long long m = getMax(v, n);
    for (long long exp = 1; m / exp > 0; exp *= baza)
        countSort(v, n, exp, baza);
}
void Merge(vector<long long>& v, int st, int mij, int dr)
{
    vector<long long> temp;

    int i, j;
    i = st;
    j = mij + 1;

    while (i <= mij && j <= dr)
    {
        if (v[i] <= v[j])
        {
            temp.push_back(v[i]);
            i++;
        }
        else
        {
            temp.push_back(v[j]);
            j++;
        }
    }
    while (i <= mij)
    {
        temp.push_back(v[i]);
        i++;
    }
    while (j <= dr)
    {
        temp.push_back(v[j]);
        j++;
    }
    for (i = st; i <= dr; i++)
        v[i] = temp[i - st];
}

void Merge_Sort(vector<long long>& v, int st, int dr)
{
    if (st < dr)
    {
        int mij = st + (dr - st) / 2;
        Merge_Sort(v, st, mij);
        Merge_Sort(v, mij + 1, dr);

        Merge(v, st, mij, dr);
    }
}
void shellSort(vector <long long> &v, int n)
{
    for (int gap = n/2; gap >= 1; gap /= 2)
    {
        for (int i = gap; i < n; i++)
        {
            long long temp = v[i];

            int j;
            for (j = i; j >= gap && v[j - gap] > temp; j -= gap)
                v[j] = v[j - gap];

            v[j] = temp;
        }
    }
}
void pivot_mediu(vector<long long> &v, int st, int dr)
{
    int index, centru;
    centru = st + (dr - st) / 2;
    long long a, b, c, aux;
    a = v[st];
    b = v[centru];
    c = v[dr];
    if ((a <= b) && (b <= c))
        index = centru;
    if ((a <= c) && (c <= b))
        index = dr;
    if ((b <= a) && (a <= c))
        index = st;
    if ((b <= c) && (c <= a))
        index = dr;
    if ((c <= a) && (a <= b))
        index = st;
    if ((c <= b) && (b <= a))
        index = centru;

    aux = v[index];
    v[index] = v[st];
    v[st] = aux;
}
void TWP(vector<long long> &v, int st, int dr, int &begin, int &end)
{
    pivot_mediu(v,st,dr);
    long long pivot = v[st];
    begin = st;
    end = dr;
    long long aux;
    for(int i = begin + 1; i <= end; i++)
    {
        if(v[i] < pivot)
        {
            if(i != begin)
            {
                aux = v[i];
                v[i] = v[begin];
                v[begin] = aux;
            }
            begin++;
        }
        if(v[i] > pivot)
        {
            if (i != end)
            {
                aux = v[i];
                v[i] = v[end];
                v[end] = aux;
            }
            end--;
            i--;
        }
    }

}
void quicksort(vector<long long> &v, int st, int dr)
{
    if(st>=dr)
    {
        return;
    }
    int begin, end;
    TWP(v, st, dr, begin, end);
    quicksort(v, st, --begin);
    quicksort(v, ++end, dr);
}
void heapify(vector <long long> &v, int n, int index)
{
    int maxim = index;
    int st = 2 * index + 1;
    int dr = st + 1;
    if (st < n && v[st] > v[maxim])
        maxim = st;
    if (dr < n && v[dr] > v[maxim])
        maxim = dr;
    if (maxim != index)
    {
        long long aux;
        aux = v[index];
        v[index] = v[maxim];
        v[maxim] = aux;

        heapify(v, n,maxim);
    }
}
void heapsort(vector <long long> &v, int n)
{
    for (int i = (n - 1) / 2 ; i >= 0; i--)
        heapify(v, n, i);
    for (int i = n - 1; i > 0; i--)
    {
        long long aux;
        aux = v[i];
        v[i] = v[0];
        v[0] = aux;

        heapify(v, i, 0);
    }

}
bool sortat_corect(vector <long long> a, vector <long long> b, int n)
{
    for (int i = 0; i < n; i++)
    {
        if(a[i] != b[i])
            return false;
    }
    return true;
}
int main()
{
    int N[] = {1000, 1000000, 100000000};
    long long M[] = {1000000, 1000000000000, 1000000000000000000};
    bool sortat;
    for (int i = 0; i <= 2; i++)
    {
        for (long long j = 0; j <= 2; j++)
        {
            random_device rng;
            mt19937 mersenne_engine {rng()};
            uniform_int_distribution<long long> interval {0, M[j]};

            auto gen = [&interval, &mersenne_engine](){
                return interval(mersenne_engine);
            };

            vector<long long> v(N[i]);
            generate(begin(v), end(v), gen);

            vector <long long> cpp = v;
            vector <long long> mysort = v;

            auto start = high_resolution_clock::now();
            //algoritm de sortare
            sort(cpp.begin(),cpp.end());
            //masurare timp
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);

            cout << "CPP sort:        N = "<<N[i]<<" M = "<<M[j]<<" Timp: "<< duration.count() << " microseconds" << "\n";

            start = high_resolution_clock::now();
            //algoritm de sortare
            radixsort(mysort,N[i],10);
            //masurare timp
            stop = high_resolution_clock::now();
            duration = duration_cast<microseconds>(stop - start);

            cout << "Radix Sort B10:  N = "<<N[i]<<" M = "<<M[j]<<" Timp: "<< duration.count() << " microseconds ";

            sortat = sortat_corect(cpp,mysort,N[i]);
            if (sortat)
            {
                cout<<"Sortat bine\n";
            }
            else cout<<"Nu e sortat bine\n";

            mysort = v;
            start = high_resolution_clock::now();
            //algoritm de sortare
            radixsort(mysort,N[i],100);
            //masurare timp
            stop = high_resolution_clock::now();
            duration = duration_cast<microseconds>(stop - start);

            cout << "Radix Sort B100: N = "<<N[i]<<" M = "<<M[j]<<" Timp: "<< duration.count() << " microseconds ";

            sortat = sortat_corect(cpp,mysort,N[i]);
            if (sortat)
            {
                cout<<"Sortat bine\n";
            }
            else cout<<"Nu e sortat bine\n";

            mysort = v;
            start = high_resolution_clock::now();
            //algoritm de sortare
            Merge_Sort(mysort,0,N[i]-1);
            //masurare timp
            stop = high_resolution_clock::now();
            duration = duration_cast<microseconds>(stop - start);

            cout << "Merge Sort:      N = "<<N[i]<<" M = "<<M[j]<<" Timp: "<< duration.count() << " microseconds ";

            sortat = sortat_corect(cpp,mysort,N[i]);
            if (sortat)
            {
                cout<<"Sortat bine\n";
            }
            else cout<<"Nu e sortat bine\n";

            mysort = v;
            start = high_resolution_clock::now();
            //algoritm de sortare
            shellSort(mysort,N[i]);
            //masurare timp
            stop = high_resolution_clock::now();
            duration = duration_cast<microseconds>(stop - start);

            cout << "Shell Sort:      N = "<<N[i]<<" M = "<<M[j]<<" Timp: "<< duration.count() << " microseconds ";

            sortat = sortat_corect(cpp,mysort,N[i]);
            if (sortat)
            {
                cout<<"Sortat bine\n";
            }
            else cout<<"Nu e sortat bine\n";

            mysort = v;
            start = high_resolution_clock::now();
            //algoritm de sortare
            quicksort(mysort,0,N[i]-1);
            //masurare timp
            stop = high_resolution_clock::now();
            duration = duration_cast<microseconds>(stop - start);

            cout << "Quick Sort:      N = "<<N[i]<<" M = "<<M[j]<<" Timp: "<< duration.count() << " microseconds ";

            sortat = sortat_corect(cpp,mysort,N[i]);
            if (sortat)
            {
                cout<<"Sortat bine\n";
            }
            else cout<<"Nu e sortat bine\n";

            mysort = v;
            start = high_resolution_clock::now();
            //algoritm de sortare
            heapsort(mysort,N[i]);
            //masurare timp
            stop = high_resolution_clock::now();
            duration = duration_cast<microseconds>(stop - start);

            cout << "Heap Sort:       N = "<<N[i]<<" M = "<<M[j]<<" Timp: "<< duration.count() << " microseconds ";

            sortat = sortat_corect(cpp,mysort,N[i]);
            if (sortat)
            {
                cout<<"Sortat bine\n";
            }
            else cout<<"Nu e sortat bine\n";

            cout<<"\n";
        }
    }
    return 0;
}
