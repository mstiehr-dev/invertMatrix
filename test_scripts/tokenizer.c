/* tokenizer.c */ 


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

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
  printf("\n");
  return 0;  
}



void printMatrixD(int m[][10], int z, int s) {
	int i,j;
	for(i=0; i<z; i++) { // alle zeilen 
		printf("|");
		for(j=0; j<s; j++) { // alle spalten
			printf("%3d|",m[i][j]);
		}
		printf("\n");
	}
}

void printMatrix5F(float m[][5], int z, int s) {
	int i,j;
	for(i=0; i<z; i++) { // alle zeilen 
		printf("|");
		for(j=0; j<s; j++) { // alle spalten
			printf("%3.1f|",m[i][j]);
		}
		printf("\n");
	}
}

void printMatrix10F(float m[][10], int z, int s) {
	int i,j;
	for(i=0; i<z; i++) { // alle zeilen 
		printf("|");
		for(j=0; j<s; j++) { // alle spalten
			printf("%3.1f|",m[i][j]);
		}
		printf("\n");
	}
}

int genWorkingMatrix(float m[][10], int dim) {
	if (dim == 2) {
		m[0][0] = 2.0f; // x1
		m[0][1] = 5.0f; // x2
		m[1][0] = 1.0f; // x3
		m[1][1] = 3.0f; // x4
	} else 
	if (dim == 3) {
		m[0][0] = 1.0f; // x1
		m[0][1] = 2.0f; // x2
		m[0][2] = 0.0f; // x3
		m[1][0] = 2.0f; // x4
		m[1][1] = 4.0f; // x5
		m[1][2] = 1.0f; // x6
		m[2][0] = 2.0f; // x7
		m[2][1] = 1.0f; // x8
		m[2][2] = 0.0f; // x9

	}
	return 0;
}

int main(int argc, char **argv) {
	//char query[] = "dimension=4&x1=10&x2=20&x3=30&x11=40&x5=50&x6=60&x7=70&x8=80&x9=90&x10=30&x11=40&x12=120&x13=130&x14=140&x15=150&x16=160";
	char query[] = "dimension=3&x1=1&x2=2&x3=0&x4=2&x5=4&x6=1&x7=2&x8=1&x9=0";
	char *delim = "=&";
	char *tok = strtok(query,delim); // dimension
	tok = strtok(NULL,delim); // var dim
	int dim; 
	dim = atoi(tok);
	printf("looking for %d variables\n",dim*dim);
	float inMatrix[dim][10];
	int i,j;
	for(i=0;i<dim;i++) { // alle Zeilen 
		for(j=0; j<dim; j++) { // alle Spalten
			tok = strtok(NULL,delim); // $x
			tok = strtok(NULL,delim); // value
			printf("x%d: %s\n",(i*dim)+j+1,tok);
			inMatrix[i][j] = atof(tok);
		}		
	}
	printf("vorher:\n");
	printMatrix10F(inMatrix,dim,dim);
	float outMatrix[dim][5];


	Inverse(inMatrix, outMatrix, dim,1);

	printf("nachher:\n");
	printMatrix5F(outMatrix,dim,dim);

	float exM[2][10];
	float exMout[2][5];
	genWorkingMatrix(exM,2);
	printMatrix10F(exM,2,2);
	Inverse(exM,exMout,2,1);
	printMatrix5F(exMout,2,2);

	printf("done.");
}