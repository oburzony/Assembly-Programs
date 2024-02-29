#include <iostream>
#include <chrono>
#include <string>
#include <fstream>
#include <random>


struct FourNum
{
    float first, second, third, fourth;
};

FourNum arrayFirst[1024];
FourNum arraySecond[1024];
FourNum result[1024];

long double sumTimeM = 0;
long double subTimeM = 0;
long double mulTimeM = 0;
long double divTimeM = 0;

long double sumTimeS = 0;
long double subTimeS = 0;
long double mulTimeS = 0;
long double divTimeS = 0;

void addopSIMD(int i);
void subopSIMD(int i);
void mulopSIMD(int i);
void divopSIMD(int i);

void addopSISD(int i);
void subopSISD(int i);
void mulopSISD(int i);
void divopSISD(int i);

void putRandomValues(int a);
void Measurement(int a);

int main()
{
    putRandomValues(1024);
    Measurement(256);
    Measurement(512);
    Measurement(1024);
}

float createRandom()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(-1000000000.0f, 1000000000.0f);
    return dis(gen);
}


void putRandomValues(int a)
{

    for (int i = 0; i < a; i++)
    {
        arrayFirst[i].first = createRandom();
        arrayFirst[i].second = createRandom();
        arrayFirst[i].third = createRandom();
        arrayFirst[i].fourth = createRandom();

        arraySecond[i].first = createRandom();
        arraySecond[i].second = createRandom();
        arraySecond[i].third = createRandom();
        arraySecond[i].fourth = createRandom();
    }
}

void Measurement(int a)
{
    for (int i = 0; i < 10; i++)
    {   
        
        auto t0  =  std::chrono::high_resolution_clock::now();
        for (int j = 0; j < a; j++)
        {
            addopSIMD(j);
        
        }
        auto t1 = std::chrono::high_resolution_clock::now();
        sumTimeM = sumTimeM + std::chrono::duration_cast<std::chrono::nanoseconds>((t1 - t0)).count();


        auto t2  = std::chrono::high_resolution_clock::now();
        for (int j = 0; j < a; j++)
        {
            subopSIMD(j);
        
        }
        auto t3 = std::chrono::high_resolution_clock::now();
        subTimeM = subTimeM + std::chrono::duration_cast<std::chrono::nanoseconds>((t3 - t2)).count();


        auto t4  = std::chrono::high_resolution_clock::now();
        for (int j = 0; j < a; j++)
        {
            mulopSIMD(j);
        
        }
        auto t5 = std::chrono::high_resolution_clock::now();
        mulTimeM = mulTimeM + std::chrono::duration_cast<std::chrono::nanoseconds>((t5 - t4)).count();

        auto t6  = std::chrono::high_resolution_clock::now();
        for (int j = 0; j < a; j++)
        {
            divopSIMD(j);
        }
        auto t7 = std::chrono::high_resolution_clock::now();
        divTimeM = divTimeM + std::chrono::duration_cast<std::chrono::nanoseconds>((t7 - t6)).count();;

        auto t8  = std::chrono::high_resolution_clock::now();
        for (int j = 0; j < a; j++)
        {
            addopSISD(j);
        
        }
        auto t9 = std::chrono::high_resolution_clock::now();
        sumTimeS = sumTimeS + std::chrono::duration_cast<std::chrono::nanoseconds>((t9 - t8)).count();


        auto t10  = std::chrono::high_resolution_clock::now();
        for (int j = 0; j < a; j++)
        {
            subopSISD(j);
        
        }
        auto t11 = std::chrono::high_resolution_clock::now();
        subTimeS = subTimeS + std::chrono::duration_cast<std::chrono::nanoseconds>((t11 - t10)).count();


        auto t12  = std::chrono::high_resolution_clock::now();
        for (int j = 0; j < a; j++)
        {
            mulopSISD(j);
        
        }
        auto t13 = std::chrono::high_resolution_clock::now();
        mulTimeS = mulTimeS + std::chrono::duration_cast<std::chrono::nanoseconds>((t13 - t12)).count();;

        auto t14  = std::chrono::high_resolution_clock::now();
        for (int j = 0; j < a; j++)
        {
            divopSISD(j);
        }
        auto t15 = std::chrono::high_resolution_clock::now();
        divTimeS = divTimeS + std::chrono::duration_cast<std::chrono::nanoseconds>((t15 - t14)).count();;

    }

    sumTimeM = ((sumTimeM) / 10);
    subTimeM = ((subTimeM) / 10);
    mulTimeM = ((mulTimeM) / 10);
    divTimeM = ((divTimeM) / 10);

    sumTimeS = ((sumTimeS) / 10);
    subTimeS = ((subTimeS) / 10);
    mulTimeS = ((mulTimeS) / 10);
    divTimeS = ((divTimeS) / 10);

    std::ofstream f1("SIMD.txt", std::ios::app);
    f1 << std::endl
       << "Typ Obliczen SIMD" << std::endl
       << "Liczba Liczb " << a*8 << std::endl
       << "Sredni czas [ns]:" << std::endl
       << "+ " << sumTimeM << std::endl
       << "- " << subTimeM << std::endl
       << "* " << mulTimeM << std::endl
       << "/ " << divTimeM << std::endl
       << std::endl;
    f1.close();

    std::ofstream f2("SISD.txt", std::ios::app);
    f2<< std::endl 
      << "Typ Obliczen SISD" << std::endl
      << "Liczba Liczb " << a*8 << std::endl
      << "Sredni czas [ns]:" << std::endl
      << "+ " << sumTimeS << std::endl
      << "- " << subTimeS << std::endl
      << "* " << mulTimeS << std::endl
      << "/ " << divTimeS << std::endl
      << std::endl;
    f2.close();   
}


