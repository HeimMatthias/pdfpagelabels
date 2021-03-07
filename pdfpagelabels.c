#include <poppler.h>
#include <glib.h>
#include <stdio.h>
#include <errno.h>   // for errno
#include <limits.h>  // for INT_MAX
#include <stdlib.h>  // for strtol
#include <stdbool.h>


/*requires poppler: sudo apt-get install libpoppler-glib-dev */
/*compile with gcc -Wall -g -Wextra  pdfpagelabels.c $(pkg-config --cflags --libs poppler-glib) -o pdfpagelabels */

int main(int argc, char *argv[])
{
    GError *error = NULL;
    PopplerDocument *document;
    PopplerPage *page;
    gchar *f;
    gchar *u;

    //g_type_init();

    if (argc < 2) {
		printf("Prints a pdf-file's page labels to stdout.\n(c) 2020 Matthias.Heim@hep-verlag.ch\n\n");
		printf("Usage: pdfpagelabels [options] <input.pdf>\n");
		printf("  -f,--first-page <int>  first page to include in page label list (default: 1)\n");
		printf("  -l,--last-page <int>   last page to include in page label list (default: last page)\n");	
		printf("  -v,--verbose           print verbose output with page number and page label instead of a pure list of labels\n");	
		//g_error("Error: no file name given");
		return 0;
	}  

    if (g_path_is_absolute(argv[argc-1]))
            f = argv[argc-1];
    else
            f = g_build_filename(g_get_current_dir(), argv[argc-1], NULL);

    u = g_filename_to_uri(f, NULL, &error);
    if (!u)
            g_error("oops: %s", error->message);

    document = poppler_document_new_from_file(u, NULL, &error);
    if (!document) {
		g_error("Error: incorrect file name given");
		return -1;
	}
	
	int firstpage = 1;
	int lastpage = poppler_document_get_n_pages (document);
	bool verbose = false;
	
	if (argc > 2) {
		int i;
		for(i=1; i < argc-1; i++) {
			if (!strcmp(argv[i],"-f") || !strcmp(argv[i],"--first-page")) {
				char *p;
				errno = 0;
				long conv = strtol(argv[i+1], &p, 10);
				if (errno != 0 || *p != '\0' || conv > INT_MAX) {
					printf("Error when parsing the arguments for option %s:\n", argv[i]);
					printf("Invalid argument: %s\n", argv[i+1]);
					g_error("Error: Invalid argument.");
				} else {
					firstpage = conv;    
					if ((firstpage<1) || (firstpage>lastpage)) g_error("Error: First page is out of bounds.");
				}
			}
			if (!strcmp(argv[i],"-l") || !strcmp(argv[i],"--last-page")) {
				char *p;
				errno = 0;
				long conv = strtol(argv[i+1], &p, 10);
				if (errno != 0 || *p != '\0' || conv > INT_MAX) {
					printf("Error when parsing the arguments for option %s:\n", argv[i]);
					printf("Invalid argument: %s\n", argv[i+1]);
					g_error("Error: Invalid argument.");
				} else {
					lastpage = conv;    
					if ((lastpage<0) || (firstpage>lastpage)) g_error("Error: First page is out of bounds.");
				}
			}
			if (!strcmp(argv[i],"-v") || !strcmp(argv[i],"--verbose"))
					verbose=true;
		}
	}

    //g_print("Number of pages in document: %d\n", poppler_document_get_n_pages (d));

	int pagenumber;

	for (pagenumber = firstpage-1; pagenumber < lastpage; ++pagenumber) 
	{
		page = poppler_document_get_page(document, pagenumber);
		if (verbose) printf("Page label of page number %d: %s\n", pagenumber+1, poppler_page_get_label(page));
		else printf("%s\n", poppler_page_get_label(page));
	}

    return 0;
}