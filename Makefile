
#==============================================================================
#                   Plik Makefile
#==============================================================================
# 
#==============================================================================
# 
.SUFFIXES: .c .cpp .o .h

DIR = `basename $(CURDIR)`
# Nazwy, ktorych bedziemy uzywac
NAME1 = cw1ab
NAME2 = cw1c
NAME3 = cw1d
NAME4 =cw1e


# Program wykonawczy: dodajemy rozszerzenie .c, ale moze byc dowolne.
EXEC1 = $(NAME1)  
EXEC2 = $(NAME2)
EXEC3 = $(NAME3)
EXEC4 = $(NAME4)

# Pliki powstale po kompilacji plikow zrodlowych, tzw. object files
OBJS1  = $(NAME1).o
OBJS2  = $(NAME2).o
OBJS3  = $(NAME3).o
OBJS4  = $(NAME4).o

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



$(EXEC2): $(OBJS2) $(LIBS1) 
	$(LD) -o $@ $(LFLAGS) $^


$(EXEC3): $(OBJS3) $(LIBS1) 
	$(LD) -o $@ $(LFLAGS) $^


$(EXEC4): $(OBJS4) $(LIBS1) 
	$(LD) -o $@ $(LFLAGS) $^


%.o: %.c %.h
	$(CO) $(CFLAGS) -c $<
	
run1: $(EXEC1)
	./$(EXEC1)

run2: $(EXEC2)
	./$(EXEC2)

run3: $(EXEC3)
	./$(EXEC3)

run4: $(EXEC4) 
	./$(EXEC4)






.PHONY: clean tar

clean:                                                     
	rm -f *.o  *~ *.a *.so *.x core core* a.out; rm -rf ${LIB_DIR}
# Archiwizacja i kompresja
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )
