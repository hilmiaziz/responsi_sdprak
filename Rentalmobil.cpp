#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <math.h>

#define DRIVER 8
#define MAX 14

using namespace std;

typedef string infotype;
//Data Mobil
typedef struct tNode *address;
typedef bool status;
typedef struct tNode{
	infotype NoTNKB;
	infotype Merk;
	infotype Warna;
	infotype Tahun;
	int biayaSewa;
	status sewa;
	address Next;
}Mobil;
typedef Mobil *List;

//Data Driver
typedef int pos;
typedef struct{
	pos Head;
	pos Tail;
	infotype noKTP[DRIVER];
	infotype Nama[DRIVER];
	infotype Alamat[DRIVER];
	infotype Usia[DRIVER];
	status service[DRIVER];
}Queue;

//Data Konsumen
typedef struct{
	pos Head;
	pos Tail;
	infotype noKTP[MAX];
	infotype Nama[MAX];
	infotype Alamat[MAX];
}Konsumen;

//Tanggal
typedef struct{
	int Tanggal;
	int Bulan;
	int Tahun;
}Date;

//Data Transaksi
typedef struct TNode *ID_Transaksi;
typedef struct TNode{
	infotype Nama_Konsumen;
	infotype Alamat;
	infotype NoTNKB;
	infotype Nama_Driver;
	Date Sewa;
	Date Kembali;
	int biayaSewa;
	ID_Transaksi Next;
}transaksi;
typedef transaksi *Transaksi;

//Data Pembayaran
typedef struct TBayar *ID_Pembayaran;
typedef struct TBayar{
	infotype Nama_Konsumen;
	infotype Alamat;
	infotype NoTNKB;
	infotype Nama_Driver;
	Date Sewa;
	Date Kembali;	
	Date Bayar;
	int Denda;
	int totBiaya;
	ID_Pembayaran Next;
}Pembayaran;
typedef Pembayaran *pembayaran;

//ADT Mobil
typedef Mobil *List;
void CreateEmpty(List &L);
bool IsEmpty(List L);
bool IsOneElement(List L);
bool isRent(List L);
void RentPertama(List &L,infotype *tnkb,int *biayasewa);
void Rent(List &L,infotype &tnkb,int &biayasewa,pos pilih,int no);
void insertFirst(List &L,address P);
void insertAfter(List &L,address Prec,address P);
address alokasi(infotype tnkb,infotype merk,infotype warna,infotype tahun,int biaya);
void addMobil(List &L,address P);
void delFirst(List &L);
void delMobil(List &L,int select,int no);
void updateTarif(List &L,int biaya,int select,int no);
void printMobil(List L,int no);
void availableMobil(List L,int no);
void inisialisasiMobil(List &L,infotype tnkb);

//ADT Driver
void CreateEmpty(Queue *D);
bool isEmpty(Queue D);
bool isFull(Queue D);
bool isTask(Queue D);
bool isOneElement(Queue D);
void addDriver(Queue *D,infotype ktp,infotype nama,infotype alamat,infotype usia);
void Task(Queue *D,infotype *nama);
void updateDriver(Queue *D,infotype update,pos select);
void delDriver(Queue *D,pos select);
void printDriver(Queue D);
void inisialisasiDriver(Queue *D,infotype nama);

//ADT Konsumen
void CreateEmpty(Konsumen *K);
bool isEmpty(Konsumen K);
bool isFull(Konsumen K);
bool isOneElement(Konsumen K);
void addKonsumen(Konsumen *K,infotype ktp,infotype nama,infotype alamat);
void printKonsumen(Konsumen K);
void delKonsumen(Konsumen *K,pos select);
void delKonsumen(Konsumen *K,infotype *nama,infotype *alamat);

//ADT Transaksi
void CreateEmpty(Transaksi &T);
bool IsEmpty(Transaksi T);
bool IsOneElement(Transaksi T);
void insertFirst(Transaksi &T,ID_Transaksi P);
void insertAfter(Transaksi &T,ID_Transaksi sblm,ID_Transaksi P);
void delPenyewaan(Transaksi &L);
void addPenyewaan(Transaksi &T,ID_Transaksi P);
ID_Transaksi Alokasi(infotype nama_Konsumen,infotype alamat,infotype tnkb,
	infotype nama_Driver,Date sewa,Date kembali,int biayasewa);
infotype getNama(Konsumen K);
void printPenyewaan(Transaksi T,int no);
void delTransaksi(Transaksi &T,infotype *nama_konsumen,infotype *alamat,infotype *tnkb,
	Date *sewa,Date *kembali,infotype *nama_driver,int *biayasewa,pos select,int no);

//Data Pembayaran
void CreateEmpty(pembayaran &B);
bool IsEmpty(pembayaran T);
bool IsOneElement(pembayaran T);
ID_Pembayaran Alokasi(infotype nama,infotype alamat,
	infotype tnkb,infotype nama_driver,Date sewa,Date bayar,int denda,int totbiaya);
int hitungBayar(int denda,int sewa,int biaya);
void insertFirst(pembayaran &B,ID_Pembayaran P);
void insertAfter(pembayaran &B,ID_Pembayaran Prec,ID_Pembayaran P);
void addPembayaran(pembayaran &B,ID_Pembayaran P);
void bayarSewa(infotype Nama_Driver,Date kembali,Date Bayar,Date Sewa,int biayaSewa,int &totdenda,int &totbayar);
void printPembayaran(pembayaran T,int no);


int main(){

	Queue Driver;
	Konsumen konsumen;
	List mobil;
	Transaksi Penyewaan;
	pembayaran Bayar_sewa;

	address data;
	ID_Transaksi Data_Pinjam;
	ID_Pembayaran Data_Pembayaran;


	infotype tnkb,merk,warna,tahun;
	int biayasewa = 0;
	int denda = 0;
	int totbiaya = 0;
	infotype nama,ktp,alamat,umur,nama_driver;
	int no=0;
	int pilih;
	int select;
	char opsi;
	Date sewa;
	Date kembali;
	Date bayar;

	CreateEmpty(&Driver);
	CreateEmpty(&konsumen);
	CreateEmpty(mobil);
	CreateEmpty(Penyewaan);
	CreateEmpty(Bayar_sewa);
	//Mobil
	data = alokasi("AB 1111 Z","INNOVA","Hitam","2008",250000);
	addMobil(mobil,data);
	data = alokasi("AB 4444 L","YARIS","Silver","2008",500000);
	addMobil(mobil,data);
	//Driver
	addDriver(&Driver,"5130422156","whoami","root","24");
	addDriver(&Driver,"5130422152","localhost","127.0.0.1","30");	
	addDriver(&Driver,"5130422153","sudonym","terminal","36");
	addDriver(&Driver,"5130422157","reese","direktori","47");
	
	do{
		cout<<"---------------------------------------------------------------------"<<endl;
		cout<<"\t\t\t\"PT ADI JAYA MAKMUR\""<<endl;
		cout<<"---------------------------------------------------------------------"<<endl;
		cout<<" 1. Data Mobil"<<endl;
		cout<<" 2. Data Driver"<<endl;
		cout<<" 3. Data Konsumen"<<endl;
		cout<<" 4. Transaksi Peminjaman"<<endl;
		cout<<" 5. Transaksi Pembayaran"<<endl;
		cout<<" 0. Keluar"<<endl;
		cout<<"---------------------------------------------------------------------"<<endl;
		cout<<"Pilih Menu : ";
		cin>>pilih;
		system("clear");
		switch(pilih){
			case 1:
				do{
					cout<<"-----------------------------------------"<<endl;
					cout<<"\t\t\"DATA MOBIL\""<<endl;
					cout<<"-----------------------------------------"<<endl;
					cout<<" 1. Tampilkan Data Mobil"<<endl;
					cout<<" 2. Tambah Data Mobil"<<endl;
					cout<<" 3. Update Tarif Sewa"<<endl;
					cout<<" 4. Hapus Data Mobil"<<endl;
					cout<<" 9. Kembali"<<endl;
					cout<<"-----------------------------------------"<<endl;
					cout<<"Pilih Menu : ";
					cin>>pilih;
					system("clear");
					switch(pilih){
						case 1:
							cout<<"0. Kembali"<<endl;
							cout<<"-----------------------------------------------------------------------------------------"<<endl;
							cout<<"| No |"<<"   No TNKB  |"<<"       MERK      |"<<"    WARNA   |"<<"  TAHUN  |"
							<<"   BIAYA   |"<<"     STATUS     |"<<endl;
							cout<<"-----------------------------------------------------------------------------------------"<<endl;
							printMobil(mobil,no);
							cout<<"-----------------------------------------------------------------------------------------"<<endl;
							cin>>pilih;
							system("clear");

							break;
						case 2:
							cout<<"Masukkan No TNKB\t: ";
							cin.ignore();
							getline(cin,tnkb);
							cout<<"Masukkan Merk Mobil\t: ";
							getline(cin,merk);
							cout<<"Masukkan Warna Mobil\t: ";
							getline(cin,warna);
							cout<<"Masukkan Tahun\t\t: ";
							cin>>tahun;
							cout<<"Masukkan Biaya Sewa\t: ";
							cin>>biayasewa;

							data = alokasi(tnkb,merk,warna,tahun,biayasewa);
							addMobil(mobil,data);
							system("clear");

							break;
						case 3:
							cout<<"0. Kembali"<<endl;
							cout<<"-----------------------------------------------------------------------------------------"<<endl;
							cout<<"| No |"<<"   No TNKB  |"<<"       MERK      |"<<"    WARNA   |"<<"  TAHUN  |"
							<<"   BIAYA   |"<<"     STATUS     |"<<endl;
							cout<<"-----------------------------------------------------------------------------------------"<<endl;
							printMobil(mobil,no);
							cout<<"-----------------------------------------------------------------------------------------"<<endl;
							cout<<"Pilih Mobil : ";
							cin>>select;
							cout<<"Masukkan tarif sewa baru : ";
							cin>>biayasewa;

							updateTarif(mobil,biayasewa,select,no);
							system("clear");
							break;
						case 4:
							cout<<"0. Kembali"<<endl;
							cout<<"-----------------------------------------------------------------------------------------"<<endl;
							cout<<"| No |"<<"   No TNKB  |"<<"       MERK      |"<<"    WARNA   |"<<"  TAHUN  |"
							<<"   BIAYA   |"<<"     STATUS     |"<<endl;
							cout<<"-----------------------------------------------------------------------------------------"<<endl;
							printMobil(mobil,no);
							cout<<"-----------------------------------------------------------------------------------------"<<endl;
							cout<<"Pilih Mobil : ";
							cin>>select;

							delMobil(mobil,select,no);
							system("clear");
							break;
						case 9:
							system("clear");
							break;
						default:
							cout<<"Menu yang anda pilih tidak tersedia"<<endl;
					}
				}while(pilih!=9);
				
				break;
			case 2:
				do{
					cout<<"-----------------------------------------"<<endl;
					cout<<"\t\t\"DATA DRIVER\"\t\t"<<endl;
					cout<<"-----------------------------------------"<<endl;
					cout<<" 1. Tampilkan Data Driver"<<endl;
					cout<<" 2. Tambah Data Driver"<<endl;
					cout<<" 3. Update Umur Driver"<<endl;
					cout<<" 4. Hapus Data Driver"<<endl;
					cout<<" 9. Kembali"<<endl;
					cout<<"-----------------------------------------"<<endl;
					cout<<"Pilih Menu : ";
					cin>>pilih;
					system("clear");
					switch(pilih){
						case 1:
							cout<<"0. Kembali"<<endl;

							printDriver(Driver);
							cin>>pilih;
							system("clear");

							break;
						case 2:
							cout<<"0. Kembali"<<endl;
							cout<<"Masukkan Nama\t\t: ";
							cin.ignore();
							getline(cin,nama);
							cout<<"Masukkan No KTP\t\t: ";
							getline(cin,ktp);
							cout<<"Masukkan Alamat\t\t: ";
							getline(cin,alamat);
							cout<<"Masukkan Umur\t\t: ";
							cin>>umur;

							addDriver(&Driver,ktp,nama,alamat,umur);
							system("clear");

							break;
						case 3:
							cout<<"0. Kembali"<<endl;

							printDriver(Driver);
							cout<<"Pilih driver : ";
							cin>>select;

							cout<<"Masukkan Umur Driver : ";
							cin>>umur;

							updateDriver(&Driver,umur,select);
							system("clear");

							break;
						case 4:
							cout<<"0. Kembali"<<endl;

							printDriver(Driver);
							cout<<"Pilih driver : ";
							cin>>select;
							delDriver(&Driver,select);
							system("clear");

							break;
						case 9:
							system("clear");
							break;
						default:
							cout<<"Menu yang anda pilih tidak tersedia"<<endl;
					}
				}while(pilih!=9);
				
				break;
			case 3:
				do{
					cout<<"-----------------------------------------"<<endl;
					cout<<"\t\t\"DATA KONSUMEN\""<<endl;
					cout<<"-----------------------------------------"<<endl;
					cout<<" 1. Tampilkan Data Konsumen"<<endl;
					cout<<" 2. Tambah Data Konsumen"<<endl;
					cout<<" 3. Hapus Data Konsumen"<<endl;
					cout<<" 9. Kembali"<<endl;
					cout<<"-----------------------------------------"<<endl;
					cout<<"Pilih Menu : ";
					cin>>pilih;
					system("clear");
					switch(pilih){
						case 1:
							cout<<"0. Kembali"<<endl;
							printKonsumen(konsumen);
							cin>>pilih;
							system("clear");

							break;
						case 2:
							cout<<"0. Kembali"<<endl;
							cout<<"Masukkan Nama \t\t: ";
							cin.ignore();
							getline(cin,nama);
							cout<<"Masukkan No KTP \t: ";
							getline(cin,ktp);
							cout<<"Masukkan Alamat \t: ";
							getline(cin,alamat);

							addKonsumen(&konsumen,ktp,nama,alamat);
							
							cin>>pilih;
							system("clear");

							break;
						case 3:
							printKonsumen(konsumen);
							cin>>select;
							delKonsumen(&konsumen,select);
							system("clear");
							break;
						case 9:
							system("clear");
							break;
						default:
							cout<<"Menu yang anda pilih tidak tersedia"<<endl;
					}
				}while(pilih!=9);
				
				break;
			case 4:
				do{
					cout<<"------------------------------------------------------"<<endl;
					cout<<"\t\t\"TRANSAKSI  PENYEWAAN\""<<endl;
					cout<<"------------------------------------------------------"<<endl;
					cout<<" 1. Tampilkan Data Transaksi"<<endl;
					cout<<" 2. Input Transaksi"<<endl;
					cout<<" 9. Kembali"<<endl;
					cout<<"------------------------------------------------------"<<endl;
					cout<<"Pilih Menu : ";
					cin>>pilih;
					system("clear");
					
void printDriver(Queue D){
	pos no = 0;
	if(isEmpty(D)){
		cout<<"Belum ada data driver yang tersimpan"<<endl;
	}else{
		cout<<"-----------------------------------------------------------------------------------------------------------------"<<endl;
		cout<<"|No |"<<"\t No KTP \t|"<<"\tNama Driver\t|"<<"\t\tAlamat\t\t|"<<"\tUsia\t|"<<"\tStatus\t|"<<endl;
		cout<<"-----------------------------------------------------------------------------------------------------------------"<<endl;
		if(D.Head <= D.Tail){
			for(pos i = D.Head; i <= D.Tail;i++){
				no++;
				cout<<"|"<<setw(3)<<no<<"|"<<setw(19)<<D.noKTP[i]<<"|"<<setw(23)<<D.Nama[i]<<"|"
				<<setw(31)<<D.Alamat[i]<<"|"<<setw(9)<<D.Usia[i]<<" Tahun|";
				if(D.service[i]==0)
					cout<<setw(16)<<"Tersedia |"<<endl;
				else
					cout<<setw(16)<<"Bertugas |"<<endl;
			}
		}else{ //sirkuler
			for(pos i = D.Head; i <= DRIVER-1;i++){
				no++;
				cout<<"|"<<setw(3)<<no<<"|"<<setw(19)<<D.noKTP[i]<<"|"<<setw(23)<<D.Nama[i]<<"|"
				<<setw(31)<<D.Alamat[i]<<"|"<<setw(9)<<D.Usia[i]<<" Tahun|";
				if(D.service[i]==0)
					cout<<setw(16)<<"Tersedia |"<<endl;
				else
					cout<<setw(16)<<"Bertugas |"<<endl;
			}

			for(pos i = 0; i <= D.Tail;i++){
				no++;
				cout<<"|"<<setw(3)<<no<<"|"<<setw(19)<<D.noKTP[i]<<"|"<<setw(23)<<D.Nama[i]<<"|"
				<<setw(31)<<D.Alamat[i]<<"|"<<setw(9)<<D.Usia[i]<<" Tahun|";
				if(D.service[i]==0)
					cout<<setw(17)<<"Tersedia |"<<endl;
				else
					cout<<setw(17)<<"Bertugas |"<<endl;
			}
		}
		cout<<"-----------------------------------------------------------------------------------------------------------------"<<endl;
	}
}

void inisialisasiDriver(Queue *D,infotype nama){
	if(isEmpty(*D)){

	}else{
		if((*D).Head <= (*D).Tail){
			for(pos i = (*D).Head; i <= (*D).Tail;i++){
				if((*D).Nama[i] == nama){
					(*D).service[i] = 0;
					break;
				}
			}
		}else{
			for(pos i = (*D).Head; i <= DRIVER-1;i++){
				if((*D).Nama[i] == nama){
					(*D).service[i] = 0;
					break;
				}
			}

			for(pos i = 0; i <= (*D).Tail;i++){
				if((*D).Nama[i] == nama){
					(*D).service[i] = 0;
					break;
				}
			}
		}
	}
}


//Konsumen
void CreateEmpty(Konsumen *K){
	(*K).Head = (*K). Tail = -1;
}

bool isEmpty(Konsumen K){
	return (K.Head == -1 && K.Tail == -1);
}

bool isFull(Konsumen K){
	return (K.Head < K.Tail && K.Tail - K.Head == MAX-1 ||
		K.Head > K.Tail && K.Head - K.Tail ==1);
}

bool isOneElement(Konsumen K){
	return (K.Head == K.Tail && K.Head != -1);
}

void addKonsumen(Konsumen *K,infotype ktp,infotype nama,infotype alamat){
	if(!isFull(*K)){
		if(isEmpty(*K)){ //jika masih kosong
			(*K).Head = (*K).Tail = 0;
			(*K).noKTP[(*K).Head] = ktp;
			(*K).Nama[(*K).Head] = nama;
			(*K).Alamat[(*K).Head] = alamat;
		}else{
			if((*K).Tail == MAX-1){ //jika sirkuler
				(*K).Tail = 0;
			}else{
				(*K).Tail++;
			}
			//pengisian 
			(*K).noKTP[(*K).Tail] = ktp;
			(*K).Nama[(*K).Tail] = nama;
			(*K).Alamat[(*K).Tail] = alamat;
		}
	}else
		cout<<"Data Konsumen Yang Akan Menyewa Penuh"<<endl;	
}

void printKonsumen(Konsumen K){
	pos no = 0;
	if(isEmpty(K)){
		cout<<"Belum ada data konsumen yang tersimpan"<<endl;
	}else{
		cout<<"---------------------------------------------------------------------------------"<<endl;
		cout<<"|"<<" No |"<<"\t  No KTP  \t|"<<"\tNama Konsumen\t|"<<"\t\tAlamat\t\t|"<<endl;
		cout<<"---------------------------------------------------------------------------------"<<endl;
		
		if(K.Head <= K.Tail){
			for(pos i = K.Head; i <= K.Tail;i++){
				no++;
				cout<<"|"<<setw(4)<<no<<"|"<<setw(18)<<K.noKTP[i]<<"|"<<setw(23)<<K.Nama[i]
				<<"|"<<setw(31)<<K.Alamat[i]<<"|"<<endl;
			}
		}else{ //sirkuler
			for(pos i = K.Head; i <= MAX-1;i++){
				no++;
				cout<<"|"<<setw(4)<<no<<"|"<<setw(18)<<K.noKTP[i]<<"|"<<setw(23)<<K.Nama[i]
				<<"|"<<setw(31)<<K.Alamat[i]<<"|"<<endl;
			}

			for(pos i = 0; i <= K.Tail;i++){
				no++;
				cout<<"|"<<setw(4)<<no<<"|"<<setw(18)<<K.noKTP[i]<<"|"<<setw(23)<<K.Nama[i]
				<<"|"<<setw(31)<<K.Alamat[i]<<"|"<<endl;
			}
		}
		cout<<"---------------------------------------------------------------------------------"<<endl;
		
	}	
}

void delKonsumen(Konsumen *K,pos select){
	int element = 0;

	if(select>=1 && select<=MAX){
		if((*K).Head <= (*K).Tail){
			for(pos i = (*K).Head+select-1; i < (*K).Tail;i++){
				(*K).Nama[i] = (*K).Nama[i+1];
				(*K).noKTP[i] = (*K).noKTP[i+1];
				(*K).Alamat[i] = (*K).Alamat[i+1];

			}
			(*K).Tail--;

		}else{

			for(pos i = (*K).Head; i <= MAX-1;i++)
				element++;

			if(select<=element){ //jika masih normal
				for(pos i = (*K).Head; i < MAX-1;i++){
					(*K).Nama[i] = (*K).Nama[i+1];
					(*K).noKTP[i] = (*K).noKTP[i+1];
					(*K).Alamat[i] = (*K).Alamat[i+1];
				}

				for(pos i = 0; i < (*K).Tail;i++){
					(*K).Nama[i] = (*K).Nama[i+1];
					(*K).noKTP[i] = (*K).noKTP[i+1];
					(*K).Alamat[i] = (*K).Alamat[i+1];
				}
				(*K).Tail--;

			}else{//sirkuler

				if((*K).Tail == 0)
					(*K).Tail = DRIVER-1;

				else{
					for(pos i = element - select-1; i < (*K).Tail;i++){
						(*K).Nama[i] = (*K).Nama[i+1];
						(*K).noKTP[i] = (*K).noKTP[i+1];
						(*K).Alamat[i] = (*K).Alamat[i+1];
					}
					(*K).Tail--;
				}
			}
		}
	}else{
		cout<<"Pilihan yang anda masukkan tidak tersedia"<<endl;
	}
}

void delKonsumen(Konsumen *K,infotype *nama,infotype *alamat){
	if(isEmpty(*K))
		cout<<"Belum ada data konsumen yang tersimpan"<<endl;
	else{
		*nama = (*K).Nama[(*K).Head];
		*alamat = (*K).Alamat[(*K).Head];
		if(isOneElement(*K))
			CreateEmpty(&(*K));
		else{
			if((*K).Head == MAX-1)
				(*K).Head = 0;
			else
				(*K).Head++;
		}
			
	}
}


//transaksi
void CreateEmpty(Transaksi &T){
	T = NULL;
}

bool IsEmpty(Transaksi T){
	return (T==NULL);
}

bool IsOneElement(Transaksi T){
	return(IsEmpty(T->Next));
}

void insertFirst(Transaksi &T,ID_Transaksi P){
	P->Next = T;
	T = P;
}

void insertAfter(Transaksi &T,ID_Transaksi sblm,ID_Transaksi P){
	P->Next = sblm->Next;
	sblm->Next = P;
}

infotype getNama(Konsumen K){
	return(K.Nama[K.Head]);
}

ID_Transaksi Alokasi(infotype nama_Konsumen,infotype alamat,infotype tnkb,infotype nama_Driver,Date sewa,Date kembali,int biayasewa){
	ID_Transaksi P = new(transaksi);

	if(P == NULL)
		return NULL;
	else{
		P->Nama_Konsumen = nama_Konsumen;
		P->Alamat  = alamat;
		P->NoTNKB = tnkb;
		P->Nama_Driver = nama_Driver;
		P->Sewa.Tanggal = sewa.Tanggal;
		P->Sewa.Bulan = sewa.Bulan;
		P->Sewa.Tahun = sewa.Tahun;
		P->Kembali.Tanggal = kembali.Tanggal;
		P->Kembali.Bulan = kembali.Bulan;
		P->Kembali.Tahun = kembali.Tahun;
		P->biayaSewa = biayasewa;
		P->Next = NULL;
	}
	return P;
}

void addPenyewaan(Transaksi &T,ID_Transaksi P){
	ID_Transaksi temp = T;
	if(IsEmpty(T))
		insertFirst(T,P);
	else if(IsOneElement(T))
		insertAfter(T,T,P);
	else
		addPenyewaan(T->Next,P);
}

void printPenyewaan(Transaksi T,int no){
	if(IsEmpty(T)){

	}else{
		no++;
		cout<<"|"<<setw(4)<<no<<"|"<<setw(13)<<T->NoTNKB<<"|"<<setw(19)<<T->Nama_Konsumen<<"|"<<setw(20)
		<<T->Alamat<<"|"<<setw(19)<<T->Nama_Driver<<"|"<<setw(6)<<T->Sewa.Tanggal<<"-"<<T->Sewa.Bulan
		<<"-"<<T->Sewa.Tahun<<"|"<<setw(6)<<T->Kembali.Tanggal<<"-"<<T->Kembali.Bulan
		<<"-"<<T->Kembali.Tahun<<"|"<<endl;

		printPenyewaan(T->Next,no);
	}
}


//pembayaran
void CreateEmpty(pembayaran &B){
	B = NULL;
}

bool IsEmpty(pembayaran T){
	return (T == NULL);
}

bool IsOneElement(pembayaran T){
	return (IsEmpty(T->Next));
}

int hitungBayar(int denda,int sewa,int biaya){
	int totbayar = 0;
	totbayar = (biaya * sewa) + denda;
	return totbayar; 
}

ID_Pembayaran Alokasi(infotype nama,infotype alamat,
	infotype tnkb,infotype nama_driver,Date sewa,Date bayar,int denda,int totbiaya){
	
	ID_Pembayaran P = new (Pembayaran);

	if(P == NULL)
		return NULL;
	else{
		P->Nama_Konsumen = nama;
		P->Alamat = alamat;
		P->NoTNKB = tnkb;
		P->Nama_Driver = nama_driver;
		P->Sewa = sewa;
		P->Bayar = bayar;
		P->Denda = denda;
		P->totBiaya = totbiaya;
		P->Next = NULL;
	}
	return P;	
}

void insertFirst(pembayaran &B,ID_Pembayaran P){
	P->Next = B;
	B = P;
}

void insertAfter(pembayaran &B,ID_Pembayaran Prec,ID_Pembayaran P){
	P->Next = Prec->Next;
	Prec->Next = P;
}

void addPembayaran(pembayaran &B,ID_Pembayaran P){
	if(IsEmpty(B))
		insertFirst(B,P);
	else if(IsOneElement(B))
		insertAfter(B,B,P);
	else
		addPembayaran(B->Next,P);
}


void printPembayaran(pembayaran T,int no){
	if(IsEmpty(T)){

	}else{	
			no++;
			cout<<"|"<<setw(4)<<no<<"|"<<setw(13)<<T->NoTNKB<<"|"<<setw(19)<<T->Nama_Konsumen<<"|"<<setw(20)
			<<T->Alamat<<"|"<<setw(19)<<T->Nama_Driver<<"|"<<setw(6)<<T->Sewa.Tanggal<<"-"<<T->Sewa.Bulan
			<<"-"<<T->Sewa.Tahun<<"|"<<setw(6)<<T->Bayar.Tanggal<<"-"<<T->Bayar.Bulan<<"-"
			<<T->Bayar.Tahun<<"|"<<setw(11)<<T->Denda<<"|"<<setw(13)<<T->totBiaya<<"|"<<endl;
		
		printPembayaran(T->Next,no);
	}
}

void delPenyewaan(Transaksi &L){
	ID_Transaksi P;
	P = L;
	L = L->Next;
	delete(P);
}

void delTransaksi(Transaksi &T,infotype *nama_konsumen,infotype *alamat,infotype *tnkb,
	Date *sewa,Date *kembali,infotype *nama_driver,int *biayasewa,pos select,int no){
	if(!IsEmpty(T)){
		no++;
		if(no==select){
			*nama_konsumen = T->Nama_Konsumen;
			*alamat = T->Alamat;
			*tnkb = T->NoTNKB;
			*sewa = T->Sewa;
			*kembali = T->Kembali;
			*nama_driver = T->Nama_Driver;
			*biayasewa = T->biayaSewa;
			delPenyewaan(T);
		}
		else
			delTransaksi(T->Next,nama_konsumen,alamat,tnkb,sewa,kembali,nama_driver,biayasewa,select,no);
	}
}

void bayarSewa(infotype Nama_Driver,Date kembali,Date Bayar,Date Sewa,int biayaSewa,int &totdenda,int &totbayar){
	int hari = 0;
	int driver = 200000;
	int denda = 100000;

	if(Bayar.Tanggal - kembali.Tanggal >=1)
		hari = Bayar.Tanggal - kembali.Tanggal;
	else
		hari = 0;

	totdenda = hari * denda;
	
	if(Nama_Driver == "")
		totbayar = hitungBayar(totdenda,kembali.Tanggal - Sewa.Tanggal,biayaSewa);
	else
		totbayar = hitungBayar(totdenda,kembali.Tanggal - Sewa.Tanggal,biayaSewa) + driver;
}
