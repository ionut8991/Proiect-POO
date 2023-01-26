#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

//Administrator
class Administrator
{
private:
   
    char nume[50], email[50];
    int profile_id;
public:
    Administrator();
    Administrator(char*, char*, int);
    ~Administrator();
    void afisare();
    friend istream& operator>>(istream&in, Administrator&);
};

Administrator::Administrator()
{
    strcpy(nume, " ");
    strcpy(email, " ");
    profile_id = 0;
}
Administrator::Administrator(char* N, char* EM, int ID)
{
    
    strcpy(nume, N);
    
    strcpy(email, EM);
    profile_id = ID;
}
Administrator::~Administrator()
{

}

void Administrator::afisare()
{
    cout << "Nume administrator: " << nume << endl;
    cout << "Date contact administrator: " << email << endl;
    cout << "Numar unic de identificare administrator: " << profile_id << endl;
}

/*
istream& operator>>(istream& in, Administrator& ax)
{
    char* tempnume =0, * tempemail =0;
    cout << "\nIntroduceti datele noului administrator: " << endl;
    cout << "Nume administrator: " << endl;
    in >> tempnume;
    ax.nume = new char[strlen(tempnume) + 1];
    strcpy(ax.nume, tempnume);
    cout << "Adresa de email administrator: " << endl;
    in >> tempemail;
    ax.email = new char[strlen(tempemail) + 1];
    strcpy(ax.email, tempemail);
    cout << "ID unic: " << endl;
    in >> ax.profile_id;
    return in;
    
}*/


