CC = gcc 
CFLAGSPYLIST = -Wall -Werror -Wextra -pedantic -std=c99 -shared -Wl,-soname,PyList -o libPyList.so -fPIC -I/usr/include/python3.8
CFLAGSLIBPYTHON = -Wall -Werror -Wextra -pedantic -std=c99 -shared -Wl,-soname,libPython.so -o libPython.so -fPIC -I/usr/include/python3.8

.PHONY: 1 2 3 4 5 clean

1:
	$(CC) $(CFLAGSPYLIST) 1-python.c
2:	
	$(CC) $(CFLAGSLIBPYTHON) 2-python.c
3:	
	$(CC) $(CFLAGSLIBPYTHON) 3-python.c
4:	
	$(CC) $(CFLAGSLIBPYTHON) 4-python.c
5:	
	$(CC) $(CFLAGSLIBPYTHON) 5-python.c
clean:
	rm -f *.so
