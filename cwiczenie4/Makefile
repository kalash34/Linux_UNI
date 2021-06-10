#==============================================================================
#                   Plik Makefile
#==============================================================================
# 
#==============================================================================
# 
.SUFFIXES: .c .cpp .o .h

DIR = `basename $(CURDIR)`
# Nazwy, ktorych bedziemy uzywac
NAME1 = czwarte

#Nasze pliki
FILE1=surowiec.txt
FILE2=towar.txt




# Program wykonawczy: dodajemy rozszerzenie .c, ale moze byc dowolne.
EXEC1  = $(NAME1)
# Pliki powstale po kompilacji plikow zrodlowych, tzw. object files
OBJS1  = $(NAME1).o
# Dolaczane biblioteki (poza standardowymi). 
# Makra moga byc puste, np. przewidziane na przyszlosc.
LIBS1  = 
# Pliki naglowkowe
HEADS1 = 
#------------------------------------------------------------------------------
LIB_DIR = ./lib
#------------------------------------------------------------------------------
# Opcje kompilatora i linkera
CFLAGS = -Wall -std=c99 -pedantic -O -fPIC
LFLAGS = -Wall -std=c99 -pedantic -O
# Biblioteki linkera zainstalowane w systemie 

LDLIBS = -lm
# Kompilator i linker 
CO = gcc
LD = $(CO)


$(EXEC1): $(OBJS1) $(LIBS1) 
	$(LD) -o $@ $(LFLAGS) $^



%.o: %.c %.h
	$(CO) $(CFLAGS) -c $<



.PHONY: run1 
run1: $(EXEC1)
	./$(EXEC1)




my_compare:
	cmp -s $(FILE1) $(FILE2); \
	RETVAL=$$?; \
	if [ $$RETVAL -eq 0 ]; then \
		echo "Takie same"; \
	else \
		echo "Rozne"; \
	fi



all: run1 my_compare





.PHONY: clean tar

clean:                                                     
	rm -f *.o  *~ *.a *.so *.x core core* a.out; rm -rf ${LIB_DIR}
# Archiwizacja i kompresja
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )
