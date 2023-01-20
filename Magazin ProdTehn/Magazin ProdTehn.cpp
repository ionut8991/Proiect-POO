#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

//Administrator
class Administrator
{
    friend class MV_ProdElec;
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
/*
void Administrator::confirmare_comenzi()
{
    if (MV_ProdElec::totalcomenzi > 0)
        cout << "Confirmare livrare comenzi";
    else
        cout << " Nu sunt comenzi de confirmat";
}
*/

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
    Magazin_virtual();
    Magazin_virtual(char*);
    ~Magazin_virtual();
    void afisare();
    friend istream& operator>>(istream& in, Magazin_virtual& mv);
};

Magazin_virtual::Magazin_virtual()
{
    tip_magazin = 0;
}

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

istream& operator>>(istream& in, Magazin_virtual& mv)
{
    cout << "Tip magazin:";
    in >> mv.tip_magazin;
    return in;
}

//Magazin produse electronice
class MV_ProdElec:public Magazin_virtual
{
    friend class Administrator;
protected:
    char* categ, * nume_prod;
    float pret;
    int nr_comenzi, stock;
public:
    MV_ProdElec();
    MV_ProdElec(char*, char*, char*, float, int, int);
    ~MV_ProdElec();
    void afisare();
    inline float actualizare_pret(float x)
    {
        pret = x;
        return pret;
       
    }
    inline void afisare_pret()
    {
        cout << "\nNoul pret al produsului este: " << pret << endl;
    }

    int act_nrcom(int xcom)
    {
        nr_comenzi = xcom;
        return nr_comenzi;
    }
    void get_nrcom()
    {
        cout << "\nNoul numar de comenzi: " << nr_comenzi << endl;
    }

    int totalcomenzi(MV_ProdElec* vecprodus[], int marime);

    int totalstock()
    {
        return stock;
    }

    MV_ProdElec operator + (const MV_ProdElec& other)
    {
        return MV_ProdElec(tip_magazin, categ, nume_prod, pret, nr_comenzi, stock + other.stock);
    }
};




MV_ProdElec::MV_ProdElec(char* TM, char* CAT, char* NP, float P, int NC, int ST):Magazin_virtual(TM)
{
    categ = new char[strlen(CAT) + 1];
    strcpy(categ, CAT);
    nume_prod = new char[strlen(NP) + 1];
    strcpy(nume_prod, NP);
    pret = P;
    nr_comenzi = NC;
    stock = ST;

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
    cout << "Total produse in stoc: " << stock << endl;
}

int MV_ProdElec::totalcomenzi(MV_ProdElec* vecprodus[], int marime)
{
    int total = 0;
    for (int i = 0; i < marime; i++)
    {
        total += vecprodus[i]->nr_comenzi;
    }
    return total;
}

//Magazin virtual Laptop
class MV_Laptop:public MV_ProdElec
{
private:
    char* so, * gpu, * nume_firma, * cpu;
    
public:
    MV_Laptop(char*, char*, char*, float, int, int, char*, char*, char*, char*);
    ~MV_Laptop();
    void afisare();
   
    
};

MV_Laptop::MV_Laptop(char* TM, char* CAT, char* NP, float P, int NC, int ST, char* SO, char* GPU, char* NF, char* CPU):MV_ProdElec(TM, CAT, NP, P, NC, ST)
{
    so = new char[strlen(SO) + 1];
    strcpy(so, SO);
    gpu = new char[strlen(GPU) + 1];
    strcpy(gpu, GPU);
    nume_firma = new char[strlen(NF) + 1];
    strcpy(nume_firma, NF);
    cpu = new char[strlen(CPU) + 1];
    strcpy(cpu, CPU);
    
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
    
public:
    MV_SistemeOffice(char*, char*, char*, float, int, int, char*, char*, char*);
    ~MV_SistemeOffice();
    void afisare();
   
};

MV_SistemeOffice::MV_SistemeOffice(char* TM, char* CAT, char* NP, float P, int NC, int ST, char* GPU, char* NF, char* CPU) :MV_ProdElec(TM, CAT, NP, P, NC, ST)
{
    
    gpu = new char[strlen(GPU) + 1];
    strcpy(gpu, GPU);
    nume_firma = new char[strlen(NF) + 1];
    strcpy(nume_firma, NF);
    cpu = new char[strlen(CPU) + 1];
    strcpy(cpu, CPU);
    
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
    int refresh_rate;
    float dim_ecran;
public:
    MV_TV(char*, char*, char*, float, int, int, char*, int, float);
    ~MV_TV();
    void afisare();
};

