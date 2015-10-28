/*
		.# Aile Hekimi Yazılımı

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
	
	// Arama sisteminde türkçe karakter desteklesin diye
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
	system("color 1f");                       // Programımızın ana rengini değiştirdik
	
	while(1)
	{
		system("cls");                        // Önceden yazılmış metinleri yok ettik

		printf("\n\n\t\t     #######################################\n");
		printf("\t\t    -#        Aile Hekimi Sistemine        #-\n");
		printf("\t\t     #             Hoşgeldiniz..           #\n");
		printf("\t\t    -#-------------------------------------#-\n");
		printf("\t\t     #     Menüdeki elemanları yukarı ve   #\n");
		printf("\t\t    -#   aşağı tuşlarıyla seçebilirsiniz   #-\n");
		printf("\t\t     # seçimi yaptıktan sonra entere basın #\n");
		printf("\t\t    -#-------------------------------------#-\n");
		printf("\t\t     #  1. %c Hasta Ekle                    #\n",(secili == 0)? 26 : ' ');
		printf("\t\t     #  2. %c Hasta Kartları                #\n",(secili == 1)? 26 : ' ');
		printf("\t\t    -#  3. %c Hasta Arama                   #-\n",(secili == 2)? 26 : ' ');
		printf("\t\t     #  4. %c Genel Raporlar                #\n",(secili == 3)? 26 : ' ');
		printf("\t\t     #  5. %c Ekstra                        #\n",(secili == 4)? 26 : ' ');
		printf("\t\t    -#  6. %c Çıkış                         #-\n",(secili == 5)? 26 : ' ');
		printf("\t\t     #-------------------------------------#\n");
		printf("\t\t    -#    ESC tuşu ilede çıkabilirsiniz    #-\n");
		printf("\t\t     #-------------------------------------#\n");
		printf("\t\t     #######################################\n");
		
		int tus = getch();
		if(tus == 80)                        // Aşağı Tuşu
			(secili < 5) ? (secili++) : 0; 
		else if(tus == 72)                   // Yukarı Tuşu
			(secili > 0) ? (secili--) : 0; 
		else if(tus == 13)                   // Enter tuşu 
			return secili;
		else if(tus == 27)                   // ESC tuşu
		{
			secili = 6;
			return secili;
		}
		else if((47 < tus) && (tus < 58))   // Hızlı sayı girişi
		{
			secili = tus - 49;              // 48 ascii karakterinde 0'a denk geliyor. Biz 1'e basıldığında ilkini yazmasını istiyoruz
			return secili;                  // ilk icin secili = 0 olması gerekiyorsa ve tuşlardan 1'in değeri 49'sa 49-49=0
		}
	}
}

/*
	- Uyar( mesaj )
	
	Ekrana 
*/
int Uyar(char* a)
{
	return Uyarsec(a,"Evet","Hayır","       ","          ","         ");
}

int Uyarsec(char* a, char* b, char* c, char* spcb,char* spcc,char* spce)
{
	int secili=1;
	system("color 2F");                       // Programımızın ana rengini değiştirdik
	
	while(1)
	{
		system("cls");        		          // Önceden yazılmış metinleri yok ettik
		
		printf("\n\n\t\t     #######################################\n");
		printf("\t\t    -#         Aile Hekimi Sistemi         #-\n");
		printf("\t\t     #-------------------------------------#\n");
		printf("\t\t    -#%s#-\n",a);
		printf("\t\t     #-------------------------------------#\n");
		printf("\t\t    -#   İşlemini Yapmak istediğinizden    #-\n");
		printf("\t\t     #             emin misiniz?           #\n");
		printf("\t\t    -#%s%c%s%s%c%s%s#-\n",spcb,(secili == 0)? 26 : ' ',b,spcc,(secili == 1)? 26 : ' ',c,spce);
		printf("\t\t     #######################################\n");
		
		int tus = getch();
		if(tus == 77)                        // Sağ Tuşu
			(secili < 1) ? (secili++) : 0; 
		else if(tus == 75)                   // Sol Tuşu
			(secili > 0) ? (secili--) : 0;
		else if(tus == 13)  				 // Enter Tuşu
			return secili;
		else if(tus == 27)                   // ESC tuşu (Hayır olarak geçer)
		{
			secili = 1;
			return secili;
		}
	}
}


void Bilgilendir(char* a)
{
	system("color F0");                       // Programımızın ana rengini değiştirdik
	
	while(1)
	{
		system("cls");        		          // Önceden yazılmış metinleri yok ettik
		
		printf("\n\n\t\t     #######################################\n");
		printf("\t\t    -#         Aile Hekimi Sistemi         #-\n");
		printf("\t\t     #-------------------------------------#\n");
		printf("\t\t    -#%s#-\n",a);
		printf("\t\t     #-------------------------------------#\n");
		printf("\t\t    -#              %c  Tamam               #-\n",26);
		printf("\t\t     #######################################\n");
		
		int tus = getch();
		if((tus == 13) || (tus == 27))        // Enter veya ESC tuşuna basıldığında çıksın
			return;
	}
}

void YeniMuayene(int id)
{
	system("color f1");                   // Programımızın ana rengini değiştirdik
	system("cls");        		          // Önceden yazılmış metinleri yok ettik
	
	printf("\n\n\t\t     #######################################\n");
	printf("\t\t    -#          Aile Hekimi Sistemi        #-\n");
	printf("\t\t     #             Muayene Ekle            #\n");
	printf("\t\t    -#-------------------------------------#-\n");
	printf("######################                                     #####################\n");
	
	struct Muayene M;

	printf("    # Muayene Teşhislerini Giriniz: ");
	scanf(" %[^\n]", M.teshisler);
	
	printf("    # Muayene Reçeteyi giriniz: ");
	scanf(" %[^\n]", M.recete);
	
	printf("    # Muayene Tarihini giriniz: ");
	scanf(" %[^\n]", M.muayenetarihi);
	
	if(MuayeneKaydet(id, M.teshisler, M.recete, M.muayenetarihi))
	{
		Bilgilendir(" Muayene kayıdı başarıyla tamamlandı ");
		return;
	}
	Bilgilendir("    Muayene kayıdı tamamlanamadı!    ");
	
}

void HastaEkle()
{
	system("color f1");                   // Programımızın ana rengini değiştirdik
	system("cls");        		          // Önceden yazılmış metinleri yok ettik
	
	printf("\n\n\t\t     #######################################\n");
	printf("\t\t    -#          Aile Hekimi Sistemi        #-\n");
	printf("\t\t     #             Hasta Ekle              #\n");
	printf("\t\t    -#-------------------------------------#-\n");
	printf("######################                                     #####################\n");
	
	struct Hasta H;
	int sgk;
	
	printf("    # Hasta Adını Giriniz: ");
	scanf(" %[^\n]", H.adi);
	
	printf("    # Hasta Soyadını Giriniz: ");
	scanf(" %[^\n]", H.soyadi);
	
	printf("    # Hasta'nın T.C. Kimlik Numarasını Giriniz: ");
	scanf(" %[^\n]", H.tckimlik);
	
	printf("    # Hasta'nın Cinsiyetini Giriniz(e/k) : ");
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
			printf("\nGeçersiz Girdiniz Yeniden girin! : ");
			goto cinsiyet_gir;
	}
	
	printf("\n    # Hasta'nın doğum tarihini girin (2 Haziran 1963): ");
	scanf(" %[^\n]",H.dogumtarihi);
	
	printf("    # Hasta'nın Ana adını Giriniz: ");
	scanf(" %[^\n]",H.anaadi);
	
	printf("    # Hasta'nın Baba adını Giriniz: ");
	scanf(" %[^\n]",H.babaadi);
	
	printf("    # Hasta'nın Kan Grubunu Giriniz (A rh+): ");
	scanf(" %[^\n]",H.kangrubu);
	
	
	printf("\n    		1. Ssk \n");
	printf("    		2. Emekli Sandığı \n");
	printf("    		3. Bağ-kur \n");
	printf("    		4. Yok \n");
	printf("    		5. Bilinmiyor \n");
	printf("    # Hasta'nın Sosyal Güvenlik Kurumunu Giriniz : ");
	
	sgk_gir:
	sgk = putch(getch());
	switch(sgk)
	{
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
			H.sgkdurumu = sgk-48; // ASCII 'de '1' = 49 ise 49-48= 1 olacaktır
			break;
		default:
			printf("\nGeçersiz Girdiniz Yeniden girin! : ");
			goto sgk_gir;
			break;
	}
	
	printf("\n    # Hasta'nın Adresini Giriniz : ");
	scanf(" %[^\n]",H.adres);
	
	if(Uyarsec("        Kayıdı sisteme geçirme       ","Geçir","Geçirme","       ","       ","         "))
	{
		Bilgilendir("     Hasta kayıdı iptal edildi!      ");
		return;
	}
	
	FILE *fs;
	fs = fopen(database, "a");
	if(fs != NULL)
	{
		fprintf(fs, "%s, %s, %s, %d, %s, %s, %s, %s, %d, %s,\n",H.adi,H.soyadi,H.tckimlik,H.cinsiyet,H.dogumtarihi,H.anaadi,H.babaadi,H.kangrubu,H.sgkdurumu,H.adres);
		fclose(fs);
		
		Bilgilendir("  Hasta kayıdı başarıyla tamamlandı! ");
		return;
	}
	
	Bilgilendir("   Hasta kayıdı hatayla sonuçlandı!  ");
	
	
	
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
			
			// Türkçe karakterlerini tek tek düzeltmeye yarayan muazzam fonksiyonumuz :D
			int i=0;
			for(i=0;i<100;i++)
			{
				if(YHasta[idx].adres[i]==-115) 
					YHasta[idx].adres[i]='ı';
				if(YHasta[idx].adres[i]==-89) 
					YHasta[idx].adres[i]='ğ';
				if(YHasta[idx].adres[i]==-90) 
					YHasta[idx].adres[i]='Ğ';
				if(YHasta[idx].adres[i]==-127) 
					YHasta[idx].adres[i]='ü';
				if(YHasta[idx].adres[i]==-102) 
					YHasta[idx].adres[i]='ü';
				if(YHasta[idx].adres[i]==-97) 
					YHasta[idx].adres[i]='ş';
				if(YHasta[idx].adres[i]==-98) 
					YHasta[idx].adres[i]='Ş';
				if(YHasta[idx].adres[i]==-104) 
					YHasta[idx].adres[i]='İ';
				if(YHasta[idx].adres[i]==-108) 
					YHasta[idx].adres[i]='Ö';
				if(YHasta[idx].adres[i]==-103) 
					YHasta[idx].adres[i]='Ö';
				if(YHasta[idx].adres[i]==-121) 
					YHasta[idx].adres[i]='ç';
				if(YHasta[idx].adres[i]==-128) 
					YHasta[idx].adres[i]='Ç';
				if(i<50)
				{
					if(YHasta[idx].adi[i]==-115) 
						YHasta[idx].adi[i]='ı';
					if(YHasta[idx].adi[i]==-89) 
						YHasta[idx].adi[i]='ğ';
					if(YHasta[idx].adi[i]==-90) 
						YHasta[idx].adi[i]='Ğ';
					if(YHasta[idx].adi[i]==-127)
						YHasta[idx].adi[i]='ü';
					if(YHasta[idx].adi[i]==-102) 
						YHasta[idx].adi[i]='ü';
					if(YHasta[idx].adi[i]==-97) 
						YHasta[idx].adi[i]='ş';
					if(YHasta[idx].adi[i]==-98) 
						YHasta[idx].adi[i]='Ş';
					if(YHasta[idx].adi[i]==-104) 
						YHasta[idx].adi[i]='İ';
					if(YHasta[idx].adi[i]==-108) 
						YHasta[idx].adi[i]='Ö';
					if(YHasta[idx].adi[i]==-103) 
						YHasta[idx].adi[i]='Ö';
					if(YHasta[idx].adi[i]==-121) 
						YHasta[idx].adi[i]='ç';
					if(YHasta[idx].adi[i]==-128) 
						YHasta[idx].adi[i]='Ç';
					
					if(YHasta[idx].soyadi[i]==-115) 
						YHasta[idx].soyadi[i]='ı';
					if(YHasta[idx].soyadi[i]==-89) 
						YHasta[idx].soyadi[i]='ğ';
					if(YHasta[idx].soyadi[i]==-90) 
						YHasta[idx].soyadi[i]='Ğ';
					if(YHasta[idx].soyadi[i]==-127) 
						YHasta[idx].soyadi[i]='ü';
					if(YHasta[idx].soyadi[i]==-102) 
						YHasta[idx].soyadi[i]='ü';
					if(YHasta[idx].soyadi[i]==-97) 
						YHasta[idx].soyadi[i]='ş';
					if(YHasta[idx].soyadi[i]==-98) 
						YHasta[idx].soyadi[i]='Ş';
					if(YHasta[idx].soyadi[i]==-104) 
						YHasta[idx].soyadi[i]='İ';
					if(YHasta[idx].soyadi[i]==-108) 
						YHasta[idx].soyadi[i]='Ö';
					if(YHasta[idx].soyadi[i]==-103) 
						YHasta[idx].soyadi[i]='Ö';
					if(YHasta[idx].soyadi[i]==-121) 
						YHasta[idx].soyadi[i]='ç';
					if(YHasta[idx].soyadi[i]==-128) 
						YHasta[idx].soyadi[i]='Ç';
					
					if(YHasta[idx].dogumtarihi[i]==-115) 
						YHasta[idx].dogumtarihi[i]='ı';
					if(YHasta[idx].dogumtarihi[i]==-89) 
						YHasta[idx].dogumtarihi[i]='ğ';
					if(YHasta[idx].dogumtarihi[i]==-90) 
						YHasta[idx].dogumtarihi[i]='Ğ';
					if(YHasta[idx].dogumtarihi[i]==-127) 
						YHasta[idx].dogumtarihi[i]='ü';
					if(YHasta[idx].dogumtarihi[i]==-102) 
						YHasta[idx].dogumtarihi[i]='ü';
					if(YHasta[idx].dogumtarihi[i]==-97) 
						YHasta[idx].dogumtarihi[i]='ş';
					if(YHasta[idx].dogumtarihi[i]==-98) 
						YHasta[idx].dogumtarihi[i]='Ş';
					if(YHasta[idx].dogumtarihi[i]==-104) 
						YHasta[idx].dogumtarihi[i]='İ';
					if(YHasta[idx].dogumtarihi[i]==-108) 
						YHasta[idx].dogumtarihi[i]='Ö';
					if(YHasta[idx].dogumtarihi[i]==-103) 
						YHasta[idx].dogumtarihi[i]='Ö';
					if(YHasta[idx].dogumtarihi[i]==-121) 
						YHasta[idx].dogumtarihi[i]='ç';
					if(YHasta[idx].dogumtarihi[i]==-128) 
						YHasta[idx].dogumtarihi[i]='Ç';
					
					if(YHasta[idx].anaadi[i]==-115) 
						YHasta[idx].anaadi[i]='ı';
					if(YHasta[idx].anaadi[i]==-89) 
						YHasta[idx].anaadi[i]='ğ';
					if(YHasta[idx].anaadi[i]==-90)
						 YHasta[idx].anaadi[i]='Ğ';
					if(YHasta[idx].anaadi[i]==-127) 
						YHasta[idx].anaadi[i]='ü';
					if(YHasta[idx].anaadi[i]==-102) 
						YHasta[idx].anaadi[i]='ü';
					if(YHasta[idx].anaadi[i]==-97) 
						YHasta[idx].anaadi[i]='ş';
					if(YHasta[idx].anaadi[i]==-98) 
						YHasta[idx].anaadi[i]='Ş';
					if(YHasta[idx].anaadi[i]==-104) 
						YHasta[idx].anaadi[i]='İ';
					if(YHasta[idx].anaadi[i]==-108) 
						YHasta[idx].anaadi[i]='Ö';
					if(YHasta[idx].anaadi[i]==-103) 
						YHasta[idx].anaadi[i]='Ö';
					if(YHasta[idx].anaadi[i]==-121) 
						YHasta[idx].anaadi[i]='ç';
					if(YHasta[idx].anaadi[i]==-128) 
						YHasta[idx].anaadi[i]='Ç';
					
					if(YHasta[idx].babaadi[i]==-115) 
						YHasta[idx].babaadi[i]='ı';
					if(YHasta[idx].babaadi[i]==-89) 
						YHasta[idx].babaadi[i]='ğ';
					if(YHasta[idx].babaadi[i]==-90) 
						YHasta[idx].babaadi[i]='Ğ';
					if(YHasta[idx].babaadi[i]==-127) 
						YHasta[idx].babaadi[i]='ü';
					if(YHasta[idx].babaadi[i]==-102) 
						YHasta[idx].babaadi[i]='ü';
					if(YHasta[idx].babaadi[i]==-97) 
						YHasta[idx].babaadi[i]='ş';
					if(YHasta[idx].babaadi[i]==-98) 
						YHasta[idx].babaadi[i]='Ş';
					if(YHasta[idx].babaadi[i]==-104) 
						YHasta[idx].babaadi[i]='İ';
					if(YHasta[idx].babaadi[i]==-108) 
						YHasta[idx].babaadi[i]='Ö';
					if(YHasta[idx].babaadi[i]==-103) 
						YHasta[idx].babaadi[i]='Ö';
					if(YHasta[idx].babaadi[i]==-121) 
						YHasta[idx].babaadi[i]='ç';
					if(YHasta[idx].babaadi[i]==-128) 
						YHasta[idx].babaadi[i]='Ç';
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
		Bilgilendir("       Şuan hasta sayısı 0'dır       ");
	}
	
	while(1)
	{
		system("color f1");                   // Programımızın ana rengini değiştirdik
		system("cls");       		          // Önceden yazılmış metinleri yok ettik
		
		printf("\n\n\t\t     #######################################\n");
		printf("\t\t    -#          Aile Hekimi Sistemi        #-\n");
		printf("\t\t     #          Hasta Kartı [%.2d/%.2d]        #\n",aktif+1,ToplamHasta);
		printf("\t\t    -#-------------------------------------#-\n");
		printf("######################                                     #####################\n\n");
		printf("    # Hasta Kayıt sırası: %d\n",aktif+1);
		printf("    # Hasta Adı Soyadı: %s %s\n",YHasta[aktif].adi,YHasta[aktif].soyadi);
		printf("    # Hasta TC Kimlik: %s\n",YHasta[aktif].tckimlik);
		printf("    # Hasta Cinsiyeti %s\n",(YHasta[aktif].cinsiyet==1?"Erkek":"Kadın"));
		printf("    # Hasta Doğum Tarihi: %s\n",YHasta[aktif].dogumtarihi);
		printf("    # Hasta Ana Adı: %s\n",YHasta[aktif].anaadi);
		printf("    # Hasta Baba Adı: %s\n",YHasta[aktif].babaadi);
		printf("    # Hasta Kan Grubu: %s\n",YHasta[aktif].kangrubu);
		printf("    # Hasta Sgk: %s\n",YHasta[aktif].sgkdurumu==1?"SSK":YHasta[aktif].sgkdurumu==2?"Emekli Sandığı":YHasta[aktif].sgkdurumu==3?"Bağ-Kur":YHasta[aktif].sgkdurumu==4?"Yok":"Bilinmiyor");
		printf("    # Hasta Adresi: %s\n",YHasta[aktif].adres);
		
		printf("\n\n--------------------------------------------------------------------------------");
		printf("\n   %csol kart      %csağ kart       %cgüncelle    (e)yeni mu.   %chastayı sil   ",27,26,24,25);
		
		int tus = getch();
		if(tus == 77)                        // Sağ Tuşu
			(aktif < ToplamHasta-1) ? (aktif++) : 0; 
		else if(tus == 75)                   // Sol Tuşu
			(aktif > 0) ? (aktif--) : 0;
		else if(tus == 13)                   // Enter Tuşu
		{
			YeniMuayene(aktif);
			return;
		}
		else if(tus == 72)					 // Yukarı tuşu  (güncelle)
		{
			HastaGuncelle(aktif);
		}
		else if(tus == 80)                   // Aşağı tuşu  (hasta sil)
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
					
					Bilgilendir("       Hasta başarıyla silindi!      ");
					return;
					
				}
			}
		}
		else if(tus == 27)                   // ESC tuşu (Ana Menüye dön)
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
		Bilgilendir(" Bu hasta daha önce muayene olmamış  ");
		return;
	}

	while(1)
	{
		system("color f1");                   // Programımızın ana rengini değiştirdik
		system("cls");       		          // Önceden yazılmış metinleri yok ettik
		
		printf("\n\n\t\t     #######################################\n");
		printf("\t\t    -#          Aile Hekimi Sistemi        #-\n");
		printf("\t\t     #          Hasta Muayene Kartı        #\n");
		printf("\t\t    -#-------------------------------------#-\n");
		printf("######################                                     #####################\n\n");
		
	
		for(i=0;i<200;i++)
		{
			if(YMuayene[i].hastaid == id)
			{
				printf("    #   Muayene Kaydı: %d\n",i);
				printf("    #   Muayene Teşhisler: %s\n",YMuayene[id].teshisler);
				printf("    #   Muayene Tarihi: %s\n",YMuayene[id].muayenetarihi);
				printf("    #   Reçete bilgisi: %s\n\n",YMuayene[id].recete);
			}
		}
		int tus = getch();
		if(tus == 27)                   // ESC tuşu (Hasta kartına dön)
			return;
	}
}


int HastaArama()
{
	git_hasta_arama:
	system("color f1");                   // Programımızın ana rengini değiştirdik
	system("cls");       		          // Önceden yazılmış metinleri yok ettik
		
	printf("\n\n\t\t     #######################################\n");
	printf("\t\t    -#          Aile Hekimi Sistemi        #-\n");
	printf("\t\t     #              Hasta Arama            #\n");
	printf("\t\t    -#-------------------------------------#-\n");
	printf("######################                                     #####################\n\n");
	
	char hastas[100];
	printf("    # Arama yaparken lütfen sadece o hastaya ait olabilecek detayları kullanın\n");
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
	
	if(Uyar("   Hastayı Bulamadık! :( Yeniden?    "))
	{
		return -1;
	}
	goto git_hasta_arama;
}

int Gelistiren()
{
	system("color f1");                   // Programımızın ana rengini değiştirdik
	system("cls");       		          // Önceden yazılmış metinleri yok ettik
	
	printf("\n\n\t\t     #######################################\n");
	printf("\t\t    -#          Aile Hekimi Sistemi        #-\n");
	printf("\t\t     #               Ekstra                #\n");
	printf("\t\t    -#-------------------------------------#-\n");
	printf("\t\t     #          Geliştiren :               #\n");
	printf("\t\t    -#               co3moz                #-\n");
	printf("\t\t     #             Doğan DERYA             #\n");
	printf("\t\t    -#             Comp. Eng.              #-\n");
	printf("\t\t     #-------------------------------------#\n");
	printf("\t\t     #######################################\n");
	getch();
}

void GenelRaporlar()
{
	system("color f1");                   // Programımızın ana rengini değiştirdik
	system("cls");       		          // Önceden yazılmış metinleri yok ettik
	
	printf("\n\n\t\t     #######################################\n");
	printf("\t\t    -#          Aile Hekimi Sistemi        #-\n");
	printf("\t\t     #             Genel Raporlar          #\n");
	printf("\t\t    -#-------------------------------------#-\n");
	printf("######################                                     #####################\n");
	
	printf("    # Toplam Kayıtlı Hasta: %d\n", ToplamHasta);
	printf("    # Toplam Kayıtlı Muayene: %d", ToplamMuayene);
	
	
	getch();
}

void HastaGuncelle(int id)
{
	system("color f1");                   // Programımızın ana rengini değiştirdik
	system("cls");        		          // Önceden yazılmış metinleri yok ettik
	
	printf("\n\n\t\t     #######################################\n");
	printf("\t\t    -#          Aile Hekimi Sistemi        #-\n");
	printf("\t\t     #            Hasta Güncelle           #\n");
	printf("\t\t    -#-------------------------------------#-\n");
	printf("######################                                     #####################\n");
	
	struct Hasta H;
	int sgk;
	
	printf("    # Hasta Adını Giriniz: ");
	scanf(" %[^\n]", H.adi);
	
	printf("    # Hasta Soyadını Giriniz: ");
	scanf(" %[^\n]", H.soyadi);
	
	printf("    # Hasta'nın T.C. Kimlik Numarasını Giriniz: ");
	scanf(" %[^\n]", H.tckimlik);
	
	printf("    # Hasta'nın Cinsiyetini Giriniz(e/k) : ");
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
			printf("\nGeçersiz Girdiniz Yeniden girin! : ");
			goto cinsiyet_gir;
	}
	
	printf("\n    # Hasta'nın doğum tarihini girin (2 Haziran 1963): ");
	scanf(" %[^\n]",H.dogumtarihi);
	
	printf("    # Hasta'nın Ana adını Giriniz: ");
	scanf(" %[^\n]",H.anaadi);
	
	printf("    # Hasta'nın Baba adını Giriniz: ");
	scanf(" %[^\n]",H.babaadi);
	
	printf("    # Hasta'nın Kan Grubunu Giriniz (A rh+): ");
	scanf(" %[^\n]",H.kangrubu);
	
	
	printf("\n    		1. Ssk \n");
	printf("    		2. Emekli Sandığı \n");
	printf("    		3. Bağ-kur \n");
	printf("    		4. Yok \n");
	printf("    		5. Bilinmiyor \n");
	printf("    # Hasta'nın Sosyal Güvenlik Kurumunu Giriniz : ");
	
	sgk_gir:
	sgk = putch(getch());
	switch(sgk)
	{
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
			H.sgkdurumu = sgk-48; // ASCII 'de '1' = 49 ise 49-48= 1 olacaktır
			break;
		default:
			printf("\nGeçersiz Girdiniz Yeniden girin! : ");
			goto sgk_gir;
			break;
	}
	
	printf("\n    # Hasta'nın Adresini Giriniz : ");
	scanf(" %[^\n]",H.adres);
	
	if(Uyar("         Kayıdı güncelleştir         "))
	{
		Bilgilendir("     Hasta kayıdı iptal edildi!      ");
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
		
		Bilgilendir("     Hasta başarıyla güncellendi     ");
		return;
	}
}


int main()
{
	// Ön Hazırlık
	int islem=0;
	system("title Aile Hekimi Sistemi"); // Program başlığını Değiştirdik
	setlocale(LC_ALL,"turkish");         // Programımızın türkçe karakterleri desteklemesini sağladık

	git_program_basi:
	// Ana Menüyü çağıralım
	islem = AnaMenu(islem);
	switch(islem)
	{
		//Hasta Ekle
		case 0:
			HastaEkle();
			goto git_program_basi;
			
			
		//Hasta Kartları
		case 1:
			HastalariYukle();
			HastaKarti(0);                //1. Hasta kartından ihtibaren göster
			goto git_program_basi;
		
		//Hasta Arama
		case 2:
			HastalariYukle();
			int hastaid=HastaArama();       //Hasta araması yaptıktan sonra
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
			
		//Çıkış
		case 5:
			if(!Uyar("                Çıkış?               "))
				return 0;
			else goto git_program_basi;
		
	}
	return 0;
}
