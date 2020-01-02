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
					switch(pilih){
						case 1:
							cout<<"0. Kembali"<<endl;
							cout<<"---------------------------------------------------------------------------------------------------------------"<<endl;
							cout<<"|"<<" No "<<"|"<<"   No TNKB   "<<"|"<<"   Nama Konsumen   "<<"|"
							<<"       Alamat       "<<"|"<<"    Nama Driver    "<<"|"<<"  Mulai Sewa  "<<"|"<<" Pengembalian "<<"|"<<endl;
							cout<<"---------------------------------------------------------------------------------------------------------------"<<endl;
							
							printPenyewaan(Penyewaan,no);
							cout<<"---------------------------------------------------------------------------------------------------------------"<<endl;
							cin>>pilih;
							system("clear");

							break;
						case 2:
							if(!isEmpty(konsumen)){
								do{
									string ulang;
									ulang:
									nama = getNama(konsumen);
									cout<<"Silahkan Saudara "<<nama<<" memilih mobil yang akan disewa"<<endl;
									cout<<"------------------------------------------------------------------------"<<endl;
									cout<<"| No |"<<"   No TNKB  |"<<"       MERK      |"<<"    WARNA   |"<<"  TAHUN  |"
									<<"   BIAYA   |"<<endl;
									cout<<"------------------------------------------------------------------------"<<endl;
									availableMobil(mobil,no);
									cout<<"------------------------------------------------------------------------"<<endl;
									
									cout<<"Pilih mobil : ";
									cin>>select;

									cout<<"Tanggal Sewa [dd-mm-yyyy]\t: ";
									cin>>sewa.Tanggal>>sewa.Bulan>>sewa.Tahun;
									sewa.Tanggal = abs(sewa.Tanggal);
									sewa.Bulan = abs(sewa.Bulan);
									sewa.Tahun = abs(sewa.Tahun);

									cout<<"Tanggal Kembali [dd-mm-yyyy]\t: ";
									cin>>kembali.Tanggal>>kembali.Bulan>>kembali.Tahun;
									//getRealNumber
									kembali.Tanggal = abs(kembali.Tanggal);
									kembali.Bulan = abs(kembali.Bulan);
									kembali.Tahun = abs(kembali.Tahun);

									if(kembali.Tanggal - sewa.Tanggal >=1 && kembali.Bulan - sewa.Bulan >=0
										&& kembali.Tahun - sewa.Tahun >=0){
										cout<<"Dengan Driver [y/N] : ";
										cin>>opsi;
										if(opsi == 'Y' || opsi == 'y')
											Task(&Driver,&nama_driver);
										else
											nama_driver = "";

										Rent(mobil,tnkb,biayasewa,select,no);//Update status mobil
										delKonsumen(&konsumen,&nama,&alamat);//getData Konsumen

										Data_Pinjam = Alokasi(nama,alamat,tnkb,nama_driver,sewa,kembali,biayasewa);
										addPenyewaan(Penyewaan,Data_Pinjam);

									}else{
										cout<<"Sewa minimal 1 hari"<<endl;										
									}
									cout<<"ulangi transaksi [y/N]: ";
									cin>>opsi;
									if(opsi == 'Y' || opsi == 'y'){
										system("clear");
										goto ulang;
										
									}else
										system("clear");
										//break;

								}while(opsi != 'N' || opsi == 'n');

							}else{
								cout<<"Belum ada data konsumen yang tersimpan"<<endl;
							}

							break;
						case 9:
							break;
						default:
							cout<<"Menu yang anda pilih tidak tersedia"<<endl;
					}
				}while(pilih!=9);

				break;
			case 5:
				do{
					cout<<"------------------------------------------------------"<<endl;
					cout<<"\t\t\"TRANSAKSI  PEMBAYARAN\""<<endl;
					cout<<"------------------------------------------------------"<<endl;
					cout<<" 1. Tampilkan Data Pembayaran"<<endl;
					cout<<" 2. Transaksi Pembayaran"<<endl;
					cout<<" 9. Kembali"<<endl;
					cout<<"------------------------------------------------------"<<endl;
					cout<<"Pilih Menu : ";
					cin>>pilih;
					system("clear");
					switch(pilih){
						case 1:
							cout<<"0. Kembali"<<endl;
							cout<<"-----------------------------------------------------------------------------------------------------------------------------------------"<<endl;
							cout<<"|"<<" No "<<"|"<<"   No TNKB   "<<"|"<<"   Nama Konsumen   "<<"|"
							<<"       Alamat       "<<"|"<<"    Nama Driver    "<<"|"<<"  Mulai Sewa  "
							<<"|"<<"  Pembayaran  "<<"|"<<"   Denda   "<<"|"<<" Total Bayar "<<"|"<<endl;
							cout<<"-----------------------------------------------------------------------------------------------------------------------------------------"<<endl;
							
							printPembayaran(Bayar_sewa,no);
							cout<<"-----------------------------------------------------------------------------------------------------------------------------------------"<<endl;
							cin>>pilih;
							system("clear");

							break;
						case 2:
							cout<<"---------------------------------------------------------------------------------------------------------------"<<endl;
							cout<<"|"<<" No "<<"|"<<"   No TNKB   "<<"|"<<"   Nama Konsumen   "<<"|"
							<<"       Alamat       "<<"|"<<"    Nama Driver    "<<"|"<<"  Mulai Sewa  "<<"|"<<" Pengembalian "<<"|"<<endl;
							cout<<"---------------------------------------------------------------------------------------------------------------"<<endl;
							
							printPenyewaan(Penyewaan,no);
							cout<<"---------------------------------------------------------------------------------------------------------------"<<endl;
							cout<<"Pilih Transaksi : ";
							cin>>select;
							cout<<"Masukkan Tanggal [dd-mm-yyyy] : ";
							cin>>bayar.Tanggal>>bayar.Bulan>>bayar.Tahun;
							delTransaksi(Penyewaan,&nama,&alamat,&tnkb,&sewa,&kembali,&nama_driver,&biayasewa,select,no);
							
							//change to available
							inisialisasiMobil(mobil,tnkb); 
							inisialisasiDriver(&Driver,nama_driver);

							//getRealNumber
							bayar.Tanggal = abs(bayar.Tanggal);
							bayar.Bulan = abs(bayar.Bulan);
							bayar.Tahun = abs(bayar.Tahun);
							
							bayarSewa(nama_driver,kembali,bayar,sewa,biayasewa,denda,totbiaya);
							Data_Pembayaran = Alokasi(nama,alamat,tnkb,nama_driver,sewa,bayar,denda,totbiaya);

							addPembayaran(Bayar_sewa,Data_Pembayaran);
							system("clear");

							break;
						case 9:
							break;
						default:
							cout<<"Menu yang anda pilih tidak tersedia"<<endl;
					}
				}while(pilih!=9);

				break;
			case 0:
				cout<<"Back with darkness"<<endl;
				break;
			default:
				cout<<"Menu yang anda pilih tidak tersedia"<<endl;
		}
	}while(pilih != 0);
	
	return 0;
}

