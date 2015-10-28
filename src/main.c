/*
		.# Aile Hekimi Yaz�l�m�
		     .<    Do�an DERYA    .>
		 	 .<    g131210016     .>
             .<  Bilg. M�h. ��.A  .>		

*/
#include <stdio.h>
#include <conio.h>
#include <locale.h>
#include <stdlib.h>

const char* database = "db.txt";
const char* databasemuayene = "dbm.txt";


struct Hasta
{
	char tckimlik[20];
	char adi[50];
	char soyadi[50];
	int cinsiyet; // 0 = bay 1 = bayan
	char babaadi[50];
	char anaadi[50];
	char dogumtarihi[20];
	char kangrubu[10];
	char adres[100];
	int sgkdurumu; // 0 = sgk yok 1 = ssk 2= emekli sandigi 3= bagkur
	
	// Arama sisteminde t�rk�e karakter desteklesin diye
	char adiara[50];
	char soyadiara[50];
	char adresara[100];
};
struct Hasta YHasta[200];
int ToplamHasta = 0;

struct Muayene
{
	int hastaid;
	char teshisler[100];
	char recete[100];
	char muayenetarihi[50];
};
struct Muayene YMuayene[200];
int ToplamMuayene = 0;

int AnaMenu(int bas)
{
	int secili = bas;
	system("color 1f");                       // Program�m�z�n ana rengini de�i�tirdik
	
	while(1)
	{
		system("cls");                        // �nceden yaz�lm�� metinleri yok ettik

		printf("\n\n\t\t     #######################################\n");
		printf("\t\t    -#        Aile Hekimi Sistemine        #-\n");
		printf("\t\t     #             Ho�geldiniz..           #\n");
		printf("\t\t    -#-------------------------------------#-\n");
		printf("\t\t     #     Men�deki elemanlar� yukar� ve   #\n");
		printf("\t\t    -#   a�a�� tu�lar�yla se�ebilirsiniz   #-\n");
		printf("\t\t     # se�imi yapt�ktan sonra entere bas�n #\n");
		printf("\t\t    -#-------------------------------------#-\n");
		printf("\t\t     #  1. %c Hasta Ekle                    #\n",(secili == 0)? 26 : ' ');
		printf("\t\t     #  2. %c Hasta Kartlar�                #\n",(secili == 1)? 26 : ' ');
		printf("\t\t    -#  3. %c Hasta Arama                   #-\n",(secili == 2)? 26 : ' ');
		printf("\t\t     #  4. %c Genel Raporlar                #\n",(secili == 3)? 26 : ' ');
		printf("\t\t     #  5. %c Ekstra                        #\n",(secili == 4)? 26 : ' ');
		printf("\t\t    -#  6. %c ��k��                         #-\n",(secili == 5)? 26 : ' ');
		printf("\t\t     #-------------------------------------#\n");
		printf("\t\t    -#    ESC tu�u ilede ��kabilirsiniz    #-\n");
		printf("\t\t     #-------------------------------------#\n");
		printf("\t\t     #######################################\n");
		
		int tus = getch();
		if(tus == 80)                        // A�a�� Tu�u
			(secili < 5) ? (secili++) : 0; 
		else if(tus == 72)                   // Yukar� Tu�u
			(secili > 0) ? (secili--) : 0; 
		else if(tus == 13)                   // Enter tu�u 
			return secili;
		else if(tus == 27)                   // ESC tu�u
		{
			secili = 6;
			return secili;
		}
		else if((47 < tus) && (tus < 58))   // H�zl� say� giri�i
		{
			secili = tus - 49;              // 48 ascii karakterinde 0'a denk geliyor. Biz 1'e bas�ld���nda ilkini yazmas�n� istiyoruz
			return secili;                  // ilk icin secili = 0 olmas� gerekiyorsa ve tu�lardan 1'in de�eri 49'sa 49-49=0
		}
	}
}

/*
	- Uyar( mesaj )
	
	Ekrana 
*/
int Uyar(char* a)
{
	return Uyarsec(a,"Evet","Hay�r","       ","          ","         ");
}

int Uyarsec(char* a, char* b, char* c, char* spcb,char* spcc,char* spce)
{
	int secili=1;
	system("color 2F");                       // Program�m�z�n ana rengini de�i�tirdik
	
	while(1)
	{
		system("cls");        		          // �nceden yaz�lm�� metinleri yok ettik
		
		printf("\n\n\t\t     #######################################\n");
		printf("\t\t    -#         Aile Hekimi Sistemi         #-\n");
		printf("\t\t     #-------------------------------------#\n");
		printf("\t\t    -#%s#-\n",a);
		printf("\t\t     #-------------------------------------#\n");
		printf("\t\t    -#   ��lemini Yapmak istedi�inizden    #-\n");
		printf("\t\t     #             emin misiniz?           #\n");
		printf("\t\t    -#%s%c%s%s%c%s%s#-\n",spcb,(secili == 0)? 26 : ' ',b,spcc,(secili == 1)? 26 : ' ',c,spce);
		printf("\t\t     #######################################\n");
		
		int tus = getch();
		if(tus == 77)                        // Sa� Tu�u
			(secili < 1) ? (secili++) : 0; 
		else if(tus == 75)                   // Sol Tu�u
			(secili > 0) ? (secili--) : 0;
		else if(tus == 13)  				 // Enter Tu�u
			return secili;
		else if(tus == 27)                   // ESC tu�u (Hay�r olarak ge�er)
		{
			secili = 1;
			return secili;
		}
	}
}


void Bilgilendir(char* a)
{
	system("color F0");                       // Program�m�z�n ana rengini de�i�tirdik
	
	while(1)
	{
		system("cls");        		          // �nceden yaz�lm�� metinleri yok ettik
		
		printf("\n\n\t\t     #######################################\n");
		printf("\t\t    -#         Aile Hekimi Sistemi         #-\n");
		printf("\t\t     #-------------------------------------#\n");
		printf("\t\t    -#%s#-\n",a);
		printf("\t\t     #-------------------------------------#\n");
		printf("\t\t    -#              %c  Tamam               #-\n",26);
		printf("\t\t     #######################################\n");
		
		int tus = getch();
		if((tus == 13) || (tus == 27))        // Enter veya ESC tu�una bas�ld���nda ��ks�n
			return;
	}
}

void YeniMuayene(int id)
{
	system("color f1");                   // Program�m�z�n ana rengini de�i�tirdik
	system("cls");        		          // �nceden yaz�lm�� metinleri yok ettik
	
	printf("\n\n\t\t     #######################################\n");
	printf("\t\t    -#          Aile Hekimi Sistemi        #-\n");
	printf("\t\t     #             Muayene Ekle            #\n");
	printf("\t\t    -#-------------------------------------#-\n");
	printf("######################                                     #####################\n");
	
	struct Muayene M;

	printf("    # Muayene Te�hislerini Giriniz: ");
	scanf(" %[^\n]", M.teshisler);
	
	printf("    # Muayene Re�eteyi giriniz: ");
	scanf(" %[^\n]", M.recete);
	
	printf("    # Muayene Tarihini giriniz: ");
	scanf(" %[^\n]", M.muayenetarihi);
	
	if(MuayeneKaydet(id, M.teshisler, M.recete, M.muayenetarihi))
	{
		Bilgilendir(" Muayene kay�d� ba�ar�yla tamamland� ");
		return;
	}
	Bilgilendir("    Muayene kay�d� tamamlanamad�!    ");
	
}

void HastaEkle()
{
	system("color f1");                   // Program�m�z�n ana rengini de�i�tirdik
	system("cls");        		          // �nceden yaz�lm�� metinleri yok ettik
	
	printf("\n\n\t\t     #######################################\n");
	printf("\t\t    -#          Aile Hekimi Sistemi        #-\n");
	printf("\t\t     #             Hasta Ekle              #\n");
	printf("\t\t    -#-------------------------------------#-\n");
	printf("######################                                     #####################\n");
	
	struct Hasta H;
	int sgk;
	
	printf("    # Hasta Ad�n� Giriniz: ");
	scanf(" %[^\n]", H.adi);
	
	printf("    # Hasta Soyad�n� Giriniz: ");
	scanf(" %[^\n]", H.soyadi);
	
	printf("    # Hasta'n�n T.C. Kimlik Numaras�n� Giriniz: ");
	scanf(" %[^\n]", H.tckimlik);
	
	printf("    # Hasta'n�n Cinsiyetini Giriniz(e/k) : ");
	cinsiyet_gir:
	switch(putch(getch()))
	{
		case 'E':
		case 'e':
			H.cinsiyet=1;
			break;
			
		case 'K':	
		case 'k':
			H.cinsiyet=0;
			break;
		
		default:
			printf("\nGe�ersiz Girdiniz Yeniden girin! : ");
			goto cinsiyet_gir;
	}
	
	printf("\n    # Hasta'n�n do�um tarihini girin (2 Haziran 1963): ");
	scanf(" %[^\n]",H.dogumtarihi);
	
	printf("    # Hasta'n�n Ana ad�n� Giriniz: ");
	scanf(" %[^\n]",H.anaadi);
	
	printf("    # Hasta'n�n Baba ad�n� Giriniz: ");
	scanf(" %[^\n]",H.babaadi);
	
	printf("    # Hasta'n�n Kan Grubunu Giriniz (A rh+): ");
	scanf(" %[^\n]",H.kangrubu);
	
	
	printf("\n    		1. Ssk \n");
	printf("    		2. Emekli Sand��� \n");
	printf("    		3. Ba�-kur \n");
	printf("    		4. Yok \n");
	printf("    		5. Bilinmiyor \n");
	printf("    # Hasta'n�n Sosyal G�venlik Kurumunu Giriniz : ");
	
	sgk_gir:
	sgk = putch(getch());
	switch(sgk)
	{
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
			H.sgkdurumu = sgk-48; // ASCII 'de '1' = 49 ise 49-48= 1 olacakt�r
			break;
		default:
			printf("\nGe�ersiz Girdiniz Yeniden girin! : ");
			goto sgk_gir;
			break;
	}
	
	printf("\n    # Hasta'n�n Adresini Giriniz : ");
	scanf(" %[^\n]",H.adres);
	
	if(Uyarsec("        Kay�d� sisteme ge�irme       ","Ge�ir","Ge�irme","       ","       ","         "))
	{
		Bilgilendir("     Hasta kay�d� iptal edildi!      ");
		return;
	}
	
	FILE *fs;
	fs = fopen(database, "a");
	if(fs != NULL)
	{
		fprintf(fs, "%s, %s, %s, %d, %s, %s, %s, %s, %d, %s,\n",H.adi,H.soyadi,H.tckimlik,H.cinsiyet,H.dogumtarihi,H.anaadi,H.babaadi,H.kangrubu,H.sgkdurumu,H.adres);
		fclose(fs);
		
		Bilgilendir("  Hasta kay�d� ba�ar�yla tamamland�! ");
		return;
	}
	
	Bilgilendir("   Hasta kay�d� hatayla sonu�land�!  ");
	
	
	
}

int MuayeneKaydet(int hastaid, char* teshisler, char* recete, char* muayenetarihi)
{
	FILE *fs;
	fs = fopen(databasemuayene, "a");
	if(fs != NULL)
	{
		fprintf(fs, "%d, %s, %s, %s,\n", hastaid, teshisler, recete, muayenetarihi);
		fclose(fs);
		return 1;
	}
	return 0;
}

void MuayeneYukle()
{
	FILE* fs;
	fs = fopen(databasemuayene,"r");
	
	ToplamMuayene = 0;
	
	int idx = 0;
	if(fs != NULL)
	{
		while(!feof(fs))
		{
			fscanf(fs,"%[^,]%*c %[^,]%*c %[^,]%*c %[^,]%*c\n", &YMuayene[idx].hastaid, &YMuayene[idx].teshisler, &YMuayene[idx].recete, &YMuayene[idx].muayenetarihi);
			YMuayene[idx].hastaid -= 48;
			
			ToplamMuayene++;
			idx++;
			
		}
		getch();
	}
}

void HastalariYukle()
{
	struct Hasta H;
	FILE* fs;
	fs = fopen(database, "r");
	
	ToplamHasta = 0;
	
	int idx = 0;
	if(fs != NULL)
	{
		while(!feof(fs))
		{
			fscanf(fs,"%[^,]%*c %[^,]%*c %[^,]%*c %[^,]%*c %[^,]%*c %[^,]%*c %[^,]%*c %[^,]%*c %[^,]%*c %[^,]%*c\n",&YHasta[idx].adi,&YHasta[idx].soyadi,&YHasta[idx].tckimlik,&YHasta[idx].cinsiyet,&YHasta[idx].dogumtarihi,&YHasta[idx].anaadi,&YHasta[idx].babaadi,&YHasta[idx].kangrubu,&YHasta[idx].sgkdurumu,&YHasta[idx].adres);
			YHasta[idx].cinsiyet-=48;
			YHasta[idx].sgkdurumu-=48;
			
			strcpy(YHasta[idx].adiara,YHasta[idx].adi);
			strcpy(YHasta[idx].soyadiara,YHasta[idx].soyadi);
			strcpy(YHasta[idx].adresara,YHasta[idx].adres);
			
			ToplamHasta++;
			
			// T�rk�e karakterlerini tek tek d�zeltmeye yarayan muazzam fonksiyonumuz :D
			int i=0;
			for(i=0;i<100;i++)
			{
				if(YHasta[idx].adres[i]==-115) 
					YHasta[idx].adres[i]='�';
				if(YHasta[idx].adres[i]==-89) 
					YHasta[idx].adres[i]='�';
				if(YHasta[idx].adres[i]==-90) 
					YHasta[idx].adres[i]='�';
				if(YHasta[idx].adres[i]==-127) 
					YHasta[idx].adres[i]='�';
				if(YHasta[idx].adres[i]==-102) 
					YHasta[idx].adres[i]='�';
				if(YHasta[idx].adres[i]==-97) 
					YHasta[idx].adres[i]='�';
				if(YHasta[idx].adres[i]==-98) 
					YHasta[idx].adres[i]='�';
				if(YHasta[idx].adres[i]==-104) 
					YHasta[idx].adres[i]='�';
				if(YHasta[idx].adres[i]==-108) 
					YHasta[idx].adres[i]='�';
				if(YHasta[idx].adres[i]==-103) 
					YHasta[idx].adres[i]='�';
				if(YHasta[idx].adres[i]==-121) 
					YHasta[idx].adres[i]='�';
				if(YHasta[idx].adres[i]==-128) 
					YHasta[idx].adres[i]='�';
				if(i<50)
				{
					if(YHasta[idx].adi[i]==-115) 
						YHasta[idx].adi[i]='�';
					if(YHasta[idx].adi[i]==-89) 
						YHasta[idx].adi[i]='�';
					if(YHasta[idx].adi[i]==-90) 
						YHasta[idx].adi[i]='�';
					if(YHasta[idx].adi[i]==-127)
						YHasta[idx].adi[i]='�';
					if(YHasta[idx].adi[i]==-102) 
						YHasta[idx].adi[i]='�';
					if(YHasta[idx].adi[i]==-97) 
						YHasta[idx].adi[i]='�';
					if(YHasta[idx].adi[i]==-98) 
						YHasta[idx].adi[i]='�';
					if(YHasta[idx].adi[i]==-104) 
						YHasta[idx].adi[i]='�';
					if(YHasta[idx].adi[i]==-108) 
						YHasta[idx].adi[i]='�';
					if(YHasta[idx].adi[i]==-103) 
						YHasta[idx].adi[i]='�';
					if(YHasta[idx].adi[i]==-121) 
						YHasta[idx].adi[i]='�';
					if(YHasta[idx].adi[i]==-128) 
						YHasta[idx].adi[i]='�';
					
					if(YHasta[idx].soyadi[i]==-115) 
						YHasta[idx].soyadi[i]='�';
					if(YHasta[idx].soyadi[i]==-89) 
						YHasta[idx].soyadi[i]='�';
					if(YHasta[idx].soyadi[i]==-90) 
						YHasta[idx].soyadi[i]='�';
					if(YHasta[idx].soyadi[i]==-127) 
						YHasta[idx].soyadi[i]='�';
					if(YHasta[idx].soyadi[i]==-102) 
						YHasta[idx].soyadi[i]='�';
					if(YHasta[idx].soyadi[i]==-97) 
						YHasta[idx].soyadi[i]='�';
					if(YHasta[idx].soyadi[i]==-98) 
						YHasta[idx].soyadi[i]='�';
					if(YHasta[idx].soyadi[i]==-104) 
						YHasta[idx].soyadi[i]='�';
					if(YHasta[idx].soyadi[i]==-108) 
						YHasta[idx].soyadi[i]='�';
					if(YHasta[idx].soyadi[i]==-103) 
						YHasta[idx].soyadi[i]='�';
					if(YHasta[idx].soyadi[i]==-121) 
						YHasta[idx].soyadi[i]='�';
					if(YHasta[idx].soyadi[i]==-128) 
						YHasta[idx].soyadi[i]='�';
					
					if(YHasta[idx].dogumtarihi[i]==-115) 
						YHasta[idx].dogumtarihi[i]='�';
					if(YHasta[idx].dogumtarihi[i]==-89) 
						YHasta[idx].dogumtarihi[i]='�';
					if(YHasta[idx].dogumtarihi[i]==-90) 
						YHasta[idx].dogumtarihi[i]='�';
					if(YHasta[idx].dogumtarihi[i]==-127) 
						YHasta[idx].dogumtarihi[i]='�';
					if(YHasta[idx].dogumtarihi[i]==-102) 
						YHasta[idx].dogumtarihi[i]='�';
					if(YHasta[idx].dogumtarihi[i]==-97) 
						YHasta[idx].dogumtarihi[i]='�';
					if(YHasta[idx].dogumtarihi[i]==-98) 
						YHasta[idx].dogumtarihi[i]='�';
					if(YHasta[idx].dogumtarihi[i]==-104) 
						YHasta[idx].dogumtarihi[i]='�';
					if(YHasta[idx].dogumtarihi[i]==-108) 
						YHasta[idx].dogumtarihi[i]='�';
					if(YHasta[idx].dogumtarihi[i]==-103) 
						YHasta[idx].dogumtarihi[i]='�';
					if(YHasta[idx].dogumtarihi[i]==-121) 
						YHasta[idx].dogumtarihi[i]='�';
					if(YHasta[idx].dogumtarihi[i]==-128) 
						YHasta[idx].dogumtarihi[i]='�';
					
					if(YHasta[idx].anaadi[i]==-115) 
						YHasta[idx].anaadi[i]='�';
					if(YHasta[idx].anaadi[i]==-89) 
						YHasta[idx].anaadi[i]='�';
					if(YHasta[idx].anaadi[i]==-90)
						 YHasta[idx].anaadi[i]='�';
					if(YHasta[idx].anaadi[i]==-127) 
						YHasta[idx].anaadi[i]='�';
					if(YHasta[idx].anaadi[i]==-102) 
						YHasta[idx].anaadi[i]='�';
					if(YHasta[idx].anaadi[i]==-97) 
						YHasta[idx].anaadi[i]='�';
					if(YHasta[idx].anaadi[i]==-98) 
						YHasta[idx].anaadi[i]='�';
					if(YHasta[idx].anaadi[i]==-104) 
						YHasta[idx].anaadi[i]='�';
					if(YHasta[idx].anaadi[i]==-108) 
						YHasta[idx].anaadi[i]='�';
					if(YHasta[idx].anaadi[i]==-103) 
						YHasta[idx].anaadi[i]='�';
					if(YHasta[idx].anaadi[i]==-121) 
						YHasta[idx].anaadi[i]='�';
					if(YHasta[idx].anaadi[i]==-128) 
						YHasta[idx].anaadi[i]='�';
					
					if(YHasta[idx].babaadi[i]==-115) 
						YHasta[idx].babaadi[i]='�';
					if(YHasta[idx].babaadi[i]==-89) 
						YHasta[idx].babaadi[i]='�';
					if(YHasta[idx].babaadi[i]==-90) 
						YHasta[idx].babaadi[i]='�';
					if(YHasta[idx].babaadi[i]==-127) 
						YHasta[idx].babaadi[i]='�';
					if(YHasta[idx].babaadi[i]==-102) 
						YHasta[idx].babaadi[i]='�';
					if(YHasta[idx].babaadi[i]==-97) 
						YHasta[idx].babaadi[i]='�';
					if(YHasta[idx].babaadi[i]==-98) 
						YHasta[idx].babaadi[i]='�';
					if(YHasta[idx].babaadi[i]==-104) 
						YHasta[idx].babaadi[i]='�';
					if(YHasta[idx].babaadi[i]==-108) 
						YHasta[idx].babaadi[i]='�';
					if(YHasta[idx].babaadi[i]==-103) 
						YHasta[idx].babaadi[i]='�';
					if(YHasta[idx].babaadi[i]==-121) 
						YHasta[idx].babaadi[i]='�';
					if(YHasta[idx].babaadi[i]==-128) 
						YHasta[idx].babaadi[i]='�';
				}
			}
			idx++;
		}
	}
	else getch();
	fclose(fs);
}

