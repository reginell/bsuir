#include "stdafx.h" 
#include <iostream> 
#include <string> 

using namespace std;

class Policlinica {
private:
  string FIO;
  string Adres;
  string Vrach;
  int Vremia;
  int Kabinet;
public:
  Policlinica() = default;
  ~Policlinica() = default;
  void getPoliclinica() {};
  void setPoliclinica(const string &FIO_set, const string &Adres_set, const string &Vrach_set, int Vremia_set, int Kabinet_set) {
    FIO = FIO_set;
    Adres = Adres_set;
    Vrach = Vrach_set;
    Vremia = Vremia_set;
    Kabinet = Kabinet_set;
  }
  void ClearKeyboardBuffer();
  void Vvod_Mass(Policlinica *polic, size_t count);
  void Show_Mass(Policlinica *polic, size_t count);
  void Change(Policlinica *polic, size_t count);
  void Search(Policlinica *polic, size_t count);
  void Sorting(Policlinica *polic, size_t count);
};

void Policlinica::ClearKeyboardBuffer() {
  cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void Policlinica::Vvod_Mass(Policlinica *polic, size_t count) {
  for (size_t i = 0; i<count; i++) {
    cout << u8"\nПациент № " << i + 1;
    cout << u8"\nВведите ФИО пациента:";
    cin >> polic[i].FIO;
    cout << u8"Введите адрес пациента:";
    cin >> polic[i].Adres;
    cout << u8"Введите ФИО врача:";
    cin >> polic[i].Vrach;
    cout << u8"Введите время приема:";
    cin >> polic[i].Vremia;
    cout << u8"Введите № кабинета:";
    cin >> polic[i].Kabinet;
    ClearKeyboardBuffer();
  }
}

void Policlinica::Show_Mass(Policlinica *polic, size_t count) {
  cout << "____________________________________________________________________________" << endl;
  for (size_t i = 0; i<count; i++) {
    cout << u8"\nПациент № " << i + 1 << endl;
    cout << u8"ФИО пациента:" << polic[i].FIO << endl;
    cout << u8"Адрес пациента:" << polic[i].Adres << endl;
    cout << u8"ФИО врача:" << polic[i].Vrach << endl;
    cout << u8"Время приема:" << polic[i].Vremia << endl;
    cout << u8"№ кабинета:" << polic[i].Kabinet << endl;
    cout << "____________________________________________________________________________" << endl;
  }
}

void Policlinica::Change(Policlinica *polic, size_t count) {
  for (size_t i = 0; i<count; i++) {
    cout << u8"\nВведите ФИО пациента:";
    getline(cin, polic[i].FIO);
  }
}

void Policlinica::Search(Policlinica *polic, size_t count) {
  int keyword;
  cout << u8"Поиск по кабинетам: ";
  cin >> keyword;

  for (size_t i = 0; i<count; i++) {
    if (keyword == polic[i].Kabinet)
      cout << u8"Нашёл:" << polic[i].Kabinet;
  }
}

void Policlinica::Sorting(Policlinica *polic, size_t count) {
  cout << u8"Сортировка\n";
  int temp = 0;
  for (size_t i = 0; i < (count - 1); i++)
    if (polic[i].Vremia > polic[i + 1].Vremia) {
      std::swap(polic[i].Vremia, polic[i + 1].Vremia);
    }
  for (size_t i = 0; i < count; i++) {
    cout << polic[i].Vremia;
  }
}

int main() {
  setlocale(LC_CTYPE, "Russian");
  size_t count;
  cout << u8"Введите кооличество элементов массива:";
  cin >> count;

  Policlinica *polic = new Policlinica[count];

  polic->ClearKeyboardBuffer();
  polic->Vvod_Mass(polic, count);
  polic->Show_Mass(polic, count);
  //polic->Change(polic, count);
  //polic->Search(polic, count);
  //polic->Sorting(polic, count);

  delete[] polic;

  return 0;
}