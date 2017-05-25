test:
	#~ gcc -D LINUX_TEST CharMenu.c -c -o CharMenu.o
	#~ gcc -D LINUX_TEST Test_CharMenu.c -c -o Test_CharMenu.o
	#~ gcc CharMenu.o Test_CharMenu.o -o test.exe
	rm CharMenu.c CharMenu.h settings.h
	cp ../CharMenu.c CharMenu.c
	cp ../CharMenu.h CharMenu.h
	cp ../settings.h settings.h
	gcc -D LINUX_TEST CharMenu.c test.c -o test.exe
	./test.exe
