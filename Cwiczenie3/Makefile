
#==============================================================================
#                   Plik Makefile
#==============================================================================
# 
#==============================================================================
# 
.SUFFIXES: .c .cpp .o .h

DIR = `basename $(CURDIR)`
# Nazwy, ktorych bedziemy uzywac
NAME1 = sygnaly
NAME2 = sygnaly2
NAME3 = sygnal3

# Program wykonawczy: dodajemy rozszerzenie .c, ale moze byc dowolne.
EXEC1  = $(NAME1).c  
EXEC2  = $(NAME2).c  
EXEC3  = $(NAME3).c  

# Pliki powstale po kompilacji plikow zrodlowych, tzw. object files
OBJS1  = $(NAME1)
OBJS2  = $(NAME2)
OBJS3  = $(NAME3)

# Dolaczane biblioteki (poza standardowymi). 
# Makra moga byc puste, np. przewidziane na przyszlosc.
LIBS1 = 
LIBS2 = 
LIBS3 =
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


$(EXEC2): $(OBJS2) $(LIBS2) 
	$(LD) -o $@ $(LFLAGS) $^



$(EXEC3): $(OBJS3) $(LIBS3) 
	$(LD) -o $@ $(LFLAGS) $^


%.o: %.c %.h
	$(CO) $(CFLAGS) -c $<

.PHONY: run1

run1: $(EXEC1)
	./$(EXEC1)


run2: $(EXEC2) $(EXEC1)
	./$(EXEC2)


run3: $(EXEC3)
	./$(EXEC3)




.PHONY: clean tar

clean:                                                     
	rm -f *.o  *~ *.a *.so *.x core core* a.out; rm -rf ${LIB_DIR}
# Archiwizacja i kompresja
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )
