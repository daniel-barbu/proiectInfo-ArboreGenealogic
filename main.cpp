#include <iostream>
#include <fstream>
//#include <algorithm> //sort(a, a+n)
//#include <string.h> //string

using namespace std;
ifstream fin("file.in");
//ofstream fout("file.out");

int n, ad[20][20]={0}; char nume[20][50];

void citire() {
  int a, b;
  fin >> n;
  for (int i=0; i<=n; i++) fin.getline(nume[i],50);
  while (fin >> a >> b) ad[a][b]=ad[b][a]=1;
}

int afisareAd() {
  cout << "   ";
  for (int i=1; i<=n; i++) cout << i << " ";
  cout << endl;
  for (int i=1; i<=n; i++) {
    if (i<10) cout << " "; cout << i << " ";
    for (int y=1; y<=n; y++) {
      cout << ad[i][y] << " ";
      if (y>=10) cout << " ";
    }
    cout << endl;
  }
}

int viz[20];
void dfs(int x){
  viz[x]=1;
  for(int i=1; i<=n; i++)
    if (ad[x][i]==1 && viz[i]==0)
      dfs(i);
}
int tipGraf() {
  int grafComp=1, grafCon=1, grafEul=1, grafHam=1;

  cout << "Neorientat: DA" << endl << "Orientat: NU" << endl << endl;

  //graf complet/partial
  for (int i=1; i<=n; i++)
    for (int y=i+1; y<=n; y++)
      if (ad[i][y]==0) {grafComp=0; break;}
  cout << "Complet: ";
  if (grafComp==1) cout << "DA"<< endl << "Partial: NU" << endl << endl;
    else cout << "NU" << endl << "Partial: DA" << endl << endl;

  //graf conex/non-conex
  dfs(1);
  for(int i=1; i<=n; i++)
    if (viz[i]==0) grafCon=0;
  cout << "Conex: ";
  if (grafCon==1) cout << "DA" << endl << endl;
    else cout << "NU" << endl << endl;

  //graf eulerian/non-eulerian


  //graf hamiltonian/non-hamiltonian


  cout << endl;
}

int nrcomp, viz2[20];
void dfs2(int x) {
  viz2[x]=nrcomp;
  for(int i=1;i<=n;i++)
    if (ad[x][i]==1 && viz2[i]==0)
      dfs2(i);
}
string numeFam(int x) {
  int i=0; char out[50];
  while (nume[x][i]!=' ') {out[i]=nume[x][i]; i++;}
  return out;
}
string numePre(int x) {
  int i=0, y=0; char out[50];
  while (nume[x][i]!=' ') i++;
  i++;
  while (nume[x][i]!=NULL) {out[y]=nume[x][i]; y++; i++;}
  return out;
}
int compCon() {
  for(int i=1; i<=n; i++)
    if (viz2[i]==0) {nrcomp++; dfs2(i);}
  for(int i=1; i<=nrcomp; i++){
    int primul=1;
    for (int j=1; j<=n; j++)
      if (viz2[j]==i) {
        if (primul==1){primul=0; cout << "Familia " << numeFam(j) << ": (" << numeFam(j) << ") " << numePre(j) << ", ";}
          else cout << "(" << numeFam(j) << ") " << numePre(j) << ", ";
      }
    cout << endl;
  }
}

int meniu() {
  int x;
  cout << "   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ " << endl
       << "  | Proiect Informatica - Grafuri Neorientate |" << endl
       << "  |     A R B O R E   G E N E A L O G I C     |" << endl
       << "  |         BARBU DANIEL, 11R2, CNBGC         |" << endl
       << "   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ " << endl << endl
       << "Functiile program:" << endl
       << "1. Afisare matrice adiacenta" << endl
       << "2. Afisare tip graf" << endl
       << "3. Afisare familii (componente conexe)" << endl
       << "4. Afisare cea mai indepartata ruda (lant elementar)" << endl
       << "5. Afisare cel mai lung ciclu elementar" << endl
       << "0. Paraseste programul" << endl << endl
       << "Optiune: "; cin >> x;
  system("cls");
  switch (x) {
    case 1:
      cout << "1. Afisare matrice adiacenta" << endl << endl;
      afisareAd();
      break;
    case 2:
      cout << "2. Afisare tip graf" << endl << endl;
      tipGraf();
      break;
    case 3:
      cout << "3. Afisare familii (componente conexe)" << endl << endl;
      compCon();
      break;
    case 4:
      cout << "4. " << endl << endl;
      afisareAd();
      break;
    case 5:
      cout << "5. " << endl << endl;
      afisareAd();
      break;
    case 0:
      return 0;
      break;
    default:
      cout << "Valoarea trebuie sa fie intre 1 si 5.";
      break;
  }
  cout << endl;
  system("pause");
  system("cls");
  meniu();
}

int main() {
  citire();
  meniu();
}
