#Document name:
DOC="FeynmanGraphs"
#Remove old version:
rm *.pdf
#Compile:
pdflatex $DOC.tex
mf *.mf
pdflatex $DOC.tex
pdflatex $DOC.tex
#Remove auxiliary files:
rm *.aux *.600pk *2602gf *.tfm *.mf *.log FeynmanDiagrams.t*
