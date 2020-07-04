# 0x08. CPython

## Requirements
* Allowed editors: vi, vim, emacs
* All your files will be compiled on Ubuntu 14.04 LTS
* All your files should end with a new line
* A README.md file, at the root of the folder of the project is mandatory

---

### [0. Lists big O](./0-python_lists_bigO)
Write the big O notations for the following lists operations (one per line, in this exact order):

* L1 - Assigning. Example: holberton[98] = 402
* L2 - Appending. Example: holberton.append(98)
* L3 - Concatenating a list of n elements. Example: holberton + [98, 402]
* L4 - Inserting an item at a given position. Example: holberton.insert(98, 402)
* L5 - Removing an element. Example: holberton.remove(98)
* L6 - Removing and returning the last item in the list. Example: holberton.pop()
* L7 - Poping an element at a given position. Example: holberton.pop(98)
* L8 - Clearing a list. Example: holberton.clear()
* L9 - Counting the list. Example: holberton.count()
* L10 - Sorting the list. Example: holberton.sort()
* L11 - Reversing the list. Example: holberton.reverse()
* L12 - Deleting the list. Example: del holberton

### [1. CPython #0: Python lists](./1-python.c)
CPython is the reference implementation of the Python programming language. Written in C, CPython is the default and most widely used implementation of the language.
Since we now know a bit of C, we can look at what is happening under the hood of Python. Let’s have fun with Python and C, and let’s look at what makes Python so easy to use.

Create a C function that prints some basic info about Python lists.

* Prototype: void print_python_list(PyObject *p);
* Format: see example
* Python version: 3.4
* Your shared library will be compiled with this command line: gcc -Wall -Werror -Wextra -pedantic -std=c99 -shared -Wl,-soname,PyList -o libPyList.so -fPIC -I/usr/include/python3.4 1-python.c
* OS: Ubuntu 14.04 LTS
* Start by reading:
	* listobject.h
	* object.h
	* Common Object Structures
	* List Objects
```
julien@ubuntu:~/CPython$ gcc -Wall -Werror -Wextra -pedantic -std=c99 -shared -Wl,-soname,PyList -o libPyList.so -fPIC -I/usr/include/python3.4 1-python.c
julien@ubuntu:~/CPython$ cat 1-test_lists.py
import ctypes

lib = ctypes.CDLL('./libPyList.so')
lib.print_python_list.argtypes = [ctypes.py_object]
l = ['hello', 'World']
lib.print_python_list(l)
del l[1]
lib.print_python_list(l)
l = l + [4, 5, 6.0, (9, 8), [9, 8, 1024], "Holberton"]
lib.print_python_list(l)
l = []
lib.print_python_list(l)
l.append(0)
lib.print_python_list(l)
l.append(1)
l.append(2)
l.append(3)
l.append(4)
lib.print_python_list(l)
l.pop()
lib.print_python_list(l)
julien@ubuntu:~/CPython$ python3 1-test_lists.py
[*] Python list info
[*] Size of the Python List = 2
[*] Allocated = 2
Element 0: str
Element 1: str
[*] Python list info
[*] Size of the Python List = 1
[*] Allocated = 2
Element 0: str
[*] Python list info
[*] Size of the Python List = 7
[*] Allocated = 7
Element 0: str
Element 1: int
Element 2: int
Element 3: float
Element 4: tuple
Element 5: list
Element 6: str
[*] Python list info
[*] Size of the Python List = 0
[*] Allocated = 0
[*] Python list info
[*] Size of the Python List = 1
[*] Allocated = 4
Element 0: int
[*] Python list info
[*] Size of the Python List = 5
[*] Allocated = 8
Element 0: int
Element 1: int
Element 2: int
Element 3: int
Element 4: int
[*] Python list info
[*] Size of the Python List = 4
[*] Allocated = 8
Element 0: int
Element 1: int
Element 2: int
Element 3: int
julien@CPython:~/CPython$
```

### [2. CPython #1: PyBytesObject](./2-python.c)
Create two C functions that print some basic info about Python lists and Python bytes objects.

