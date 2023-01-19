#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

//Administrator
class Administrator
{
private:
    char* nume, * email;
    int profile_id;
public:
    Administrator(char*, char*, int);
    ~Administrator();
    void afisare();
    void confirmare_comenzi();
};

Administrator::Administrator(char* N, char* EM, int ID)
{
    nume = new char[strlen(N) + 1];
    strcpy(nume, N);
    email = new char[strlen(EM) + 1];
    strcpy(email, EM);
    profile_id = ID;
}
Administrator::~Administrator()
{
    delete nume;
    delete email;
}

void Administrator::afisare()
{
    cout << "Nume administrator: " << nume << endl;
    cout << "Date contact administrator: " << email << endl;
    cout << "Numar unic de identificare administrator: " << profile_id << endl;
}




//Magazin
class Magazin
{
public:
    virtual void afisare() = NULL;
};



//Magazin virtual
class Magazin_virtual :public Magazin
{
protected:
    char* tip_magazin;
public:
    Magazin_virtual(char*);
    ~Magazin_virtual();
    void afisare();
};

Magazin_virtual::Magazin_virtual(char* TM)
{
    tip_magazin = new char[strlen(TM) + 1];
    strcpy(tip_magazin, TM);
}

Magazin_virtual::~Magazin_virtual()
{
    delete tip_magazin;
}

void Magazin_virtual::afisare()
{
    cout << "\nTipul magazinului este: " << tip_magazin;
}



//Magazin produse electronice
class MV_ProdElec:public Magazin_virtual
{
protected:
    char* categ, * nume_prod;
    float pret;
public:
    MV_ProdElec(char*, char*, char*, float);
    ~MV_ProdElec();
    void afisare();
    inline float actualizare_pret(float x)
    {
        pret = x;
        return pret;
    }


};

MV_ProdElec::MV_ProdElec(char* TM, char* CAT, char* NP, float P):Magazin_virtual(TM)
{
    categ = new char[strlen(CAT) + 1];
    strcpy(categ, CAT);
    nume_prod = new char[strlen(NP) + 1];
    strcpy(nume_prod, NP);
    pret = P;
}

MV_ProdElec::~MV_ProdElec()
{
    delete categ;
    delete nume_prod;
}
void MV_ProdElec::afisare()
{
    Magazin_virtual::afisare();
    cout << "\nCategoria produsului este: " << categ << endl;
    cout << "Numele produsul este: " << nume_prod << endl;
    cout << "Pretul produsul este: " << pret << endl;
}


//Magazin virtual Laptop
class MV_Laptop:public MV_ProdElec
{
private:
    char* so, * gpu, * nume_firma, * cpu;
    int nr_comenzi;
public:
    MV_Laptop(char*, char*, char*, float, char*, char*, char*, char*, int);
    ~MV_Laptop();
    void afisare();
};

MV_Laptop::MV_Laptop(char* TM, char* CAT, char* NP, float P, char* SO, char* GPU, char* NF, char* CPU, int NC):MV_ProdElec(TM, CAT, NP, P)
{
    so = new char[strlen(SO) + 1];
    strcpy(so, SO);
    gpu = new char[strlen(GPU) + 1];
    strcpy(gpu, GPU);
    nume_firma = new char[strlen(NF) + 1];
    strcpy(nume_firma, NF);
    cpu = new char[strlen(CPU) + 1];
    strcpy(cpu, CPU);
    nr_comenzi = NC;
}

MV_Laptop::~MV_Laptop()
{
    delete so;
    delete gpu;
    delete nume_firma;
    delete cpu;
}

void MV_Laptop::afisare()
{
    MV_ProdElec::afisare();
    cout << "Numele firmei producatoare:" << nume_firma << endl;
    cout << "Sistemul de operare activ pe Laptop: " << so << endl;
    cout << "Placa video: " << gpu << endl;
    cout << "Procesor: " << cpu << endl;
    cout << "Numar de comenzi: " << nr_comenzi << endl;
}