void HastaKarti(int basnok)
{
	int aktif=basnok;
	
	if(ToplamHasta == 0)
	{
		Bilgilendir("       �uan hasta say�s� 0'd�r       ");
	}
	
	while(1)
	{
		system("color f1");                   // Program�m�z�n ana rengini de�i�tirdik
		system("cls");       		          // �nceden yaz�lm�� metinleri yok ettik
		
		printf("\n\n\t\t     #######################################\n");
		printf("\t\t    -#          Aile Hekimi Sistemi        #-\n");
		printf("\t\t     #          Hasta Kart� [%.2d/%.2d]        #\n",aktif+1,ToplamHasta);
		printf("\t\t    -#-------------------------------------#-\n");
		printf("######################                                     #####################\n\n");
		printf("    # Hasta Kay�t s�ras�: %d\n",aktif+1);
		printf("    # Hasta Ad� Soyad�: %s %s\n",YHasta[aktif].adi,YHasta[aktif].soyadi);
		printf("    # Hasta TC Kimlik: %s\n",YHasta[aktif].tckimlik);
		printf("    # Hasta Cinsiyeti %s\n",(YHasta[aktif].cinsiyet==1?"Erkek":"Kad�n"));
		printf("    # Hasta Do�um Tarihi: %s\n",YHasta[aktif].dogumtarihi);
		printf("    # Hasta Ana Ad�: %s\n",YHasta[aktif].anaadi);
		printf("    # Hasta Baba Ad�: %s\n",YHasta[aktif].babaadi);
		printf("    # Hasta Kan Grubu: %s\n",YHasta[aktif].kangrubu);
		printf("    # Hasta Sgk: %s\n",YHasta[aktif].sgkdurumu==1?"SSK":YHasta[aktif].sgkdurumu==2?"Emekli Sand���":YHasta[aktif].sgkdurumu==3?"Ba�-Kur":YHasta[aktif].sgkdurumu==4?"Yok":"Bilinmiyor");
		printf("    # Hasta Adresi: %s\n",YHasta[aktif].adres);
		
		printf("\n\n--------------------------------------------------------------------------------");
		printf("\n   %csol kart      %csa� kart       %cg�ncelle    (e)yeni mu.   %chastay� sil   ",27,26,24,25);
		
		int tus = getch();
		if(tus == 77)                        // Sa� Tu�u
			(aktif < ToplamHasta-1) ? (aktif++) : 0; 
		else if(tus == 75)                   // Sol Tu�u
			(aktif > 0) ? (aktif--) : 0;
		else if(tus == 13)                   // Enter Tu�u
		{
			YeniMuayene(aktif);
			return;
		}
		else if(tus == 72)					 // Yukar� tu�u  (g�ncelle)
		{
			HastaGuncelle(aktif);
		}
		else if(tus == 80)                   // A�a�� tu�u  (hasta sil)
		{
			if(!Uyar("             Hasta Silme             "))
			{
				FILE *fs;
				fs = fopen(database, "w");
				if(fs != NULL)
				{
					int i=0;
					for(i=0;i<ToplamHasta;i++)
					{
						if(i == aktif) continue;
						fprintf(fs, "%s, %s, %s, %d, %s, %s, %s, %s, %d, %s,\n",YHasta[i].adi,YHasta[i].soyadi,YHasta[i].tckimlik,YHasta[i].cinsiyet,YHasta[i].dogumtarihi,YHasta[i].anaadi,YHasta[i].babaadi,YHasta[i].kangrubu,YHasta[i].sgkdurumu,YHasta[i].adres);
					}
					fclose(fs);
					
					Bilgilendir("       Hasta ba�ar�yla silindi!      ");
					return;
					
				}
			}
		}
		else if(tus == 27)                   // ESC tu�u (Ana Men�ye d�n)
			return;
	}
	
}

