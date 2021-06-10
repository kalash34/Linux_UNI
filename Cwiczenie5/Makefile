#==============================================================================
#                   Plik Makefile
#==============================================================================
# 
#==============================================================================
# 
.SUFFIXES: .c .cpp .o .h

DIR = `basename $(CURDIR)`
# Nazwy, ktorych bedziemy uzywac
NAME4 = piatka
NAME1 = producent
NAME2 = konsument
NAME3 = cw5

#Nasze pliki
FILE1=surowiec.txt
FILE2=towar.txt


# Program wykonawczy: dodajemy rozszerzenie .c, ale moze byc dowolne.
EXEC1  = $(NAME1)
# Pliki powstale po kompilacji plikow zrodlowych, tzw. object files
OBJS1  = $(NAME1).o
EXEC2 = $(NAME2)
OBJS2 =$(NAME2).o
EXEC3 = $(NAME3)
OBJS3 =$(NAME3).o


EXEC4 = $(NAME4)
OBJS4 =$(NAME4).o

#HEADS1 = $(NAME1).h
#HEADS2 = $(NAME2).h

$(OBJS2): $(HEADS2)
$(OBJS1): $(HEADS1)



# Dolaczane biblioteki (poza standardowymi). 
# Makra moga byc puste, np. przewidziane na przyszlosc.
LIBS1  = 

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

$(EXEC4): $(OBJS4) 
	$(LD) -o $@ $(LFLAGS) $^




%.o: %.c %.h
	$(CO) $(CFLAGS) -c $<

.PHONY: run1 

run1: $(EXEC1)
	./$(EXEC1)
run2: $(EXEC2)
	./$(EXEC2)
run3: $(EXEC3)
	./$(EXEC3)



run4: $(EXEC4)
	./$(EXEC4)
	#moja interpretacja to uruchomienie tego programu dwa razy aby zarowno proces konsumenta i producenta dzialal
	#w obydwu
separate: $(EXEC3)
	xterm -hold -title producent -e ./$(EXEC3)  & xterm -hold -title konsument -e ./$(EXEC3)


jedynka: piatka.o
	$(CC) -o $@ $^

piatka.o: piatka.c
	$(CC) -c $<

jeden: jedynka


dwa: run1 run2 run3 separate  


.PHONY: clean tar

clean:                                                     
	rm -f *.o  *~ *.a *.so *.x core core* a.out; rm -rf ${LIB_DIR}

# Archiwizacja i kompresja

tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )
