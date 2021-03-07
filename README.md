pdfpagelabels(1) -- PDF page label reader
=========================================

## About

  pdfpagelabels is a small _Poppler_ based tool for extracting page labels (as opposed to page numbers) from a pdf file.

## Usage

  pdfpagelabels [options] <input.pdf>
  
  -f,--first-page <int>  first page to include in page label list (default: 1)
  -l,--last-page <int>   last page to include in page label list (default: last page)
  -v,--verbose           print verbose output with page number and page label instead of a pure list of labels
  
## Author

  Matthias Heim, 2020 (Matthias.Heim@hep-verlag.ch)