void MuayeneBilgisi(int id)
{
	int HMuSay=0;
	int i;
	for(i=0;i<200;i++) if(YMuayene[i].hastaid == id) HMuSay++;
	
	if(HMuSay == 0)
	{
		Bilgilendir(" Bu hasta daha �nce muayene olmam��  ");
		return;
	}

	while(1)
	{
		system("color f1");                   // Program�m�z�n ana rengini de�i�tirdik
		system("cls");       		          // �nceden yaz�lm�� metinleri yok ettik
		
		printf("\n\n\t\t     #######################################\n");
		printf("\t\t    -#          Aile Hekimi Sistemi        #-\n");
		printf("\t\t     #          Hasta Muayene Kart�        #\n");
		printf("\t\t    -#-------------------------------------#-\n");
		printf("######################                                     #####################\n\n");
		
	
		for(i=0;i<200;i++)
		{
			if(YMuayene[i].hastaid == id)
			{
				printf("    #   Muayene Kayd�: %d\n",i);
				printf("    #   Muayene Te�hisler: %s\n",YMuayene[id].teshisler);
				printf("    #   Muayene Tarihi: %s\n",YMuayene[id].muayenetarihi);
				printf("    #   Re�ete bilgisi: %s\n\n",YMuayene[id].recete);
			}
		}
		int tus = getch();
		if(tus == 27)                   // ESC tu�u (Hasta kart�na d�n)
			return;
	}
}


int HastaArama()
{
	git_hasta_arama:
	system("color f1");                   // Program�m�z�n ana rengini de�i�tirdik
	system("cls");       		          // �nceden yaz�lm�� metinleri yok ettik
		
	printf("\n\n\t\t     #######################################\n");
	printf("\t\t    -#          Aile Hekimi Sistemi        #-\n");
	printf("\t\t     #              Hasta Arama            #\n");
	printf("\t\t    -#-------------------------------------#-\n");
	printf("######################                                     #####################\n\n");
	
	char hastas[100];
	printf("    # Arama yaparken l�tfen sadece o hastaya ait olabilecek detaylar� kullan�n\n");
	printf("    # Hasta Ara: ");
	scanf(" %[^\n]",hastas);
	
	int i;
	for(i=0;i<ToplamHasta;i++)
	{
		if((strstr(YHasta[i].adiara,hastas) != NULL) || (strstr(YHasta[i].soyadiara,hastas) != NULL) || (strstr(YHasta[i].tckimlik,hastas) != NULL) || (strstr(YHasta[i].adresara,hastas) != NULL))
		{
			return i;
		}	
	}
	
	if(Uyar("   Hastay� Bulamad�k! :( Yeniden?    "))
	{
		return -1;
	}
	goto git_hasta_arama;
}

int Gelistiren()
{
	system("color f1");                   // Program�m�z�n ana rengini de�i�tirdik
	system("cls");       		          // �nceden yaz�lm�� metinleri yok ettik
	
	printf("\n\n\t\t     #######################################\n");
	printf("\t\t    -#          Aile Hekimi Sistemi        #-\n");
	printf("\t\t     #               Ekstra                #\n");
	printf("\t\t    -#-------------------------------------#-\n");
	printf("\t\t     #          Geli�tiren :               #\n");
	printf("\t\t    -#               co3moz                #-\n");
	printf("\t\t     #             Do�an DERYA             #\n");
	printf("\t\t    -#             Comp. Eng.              #-\n");
	printf("\t\t     #-------------------------------------#\n");
	printf("\t\t     #######################################\n");
	getch();
}

void GenelRaporlar()
{
	system("color f1");                   // Program�m�z�n ana rengini de�i�tirdik
	system("cls");       		          // �nceden yaz�lm�� metinleri yok ettik
	
	printf("\n\n\t\t     #######################################\n");
	printf("\t\t    -#          Aile Hekimi Sistemi        #-\n");
	printf("\t\t     #             Genel Raporlar          #\n");
	printf("\t\t    -#-------------------------------------#-\n");
	printf("######################                                     #####################\n");
	
	printf("    # Toplam Kay�tl� Hasta: %d\n", ToplamHasta);
	printf("    # Toplam Kay�tl� Muayene: %d", ToplamMuayene);
	
	
	getch();
}

