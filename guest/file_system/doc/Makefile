file = report
compile = pdflatex -shell-escape $(file).tex

all:
	make clean; \
	$(compile); $(compile); \
 	zathura $(file).pdf

.PHONY: clean
clean:
	rm *.aux *.bbl *.bcf *.blg *.log *.out *.run.xml *.toc; rm -rf _minted-report *.pygtex