istream& operator>>(istream& in, Administrator& ax)
{
    cout << "\nIntroduceti datele noului administrator: " << endl;
    cout << "Nume administrator: " << endl;
    in >> ax.nume;
    cout << "Adresa de email administrator: " << endl;
    in >> ax.email;
    cout << "ID unic: " << endl;
    in >> ax.profile_id;
    return in;
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
    Magazin_virtual();
    Magazin_virtual(char*);
    ~Magazin_virtual();
    void afisare();
    
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



//Magazin produse electronice
class MV_ProdElec:public Magazin_virtual
{
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

    //total stock produse;
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

//total numar comenzi;
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
    void verificare_stoc();
    int actualizare_stoc(int);
    
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

void MV_Laptop::verificare_stoc()
{
    if (this->stock > 0)
    {
        cout << "Stock-ul acestui produs este suficient!" << endl;
    }
    else
    {
        cout << "Nu mai sunt produse in stock, va rugam asteptati!" << endl;
    }
}

int MV_Laptop::actualizare_stoc(int st)
{
    this->stock = st;
    cout << "\nNoul numar de produse in stock este: " << this->stock << endl;
    return stock;
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
    void verificare_stoc();
    int actualizare_stoc(int);
   
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

void MV_SistemeOffice::verificare_stoc()
{
    if (this->stock > 0)
    {
        cout << "Stock-ul acestui produs este suficient!" << endl;
    }
    else
    {
        cout << "Nu mai sunt produse in stock, va rugam asteptati!" << endl;
    }
}

int MV_SistemeOffice::actualizare_stoc(int st)
{
    this->stock = st;
    cout << "\nNoul numar de produse in stock este: " << this->stock << endl;
    return stock;
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
    void verificare_stoc();
    int actualizare_stoc(int);
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

void MV_TV::verificare_stoc()
{
    if (this->stock > 0)
    {
        cout << "Stock-ul acestui produs este suficient!" << endl;
    }
    else
    {
        cout << "Nu mai sunt produse in stock, va rugam asteptati!" << endl;
    }
}

int MV_TV::actualizare_stoc(int st)
{
    this->stock = st;
    cout << "\nNoul numar de produse in stock este: " << this->stock << endl;
    return stock;
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
    void verificare_stoc();
    int actualizare_stoc(int);
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

void MV_Mobile::verificare_stoc()
{
    if (this->stock > 0)
    {
        cout << "Stock-ul acestui produs este suficient!" << endl;
    }
    else
    {
        cout << "Nu mai sunt produse in stock, va rugam asteptati!" << endl;
    }
}

int MV_Mobile::actualizare_stoc(int st)
{
    this->stock = st;
    cout << "\nNoul numar de produse in stock este: " << this->stock << endl;
    return stock;
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
    void verificare_stoc();
    int actualizare_stoc(int);

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

void MV_ComponentePC::verificare_stoc()
{
    if (this->stock > 0)
    {
        cout << "Stock-ul acestui produs este suficient!" << endl;
    }
    else
    {
        cout << "Nu mai sunt produse in stock, va rugam asteptati!" << endl;
    }
}

int MV_ComponentePC::actualizare_stoc(int st)
{
    this->stock = st;
    cout << "\nNoul numar de produse in stock este: " << this->stock << endl;
    return stock;
}

int main()
{
    cout << "\n_______________________________________________________________________\n" << endl;
    cout << "Primul set de date: " << endl;
    cout << "_______________________________________________________________________" << endl;


    //administrator
    Administrator admin1((char*)"Ioan Andrei", (char*)"ioangg@gmail.com", (int)1);
    admin1.afisare();


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
    laptop1->act_nrcom(4);
    laptop1->get_nrcom();
    laptop1->verificare_stoc();
    laptop1->actualizare_stoc(0);
    laptop1->verificare_stoc();


    //magazin sisteme office
    MV_SistemeOffice* soffice1 = new MV_SistemeOffice((char*)"virtual", (char*)"Sisteme Office", (char*)"Lenovo ThinkPad", (float)8999.99, (int)2, (int)50, (char*)"Nvidia RTX 4090TI", (char*)"Lenovo", (char*)"Ryzen 9");
    soffice1->afisare();
    soffice1->actualizare_pret(5434);
    soffice1->afisare_pret();
    soffice1->act_nrcom(9);
    soffice1->get_nrcom();


    //magazin TV-uri
    MV_TV* tv1 = new MV_TV((char*)"virtual", (char*)"Televizoare", (char*)"LG G325253", (float)8999.99, (int)5, (int)40, (char*)"LG", (int)120,  (float)34.5);
    tv1->afisare();
    tv1->actualizare_pret(5434);
    tv1->afisare_pret();
    tv1->act_nrcom(53);
    tv1->get_nrcom();

    //magazin telefoane mobile
    MV_Mobile* mobile1 = new MV_Mobile((char*)"virtual", (char*)"Smartphone-uri", (char*)"LG G325253", (float)8999.99, (int)73, (int)130, (char*)"Android", (char*)"Google", (int)48,  (float)6.7);
    mobile1->afisare();
    mobile1->actualizare_pret(5434);
    mobile1->afisare_pret();
    mobile1->act_nrcom(625);
    mobile1->get_nrcom();

    //magazin Componente PC
    MV_ComponentePC* comp1 = new MV_ComponentePC((char*)"virtual", (char*)"Componente PC", (char*)"i9 134000", (float)8999.99, (int)6, (int)80, (char*)"Procesor", (char*)"Intel", (char*)"3.5GHZ, 3MB Cache");
    comp1->afisare();
    comp1->actualizare_pret(5434);
    comp1->afisare_pret();
    comp1->act_nrcom(34);
    comp1->get_nrcom();
    
    //verificare total nr de comenzi
    MV_ProdElec* vecprodus[] = { laptop1, soffice1, tv1, mobile1, comp1 };
    int marime = sizeof(vecprodus) / sizeof(vecprodus[0]);
    cout << "\nNr total comenzi: " << MVprod1->totalcomenzi(vecprodus, marime) << endl;
    
    //verificare total stock produse din magazine
    MV_ProdElec* total = new MV_ProdElec(*laptop1 + *soffice1 + *comp1 + *mobile1);
    cout << "\nTotal stock produse magazin: " << total->totalstock() << endl;


    //adaugare administrator nou;
    Administrator admin2;
    cin >> admin2;
    admin2.afisare();


    cout << "\n_______________________________________________________________________\n" << endl;
    cout << "Al doilea set de date: " << endl;
    cout << "_______________________________________________________________________" << endl;

    Administrator admin3((char*)"Vasilica Ioan", (char*)"vasion@gmail.com", (int)2);
    admin3.afisare();


    //magazin virtual
    Magazin_virtual* MV2 = new Magazin_virtual((char*)"virtual");
    MV2->afisare();



    //magazin produse electronice
    MV_ProdElec* MVprod2 = new MV_ProdElec((char*)"virtual", (char*)"Categorie", (char*)"Nume produs", (float)0, (int)0, (int)0);
    MVprod2->afisare();




    //magazin laptop-uri
    MV_Laptop* laptop2 = new MV_Laptop((char*)"virtual", (char*)"Laptop-uri", (char*)"Acer Nitro 5", (float)3499.99, (int)6, (int)160, (char*)"Windows 10", (char*)"GeForce GTX™ 1650 4GB", (char*)"Acer", (char*)"i5-11400H");
    laptop2->afisare();
    laptop2->actualizare_pret(6643);
    laptop2->afisare_pret();
    laptop2->act_nrcom(4);
    laptop2->get_nrcom();
    laptop2->verificare_stoc();
    laptop2->actualizare_stoc(0);
    laptop2->verificare_stoc();


    //magazin sisteme office
    MV_SistemeOffice* soffice2 = new MV_SistemeOffice((char*)"virtual", (char*)"Sisteme Office", (char*)"Mac Mini PC", (float)3499.99, (int)7, (int)64, (char*)"Integrata", (char*)"Apple", (char*)"Apple M2");
    soffice2->afisare();
    soffice2->actualizare_pret(5434);
    soffice2->afisare_pret();
    soffice2->act_nrcom(9);
    soffice2->get_nrcom();


    //magazin TV-uri
    MV_TV* tv2 = new MV_TV((char*)"virtual", (char*)"Televizoare", (char*)"Nei 40NE6900", (float)1028.10, (int)5, (int)30, (char*)"NEI", (int)60, (float)39);
    tv2->afisare();
    tv2->actualizare_pret(5434);
    tv2->afisare_pret();
    tv2->act_nrcom(53);
    tv2->get_nrcom();

    //magazin telefoane mobile
    MV_Mobile* mobile2 = new MV_Mobile((char*)"virtual", (char*)"Smartphone-uri", (char*)"Moto G62", (float)999.99, (int)33, (int)130, (char*)"Android", (char*)"Motorola", (int)50, (float)6.5);
    mobile2->afisare();
    mobile2->actualizare_pret(5434);
    mobile2->afisare_pret();
    mobile2->act_nrcom(625);
    mobile2->get_nrcom();

    //magazin Componente PC
    MV_ComponentePC* comp2 = new MV_ComponentePC((char*)"virtual", (char*)"Componente PC", (char*)"ASUS GeForce RTX® 3060TI TUF GAMING", (float)3499.99, (int)6, (int)80, (char*)"Placa video", (char*)"nVidia", (char*)"8GB GDDR6X, 256-bit");
    comp2->afisare();
    comp2->actualizare_pret(5434);
    comp2->afisare_pret();
    comp2->act_nrcom(34);
    comp2->get_nrcom();

    //verificare total nr de comenzi
    MV_ProdElec* vecprodus2[] = { laptop2, soffice2, tv2, mobile2, comp2 };
    int marime2 = sizeof(vecprodus2) / sizeof(vecprodus2[0]);
    cout << "\nNr total comenzi: " << MVprod1->totalcomenzi(vecprodus2, marime2) << endl;

    //verificare total stock produse din magazine
    MV_ProdElec* total2 = new MV_ProdElec(*laptop2 + *soffice1 + *comp2 + *mobile2);
    cout << "\nTotal stock produse magazin: " << total2->totalstock() << endl;


    //adaugare administrator nou;
    Administrator admin4;
    cin >> admin4;
    admin4.afisare();


    cout << "\n_______________________________________________________________________\n" << endl;
    cout << "Al doilea set de date: " << endl;
    cout << "_______________________________________________________________________" << endl;

    Administrator admin5((char*)"Vasilica Ioan", (char*)"vasion@gmail.com", (int)2);
    admin5.afisare();


    //magazin virtual
    Magazin_virtual* MV3 = new Magazin_virtual((char*)"virtual");
    MV3->afisare();



    //magazin produse electronice
    MV_ProdElec* MVprod3 = new MV_ProdElec((char*)"virtual", (char*)"Categorie", (char*)"Nume produs", (float)0, (int)0, (int)0);
    MVprod3->afisare();




    //magazin laptop-uri
    MV_Laptop* laptop3 = new MV_Laptop((char*)"virtual", (char*)"Laptop-uri", (char*)"HP VICTUS 15-fb0026nq", (float)3499.99, (int)9, (int)160, (char*)"Windows 10", (char*)"GeForce GTX 1650 4GB", (char*)"HP", (char*)"AMD Ryzen™ 5 5600H");
    laptop3->afisare();
    laptop3->actualizare_pret(6643);
    laptop3->afisare_pret();
    laptop3->act_nrcom(4);
    laptop3->get_nrcom();
    laptop3->verificare_stoc();
    laptop3->actualizare_stoc(0);
    laptop3->verificare_stoc();


    //magazin sisteme office
    MV_SistemeOffice* soffice3 = new MV_SistemeOffice((char*)"virtual", (char*)"Sisteme Office", (char*)"eXpert GAMING", (float)2569.99, (int)5, (int)74, (char*)"AMD Radeon R9 370", (char*)"EXPERT COMPUTERS", (char*)"i5-9400");
    soffice3->afisare();
    soffice3->actualizare_pret(5434);
    soffice3->afisare_pret();
    soffice3->act_nrcom(9);
    soffice3->get_nrcom();


    //magazin TV-uri
    MV_TV* tv3 = new MV_TV((char*)"virtual", (char*)"Televizoare", (char*)"QLED 43Q60B", (float)1999.99, (int)18, (int)70, (char*)"Samsung", (int)50, (float)42.5);
    tv3->afisare();
    tv3->actualizare_pret(5434);
    tv3->afisare_pret();
    tv3->act_nrcom(53);
    tv3->get_nrcom();

    //magazin telefoane mobile
    MV_Mobile* mobile3 = new MV_Mobile((char*)"virtual", (char*)"Smartphone-uri", (char*)"iPhone 14 Pro", (float)6339.99, (int)29, (int)0, (char*)"IOS", (char*)"Apple", (int)48, (float)6.1);
    mobile3->afisare();
    mobile3->actualizare_pret(5434);
    mobile3->afisare_pret();
    mobile3->act_nrcom(625);
    mobile3->get_nrcom();

    //magazin Componente PC
    MV_ComponentePC* comp3 = new MV_ComponentePC((char*)"virtual", (char*)"Componente PC", (char*)"CV Series™ CV650", (float)377.99, (int)9, (int)53, (char*)"Sursa PC", (char*)"Corsair", (char*)"80 PLUS Bronze, 650W, Dual EPS");
    comp3->afisare();
    comp3->actualizare_pret(5434);
    comp3->afisare_pret();
    comp3->act_nrcom(34);
    comp3->get_nrcom();

    //verificare total nr de comenzi
    MV_ProdElec* vecprodus3[] = { laptop3, soffice3, tv3, mobile3, comp3 };
    int marime3 = sizeof(vecprodus3) / sizeof(vecprodus3[0]);
    cout << "\nNr total comenzi: " << MVprod1->totalcomenzi(vecprodus3, marime3) << endl;

    //verificare total stock produse din magazine
    MV_ProdElec* total3 = new MV_ProdElec(*laptop3 + *soffice1 + *comp3 + *mobile3);
    cout << "\nTotal stock produse magazin: " << total3->totalstock() << endl;


    //adaugare administrator nou;
    Administrator admin6;
    cin >> admin6;
    admin6.afisare();
}