//Magazin virtual sisteme office
class MV_SistemeOffice :public MV_ProdElec
{
private:
    char * gpu, * nume_firma, * cpu;
    int nr_comenzi;
public:
    MV_SistemeOffice(char*, char*, char*, float, char*, char*, char*, int);
    ~MV_SistemeOffice();
    void afisare();
};

MV_SistemeOffice::MV_SistemeOffice(char* TM, char* CAT, char* NP, float P, char* GPU, char* NF, char* CPU, int NC) :MV_ProdElec(TM, CAT, NP, P)
{
    
    gpu = new char[strlen(GPU) + 1];
    strcpy(gpu, GPU);
    nume_firma = new char[strlen(NF) + 1];
    strcpy(nume_firma, NF);
    cpu = new char[strlen(CPU) + 1];
    strcpy(cpu, CPU);
    nr_comenzi = NC;
}

MV_SistemeOffice::~MV_SistemeOffice()
{
    
    delete gpu;
    delete nume_firma;
    delete cpu;
}

void MV_SistemeOffice::afisare()
{
    MV_ProdElec::afisare();
    cout << "Numele firmei producatoare:" << nume_firma << endl;
    cout << "Placa video: " << gpu << endl;
    cout << "Procesor: " << cpu << endl;
    cout << "Numar de comenzi: " << nr_comenzi << endl;
}


//Magazin TV
class MV_TV :public MV_ProdElec
{
private:
    char * nume_firma;
    int refresh_rate, nr_comenzi;
    float dim_ecran;
public:
    MV_TV(char*, char*, char*, float, char*, int, int, float);
    ~MV_TV();
    void afisare();
};

MV_TV::MV_TV(char* TM, char* CAT, char* NP, float P, char* NF, int R, int NC, float DE) :MV_ProdElec(TM, CAT, NP, P)
{
    nume_firma = new char[strlen(NF) + 1];
    strcpy(nume_firma, NF); 
    refresh_rate = R;
    nr_comenzi = NC;
    dim_ecran = DE;
}

MV_TV ::~MV_TV()
{
    delete nume_firma;   
}

void MV_TV::afisare()
{
    MV_ProdElec::afisare();
    cout << "Numele firmei producatoare:" << nume_firma << endl;
    cout << "Refresh rate-ul TV-ului: " << refresh_rate << endl;
    cout << "Dimensiune ecran: " << dim_ecran << endl;
    cout << "Numar de comenzi: " << nr_comenzi << endl;
}
int main()
{
    //administrator
    Administrator* admin1 = new Administrator((char*)"Ioan Andrei", (char*)"ioangg@gmail.com", (int)1);
    admin1->afisare();


    //magazin virtual
    Magazin_virtual* MV1 = new Magazin_virtual((char*)"virtual");
    MV1->afisare();


    //magazin produse electronice
    MV_ProdElec* MVprod1 = new MV_ProdElec((char*) "virtual", (char*)"Sisteme Office", (char*)"Dell Office PC", (float)899.99);
    MVprod1->afisare();


    //magazin laptop-uri
    MV_Laptop* laptop1 = new MV_Laptop((char*)"virtual", (char*)"Laptop-uri", (char*)"Dell Inspiration", (float)8999.99, (char*)"Windows", (char*)"Nvidia RTX 3080TI", (char*)"Dell", (char*)"Ryzen 9", (int)3);
    laptop1->afisare();


    //magazin sisteme office
    MV_SistemeOffice* soffice1 = new MV_SistemeOffice((char*)"virtual", (char*)"Sisteme Office", (char*)"Lenovo ThinkPad", (float)8999.99, (char*)"Nvidia RTX 4090TI", (char*)"Lenovo", (char*)"Ryzen 9", (int)2);
    soffice1->afisare();


    //magazin TV-uri
    MV_TV* tv1 = new MV_TV((char*)"virtual", (char*)"Laptop-uri", (char*)"Dell Inspiration", (float)8999.99, (char*)"LG", (int)120, (int)5, (float)34.5);
    tv1->afisare();

}

