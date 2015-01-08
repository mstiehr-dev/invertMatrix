/* time.c */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


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
         printf("<td>%3.1f</td>\n",m[i][j]);
      }
      printf("</tr>\n");
   }
   printf("</table>\n");
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
   printf("<img id=\"arrow\" src=\"http://maltin.pisces.uberspace.de/it2/transparent-arrow-hi.png\" />\n");
   printf("</div>\n");
   printf("<div class=\"right\">Inverse Matrix:\n");
   printMatrix10F(matrix_in,dim,dim);
   printf("</div>\n");
   printf("</div>\n");
   printf("<div class=\"time_footer\">\n");
   print_time();
   printf("</div>\n");
   printf("</div>\n");
   print_html_end();
   return EXIT_SUCCESS;
}