Python lists:

* Prototype: void print_python_list(PyObject *p);
* Format: see example

Python bytes:

* Prototype: void print_python_bytes(PyObject *p);
* Format: see example
* Line “first X bytes”: print a maximum of 10 bytes
* If p is not a valid PyBytesObject, print an error message (see example)
* Read /usr/include/python3.4/bytesobject.h

About:

* Python version: 3.4
* Your shared library will be compiled with this command line: gcc -Wall -Werror -Wextra -pedantic -std=c99 -shared -Wl,-soname,libPython.so -o libPython.so -fPIC -I/usr/include/python3.4 2-python.c
* You are not allowed to use the following macros/functions:
	* Py_SIZE
	* Py_TYPE
	* PyList_GetItem
	* PyBytes_AS_STRING
	* PyBytes_GET_SIZE
```
julien@ubuntu:~/CPython$ python3 --version
Python 3.4.3
julien@ubuntu:~/CPython$ gcc -Wall -Werror -Wextra -pedantic -std=c99 -shared -Wl,-soname,libPython.so -o libPython.so -fPIC -I/usr/include/python3.4 2-python.c
julien@ubuntu:~/CPython$ cat 2-tests.py
import ctypes

lib = ctypes.CDLL('./libPython.so')
lib.print_python_list.argtypes = [ctypes.py_object]
lib.print_python_bytes.argtypes = [ctypes.py_object]
s = b"Hello"
lib.print_python_bytes(s);
b = b'\xff\xf8\x00\x00\x00\x00\x00\x00';
lib.print_python_bytes(b);
b = b'What does the \'b\' character do in front of a string literal?';
lib.print_python_bytes(b);
l = [b'Hello', b'World']
lib.print_python_list(l)
del l[1]
lib.print_python_list(l)
l = l + [4, 5, 6.0, (9, 8), [9, 8, 1024], b"Holberton", "Betty"]
lib.print_python_list(l)
l = []
lib.print_python_list(l)
l.append(0)
lib.print_python_list(l)
l.append(1)
l.append(2)
l.append(3)
l.append(4)
lib.print_python_list(l)
l.pop()
lib.print_python_list(l)
l = ["Holberton"]
lib.print_python_list(l)
lib.print_python_bytes(l);
julien@ubuntu:~/CPython$ python3 2-tests.py
[.] bytes object info
  size: 5
  trying string: Hello
  first 6 bytes: 48 65 6c 6c 6f 00
[.] bytes object info
  size: 8
  trying string: �
  first 9 bytes: ff f8 00 00 00 00 00 00 00
[.] bytes object info
  size: 60
  trying string: What does the 'b' character do in front of a string literal?
  first 10 bytes: 57 68 61 74 20 64 6f 65 73 20
[*] Python list info
[*] Size of the Python List = 2
[*] Allocated = 2
Element 0: bytes
[.] bytes object info
  size: 5
  trying string: Hello
  first 6 bytes: 48 65 6c 6c 6f 00
Element 1: bytes
[.] bytes object info
  size: 5
  trying string: World
  first 6 bytes: 57 6f 72 6c 64 00
[*] Python list info
[*] Size of the Python List = 1
[*] Allocated = 2
Element 0: bytes
[.] bytes object info
  size: 5
  trying string: Hello
  first 6 bytes: 48 65 6c 6c 6f 00
[*] Python list info
[*] Size of the Python List = 8
[*] Allocated = 8
Element 0: bytes
[.] bytes object info
  size: 5
  trying string: Hello
  first 6 bytes: 48 65 6c 6c 6f 00
Element 1: int
Element 2: int
Element 3: float
Element 4: tuple
Element 5: list
Element 6: bytes
[.] bytes object info
  size: 9
  trying string: Holberton
  first 10 bytes: 48 6f 6c 62 65 72 74 6f 6e 00
Element 7: str
[*] Python list info
[*] Size of the Python List = 0
[*] Allocated = 0
[*] Python list info
[*] Size of the Python List = 1
[*] Allocated = 4
Element 0: int
[*] Python list info
[*] Size of the Python List = 5
[*] Allocated = 8
Element 0: int
Element 1: int
Element 2: int
Element 3: int
Element 4: int
[*] Python list info
[*] Size of the Python List = 4
[*] Allocated = 8
Element 0: int
Element 1: int
Element 2: int
Element 3: int
[*] Python list info
[*] Size of the Python List = 1
[*] Allocated = 1
Element 0: str
[.] bytes object info
  [ERROR] Invalid Bytes Object
julien@ubuntu:~/CPython$
```

