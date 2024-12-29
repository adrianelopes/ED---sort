#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <fstream>
#include <string>
#include <chrono>
#include <algorithm>
// #define NDEBUG
using namespace std;
using namespace chrono;

vector<long> insertionsort(vector<long> &A, int n)
{

    int pivo = 0;
    int j = 0;

    for (int i = 1; i <= n - 1; i++)
    {

        pivo = A[i];
        j = i - 1;

        while (j >= 0 && A[j] > pivo)
        {
            A[j + 1] = A[j];
            j = j - 1;
        }
        A[j + 1] = pivo;
    }

    return A;
}

vector<long> selectionsort(vector<long> &A, int n)
{

    int min = 0;
    int aux = 0;
    for (int i = 0; i <= n - 2; i++)

    {
        min = i;
        for (int j = i + 1; j <= n - 1; j++)
        {
            if (A[j] < A[min])
            {
                min = j;
            }
        }
        if (min != i)
        {
            aux = A[i];
            A[i] = A[min];
            A[min] = aux;
        }
    }

    return A;
}

// Função que lê o arquivo e passa os número para um vetor

void readfile(const string &filename, vector<long> &A)
{
    std::ifstream file(filename);

    if (file.is_open())
    {
        std::string number;
        while (file >> number)
        {
            A.push_back(stoll(number));
        }
    }
    else
    {
        std::cerr << "Erro ao abrir o arquivo: " << filename << std::endl;
        return;
    }

    file.close();
}

// A função copia o vetor original e o ordena, depois compara com o insertion sort e o selection sort, essa função é apenas para testar a ordem da solução
bool testasolucao(vector<long> teste, vector<long> vec)
{
    sort(teste.begin(), teste.end());
    int n = teste.size();
    bool k = true;

    for (int i = 0; i < n; i++)
    {
        if (teste[i] != vec[i])
        {
            k = false;
        }
    }

    return k;
}

int main(int argc, char **argv)
{

    srand(time(NULL));

    if (argc < 2)
    {
        cerr << "Uso: " << argv[0] << " <arquivo_de_entrada>" << endl;
        return 1;
    }

    vector<long> A;
    string filename = argv[1];
    readfile(filename, A);

    int n = A.size();
    vector<long> A2 = A;
    vector<long> teste = A;

    // Calcula o tempo em que o insertion sort demora para ordenar o vetor
    auto inicio1 = high_resolution_clock::now();
    insertionsort(A, n);
    auto fim1 = high_resolution_clock::now();

    // Utilize essa função para verificar o ordenamento do vetor (basta descomentar, se a função retornar falso, então o programa vai parar)
    // assert(testasolucao(teste, A));

    auto tempo1 = duration_cast<microseconds>(fim1 - inicio1);

    cout << "Tempo do insertion sort: " << endl;
    cout << (tempo1.count() / 1e7) << endl;
    cout << "Sequência: " << endl;

    for (int i = 0; i < n; i++)
    {
        cout << A[i] << " ";
    }
    cout << endl;

    // Calcula o tempo em que o selection sort demora para ordenar o vetor

    auto inicio2 = high_resolution_clock::now();
    selectionsort(A2, n);
    auto fim2 = high_resolution_clock::now();

    // Utilize essa função para verificar o ordenamento do vetor (basta descomentar, se a função retornar falso, então o programa vai parar)
    // assert(testasolucao(teste, A2));

    auto tempo2 = duration_cast<microseconds>(fim2 - inicio2);

    cout << "Tempo do selection sort: " << endl;
    cout << (tempo2.count() / 1e7) << endl;
    cout << "Sequência: " << endl;

    for (int i = 0; i < n; i++)
    {
        cout << A2[i] << " ";
    }
    cout << endl;

    return 0;
}