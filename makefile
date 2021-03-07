# Specify the target file and the install directory
OUTPUTFILE=pdfpagelabels
INSTALLDIR=/usr/local/bin

# Default target
.PHONY: all
all: $(OUTPUTFILE)

# Build binary from c file, include poppler libraries
$(OUTPUTFILE): pdfpagelabels.c
	gcc -Wall -g -Wextra  $< $$(pkg-config --cflags --libs poppler-glib) -o $@

# Copy binary to the local user bin directory, use sudo
.PHONY: install
install:
#	mkdir -p $(INSTALLDIR)
	cp -p $(OUTPUTFILE) $(INSTALLDIR)

# Delete hello
.PHONY: clean 
clean:
	rm -f $(OUTPUTFILE)