MV_TV::MV_TV(char* TM, char* CAT, char* NP, float P, int NC, int ST, char* NF, int R, float DE) :MV_ProdElec(TM, CAT, NP, P, NC, ST)
{
    nume_firma = new char[strlen(NF) + 1];
    strcpy(nume_firma, NF); 
    refresh_rate = R;
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


//Magazin Telefoane Mobile
class MV_Mobile :public MV_ProdElec
{
private:
    char*so, * nume_firma;
    int dim_camera;
    float dim_ecran;
public:
    MV_Mobile(char*, char*, char*, float, int, int, char*,char*, int, float);
    ~MV_Mobile();
    void afisare();
};

MV_Mobile::MV_Mobile(char* TM, char* CAT, char* NP, float P, int NC, int ST, char*SO, char* NF, int DC, float DE) :MV_ProdElec(TM, CAT, NP, P, NC, ST)
{
    so = new char[strlen(SO) + 1];
    strcpy(so, SO);
    nume_firma = new char[strlen(NF) + 1];
    strcpy(nume_firma, NF);
    dim_camera = DC;
    dim_ecran = DE;
}

MV_Mobile ::~MV_Mobile()
{
    delete nume_firma;
    delete so;
}

void MV_Mobile::afisare()
{
    MV_ProdElec::afisare();
    cout << "Numele firmei producatoare:" << nume_firma << endl;
    cout << "Sistemul de operare al telefonului este:" << so << endl;
    cout << "Dimensiune camera: " << dim_camera << " MB" << endl;
    cout << "Dimensiune ecran: " << dim_ecran << endl;
    cout << "Numar de comenzi: " << nr_comenzi << endl;
}



//Magazin Componente PC
class MV_ComponentePC :public MV_ProdElec
{
private:
    char* tip_produs, * nume_firma, * specificatii;
public:
    MV_ComponentePC(char*, char*, char*, float, int,int, char*, char*, char*);
    ~MV_ComponentePC();
    void afisare();

};

MV_ComponentePC::MV_ComponentePC(char* TM, char* CAT, char* NP, float P, int NC, int ST, char* TP, char* NF, char* SP) :MV_ProdElec(TM, CAT, NP, P, NC, ST)
{

    tip_produs = new char[strlen(TP) + 1];
    strcpy(tip_produs, TP);
    nume_firma = new char[strlen(NF) + 1];
    strcpy(nume_firma, NF);
    specificatii = new char[strlen(SP) + 1];
    strcpy(specificatii, SP);
}

MV_ComponentePC::~MV_ComponentePC()
{

    delete tip_produs;
    delete nume_firma;
    delete specificatii;
}

void MV_ComponentePC::afisare()
{
    MV_ProdElec::afisare();
    cout << "Numele firmei producatoare:" << nume_firma << endl;
    cout << "Tip produs: " << tip_produs << endl;
    cout << "Specificatii produs: " << specificatii << endl;
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
    MV_ProdElec* MVprod1 = new MV_ProdElec((char*) "virtual", (char*)"Categorie", (char*)"Nume produs", (float)0, (int)0, (int)0);
    MVprod1->afisare();
    



    //magazin laptop-uri
    MV_Laptop* laptop1 = new MV_Laptop((char*)"virtual", (char*)"Laptop-uri", (char*)"Dell Inspiration", (float)8999.99, (int)3, (int)100, (char*)"Windows", (char*)"Nvidia RTX 3080TI", (char*)"Dell", (char*)"Ryzen 9");
    laptop1->afisare();
    laptop1->actualizare_pret(6643);
    laptop1->afisare_pret();
    laptop1->act_nrcom(6);
    laptop1->get_nrcom();


    //magazin sisteme office
    MV_SistemeOffice* soffice1 = new MV_SistemeOffice((char*)"virtual", (char*)"Sisteme Office", (char*)"Lenovo ThinkPad", (float)8999.99, (int)2, (int)50, (char*)"Nvidia RTX 4090TI", (char*)"Lenovo", (char*)"Ryzen 9");
    soffice1->afisare();
    soffice1->actualizare_pret(5434);
    soffice1->afisare_pret();
    soffice1->act_nrcom(6);
    soffice1->get_nrcom();


    //magazin TV-uri
    MV_TV* tv1 = new MV_TV((char*)"virtual", (char*)"Televizoare", (char*)"LG G325253", (float)8999.99, (int)5, (int)40, (char*)"LG", (int)120,  (float)34.5);
    tv1->afisare();
    tv1->actualizare_pret(5434);
    tv1->afisare_pret();
    tv1->act_nrcom(6);
    tv1->get_nrcom();

    //magazin telefoane mobile
    MV_Mobile* mobile1 = new MV_Mobile((char*)"virtual", (char*)"Smartphone-uri", (char*)"LG G325253", (float)8999.99, (int)73, (int)130, (char*)"Android", (char*)"Google", (int)48,  (float)6.7);
    mobile1->afisare();
    mobile1->actualizare_pret(5434);
    mobile1->afisare_pret();
    mobile1->act_nrcom(6);
    mobile1->get_nrcom();

    //magazin Componente PC
    MV_ComponentePC* comp1 = new MV_ComponentePC((char*)"virtual", (char*)"Componente PC", (char*)"i9 134000", (float)8999.99, (int)6, (int)80, (char*)"Procesor", (char*)"Intel", (char*)"3.5GHZ, 3MB Cache");
    comp1->afisare();
    comp1->actualizare_pret(5434);
    comp1->afisare_pret();
    comp1->act_nrcom(6);
    comp1->get_nrcom();
    
    /*
    MV_ProdElec* vecprodus[] = { *laptop1, *soffice1, *tv1, *mobile1, *comp1 };
    int marime = sizeof(vecprodus) / sizeof(vecprodus[0]);
    cout << "Nr total comenzi" << MV_ProdElec::totalcomenzi(vecprodus, marime) << endl;
    */
    /*
    Magazin_virtual mv1;
    cin >> mv1;
    mv1.afisare();
    */

    MV_ProdElec* total = new MV_ProdElec(*laptop1 + *soffice1 + *comp1 + *mobile1);
    cout << "\nTotal stock produse magazin: " << total->totalstock() << endl;
   
    
}

