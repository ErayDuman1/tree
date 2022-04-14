#include<iostream>
#include<fstream>
#include<string.h>
#include <stack>
#include <queue>
#include<fstream>

using namespace std;

struct Ogrenci 
{
	char ogrno[15];
	char ad[30];
	char soyad[30];		//Ogrenci struct inin elemanlarinin tanimlandigi yer
	Ogrenci* sol;		//Agac yapisisnin dallanmasi icin gerekli olan pointerlar
	Ogrenci* sag;
};

struct Agac
{
	Ogrenci* kok1;
	Ogrenci* kok2;		//dosyalarin icindeki verilerin atanmasi icin kok tanimi
	Ogrenci* kok3;
	void ekle(Ogrenci**,char*,char*,char*);
	void agacKur(string,Ogrenci**);
	void menuYazdir();
	void listeMenu();
	void dataMenu(string);
	bool islemYap(char);
	void inorderTara(Ogrenci*);
	void preorderTara(Ogrenci*);
	void postorderTara(Ogrenci*);		//Agac structinin icinde istenilen fonskisyonlar
	void agac_olustur();				
	void ilkDerinlikAra(Ogrenci*);
	void araMenu();
	void ilkGenislikAra(Ogrenci*);
	int ara(char*,Ogrenci*);
	void ogrenciSil(char*,Ogrenci**);
	void sil(char *,Ogrenci**);
	void sil1(Ogrenci**);
	void agacBosalt(Ogrenci*);
	void preorderYazdir(Ogrenci*,ofstream&);
	void dosyayaYaz(Ogrenci*);
};

void Agac::agac_olustur()
{
	kok1 = NULL;
	kok2 = NULL;			//Agacin kuruldugu fonksiyondur
	kok3 = NULL;
	agacKur("data1.txt ",&kok1);
	agacKur("data2.txt ",&kok2);
	agacKur("data3.txt ",&kok3);
}

int main()
{
	Agac agac;
	agac.agac_olustur();
    bool bitir = false;
    char secim;
    while (!bitir) {
        agac.menuYazdir();
        cin >> secim;					//switch-case yaziliyor
        bitir = agac.islemYap(secim);
    }
	agac.agacBosalt(agac.kok1);
	agac.agacBosalt(agac.kok2);		//programın sonunda bellekte tutulan yerleri geri veriyor
	agac.agacBosalt(agac.kok3);
	return 0;
}

void Agac::menuYazdir()
{
    cout << ("Asagidaki islemlerden birini seciniz...") << endl;
    cout << ("  Arama yapmak icin: A") << endl;
    cout << ("  Listeye ekrana yazdirmak icin: L") << endl;
    cout << ("  Ogrenci silmek icin: S") << endl;
    cout << ("  Dosyaya yazmak icin : Y") << endl;        //menu elemanlari tanimlaniyor.
    cout << ("  Cikis icin: C") << endl;
    cout << ("  Seciminiz:");
}

void Agac::dataMenu(string siralamaTürü)
{
	cout <<("Hangi dosya icin ")<<(""+siralamaTürü)<<(" yapmak istiyorsunuz?...") << endl;
	cout << ("Data1: 1") << endl;
	cout << ("Data2: 2") << endl;		//Hangi dosyanin isleme giricegi seciliyor
	cout << ("Data3: 3") << endl;
	cout << endl;
	cout << "Seciminizi giriniz:";
}
void Agac::araMenu()
{
	cout << "ilk derinlikli ara: D" << endl;
	cout << "ilk genislikli ara: G" << endl;
	char araSecim;								//Hangi tur arama yapilacagi seciliyor
	char dataSecim;
	cout << "Seciminizi giriniz:";
	cin >> araSecim;
	switch (araSecim)
	{
	case 'D':case'd':
	{
		dataMenu("ilk derinlikli arama");	//Aramanin hangi dosyada yapilacagi seciliyor
		cin >> dataSecim;
		if (dataSecim == '1')
		{
			ilkDerinlikAra(kok1);
		}
		if (dataSecim == '2')
		{
			ilkDerinlikAra(kok2);
		}
		if (dataSecim == '3')
		{
			ilkDerinlikAra(kok3);
		}
		break;
	}
	case 'G': case'g':
	{
		dataMenu("ilk genislikli arama");	//Aramanin hangi dosyada yapilacagi seciliyor
		cin >> dataSecim;
		if (dataSecim == '1')
		{
			ilkGenislikAra(kok1);
		}
		if (dataSecim == '2')
		{
			ilkGenislikAra(kok2);
		}
		if (dataSecim == '3')
		{
			ilkGenislikAra(kok3);
		}
		break;
	}
	}
}