### [3. CPython #2: PyFloatObject](./3-python.c)
Create three C functions that print some basic info about Python lists, Python bytes an Python float objects.

Python lists:

* Prototype: void print_python_list(PyObject *p);
* Format: see example
* If p is not a valid PyListObject, print an error message (see example)

Python bytes:

* Prototype: void print_python_bytes(PyObject *p);
* Format: see example
* Line “first X bytes”: print a maximum of 10 bytes
* If p is not a valid PyBytesObject, print an error message (see example)

Python float:

* Prototype: void print_python_float(PyObject *p);
* Format: see example
* If p is not a valid PyFloatObject, print an error message (see example)
* Read /usr/include/python3.4/floatobject.h

About:

* Python version: 3.4
* You are allowed to use the C standard library
* Your shared library will be compiled with this command line: gcc -Wall -Werror -Wextra -pedantic -std=c99 -shared -Wl,-soname,libPython.so -o libPython.so -fPIC -I/usr/include/python3.4 3-python.c
* You are not allowed to use the following macros/functions:
	* Py_SIZE
	* Py_TYPE
	* PyList_Size
	* PyList_GetItem
	* PyBytes_AS_STRING
	* PyBytes_GET_SIZE
	* PyBytes_AsString
	* PyFloat_AS_DOUBLE
	* PySequence_GetItem
	* PySequence_Fast_GET_SIZE
	* PySequence_Fast_GET_ITEM
	* PySequence_ITEM
	* PySequence_Fast_ITEMS

NOTE:

