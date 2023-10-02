#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

void stampa_matrice (double **matrice, int k) //stampa una matrice quadrata inserita dall'utente, conoscendo la dimensione n//
{
 for (int i=0; i<k; i++) {
      for (int j=0; j<k; j++) {
          if (fabs(matrice[i][j])<1.e-15 || matrice[i][j] == 0.) cout<<fixed<<setprecision(4)<<0.<<" ";
          else cout<<fixed<<setprecision(4)<<matrice[i][j]<<" ";
                             }
     cout<<'\n'<<'\n';
                         
}

int cerca_valore (double **matrice, int y, int k)//cerca nella colonna x il primo elemento matrice[x1][x] != 0, con x1>x; viene richiamata durante l'esecuzione del programma se l'elemento matrice[x][x] è 0 e restituisce x1//
{  
 int y1=y;
 if (y == k-1 && matrice[y][y] == 0) return (y+1);    
 if (y == k-1 && matrice[y][y] != 0) return (y);
 do ;
 while (matrice[y++][y1]==0 && (y<k));
 if (matrice[y-1][y1] == 0) return (y);
 else return (y-1);
}

void scambio (double **matrice, int y, int y1, int k)//nel caso venisse richiamata la funzione "cerca_valore", questa funzione sposta le righe x1 e x, con x1>x, a condizione che esiste un elemento matrice[x1][x] != 0//
{
 double *sposta;
 sposta = new double [k];                                                       
 sposta = matrice[y1];
 matrice[y1] = matrice[y];
 matrice[y] = sposta;
 delete [] sposta;
}

void gauss (double **matrice_1, double **matrice_2, double c, int y, int k) //esegue l'algoritmo di gauss della matrice a, assieme a quella identità, per trasformarla nella sua inversa//
{
 for (int j=0;j<k;j++) {
         matrice_1[y][j] /= c;
         matrice_2[y][j] /= c;
                       }
 for (int i=0;i<k;i++) {
         c = matrice_1[i][y];
         if (i != y) {
            for (int j=0;j<k;j++) {
                matrice_1[i][j] -= matrice_1[y][j]*c;
                matrice_2[i][j] -= matrice_2[y][j]*c;
                                  }
                     }
                           } 
                        
}

void verifica (double **matrice_1, double **matrice_2, double **matrice_3, int k) //verifica che inv sia l'inversa di a moltiplicando le due matrici e verfificando che il prodotto restituisca la matrice identità//
{
 for (int i=0;i<k;i++) {
        for (int j=0;j<k;j++) {
            matrice_1[i][j] = 0;
            for (int x=0;x<k;x++) {
                matrice_1[i][j]+=matrice_2[i][x]*matrice_3[x][j];
                                  }
                              }
                      }
}


int main () {
  int scelta, n, x1;
  double **a, **orig, **iden, **inv, **fine, coeff;
//ciclo do-while affinchè si possa ripetere il programma tante volte quante ne desidera l'utente//
do {
    cout<<'\n'<<"Ciao! Questo programma permette di eseguire operazioni con matrici quadrate n*n."<<'\n'<<'\n';
    cout<<"Per iniziare, dimmi la dimensione n della tua matrice: "; 
    cin>>n;
    cout<<'\n';
    //allocazione dinamica delle matrici utilizzate nel programma//
    a = new double* [n];
    orig = new double* [n];
    iden = new double* [n];
    inv = new double* [n];
    fine = new double* [n];
    for (int i=0;i<n;i++) {
        a[i] = new double[n];
        orig[i] = new double[n];
        iden[i] = new double[n];
        inv[i] = new double[n];
        fine[i] = new double[n];
                          }
    cout<<"Ora è il momento di scrivere la matrice."<<'\n'<<'\n';
    //riempimento della matrice di partenza dall'inserimento di numeri dalla tastiera//
    for (int i=0;i<n;i++) {
        for (int j=0;j<n;j++) {
            cout<<"Dimmi l'elemento di riga "<<i+1<<" e colonna "<<j+1<<" :";
            cin>>a[i][j];
            orig[i][j] = a[i][j];
            if (i==j) iden[i][j] = 1.;
            else iden[i][j] = 0.;
            inv[i][j] = iden[i][j];              
                              }
                          }
    cout<<"\nEcco la tua matrice a: "<<'\n'<<'\n';
    stampa_matrice (a, n); //stampa la matrice "a" inserita dall'utente//
    cout<<'\n';
    cout<<"Ora proviamo a calcolarci l'inversa della tua matrice."<<'\n'<<'\n'; 
    //questi cicli verificano l'invertibilità della matrice//
    for (int x=0;x<n;x++) {
            coeff = a[x][x];
            x1 = cerca_valore (a, x, n);
            if (x1>(n-1)) {
               cout<<"ERRORE! La matrice non è invertibile poichè il determinante è 0!"<<'\n'<<'\n'<<"Arrivederci!"<<'\n';
               return 1;
                        } 
           scambio (a, x, x1, n);
           scambio (inv, x, x1, n);
           coeff = a[x][x];
           gauss (a, inv, coeff, x, n);}
             //esegue l'algoritmo di gauss sulla matrice a e sulla matrice inv//
    cout<<"Ecco la la matrice inversa di a : "<<'\n'<<'\n';
    stampa_matrice (inv, n); //stampa la matrice inversa di a//
    cout<<"\n\nPer confermare che questa è la matrice inversa, ora verrà mostrato "<<'\n';
    cout<<"il prodotto tra la matrice di partenza e quella inversa, il cui risultato "<<'\n';
    cout<<"dovrà essere la matrice identità. "<<'\n'<<'\n';
    verifica (fine, inv, orig, n);
    cout<<"Ecco il prodotto a*inv(a): "<<'\n'<<'\n';//mostra il prodotto tra la matrice inversa e quella di partenza, che deve dare la     matrice identità//
    stampa_matrice (fine, n);
    //deallocazione di memoria dei puntatori//
    for (int i=0;i<n;i++) {
         delete[] a [i];
         delete[] orig [i];
         delete[] iden [i];
         delete[] inv [i];
         delete[] fine [i];
                      } 
         delete[] a;
         delete[] orig ;
         delete[] iden ;
         delete[] inv;
         delete[] fine;
    cout<<'\n';
    cout<<"Ti è piaciuto? Se vuoi riniziare il programma, premi 1, altrimenti "<<'\n';
    cout<<"premi qualsiasi altro tasto per interromperlo: ";
    cin>>scelta; }
    while (scelta == 1);
    if (scelta!=1) 
    cout<<'\n'<<"Arrivederci!"<<'\n'<<'\n';
}

