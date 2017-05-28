test:
	rm -f CharMenu.c CharMenu.h
	cp ../CharMenu.c CharMenu.c
	cp ../CharMenu.h CharMenu.h
	gcc -D TEST_LINUX CharMenu.c test.c mock.c -o test.exe
	@echo "________________\nStart test\n________________"
	@./test.exe