void HastaGuncelle(int id)
{
	system("color f1");                   // Program�m�z�n ana rengini de�i�tirdik
	system("cls");        		          // �nceden yaz�lm�� metinleri yok ettik
	
	printf("\n\n\t\t     #######################################\n");
	printf("\t\t    -#          Aile Hekimi Sistemi        #-\n");
	printf("\t\t     #            Hasta G�ncelle           #\n");
	printf("\t\t    -#-------------------------------------#-\n");
	printf("######################                                     #####################\n");
	
	struct Hasta H;
	int sgk;
	
	printf("    # Hasta Ad�n� Giriniz: ");
	scanf(" %[^\n]", H.adi);
	
	printf("    # Hasta Soyad�n� Giriniz: ");
	scanf(" %[^\n]", H.soyadi);
	
	printf("    # Hasta'n�n T.C. Kimlik Numaras�n� Giriniz: ");
	scanf(" %[^\n]", H.tckimlik);
	
	printf("    # Hasta'n�n Cinsiyetini Giriniz(e/k) : ");
	cinsiyet_gir:
	switch(putch(getch()))
	{
		case 'E':
		case 'e':
			H.cinsiyet=1;
			break;
			
		case 'K':	
		case 'k':
			H.cinsiyet=0;
			break;
		
		default:
			printf("\nGe�ersiz Girdiniz Yeniden girin! : ");
			goto cinsiyet_gir;
	}
	
	printf("\n    # Hasta'n�n do�um tarihini girin (2 Haziran 1963): ");
	scanf(" %[^\n]",H.dogumtarihi);
	
	printf("    # Hasta'n�n Ana ad�n� Giriniz: ");
	scanf(" %[^\n]",H.anaadi);
	
	printf("    # Hasta'n�n Baba ad�n� Giriniz: ");
	scanf(" %[^\n]",H.babaadi);
	
	printf("    # Hasta'n�n Kan Grubunu Giriniz (A rh+): ");
	scanf(" %[^\n]",H.kangrubu);
	
	
	printf("\n    		1. Ssk \n");
	printf("    		2. Emekli Sand��� \n");
	printf("    		3. Ba�-kur \n");
	printf("    		4. Yok \n");
	printf("    		5. Bilinmiyor \n");
	printf("    # Hasta'n�n Sosyal G�venlik Kurumunu Giriniz : ");
	
	sgk_gir:
	sgk = putch(getch());
	switch(sgk)
	{
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
			H.sgkdurumu = sgk-48; // ASCII 'de '1' = 49 ise 49-48= 1 olacakt�r
			break;
		default:
			printf("\nGe�ersiz Girdiniz Yeniden girin! : ");
			goto sgk_gir;
			break;
	}
	
	printf("\n    # Hasta'n�n Adresini Giriniz : ");
	scanf(" %[^\n]",H.adres);
	
	if(Uyar("         Kay�d� g�ncelle�tir         "))
	{
		Bilgilendir("     Hasta kay�d� iptal edildi!      ");
		return;
	}
	
	YHasta[id].cinsiyet=H.cinsiyet;
	YHasta[id].sgkdurumu=H.sgkdurumu;
	int k;
	for(k=0;k<100;k++)
	{
		if(k<50)
		{
			YHasta[id].adi[k]=H.adi[k];
			YHasta[id].soyadi[k]=H.soyadi[k];
			YHasta[id].tckimlik[k]=H.tckimlik[k];
			YHasta[id].dogumtarihi[k]=H.dogumtarihi[k];
			YHasta[id].anaadi[k]=H.anaadi[k];
			YHasta[id].babaadi[k]=H.babaadi[k];
			YHasta[id].kangrubu[k]=H.kangrubu[k];
		}
		else
		{
			YHasta[id].adres[k]=H.adres[k];
		}
	}

	FILE *fs;
	fs = fopen(database, "w");
	if(fs != NULL)
	{
		int i=0;
		for(i=0;i<ToplamHasta;i++)
		{
			fprintf(fs, "%s, %s, %s, %d, %s, %s, %s, %s, %d, %s,\n",YHasta[i].adi,YHasta[i].soyadi,YHasta[i].tckimlik,YHasta[i].cinsiyet,YHasta[i].dogumtarihi,YHasta[i].anaadi,YHasta[i].babaadi,YHasta[i].kangrubu,YHasta[i].sgkdurumu,YHasta[i].adres);
		}
		fclose(fs);
		
		Bilgilendir("     Hasta ba�ar�yla g�ncellendi     ");
		return;
	}
}


int main()
{
	// �n Haz�rl�k
	int islem=0;
	system("title Aile Hekimi Sistemi"); // Program ba�l���n� De�i�tirdik
	setlocale(LC_ALL,"turkish");         // Program�m�z�n t�rk�e karakterleri desteklemesini sa�lad�k

	git_program_basi:
	// Ana Men�y� �a��ral�m
	islem = AnaMenu(islem);
	switch(islem)
	{
		//Hasta Ekle
		case 0:
			HastaEkle();
			goto git_program_basi;
			
			
		//Hasta Kartlar�
		case 1:
			HastalariYukle();
			HastaKarti(0);                //1. Hasta kart�ndan ihtibaren g�ster
			goto git_program_basi;
		
		//Hasta Arama
		case 2:
			HastalariYukle();
			int hastaid=HastaArama();       //Hasta aramas� yapt�ktan sonra
			if(hastaid != -1)
				HastaKarti(hastaid);
			goto git_program_basi;
		
		//Genel Raporlar
		case 3:
			HastalariYukle();
			MuayeneYukle();
			GenelRaporlar();
			goto git_program_basi;
		
		//Ekstra
		case 4:
			Gelistiren();
			goto git_program_basi;
			
		//��k��
		case 5:
			if(!Uyar("                ��k��?               "))
				return 0;
			else goto git_program_basi;
		
	}
	return 0;
}