void addopSIMD(int i)
{
    asm volatile(
        "movaps %1, %%xmm0\n"
        "movaps %2, %%xmm1\n"
        "addps  %%xmm1, %%xmm0\n"
        "movaps %%xmm0, %0\n"
        : "=m"(result[i])
        : "m"(arrayFirst[i]), "m"(arraySecond[i])
    );
  
}

void subopSIMD(int i)
{
    asm volatile(
        "movaps %1, %%xmm0\n"
        "movaps %2, %%xmm1\n"
        "subps  %%xmm1, %%xmm0\n"
        "movaps %%xmm0, %0\n"
        : "=m"(result[i])
        : "m"(arrayFirst[i]), "m"(arraySecond[i])
    );
}

void mulopSIMD(int i)
{
    asm volatile(
        "movaps %1, %%xmm0\n"
        "movaps %2, %%xmm1\n"
        "mulps  %%xmm1, %%xmm0\n"
        "movaps %%xmm0, %0\n"
        : "=m"(result[i])
        : "m"(arrayFirst[i]), "m"(arraySecond[i])
    );
}

void divopSIMD(int i)
{
    asm volatile(
        "movaps %1, %%xmm0\n"
        "movaps %2, %%xmm1\n"
        "divps  %%xmm1, %%xmm0\n"
        "movaps %%xmm0, %0\n"
        : "=m"(result[i])
        : "m"(arrayFirst[i]), "m"(arraySecond[i])
    );
}

void addopSISD(int i)
{
    asm volatile(
    "fld %4\n"
    "fadd %5\n"
    "fstp %0\n"

    "fld %6\n"
    "fadd %7\n"
    "fstp %1\n"

    "fld %8\n"
    "fadd %9\n"
    "fstp %2\n"

    "fld %10\n"
    "fadd %11\n"
    "fstp %3\n"

    : "=m"(result[i].first), "=m"(result[i].second), "=m"(result[i].third), "=m"(result[i].fourth)
    : "f"(arrayFirst[i].first), "f"(arraySecond[i].first),
      "f"(arrayFirst[i].second), "f"(arraySecond[i].second),
      "f"(arrayFirst[i].third), "f"(arraySecond[i].third),
      "f"(arrayFirst[i].fourth), "f"(arraySecond[i].fourth)
    );
}

void subopSISD(int i)
{
   
    asm volatile(
    "fld %4\n"
    "fsub %5\n"
    "fstp %0\n"

    "fld %6\n"
    "fsub %7\n"
    "fstp %1\n"

    "fld %8\n"
    "fsub %9\n"
    "fstp %2\n"

    "fld %10\n"
    "fsub %11\n"
    "fstp %3\n"

    : "=m"(result[i].first), "=m"(result[i].second), "=m"(result[i].third), "=m"(result[i].fourth)
    : "f"(arrayFirst[i].first), "f"(arraySecond[i].first),
      "f"(arrayFirst[i].second), "f"(arraySecond[i].second),
      "f"(arrayFirst[i].third), "f"(arraySecond[i].third),
      "f"(arrayFirst[i].fourth), "f"(arraySecond[i].fourth)
    );
    
}

void mulopSISD(int i)
{
    asm volatile(
    "fld %4\n"
    "fmul %5\n"
    "fstp %0\n"

    "fld %6\n"
    "fmul %7\n"
    "fstp %1\n"

    "fld %8\n"
    "fmul %9\n"
    "fstp %2\n"

    "fld %10\n"
    "fmul %11\n"
    "fstp %3\n"

    : "=m"(result[i].first), "=m"(result[i].second), "=m"(result[i].third), "=m"(result[i].fourth)
    : "f"(arrayFirst[i].first), "f"(arraySecond[i].first),
      "f"(arrayFirst[i].second), "f"(arraySecond[i].second),
      "f"(arrayFirst[i].third), "f"(arraySecond[i].third),
      "f"(arrayFirst[i].fourth), "f"(arraySecond[i].fourth)
    );
}

void divopSISD(int i)
{
    asm volatile(
    "fld %4\n"
    "fdiv %5\n"
    "fstp %0\n"

    "fld %6\n"
    "fdiv %7\n"
    "fstp %1\n"

    "fld %8\n"
    "fdiv %9\n"
    "fstp %2\n"

    "fld %10\n"
    "fdiv %11\n"
    "fstp %3\n"

    : "=m"(result[i].first), "=m"(result[i].second), "=m"(result[i].third), "=m"(result[i].fourth)
    : "f"(arrayFirst[i].first), "f"(arraySecond[i].first),
      "f"(arrayFirst[i].second), "f"(arraySecond[i].second),
      "f"(arrayFirst[i].third), "f"(arraySecond[i].third),
      "f"(arrayFirst[i].fourth), "f"(arraySecond[i].fourth)
    );
}