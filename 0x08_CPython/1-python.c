#include <Python.h>
#include <stdio.h>

void print_python_list(PyObject *list)
{
	Py_ssize_t i;

	printf("[*] Python list info\n[*] Size of the Python List = %li\n"
			"[*] Allocated = %li\n",
			Py_SIZE(list), ((PyListObject *) list)->allocated);
	for (i = 0; i < Py_SIZE(list); ++i)
		printf("Element %li: %s\n",
				i, Py_TYPE((PyList_GetItem(list, i)))->tp_name);
}
