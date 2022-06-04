#include <iostream>
#include <fstream>

using namespace std;


void dynamicznyProblemPlecakowy(int *wagi,int *wartosci, int n,int poj,int *rozwiazanie);
void silowy(int *wagi, int *wartosci, int n, int poj);
void zachlanny(int *wagi, int *wartosci, int n, int poj);

void decToBin(int x, bool *tab);
int cinInt();



int main()
{
    char c;
    int n, poj, *wagi, *wartosci;
    cout << "1 - Wczytaj dane z pliku.\t2 - Wczytaj dane z klawiatury.\n";
    fstream file;

    do
    {
        fflush(stdin);
        cin >> c;
        if(c == '1')
        {
            file.open("dane.txt", ios::in);

            file >> n;
            file >> poj;

            wagi = new int[n];//
            wartosci = new int[n];//

            for(int i=0; i<n; i++)
            {
                file >> wagi[i];
                file >> wartosci[i];
            }
        }
        else if(c == '2')
        {
            cout << "Podaj ilosc przedmiotow i pojemnosc plecaka:\n";
            //cin  >> n >> poj;
            n = cinInt();
            poj = cinInt();

            wagi = new int[n];//
            wartosci = new int[n];//
            cout << "Podaj wagi i wartosci przedmiowow:\n";
            for(int i=0; i<n; i++)
            {
                //cin >> wagi[i] >> wartosci[i];
                wagi[i] = cinInt();
                wartosci[i] = cinInt();
            }
        }
        else
        {
            cout << "Program nie obsluguje podanej operacji\n";
        }
    }while(c != '2' && c != '1');

    /*char o;
    cout << "Wybierz algorytm:\n1 - Programowania dynamicznego\t2 - zachlanny\t3 - silowy\n";
    cin >> o;

    if(o == '1')
    {
        int *rozwiazanie = nullptr;
        dynamicznyProblemPlecakowy(wagi, wartosci, n, poj, rozwiazanie);
    }
    else if(o == '2')
    {
        zachlanny(wagi, wartosci, n, poj);
    }
    else if(o == '3')
    {
        silowy(wagi, wartosci, n, poj);
    }
    else
    {
        cout << "Program nie obsluguje podanej operacji, wybierz jeszcze raz lub zakoñcz program.\n";
    }*/
    cout << "Przedmioty indeksowane od 1.\n\nAlgorytm programowania dynamicznego:\n";
    int *rozwiazanie = nullptr;
    dynamicznyProblemPlecakowy(wagi, wartosci, n, poj, rozwiazanie);

    cout << "\n\nAlgorytm silowy:\n";
    silowy(wagi, wartosci, n, poj);

    cout << "\nAlgorytm zachlanny:\n";
    zachlanny(wagi, wartosci, n, poj);

    return 0;
}

void zachlanny(int *wagi, int *wartosci, int n, int poj)
{
    double oplacalnosc[n];
    int indeksy[n];
    for(int i=0; i<n; i++)
    {
        indeksy[i] = i;
        oplacalnosc[i] = (double)wartosci[i]/wagi[i];
    }

    /// insertion sort
    int j;
    for(int i=1; i<n; i++)
    {
        j = i;

        while(j > 0 && oplacalnosc[j] >= oplacalnosc[j-1])
        {
            double tm = oplacalnosc[j];
            oplacalnosc[j] = oplacalnosc[j-1];
            oplacalnosc[j-1] = tm;

            int tmp = indeksy[j];
            indeksy[j] = indeksy[j-1];
            indeksy[j-1] = tmp;

            tmp = wagi[j];
            wagi[j] = wagi[j-1];
            wagi[j-1] = tmp;

            tmp = wartosci[j];
            wartosci[j] = wartosci[j-1];
            wartosci[j-1] = tmp;

            j--;
        }
    }
    /// koniec
    int sumwag = 0, sumwar = 0;

    cout << "Przedmioty w plecaku: ";
    for(int i=0; i<n; i++)
    {
        if(sumwag+wagi[i] <= poj)
        {
            sumwag += wagi[i];
            sumwar += wartosci[i];
            cout << indeksy[i]+1 << ", ";
        }
    }
    cout << "\nSuma wag przedmiotow w plecaku: " << sumwag << endl;
    cout << "Suma wartosci przedmiotow w plecaku: " << sumwar << endl;
    /*j = 0;
    while(sumwag <= poj)
    {
        sumwag += wagi[j];
        j++;
    }
    cout << "Przedmioty w plecaku: ";
    sumwag = 0;
    for(int i=0; i<j-1; i++)
    {
        cout << indeksy[i]+1 << ", ";
        sumwag += wagi[i];
        sumwar += wartosci[i];
    }
    cout << "\nSuma wag przedmiotow w plecaku: " << sumwag << endl;
    cout << "Suma wartosci przedmiotow w plecaku: " << sumwar << endl;*/
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
        if(sumwag <= poj && sumwar > reswar)
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
    cout<<"Przedmioty w plecaku: ";
    for(int i=0; i<n; i++)
    {
        if(rozwiazanie[i])
        {
            sum += rozwiazanie[i]*wagi[i];
            cout << i+1 << ", ";
        }
    }
    cout << "\nSuma wag przedmiotow w plecaku: " << sum;
    cout << "\nSuma wartosci przedmiotow w plecaku: " << tab[n][poj];
}

void decToBin(int x, bool *tab)
{
    int i = 0;

    while(x)
    {
        tab[i++] = x%2;
        x /= 2;
    }
}

int cinInt()
{
    int x;
    while(!(cin >> x) || x < 0)
    {

        cin.clear();
        cin.sync();
        cout << "Podaj liczbe dodatnia: \n";
    }
    return x;
}
