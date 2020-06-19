CC=gcc
STD=-std=gnu99
FLAG=-Wall -Werror
LIB=-lmsg

export CC STD FLAG
all:
	cd lib && make
	$(CC) $(STD) $(FLAG) server.c   -oserver        -static $(LIB) -L lib/ -Iinclude/
	$(CC) $(STD) $(FLAG) open.c     -obin/open      -static $(LIB) -L lib/ -Iinclude/
	$(CC) $(STD) $(FLAG) login.c    -obin/login     -static $(LIB) -L lib/ -Iinclude/
	$(CC) $(STD) $(FLAG) destroy.c  -obin/destory   -static $(LIB) -L lib/ -Iinclude/
	$(CC) $(STD) $(FLAG) unlock.c   -obin/unlock    -static $(LIB) -L lib/ -Iinclude/
	$(CC) $(STD) $(FLAG) save.c     -obin/save      -static $(LIB) -L lib/ -Iinclude/
	$(CC) $(STD) $(FLAG) take.c     -obin/take      -static $(LIB) -L lib/ -Iinclude/
	$(CC) $(STD) $(FLAG) query.c    -obin/query     -static $(LIB) -L lib/ -Iinclude/
	$(CC) $(STD) $(FLAG) transfer.c -obin/transfer  -static $(LIB) -L lib/ -Iinclude/
	$(CC) $(STD) $(FLAG) repass.c   -obin/repass    -static $(LIB) -L lib/ -Iinclude/
	$(CC) $(STD) $(FLAG) client.c   -oclient $(LIB) -L lib/ -Iinclude/

