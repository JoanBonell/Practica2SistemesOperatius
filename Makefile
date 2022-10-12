#Makefile de rmsf.c
compilar:
	gcc -o rmsf rmsf.c
executar: rmsf.o
	./rmsf
esborrar:
	rm -rf rmsf rmsf.o
testmultiples:
	./rmsf < testmultiples.txt
testuno:
	./rmsf < testuno.txt
# Fi de fitxer.