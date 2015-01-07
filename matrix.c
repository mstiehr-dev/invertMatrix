/* time.c */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/* die Kopfzeile eines Standard-HTML-Dokuments;
 * Titel: String, der als Titel erscheinen soll
 */
void print_html_header(char *titel) {
   printf("<html><head>\n");
   printf("<title>%s</title>\n",titel);
   printf("<meta charset=\"utf-8\" />");
   printf("</head><body>\n");
}

/* das Ende eines HTML-Dokuments */
void print_html_end(void) {
   printf("</body></html>\n");
}

/* damit überhaupt ein HTML-Dokument ausgegeben wird */
void print_header(void) {
   printf("Content-Type: text/html\n\n");
}

void print_time(void) {
   time_t zeit;

   time(&zeit);
   printf("Aktuelle Systemzeit: ");
   printf("%s\n",ctime(&zeit));
}

void greet(char *s) {
	printf("<p>hallo %s!</p>",s);
	return;
}

int main(void) {
   print_header();
   print_html_header("Hallo Welt in CGI mit Zeit\n");
   char *name, *query;
   printf("<br/><br/>der alte gibt den code nicht raus<br/><br/>");
   printf("<p><a href=\"http://maltin.pisces.uberspace.de/it2/\">reload</a></p>");
/* method POST */
   char *lenStr = getenv("CONTENT_LENGTH");
   int len = atoi(lenStr);
   char buf[len+1];
   fgets(buf,len+1,stdin);
   printf("query: %s<br/>",buf);
   printf("content length: %d<br/>",len);
   // anzahl der elemente: 
   int elements; 
   char str[20];
   sscanf(buf,"dimension=%d",&elements);
   elements *= elements; 
   int matrix[elements];
   int i=0;
   while(i<elements) {
      //strtok
      i++;
   }
   printf("Elemente: %d<br/>",elements);
   //char anrede[ilen+1];
   //sscanf(buf,"textfeld=%s",anrede);
   //greet(anrede);
   print_time();
   print_html_end();
   return EXIT_SUCCESS;
}
