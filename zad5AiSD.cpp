#include <iostream>

using namespace std;


void dynamicznyProblemPlecakowy(int *wagi,int *wartosci, int n,int poj,int *rozwiazanie);
void silowy(int *wagi, int *wartosci, int n, int poj);

void decToBin(int x, bool *tab);



int main()
{
    int n, poj;
    cout << "Podaj ilosc przedmiotow i pojemnosc plecaka:\n";
    cin  >> n >> poj;
    int *wagi = new int[n];
    int *wartosci = new int[n];
    cout << "Podaj wagi i wartosci przedmiowow:\n";
    for(int i=0; i<n; i++)
    {
        cin >> wagi[i] >> wartosci[i];
    }
    char o;
    cout << "Wybierz algorytm:\n1 - Programowania dynamicznego\t2 - zachlanny\t3 - silowy\n";
    cin >> o;

    if(o == '1')
    {
        int *rozwiazanie = nullptr;
        dynamicznyProblemPlecakowy(wagi, wartosci, n, poj, rozwiazanie);
    }
    else if(o == '2')
    {

    }
    else if(o == '3')
    {
        silowy(wagi, wartosci, n, poj);
    }
    else
    {
        cout << "Program nie obsluguje podanej operacji, wybierz jeszcze raz lub zakończ program.\n";
    }

}

void silowy(int *wagi, int *wartosci, int n, int poj)
{

    int sumwag, sumwar, res = 0, reswag = 0, reswar = 0;
    bool tab[n] = {0};

    for(int i=0; i<(1<<n); i++)
    {
        sumwag = 0;
        sumwar = 0;
        decToBin(i, tab);
        for(int j=0; j<n; j++)
        {
            if(tab[j] == 1)
            {
                sumwag += wagi[j];
                sumwar += wartosci[j];
            }
        }
        if(sumwag < poj && sumwar > reswar)
        {
            res = i;
            reswag = sumwag;
            reswar = sumwar;
        }
    }

    cout << "Przedmioty w plecaku: ";
    int i = 0;
    while(res)
    {
        if(res % 2)
            cout << i+1 << ", ";
        res /= 2;
        i++;
    }
    cout << "\nSuma wag przedmiotow w plecaku: " << reswag << endl;
    cout << "Suma wartosci przedmiotow w plecaku: " << reswar << endl;
}

void dynamicznyProblemPlecakowy(int *wagi, int *wartosci, int n, int poj, int *rozwiazanie)
{
    rozwiazanie = new int[n];
    int **tab = new int* [n + 1];
    bool **pom = new bool* [n + 1];
    for(int i=0;i<n+1;i++)
    {
        tab[i] = new int[poj+1];
        pom[i] = new bool[poj+1];
    }

    for(int i=0;i<n+1;i++)
    {
        for(int j=0;j<poj+1;j++)
        {
            if(i == 0)
            {
                tab[i][j] = 0;
                pom[i][j] = 0;
            }
            else
            {
                if(wagi[i - 1] > j)
                {
                    tab[i][j] = tab[i - 1][j];
                    pom[i][j] = 0;
                }
                else
                {
                    if(tab[i - 1][j - wagi[i - 1]] + wartosci[i - 1] > tab[i - 1][j])
                    {
                        tab[i][j] = tab[i - 1][j - wagi[i - 1]] + wartosci[i - 1];
                        pom[i][j] = 1;
                    }
                    else
                    {
                        tab[i][j] = tab[i - 1][j];
                        pom[i][j] = 0;
                    }
                }
            }


        }
    }

    /*
    for(int i=0;i<n+1;i++)
    {
        for(int j=0;j<poj+1;j++)
        {
            cout<<tab[i][j]<<" ";
        }
        cout<<"\n";
    }
    */
    int i = n,j = poj;
    while(i != 0)
    {
        if(tab[i][j] != tab[i - 1][j])
        {
            rozwiazanie[i - 1] = 1;
            j -= wagi[i - 1];
            i--;
        }
        else
        {
            rozwiazanie[i - 1] = 0;
            i--;
        }
    }
    int sum = 0;
    cout<<"Indeksy zapakowanych elementow (liczone od 1): ";
    for(int i=0;i<n;i++)
    {
        if(rozwiazanie[i])
        {
            sum+=rozwiazanie[i]*wagi[i];
            cout<<i+1<<" ";
        }
    }
    cout<<"\nSuma wag zapakowanych przedmiotow wynosi: "<<sum;
    cout<<"\nSuma wartosci zapakowanych przedmiotow wynosi: "<<tab[n][poj];
}

void decToBin(int x, bool *tab)
{
    int i = 0;

    while(x)
    {
        tab[i++] = x %2;
        x /= 2;
    }
}

