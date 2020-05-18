#include <Python.h>

/**
 * print_python_bytes - print basic info about Python byte objects
 * @p: Python object
 */
void print_python_bytes(PyObject *p)
{
	Py_ssize_t size, i;
	char *s;

	puts("[.] bytes object info");
	if (!PyBytes_Check(p))
	{
		puts("  [ERROR] Invalid Bytes Object");
		return;
	}
	size = PyBytes_Size(p);
	s = PyBytes_AsString(p);
	printf("  size: %li\n"
			"  trying string: %s\n"
			"  first %li bytes:",
			size, s, size < 10 ? size + 1 : 10);
	for (i = 0; i <= size && i < 10; ++i)
		printf(" %02hhx", s[i]);
	putchar('\n');
}

/**
 * print_python_list - print basic info about Python list objects
 * @p: Python object
 */
void print_python_list(PyObject *p)
{
	Py_ssize_t i, size;
	PyObject *item;

	size = PyList_Size(p);
	printf("[*] Python list info\n"
			"[*] Size of the Python List = %li\n"
			"[*] Allocated = %li\n",
			size, ((PyListObject *) p)->allocated);
	for (i = 0; i < size; ++i)
	{
		item = PyList_GET_ITEM(p, i);
		printf("Element %li: %s\n",
				i, item->ob_type->tp_name);
		if (PyBytes_Check(item))
			print_python_bytes(item);
	}
}
