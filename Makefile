CC=g++
CFLAGS=-g
TARGET:server.exe
LIBS=-lpthread
WINDOWLIBS=-lws2_32
OBJS=ClientDbManager.o 		 		\
			ClientServiceManager.o 		 \
			ConnectionAcceptor.o 	 \
			ServerController.o 				  \
			network_utils.o					\
			TcpClient.o

server.exe:server.o ${OBJS}
	${CC} ${CFLAGS} ${OBJS} server.o -o server.exe ${LIBS} ${WINDOWLIBS}

server.o:server.cpp
	${CC} ${CFLAGS} -c server.cpp -o server.o

ClientDbManager.o:ClientDbManager.cpp
	${CC} ${CFLAGS} -c ClientDbManager.cpp -o ClientDbManager.o

ClientServiceManager.o:ClientServiceManager.cpp
	${CC} ${CFLAGS} -c ClientServiceManager.cpp -o ClientServiceManager.o

ConnectionAcceptor.o:ConnectionAcceptor.cpp
	${CC} ${CFLAGS} -c ConnectionAcceptor.cpp -o ConnectionAcceptor.o

ServerController.o:ServerController.cpp
	${CC} ${CFLAGS} -c ServerController.cpp -o ServerController.o

TcpClient.o:TcpClient.cpp
	${CC} ${CFLAGS} -c TcpClient.cpp -o TcpClient.o

network_utils.o:network_utils.cpp
	${CC} ${CFLAGS} -c network_utils.cpp -o network_utils.o 

clean:
	rm -f *.o
	rm -f *exe
