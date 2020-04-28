#include <iostream>
#include <fstream>
#include <algorithm>
#include <time.h>
#include <chrono>
#include <bits/stdc++.h>

using namespace std;
using namespace std::chrono;

ifstream in("sortare.in");
ofstream out("sortare.out");

const int N = 10000005;
long long c[N];

void BubbleSort(long long v[],int l)
{
    int i,j;
    for(i = 1; i <= l ; i++)
        for(j = 1; j <= l ; j++)
            if(v[i] < v[j])
                swap(v[i],v[j]);
}
void CountSort(long long v[],int l)
{
    int j,maxim=0,i,k=0;
    for(i = 1; i <= l ; i++)
        if(v[i] > maxim)
            maxim = v[i];
    int *fr = new int[maxim + 1];
    for(i = 0; i <= maxim ; i++)
        fr[i]=0;
    for(i = 1; i <= l ; i++)
    {
        fr[v[i]]++;
    }
    for(i = 0; i <= maxim ; i++)
        for(j = 1; j <= fr[i] ; j++)
            v[++k]=i;
}

long long aux[N];

void interclasare(long long v[], int st, int dr)
{
    int i, j, k, m = (st + dr) / 2;
    i = k = st;
    j = m + 1;
    while (i <= m && j <= dr)
    {
        if (v[i] <= v[j])
        {
            aux[k++] = v[i++];
        }
        else
        {
            aux[k++] = v[j++];
        }
    }
    while (i <= m)
    {
        aux[k++] = v[i++];
    }
    while (j <= dr)
    {
        aux[k++] = v[j++];
    }
    for (k = st; k <= dr; k++)
    {
        v[k] = aux[k];
    }
}

void MergeSort(long long v[], int st, int dr)
{
    int i;
    if (st == dr)
    {
        return;
    }
    int m = (st + dr) / 2;
    MergeSort(v, st, m);
    MergeSort(v, m + 1, dr);
    interclasare(v, st, dr);
}

void QuickSort(long long v[], int st, int dr)
{
    if(st < dr)
    {
        int m = (st + dr) / 2;
        int aux = v[st];
        v[st] = v[m];
        v[m] = aux;
        int i = st, j = dr, d = 0;
        while(i < j)
        {
            if(v[i] > v[j])
            {
                aux = v[i];
                v[i] = v[j];
                v[j] = aux;
                d = 1 - d;
            }
            i += d;
            j -= 1 - d;
        }
        QuickSort(v, st, i - 1);
        QuickSort(v, i + 1, dr);
    }
}

void RadixSort(long long v[],int n,int p)
{
    vector <long long> Bucket[256];
    long long Shift = p*8;
    long long Mask = (1<<8) - 1;
    for(int i = 1; i <= n; ++i)
    {
        Bucket[(v[i] >> Shift) & Mask].push_back(v[i]);
    }
    int k = 0;
    for(int i = 0; i <= 255; ++i)
    {
        for(int j = 0; j < (int)Bucket[i].size(); ++j)
            v[++k] = Bucket[i][j];
    }
}

void StlSort(long long v[],int l)
{
    sort(v+1,v+l+1);
}

void generare(int n, long long v[], bool negativ, long long Max)
{
    srand(time(NULL));
    long long aux;

    for (int i = 1; i <= n ; i++)
    {
        if (negativ == 0)
        {
            aux = 1LL * rand() * rand() % (2*Max + 1) - Max;
        }
        else
        {
            aux = 1LL * rand() * rand() % (Max + 1);
        }
        v[i]=(aux);
    }
}

void afisare(long long v[],int n)
{
    for(int i = 1 ; i <= n; i++)
        out<<v[i]<<" ";
    out<<'\n';
}


void copiere(long long v[],long long c[],int n)
{
    for( int i = 1 ; i <= n; i++)
        v[i]=c[i];
}

int main()
{
    int n;
    out<<setprecision(15)<<fixed;
    int i,q;
    long long *v = new long long[N];
    //long long *c = new long long[10000005];
    long long val_max;
    int tip;//daca apar numere negative sau nu
    int nrteste;
    in>>nrteste;
    for(q = 1; q <= nrteste ; q++)
    {
        in >>n >> val_max >> tip;
        out<<"Avem de sortat " << n << " numere " << " cu valoarea maxima de " << val_max << '\n';
        generare(n,v,tip,val_max);
        copiere(c,v,n);

        auto start = high_resolution_clock::now();
        MergeSort(v,1,n);
        auto finish = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(finish - start);
        if(is_sorted(v + 1,v + n + 1 ) == true )
            out<<"MergeSort a sortat corect in "<<(double) duration.count()<<'\n';
        else
            out<<"MergeSort nu a sortat corect"<<'\n';
        copiere(v,c,n);

        start = high_resolution_clock::now();
        QuickSort(v,1,n);
        finish = high_resolution_clock::now();
        duration = duration_cast<microseconds>(finish - start);
        if(is_sorted(v + 1,v + n + 1 ) == true )
            out<<"QuickSort a sortat corect in "<<(double) duration.count()<<'\n';
        else
            out<<"QuickSort nu a sortat corect"<<'\n';
        copiere(v,c,n);

        if(val_max <= 10000005 && tip == 1)
        {
            start = high_resolution_clock::now();
            CountSort(v,n);
            finish = high_resolution_clock::now();
            duration = duration_cast<microseconds>(finish - start);
            if(is_sorted(v + 1,v + n + 1 ) == true )
                out<<"CountSort a sortat corect in "<<(double) duration.count()<<'\n';
            else
                out<<"CountSort nu a sortat corect"<<'\n';
            copiere(v,c,n);
        }
        else
            out<<"CountSort nu poate sorta deoarece val_max este prea mare sau apar numere negative"<<'\n';

        if(n <= 100000)
        {
            start = high_resolution_clock::now();
            BubbleSort(v,n);
            finish = high_resolution_clock::now();
            duration = duration_cast<microseconds>(finish - start);
            if(is_sorted(v + 1,v + n + 1 ) == true )
                out<<"BubbleSort a sortat corect in "<<(double) duration.count()<<'\n';
            else
                out<<"BubbleSort nu a sortat corect"<<'\n';
            copiere(v,c,n);
        }
        else
            out<<"BubbleSort nu poate sorta deoarece sunt prea multe numere"<<'\n';


        start = high_resolution_clock::now();
        StlSort(v,n);
        finish = high_resolution_clock::now();
        duration = duration_cast<microseconds>(finish - start);
        if(is_sorted(v + 1,v + n + 1 ) == true )
            out<<"StlSort a sortat corect in "<<(double) duration.count() <<'\n';
        else
            out<<"StlSort nu a sortat corect"<<'\n';
        copiere(v,c,n);

        if(tip == 1)
        {
            start = high_resolution_clock::now();
            for(int j = 0 ; j < 4 ; j++)
            {
                RadixSort(v,n,j);
            }
            finish = high_resolution_clock::now();
            duration = duration_cast<microseconds>(finish - start);
            if(is_sorted(v + 1, v + n + 1 ) == true )
                out<<"RadixSort a sortat corect in "<<(double) duration.count()<<'\n';
            else
                out<<"RadixSort nu a sortat corect"<<'\n';
        }
        else
            out<<"RadixSort nu poate sorta deoarece apar numere negative"<<'\n';
        out<<'\n';
    }
    return 0;
}
