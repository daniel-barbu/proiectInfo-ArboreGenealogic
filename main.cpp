#include <iostream>
#include <fstream>

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

void afisareAd() { //1
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
void dfs(int x){ //2
  viz[x]=1;
  for(int i=1; i<=n; i++)
    if (ad[x][i]==1 && viz[i]==0)
      dfs(i);
}
void tipGraf() { //2
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
  if (grafCon==1) cout << "DA";
    else cout << "NU";
  cout << endl;
}

int nrcomp=0, viz2[20];
void dfs2(int x) { //3
  viz2[x]=nrcomp;
  for(int i=1;i<=n;i++)
    if (ad[x][i]==1 && viz2[i]==0)
      dfs2(i);
}
string numeFam(int x) { //returneaza numele de familie al lui x
  int i=0; char out[50];
  while (nume[x][i]!=' ') {out[i]=nume[x][i]; i++;}
  return out;
}
string numePre(int x) { //returneaza prenumele lui x
  int i=0, y=0; char out[50];
  while (nume[x][i]!=' ') i++;
  i++;
  while (nume[x][i]!=NULL) {out[y]=nume[x][i]; y++; i++;}
  return out;
}
void compCon() { //3
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

int minDistance(int dist[], bool sptSet[]){ //4
  int min = INT_MAX, min_index;
  for (int v = 1; v <= n; v++)
    if (sptSet[v] == false && dist[v] <= min)
      min = dist[v], min_index = v;
  return min_index;
}

void dijkstra(int src, int (&dist)[20]) { //4
  bool sptSet[n];
  for (int i = 1; i <= n; i++)
    dist[i] = INT_MAX, sptSet[i] = false;
  dist[src] = 0;
  for (int count = 1; count <= n - 1; count++) {
    int u = minDistance(dist, sptSet);
    sptSet[u] = true;
    for (int v = 1; v <= n; v++)
      if (!sptSet[v] && ad[u][v] && dist[u] != INT_MAX && dist[u] + ad[u][v] < dist[v])
        dist[v] = dist[u] + ad[u][v];
  }
}

void lantLung() { //4
  int x=-1;
  cout << "4. Afisare cea mai indepartata ruda (lant elementar)" << endl << endl;
  cout << "Cea mai indepartata ruda de persoana cu indicele: ";  cin >> x;
  if (!(x>=1 && x<=n)) {
    cout << endl << "Valoarea trebuie sa fie intre 1 si " << n << "." << endl << endl;
    system("pause");
    system("cls");
    lantLung();
  }
  else {
    cout << endl;
    int distLant[20], distMax=-1, pers[20], nrPers=1;
    dijkstra(x, distLant);
    for (int i=1; i<=n; i++)
      if (distLant[i]>=1 && distLant[i]<n) {
        if (distLant[i]>distMax) {nrPers=1; pers[nrPers]=i; distMax=distLant[i];}
        else if (distLant[i]==distMax) {nrPers++; pers[nrPers]=i;}
      }
    if (nrPers==1) cout << "Cea mai indepartata ruda de " << nume[x] << " (" << x << ") este " << nume[pers[nrPers]] << " (" << pers[nrPers] << "). ";
    else {
      cout << "Cele mai indepartate rude de " << nume[x] << " (" << x << ") sunt ";
      for (int i=1; i<nrPers; i++)
        cout << nume[pers[i]] << " (" << pers[i] << "), ";
      cout << nume[pers[nrPers]] << " (" << pers[nrPers] << ").";
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
      lantLung();
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
