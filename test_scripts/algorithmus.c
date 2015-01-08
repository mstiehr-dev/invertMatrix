//Inverse einer Matrix
#include <math.h>
#include <stdio.h>


int Inverse (float a[][10], float ainv[][5], int n,int druck) 
{ //druck=1: Ausdruck der Schritte
  int   i, j;                    // Zeile, Spalte
  int   s;                       // Elimininationsschritt
  int   pzeile;                  // Pivotzeile
  int   fehler = 0;              // Fehlerflag
  float f,h;                     // Multiplikationsfaktor, Hilfsvar.
  const float Epsilon = 0.01f;   // Genauigkeit
  float Maximum;                 // Zeilenpivotisierung
  
  int pivot = 1;
  //Ausgabe Original-Matrix 
  if (druck) {
     printf("Ausgangsmatrix:\n");
     for (i = 0; i < n; i++) {
	       printf("\n");
		  for (j = 0; j < n; j++)
         printf("%7.2f   ",a[i][j]);
	 }
  }
  // ergaenze die Matrix a um eine Einheitsmatrix (rechts anhaengen)
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++)
    {
      a[i][n+j] = 0.0;
      if (i == j)
        a[i][n+j] = 1.0;
    }
  }
  
  
  // die einzelnen Eliminationsschritte
  s = 0;
  do {  // Pivotisierung vermeidet unnoetigen Abbruch bei einer
	    // Null in der Diagnonalen und erhoeht die Rechengenauigkeit
    Maximum = fabs(a[s][s]);
    if (pivot)
    {
       pzeile = s ; 
       for (i = s+1; i < n; i++)
         if (fabs(a[i][s]) > Maximum) {
           Maximum = fabs(a[i][s]) ;
           pzeile = i;
         }
    }
    fehler = (Maximum < Epsilon);

    if (fehler) break;           // nicht loesbar 

    if (pivot)
    {
      if (pzeile != s)  // falls erforderlich, Zeilen tauschen
      {  
        for (j = s ; j < 2*n; j++) {
          h = a[s][j];
          a[s][j] = a[pzeile][j];
          a[pzeile][j]= h;
        }
      }
    }

    // Eliminationszeile durch Pivot-Koeffizienten f = a[s][s] dividieren
    f = a[s][s];
    for (j = s; j < 2*n; j++)
      a[s][j] = a[s][j] / f;

    // Elimination --> Nullen in Spalte s oberhalb und unterhalb der 
    // Diagonalen durch Addition der mit f multiplizierten
    // Zeile s zur jeweiligen Zeile i
    for (i = 0; i < n; i++ ) {
      if (i != s) 
      {
        f = -a[i][s];                 // Multiplikationsfaktor
        for (j = s; j < 2*n ; j++)    // die einzelnen Spalten
          a[i][j] += f*a[s][j];       // Addition der Zeilen i, s
      }
    }
     
  //Ausgabe Matrix nach jedem Schritt
	 if (druck) {
 	  printf("\n\nNach %1i-tem Eliminationschritt:\n", s+1);
      for (i = 0; i < n; i++) {
	    printf("\n");
		for (j = 0; j < n; j++) printf("%7.2f   ",a[i][j]);
	  }
	 }    
    s++;
  } while ( s < n ) ;

  if (fehler) 
  {
    printf ("\n\nInverse: Matrix ist singulaer - es existiert keine inverse Matrix\n");
    return 1; 
  }
  // Die angehaengte Einheitsmatrix Matrix hat sich jetzt in 
  // die inverse Matrix umgewandelt; Umkopieren auf die Zielmatrix ainv
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      ainv[i][j] = a[i][n+j];
    }
  }
  return 0;  
}
int main() {
  //float m[5][10]={{0,0,2,1,1,5},{1,0,0,2,1,5},{1,1,0,0,2,7},{2,1,1,0,0,12}, {0,2,1,1,0,11}};
 float m[3][10]={{-1,6,2},{3,-4,-2},{2,-2,-1}};
 float minv[5][5];
 //float m[3][6]={{2,3,2},{1,2,1},{1,-1,0}};
 //float m[3][6]={{-1,6,2},{3,-4,-2},{2,-2,-1}};
 //float m[4][8]={{1,1,0,0},{1,1,1,0},{0,1,1,1},{0,0,1,1}};
 int i,j,n=5;
 if (Inverse (m, minv, n,0)==0){ 
    printf ("\n\nInverse Matrix:");
    for (i = 0; i < n; i++) {
	    printf("\n");
		  for (j = 0; j < n; j++)
        printf("%7.2f   ",minv[i][j]);
	  }
 }
 printf("\n");
 return 0;
}