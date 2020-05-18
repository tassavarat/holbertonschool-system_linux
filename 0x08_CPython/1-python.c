#include <Python.h>

/**
 * print_python_list - print basic info about Python list objects
 * @p: Python object
 */
void print_python_list(PyObject *p)
{
	Py_ssize_t i;

	printf("[*] Python list info\n"
			"[*] Size of the Python List = %li\n"
			"[*] Allocated = %li\n",
			Py_SIZE(p), ((PyListObject *) p)->allocated);
	for (i = 0; i < Py_SIZE(p); ++i)
		printf("Element %li: %s\n",
				i, Py_TYPE((PyList_GetItem(p, i)))->tp_name);
}
