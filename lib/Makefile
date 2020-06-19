all:
	$(CC) $(STD) $(FLAG) -c tools.c -I ../include
	$(CC) $(STD) $(FLAG) -c msg_queue.c -I ../include
	ar -r libmsg.a tools.o msg_queue.o
	$(CC) $(STD) $(FLAG) -c -fpic tools.c -I ../include
	$(CC) $(STD) $(FLAG) -c msg_queue.c -I ../include
	$(CC) -shared tools.o msg_queue.o -o libmsg.so