* The python script will be launched using the -u option (Force stdout to be unbuffered).
* It is strongly advised to either use setbuf(stdout, NULL); or fflush(stdout) in your C functions IF you choose to use printf. The reason to that is that Pythonsprintand libCs printf don’t share the same buffer, and the output can appear disordered.
```
julien@ubuntu:~/CPython$ python3 --version
Python 3.4.3
julien@ubuntu:~/CPython$ gcc -Wall -Werror -Wextra -pedantic -std=c99 -shared -Wl,-soname,libPython.so -o libPython.so -fPIC -I/usr/include/python3.4 3-python.c
julien@ubuntu:~/CPython$ cat 3-tests.py
#!/usr/bin/python3 -u

import ctypes

lib = ctypes.CDLL('./libPython.so')
lib.print_python_list.argtypes = [ctypes.py_object]
lib.print_python_bytes.argtypes = [ctypes.py_object]
lib.print_python_float.argtypes = [ctypes.py_object]
s = b"Hello"
lib.print_python_bytes(s);
b = b'\xff\xf8\x00\x00\x00\x00\x00\x00';
lib.print_python_bytes(b);
b = b'What does the \'b\' character do in front of a string literal?';
lib.print_python_bytes(b);
l = [b'Hello', b'World']
lib.print_python_list(l)
del l[1]
lib.print_python_list(l)
l = l + [4, 5, 6.0, (9, 8), [9, 8, 1024], b"Holberton", "Betty"]
lib.print_python_list(l)
l = []
lib.print_python_list(l)
l.append(0)
lib.print_python_list(l)
l.append(1)
l.append(2)
l.append(3)
l.append(4)
lib.print_python_list(l)
l.pop()
lib.print_python_list(l)
l = ["Holberton"]
lib.print_python_list(l)
lib.print_python_bytes(l);
f = 3.14
lib.print_python_float(f);
l = [-1.0, -0.1, 0.0, 1.0, 3.14, 3.14159, 3.14159265, 3.141592653589793238462643383279502884197169399375105820974944592307816406286]
print(l)
lib.print_python_list(l);
lib.print_python_float(l);
lib.print_python_list(f);
julien@ubuntu:~/CPython$ ./3-tests.py
[.] bytes object info
  size: 5
  trying string: Hello
  first 6 bytes: 48 65 6c 6c 6f 00
[.] bytes object info
  size: 8
  trying string: ??
  first 9 bytes: ff f8 00 00 00 00 00 00 00
[.] bytes object info
  size: 60
  trying string: What does the 'b' character do in front of a string literal?
  first 10 bytes: 57 68 61 74 20 64 6f 65 73 20
[*] Python list info
[*] Size of the Python List = 2
[*] Allocated = 2
Element 0: bytes
[.] bytes object info
  size: 5
  trying string: Hello
  first 6 bytes: 48 65 6c 6c 6f 00
Element 1: bytes
[.] bytes object info
  size: 5
  trying string: World
  first 6 bytes: 57 6f 72 6c 64 00
[*] Python list info
[*] Size of the Python List = 1
[*] Allocated = 2
Element 0: bytes
[.] bytes object info
  size: 5
  trying string: Hello
  first 6 bytes: 48 65 6c 6c 6f 00
[*] Python list info
[*] Size of the Python List = 8
[*] Allocated = 8
Element 0: bytes
[.] bytes object info
  size: 5
  trying string: Hello
  first 6 bytes: 48 65 6c 6c 6f 00
Element 1: int
Element 2: int
Element 3: float
[.] float object info
  value: 6.0
Element 4: tuple
Element 5: list
Element 6: bytes
[.] bytes object info
  size: 9
  trying string: Holberton
  first 10 bytes: 48 6f 6c 62 65 72 74 6f 6e 00
Element 7: str
[*] Python list info
[*] Size of the Python List = 0
[*] Allocated = 0
[*] Python list info
[*] Size of the Python List = 1
[*] Allocated = 4
Element 0: int
[*] Python list info
[*] Size of the Python List = 5
[*] Allocated = 8
Element 0: int
Element 1: int
Element 2: int
Element 3: int
Element 4: int
[*] Python list info
[*] Size of the Python List = 4
[*] Allocated = 8
Element 0: int
Element 1: int
Element 2: int
Element 3: int
[*] Python list info
[*] Size of the Python List = 1
[*] Allocated = 1
Element 0: str
[.] bytes object info
  [ERROR] Invalid Bytes Object
[.] float object info
  value: 3.14
[-1.0, -0.1, 0.0, 1.0, 3.14, 3.14159, 3.14159265, 3.141592653589793]
[*] Python list info
[*] Size of the Python List = 8
[*] Allocated = 8
Element 0: float
[.] float object info
  value: -1.0
Element 1: float
[.] float object info
  value: -0.1
Element 2: float
[.] float object info
  value: 0.0
Element 3: float
[.] float object info
  value: 1.0
Element 4: float
[.] float object info
  value: 3.14
Element 5: float
[.] float object info
  value: 3.14159
Element 6: float
[.] float object info
  value: 3.14159265
Element 7: float
[.] float object info
  value: 3.141592653589793
[.] float object info
  [ERROR] Invalid Float Object
  [ERROR] Invalid List Object
julien@ubuntu:~/CPython$
```

### [4. CPython #3: Python Strings](./4-python.c)
Create a function that prints Python strings.

* Prototype: void print_python_string(PyObject *p);
* Format: see example
* If p is not a valid string, print an error message (see example)
* Read: Unicode HOWTO

About:

