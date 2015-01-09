/* time.c */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>


/* damit überhaupt ein HTML-Dokument ausgegeben wird */
void print_header(void) {
   printf("Content-Type: text/html\n\n");
}

/* die Kopfzeile eines Standard-HTML-Dokuments;
 * Titel: String, der als Titel erscheinen soll
 */
void print_html_header(char *titel) {
   print_header();
   printf("<html>\n<head>\n");
   printf("<title>%s</title>\n",titel);
   printf("<meta charset=\"utf-8\" />\n");
   printf("<link rel=\"stylesheet\" type=\"text/css\" href=\"http://maltin.pisces.uberspace.de/it2/style.css\" />\n");
   printf("</head><body>\n");
}

/* das Ende eines HTML-Dokuments */
void print_html_end(void) {
   printf("</body></html>\n");
}



void print_time(void) {
   time_t zeit;

   time(&zeit);
   printf("<br/><br/><br/><br/><br/><br/><br/><br/>");
   printf("<p>");
   printf("Aktuelle Systemzeit: ");
   printf("%s\n",ctime(&zeit));
   printf("</p>\n");
}

void printMatrix10F(float m[][10], int z, int s) {
   printf("<table>\n");
   int i,j;
   for(i=0; i<z; i++) { // alle zeilen 
      printf("<tr>\n");
      for(j=0; j<s; j++) { // alle spalten
         printf("<td class=\"output\">%3.1f</td>\n",m[i][j]);
      }
      printf("</tr>\n");
   }
   printf("</table>\n");
}
void printMatrix5F(float m[][5], int z, int s) {
   printf("<table>\n");
   int i,j;
   for(i=0; i<z; i++) { // alle zeilen 
      printf("<tr>\n");
      for(j=0; j<s; j++) { // alle spalten
         printf("<td class=\"output\">%3.1f</td>\n",m[i][j]);
      }
      printf("</tr>\n");
   }
   printf("</table>\n");
}

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
  // ergaenze die Matrix a um eine Einheitsmatrix (rechts anhaengen)
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
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

    if (pivot) {
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
    return 0; 
  }
  // Die angehaengte Einheitsmatrix Matrix hat sich jetzt in 
  // die inverse Matrix umgewandelt; Umkopieren auf die Zielmatrix ainv
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      ainv[i][j] = a[i][n+j];
    }
  }
  return 1;  
}

int main(void) {
   print_html_header("Beleg IT2");
   printf("<div class=\"dokument\">\n");
   char *query;
   printf("<p><a href=\"http://maltin.pisces.uberspace.de/it2/\">zurück</a></p>\n");
   char *lenStr = getenv("CONTENT_LENGTH");
   if(lenStr==NULL) {
      printf("<p1 id=\"error\">\nCONTENT_LENGTH == NULL\n</p1>\n");
      print_html_end();
      return -1;
   } /* else */
   int len = atoi(lenStr);
   char buf[len+1];
   fgets(buf,len+1,stdin);
   /* testausgaben */
   //printf("<p>query: %s</p>\n",buf);
   //printf("<p>content length: %d</p>\n",len);
   int dim; 
   char str[strlen("dimension=")+3];
   sscanf(buf,"dimension=%d",&dim);
   int elements = dim*dim;
   float matrix_in[dim][10]; 
   float matrix_out[dim][5];
   /* parsen: */
   char *delim = "=&";
   char *token = strtok(buf,delim); // zeigt auf 'dimension'
   token = strtok(NULL,delim); // zeigt auf $dim
   token = strtok(NULL,delim); // zeigt auf 'x1'
   int i,j;
   for(i=0; i<dim; i++) { // durch Zeilen iterieren
      for(j=0; j<dim; j++) {
         token = strtok(NULL,delim); // zeigt auf einen Wert
         matrix_in[i][j] = atof(token);
         token = strtok(NULL,delim); // zeigt auf 'xy'
      }
   }
   printf("<div class=\"output\">");
   printf("<div class=\"left\">Eingabematrix:\n");
   printMatrix10F(matrix_in,dim,dim);
   printf("</div>\n");
   printf("<div class=\"center\">\n");
   //printf("<img id=\"arrow\" src=\"http://maltin.pisces.uberspace.de/it2/transparent-arrow-hi.png\" />\n");
   printf("<p id=\"img\"><a href=\"https://github.com/mstiehr-dev/invertMatrix\">=></a></p>\n");
   printf("</div>\n");
   printf("<div class=\"right\">Inverse Matrix:\n");
   Inverse(matrix_in, matrix_out, dim, 0);
   printMatrix5F(matrix_out,dim,dim);
   printf("</div>\n");
   printf("</div>\n");
   printf("<div class=\"time_footer\">\n");
   print_time();
   printf("</div>\n");
   printf("</div>\n");
   print_html_end();
   return EXIT_SUCCESS;
}