void Agac::listeMenu()
{
	cout << "Preorder listeleme yapmak icin: R" << endl;
	cout << "Inorder listeleme yapmak icin: I" << endl;		//Elemanlarin hangi tur listelenecegi seciliyor
	cout << "Postorder listeleme yapmak icin: P" << endl;
	char listeSecim;
	cout << "Seciminizi giriniz:";
	cin >> listeSecim;
	char datasecim;

	switch(listeSecim)
	{
	case'R':case'r':
	{
		dataMenu("preorder listeleme");		//Hangi dosyanin preorder listelenecegi seciliyor
		cin >> datasecim;
		if (datasecim == '1')
		{
			preorderTara(kok1);
		}
		if (datasecim == '2')
		{
			preorderTara(kok2);
		}
		if (datasecim == '3')
		{
			preorderTara(kok3);
		}
		break;
	}
	case'I': case'i':
	{
		dataMenu("inorder listeleme");		//Hangi dosyanin inorder listelenecegi seciliyor
		cin >> datasecim;
		if (datasecim == '1')
		{
			inorderTara(kok1);
		}
		if (datasecim == '2')
		{
			inorderTara(kok2);
		}
		if (datasecim == '3')
		{
			inorderTara(kok3);
		}
		break;
	}
	case'P':case'p':
		dataMenu("postorder listeleme");	  //Hangi dosyanin postorder listelenecegi seciliyor
		cin >> datasecim;
		if (datasecim == '1')
		{
			postorderTara(kok1);
		}
		if (datasecim == '2')
		{
			postorderTara(kok2);
		}
		if (datasecim == '3')
		{
			postorderTara(kok3);
		}
		break;
		
	}
}

bool Agac::islemYap(char secim)
{
    bool sonlandir = false;
    switch (secim) {		//AnaMenu de hangi islemin yapilacagi seciliyor
    case 'A': case 'a':
		araMenu();		//Arama
        break;
    case 'L': case 'l':
		listeMenu();	//Listeleme
        break;
    case 'S': case 's':	//Silme
		char ogrno[30];
		char secim;
		cout << "Silinmesini istediginiz ogrenciyi giriniz:";
		cin >> ogrno;
		dataMenu("ogrenci silme islemi");
		cin >> secim;
		if (secim == '1')
		{
			ogrenciSil(ogrno, &kok1);
		}
		if (secim == '2')
		{
			ogrenciSil(ogrno, &kok2);
		}
		if (secim == '3')
		{
			ogrenciSil(ogrno, &kok3);
		}	
        break;
    case 'Y':case 'y':	//Dosyaya Yazdirma
		dataMenu("ogrenci listeleme islemi");
		cin >> secim;
		if (secim == '1')
		{
			dosyayaYaz(kok1);
		}
		if (secim == '2')
		{
			dosyayaYaz(kok2);
		}
		if (secim == '3')
		{
			dosyayaYaz(kok3);
		}
        break;
    case 'C': case 'c':	 //Programdan cikis
        cout << "Programi sonlandirmak istediğinize emin misiniz? (E/H):";  //sistemden cikar.
        cin >> secim;
        if (secim == 'E' || secim == 'e')
            sonlandir = true;
        break;
    default:
        cout << "Hata: Yanlis giris yaptiniz" << endl;             //hatali harf girilmisse uyari verir ve sisteme geri döndürür.
        cout << "Tekrar deneyiniz {A,L, S, Y, C} :";
        cin >> secim;
        sonlandir = islemYap(secim);
        break;
    }
    return sonlandir;
}

void Agac::agacKur(string dosyaAd,Ogrenci **kok)
{
	Ogrenci ogr;
	char satirAl[75];
	char* ptr;
	ifstream dosya1(dosyaAd);			//ifstream ile "data1.txt" dosyasını okumak için dosyayı açma
	dosya1.getline(satirAl, 75);
	for (int i = 0;i < 75;i++) {				//satır sonundaki '\r' karakterini, '\0' karakteri ile değiştirme
		if (satirAl[i] == '\r')
			satirAl[i] = '\0';
	}
	while (dosya1) {					//while döngüsü içinde dosyayı sonuna kadar satır satır okuma ve okunan satırları boşluklara göre parçalayıp, 
		ptr = strtok(satirAl, "\t");		//	j sayacının değerine göre değişkenlere atama
		int j = 0;
		while (ptr != NULL) {
			if (j == 0)
				strcpy(ogr.ogrno, ptr);
			if (j == 1)
				strcpy(ogr.ad, ptr);
			if (j == 2)
				strcpy(ogr.soyad, ptr);
			if (j == 3) {			//bir ad ve bir soyad okunmasına rağmen satır sonu gelmedi ise öğrencinin iki adı var demektir,
				strcat(ogr.ad, " ");		//	bu iki ad arada bir boşluk bırakılarak öğrenci değişkenine atanır ve soyadı tekrar okunur
				strcat(ogr.ad,ogr.soyad);
				strcpy(ogr.soyad, ptr);
			}
			ptr = strtok(NULL, " ");
			j++;
		}
		ekle(kok,ogr.ogrno,ogr.ad,ogr.soyad);	//dosyadan okunan ögrenciler agac a eklenir
		dosya1.getline(satirAl, 75);
		for (int i = 0;i < 75;i++) {
			if (satirAl[i] == '\r')
				satirAl[i] = '\0';
		}
	}
	dosya1.close();
}

void Agac::ekle(Ogrenci**kok,char *ogrNo,char *Ad,char *Soyad)
{
	bool eklendi = false;
	Ogrenci* tara; Ogrenci* yeni = new Ogrenci; 
	tara = *kok;		//tara bir onceki kisinin verilerini tutar ve karsilasitrma yapar
	int karsilas;
	strcpy(yeni->ogrno, ogrNo);
	strcpy(yeni->ad, Ad);
	strcpy(yeni->soyad, Soyad);
	yeni->sol = NULL; yeni->sag = NULL;		//sag ve sol dallar NULL a esitleniyor

	if (*kok == NULL) {		//Eger hic kok eklenmemisse ilk ogrenciyi koke ekler
		*kok= yeni;
		return;
	}
	while ((tara != NULL) && (!eklendi))	//Agac yapisini listeler
	{
		karsilas = strcmp(yeni->ogrno, tara->ogrno);	//yeni->ogrno buyuk mu tara->ogrno kontrol eder ve sayi dondurur
		if (karsilas<0)									//tara->ogrno daha buyuk ve kisiyi sol dala atar
		{
			if (tara->sol != NULL) { tara = tara->sol; }	//sol dali bos bir deger gorene kadar kontrol eder
			else
			{
				tara->sol = yeni;
				eklendi = true;
			}
		}
		else if (karsilas>0)		//yeni->ogrno daha buyuk ve kisisyi saga atar
		{
			if (tara->sag != NULL) { tara = tara->sag; }//sag dali bos deger gorene kadar kontrol eder
			else
			{
				tara->sag = yeni;
				eklendi = true;
			}
		}
		else { cout << "Kopya" << endl;  return; }//yeni->ogrno=tara->ogrno ise ogrenci zaten var demektir
	}
}
void Agac::inorderTara(Ogrenci* p)
{
	if (p)		//Agacta ilk sol sonra kok sonra sagdaki kisiyi yazdirir.
	{
		inorderTara(p->sol);
		cout << p->ogrno << " " << p->ad <<" "<<p->soyad << endl;
		inorderTara(p->sag);
	}
}
void Agac::preorderTara(Ogrenci* p)
{
	if (p)		//Agacta ilk kok sonra sol sonra sagdaki kisiyi yazdirir
	{
		cout << p->ogrno << " " << p->ad << " " << p->soyad << endl;
		preorderTara(p->sol);
		preorderTara(p->sag);
	}	
}
void Agac::postorderTara(Ogrenci *p)
{
	if (p)		//Agacta ilk sol sonra sag sonra da kokteki degeri yazdirir
	{
		postorderTara(p->sol);
		postorderTara(p->sag);
		cout << p->ogrno << " " << p->ad << " " << p->soyad << endl;
	}
}
void Agac::ilkDerinlikAra(Ogrenci* kok) 
{
	int sayac = 1;		//kisiyi kacinci aramada buldugunu ogrenmek icin
	char ogrno[30];
	cout << "Ogrenci numarasini giriniz:";
	cin >> ogrno;		//silinecek ogrencinin numarasi aliniyor.
	Ogrenci* ogr;
	stack <Ogrenci*>yigin;	//yigin adinda bir stack olusturluyor
	yigin.push(kok);		//Agactaki elemanlar yigina gonderiliyor
	while (!yigin.empty())
	{
		ogr = yigin.top();
		yigin.pop();
		if (strcmp(ogrno, ogr->ogrno) == 0)//ogrno aranan kayit ile karsilasitirlir
		{
			cout << ogr->ogrno << " " << ogr->ad << " " << ogr->soyad << endl;
			cout << sayac << endl;
			return;
		}
		if (ogr->sag)
			yigin.push(ogr->sag);//sag da eleman varsa yigina eklenir
		if (ogr->sol)
			yigin.push(ogr->sol);//solda eleman varsa yigina eklenir
		sayac++; //Her aramadan sonra sayac artar ve kacinci adimda buldugunu hesaplar
	}
}
void Agac::ilkGenislikAra(Ogrenci*kok)
{
	int sayac = 1;
	char ogrno[30];
	cout << "Ogrenci numarasini giriniz:";
	cin >> ogrno;
	Ogrenci* ogr;
	queue <Ogrenci*>kuyruk;	//kuyruk tanimlanir
	kuyruk.push(kok);		//kok dugumu kuyruga atilir
	while (!kuyruk.empty())
	{
		ogr = kuyruk.front();	//kuyrugun basindaki kayit
		kuyruk.pop();
		if (strcmp(ogrno, ogr->ogrno) == 0)	//ogrno aranan kayit ile karsilastirilir
		{
			cout << ogr->ogrno << " " << ogr->ad << " " << ogr->soyad << endl;
			cout << sayac<<endl ;
			return;
		}
		if (ogr->sol)
			kuyruk.push(ogr->sol);	//solda eleman varsa kuyruga eklenir
		if (ogr->sag)
			kuyruk.push(ogr->sag);	//sagda eleman varsa kuyruga eklenir
		sayac++;	//Her aramadan sonra sayac artar ve kacinci adimda buldugunu hesaplar
	}

}
int Agac::ara(char* ogrno,Ogrenci *kok)
{
	Ogrenci* tara;
	tara = kok;
	int bulunan=0;
	int karsilas = 0;
	while (tara && !bulunan)
	{
		karsilas=strcmp(ogrno, tara->ogrno);	//silinmesini istedigimiz ogrenciyi bulur
		if (karsilas < 0)	//ogrno kokten kucukse sola gider
		{
			tara = tara->sol;
		}
		else if (karsilas > 0)//ogrno kokten buyukse saga gider
		{
			tara = tara->sag;
		}
		else // esit ise ogrenci bulunur
		{
			cout << tara->ogrno << endl;
			bulunan++;
		}
	}
	return bulunan;
}
void Agac::ogrenciSil(char*ogrno,Ogrenci **kok)
{
	int ogrSayi = ara(ogrno,*kok);	//ara fonskiyonu ile ogrencinin agacta olup olmadıgına bakılır
	if (ogrSayi == 0)
	{
		cout << "Yanlis ogrenci girdiniz"<<endl;
	}
	else
	{
		sil(ogrno, kok);
	}
}
void Agac::sil(char*ogrNo,Ogrenci**kok)
{
	Ogrenci* tara, *ust;
	tara = *kok;
	ust = nullptr;
	bool bulundu = false;
	char yon = 'k';
	while (tara && !bulundu)
	{
		int karsilas = strcmp(ogrNo, tara->ogrno);
		if (karsilas < 0)//ogrencinin solda mi sagdami oldugunu bulur
		{
			ust = tara;
			yon = 'l';
			tara = tara->sol;
		}
		else if (karsilas > 0)
		{
			ust = tara;
			yon = 'r';
			tara = tara->sag;
		}
		else{bulundu = true;}
	}
		if (bulundu)
		{
			if (yon == 'l')	//girilen sayisolda ise
				sil1(&ust->sol);
			else if (yon == 'r') //girilen sayi sagda ise
				sil1(&ust->sag);
			else
				sil1(kok); //girilen sayi kok ise
			cout << "Kayit basarili bir sekilde silindi" << endl;
		}
		else
		{
			cout << "silinecek kayit bulunamadi" << endl;
		}
}

void Agac::sil1(Ogrenci** p)
{
	Ogrenci* r, * q;
	r = *p;
	if (r == NULL)
		return;
	else if (r->sag == NULL)//silenecek elemanin sagi bos ise elemani siler ve sol cocugu atar
	{
			*p = r->sol;
			delete r;	
	}
	else if (r->sol==NULL)//silenecek elemanin solu bos ise elemani siler ve sag cocugu atar
	{
			*p = r->sag;
			delete r;
	}
	else
	{
		for (q = r->sag;!q->sol;q = q->sol) //silincek elemanin 2 cocugu var ise 
		{
			q->sol = r->sol;
		}
		*p = r->sag;
		delete r;
	}
}
void Agac::agacBosalt(Ogrenci* p)
{
	if (p)		//Agactaki tutulan bellekleri siler
	{
		if (p->sol != NULL) {
			agacBosalt(p->sol);
			p->sol = NULL;
		}
		if (p->sag != NULL) {
			agacBosalt(p->sag);
			p->sag = NULL;
		}
		delete p;
	}
}
void Agac::preorderYazdir(Ogrenci* p,ofstream &dosya)
{
	if (p)		//dosyaya yazma islemi icin kullanilir
	{
		dosya << p->ogrno << " " << p->ad << " " << p->soyad << endl;
		preorderYazdir(p->sol, dosya);
		preorderYazdir(p->sag, dosya);
	}

}
void Agac::dosyayaYaz(Ogrenci*kok)
{
	ofstream dosya("cikti.txt");
	preorderYazdir(kok, dosya);	//Dosyaya preorder istenilen datayi preorder seklinde yazar
	dosya.close();
}