* Python version: 3.4
* You are allowed to use the C standard library
* Your shared library will be compiled with this command line: gcc -Wall -Wextra -pedantic -Werror -std=c99 -shared -Wl,-soname,libPython.so -o libPython.so -fPIC -I/usr/include/python3.4 4-python.c
```
julien@ubuntu:~/0x07. Pyhton Strings$ cat 4-tests.py
import ctypes

lib = ctypes.CDLL('./libPython.so')
lib.print_python_string.argtypes = [ctypes.py_object]
s = "The spoon does not exist"
lib.print_python_string(s)
s = "ложка не существует"
lib.print_python_string(s)
s = "La cuillère n'existe pas"
lib.print_python_string(s)
s = "勺子不存在"
lib.print_python_string(s)
s = "숟가락은 존재하지 않는다."
lib.print_python_string(s)
s = "スプーンは存在しない"
lib.print_python_string(s)
s = b"The spoon does not exist"
lib.print_python_string(s)
julien@ubuntu:~/0x07. Pyhton Strings$ gcc -Wall -Wextra -pedantic -Werror -std=c99 -shared -Wl,-soname,libPython.so -o libPython.so -fPIC -I/usr/include/python3.4 4-python.c
julien@ubuntu:~/0x07. Pyhton Strings$ python3 ./4-tests.py
[.] string object info
  type: compact ascii
  length: 24
  value: The spoon does not exist
[.] string object info
  type: compact unicode object
  length: 19
  value: ложка не существует
[.] string object info
  type: compact unicode object
  length: 24
  value: La cuillère n'existe pas
[.] string object info
  type: compact unicode object
  length: 5
  value: 勺子不存在
[.] string object info
  type: compact unicode object
  length: 14
  value: 숟가락은 존재하지 않는다.
[.] string object info
  type: compact unicode object
  length: 10
  value: スプーンは存在しない
[.] string object info
  [ERROR] Invalid String Object
julien@ubuntu:~/0x07. Pyhton Strings$
```

### [5. CPython Integers](./5-python.c)
Create a C function that prints Python integers.

* Prototype: void print_python_int(PyObject *p);
* Format: see example
* If p is not a valid string, print an error message (see example)
* The function should first translate the Python int to a C unsigned long int and then use printf to print the number
	* If the absolute value of the number is too big to be stored in a C unsigned long int, print C unsigned long int overflow, followed by a new line
* Read: /usr/include/python3.4/longintrepr.h

About:

* Python version: 3.4
* You are allowed to use the C standard library
* You are only allowed to use the following Python macros / functions:
	* PyLong_SHIFT
	* PyLong_Check
* Your shared library will be compiled with this command line: gcc -Wall -Wextra -pedantic -Werror -std=c99 -shared -Wl,-soname,libPython.so -o libPython.so -fPIC -I/usr/include/python3.4 5-python.c
```
julien@ubuntu:~/Python Integers$ cat 5-tests.py
import ctypes

lib = ctypes.CDLL('./libPython.so')
lib.print_python_int.argtypes = [ctypes.py_object]
i = -1
lib.print_python_int(i)
i = 0
lib.print_python_int(i)
i = 1
lib.print_python_int(i)
i = 123456789
lib.print_python_int(i)
i = -123456789
lib.print_python_int(i)
i = 12345678901
lib.print_python_int(i)
i = 10304719833506056896
lib.print_python_int(i)
i = -9223372036854775808
lib.print_python_int(i)
i = 9223372036854775807
lib.print_python_int(i)
i = 18446744073709551615
lib.print_python_int(i)
i = -18446744073709551615
lib.print_python_int(i)
i = 18446744073709551616
lib.print_python_int(i)
i = "1"
lib.print_python_int(i)
julien@ubuntu:~/Python Integers$
julien@ubuntu:~/Python Integers$ gcc -Wall -Wextra -pedantic -Werror -std=c99 -shared -Wl,-soname,libPython.so -o libPython.so -fPIC -I/usr/include/python3.4 5-python.c
julien@ubuntu:~/Python Integers$ python3 5-tests.py
-1
0
1
123456789
-123456789
12345678901
10304719833506056896
-9223372036854775808
9223372036854775807
18446744073709551615
-18446744073709551615
C unsigned long int overflow
Invalid Int Object
julien@ubuntu:~/Python Integers$
```
