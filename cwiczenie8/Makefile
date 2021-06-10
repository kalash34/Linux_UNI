

GEN_EXE = client server \
	


EXE = ${GEN_EXE} 

all : ${EXE}

allgen : ${GEN_EXE}

clean : 
	${RM} ${EXE} *.o

client.o server.o : wiadomosc.h

showall :
	@ echo ${EXE}

${EXE} : ${TLPI_LIB}		