void CreateEmpty(List &L){
	L = NULL;	
}

bool IsEmpty(List L){
	return (L == NULL);
}

bool IsOneElement(List L){
	return (IsEmpty(L->Next));
}

bool isRent(List L){
	return (L->sewa == 1);
}

void insertFirst(List &L,address P){
	P->Next = L;
	L = P;
}

void insertAfter(List &L,address Prec,address P){
	P->Next = Prec->Next;
	Prec->Next = P;
}

address alokasi(infotype tnkb,infotype merk,infotype warna,infotype tahun,int biaya){
	address P = new(Mobil);

	if(P == NULL)
		return NULL;
	else{
		P->NoTNKB = tnkb;
		P->Merk = merk;
		P->Warna = warna;
		P->Tahun = tahun;
		P->biayaSewa = biaya;
		P->sewa = 0;
		P->Next = NULL;
		return P;
	}
}

void addMobil(List &L,address P){
	if(IsEmpty(L)){
		insertFirst(L,P);
	}else if(IsOneElement(L)){
		insertAfter(L,L,P);
	}else{
		addMobil(L->Next,P);
	}	
}

void delFirst(List &L){
	address P;
	P = L;
	L = L->Next;
	delete(P);
}

void delMobil(List &L,int select,int no){
	if(!IsEmpty(L)){
		no++;
		if(no == select)
			delFirst(L);
		else
			delMobil(L->Next,select,no);
	}else{}
}

void updateTarif(List &L,int biaya,int select,int no){
	if(!IsEmpty(L)){
		no++;
		if(no == select)
			L->biayaSewa = biaya;
		else
			updateTarif(L->Next,biaya,select,no);
	}else{}
}

void Rent(List &L,infotype &tnkb,int &biayasewa,pos pilih,int no){
	if(!IsEmpty(L)){
		no++;
		if(no==pilih){
			L->sewa = 1;
			tnkb = L->NoTNKB;
			biayasewa = L->biayaSewa;
		}else
			Rent(L->Next,tnkb,biayasewa,pilih,no);
	}
}

void printMobil(List L,int no){
	if(IsEmpty(L)){
		// cout<<"-----------------------------------------------------------------------------------------"<<endl;
	}else{
		no++;
		cout<<"|"<<setw(4)<<no<<"|"<<setw(12)<<L->NoTNKB<<"|"<<setw(17)<<L->Merk<<"|"<<setw(12)<<L->Warna<<"|"
		<<setw(9)<<L->Tahun<<"|"<<setw(11)<<L->biayaSewa<<"|";
		if(L->sewa==0)
			cout<<setw(17)<<"TERSEDIA|"<<endl;
		else
			cout<<setw(17)<<"DISEWAKAN|"<<endl;
		printMobil(L->Next,no);
	}
}

void availableMobil(List L,int no){
	if(IsEmpty(L)){
		// cout<<"-----------------------------------------------------------------------------------------"<<endl;
	}else{
		if(L->sewa == 0){
			no++;
			cout<<"|"<<setw(4)<<no<<"|"<<setw(12)<<L->NoTNKB<<"|"<<setw(17)<<L->Merk<<"|"<<setw(12)<<L->Warna<<"|"
			<<setw(9)<<L->Tahun<<"|"<<setw(11)<<L->biayaSewa<<"|"<<endl;		
		}else{}

		availableMobil(L->Next,no);
	}
}

void inisialisasiMobil(List &L,infotype tnkb){
	if(IsEmpty(L)){

	}else{
		if(L->NoTNKB == tnkb)
			L->sewa = 0;
		inisialisasiMobil(L->Next,tnkb);
	}
}


//Driver
void CreateEmpty(Queue *D){
	(*D).Head = (*D).Tail = -1;
}

bool isEmpty(Queue D){
	return (D.Head == -1 && D.Tail == -1);
}

bool isFull(Queue D){
	return (D.Head < D.Tail && D.Tail - D.Head == DRIVER-1||
		D.Head > D.Tail && D.Head - D.Tail == 1);
}

bool isOneElement(Queue D){
	return (D.Head == D.Tail && D.Head != -1);
}

bool isTask(Queue D){
	return (D.service[D.Head] == 1);
}

void addDriver(Queue *D,infotype ktp,infotype nama,infotype alamat,infotype usia){
	if(!isFull(*D)){
		if(isEmpty(*D)){ //jika masih kosong
			(*D).Head = (*D).Tail = 0;
			(*D).noKTP[(*D).Head] = ktp;
			(*D).Nama[(*D).Head] = nama;
			(*D).Alamat[(*D).Head] = alamat;
			(*D).Usia[(*D).Head] = usia;
			(*D).service[(*D).Head] = 0;
		}else{
			if((*D).Tail == DRIVER-1){ //jika sirkuler
				(*D).Tail = 0;
			}else{
				(*D).Tail++;
			}
			//pengisian 
			(*D).noKTP[(*D).Tail] = ktp;
			(*D).Nama[(*D).Tail] = nama;
			(*D).Alamat[(*D).Tail] = alamat;
			(*D).Usia[(*D).Tail] = usia;
			(*D).service[(*D).Tail] = 0;
		}
	}
}

void updateDriver(Queue *D,infotype update,pos select){
	int element = 0;
	if((*D).Head <= (*D).Tail)
		(*D).Usia[(*D).Head + select - 1] = update;
	else{ //sirkuler
		//count element head to MAX element
		for(pos i = (*D).Head; i <= DRIVER-1;i++)
			element++;

		if(select<=element)
			(*D).Usia[(*D).Head + select - 1] = update;
		else
			(*D).Usia[element - select - 1] = update;
	}
}

void delDriver(Queue *D,pos select){
	int element = 0;

	if(select>=1 && select<=DRIVER){
		if((*D).Head <= (*D).Tail){
			for(pos i = (*D).Head+select-1; i < (*D).Tail;i++){
				(*D).Nama[i] = (*D).Nama[i+1];
				(*D).noKTP[i] = (*D).noKTP[i+1];
				(*D).Alamat[i] = (*D).Alamat[i+1];
				(*D).Usia[i] = (*D).Usia[i+1];
				(*D).service[i] = (*D).service[i+1];
			}
			(*D).Tail--;

		}else{

			for(pos i = (*D).Head; i <= DRIVER-1;i++)
				element++;

			if(select<=element){ //jika masih normal
				for(pos i = (*D).Head; i < DRIVER-1;i++){
					(*D).Nama[i] = (*D).Nama[i+1];
					(*D).noKTP[i] = (*D).noKTP[i+1];
					(*D).Alamat[i] = (*D).Alamat[i+1];
					(*D).Usia[i] = (*D).Usia[i+1];
					(*D).service[i] = (*D).service[i+1];
				}

				for(pos i = 0; i < (*D).Tail;i++){
					(*D).Nama[i] = (*D).Nama[i+1];
					(*D).noKTP[i] = (*D).noKTP[i+1];
					(*D).Alamat[i] = (*D).Alamat[i+1];
					(*D).Usia[i] = (*D).Usia[i+1];
					(*D).service[i] = (*D).service[i+1];
				}
				(*D).Tail--;

			}else{//sirkuler

				if((*D).Tail == 0)
					(*D).Tail = DRIVER-1;

				else{
					for(pos i = element - select-1; i < (*D).Tail;i++){
						(*D).Nama[i] = (*D).Nama[i+1];
						(*D).noKTP[i] = (*D).noKTP[i+1];
						(*D).Alamat[i] = (*D).Alamat[i+1];
						(*D).Usia[i] = (*D).Usia[i+1];
						(*D).service[i] = (*D).service[i+1];
					}
					(*D).Tail--;
				}
			}
		}
	}else{
		cout<<"Pilihan yang anda masukkan tidak tersedia"<<endl;
	}
}

void Task(Queue *D,infotype *nama){
	Queue temp; 
	if(!isEmpty(*D)){
		*nama = (*D).Nama[(*D).Head];
		(*D).service[(*D).Head] = 1;
		temp = *D;

		(*D).Head++;
		if(++(*D).Tail == MAX)
			(*D).Tail = 0;
		else
			(*D).Tail;

		(*D).noKTP[(*D).Tail] = temp.noKTP[temp.Head];
		(*D).Nama[(*D).Tail] = temp.Nama[temp.Head];
		(*D).Alamat[(*D).Tail] = temp.Nama[temp.Head];
		(*D).Usia[(*D).Tail] = temp.Usia[temp.Head];
		(*D).service[(*D).Tail] = temp.service[temp.Head];

	}else{
		cout<<"Belum ada data yang tersimpan"<<endl;
	}
}
