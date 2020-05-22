#include <Python.h>

/**
 * print_python_string - print basic information about Python string objects
 * @p: Python object
 */
void print_python_string(PyObject *p)
{
	char *type;
	wchar_t *value;

	puts("[.] string object info");
	if (!PyUnicode_Check(p))
	{
		puts("  [ERROR] Invalid String Object");
		return;
	}
	if (PyUnicode_IS_COMPACT_ASCII(p))
		type = "compact ascii";
	else if (PyUnicode_IS_COMPACT(p) && !PyUnicode_IS_ASCII(p))
		type = "compact unicode object";
	value = PyUnicode_AsWideCharString(p, NULL);
	printf("  type: %s\n"
			"  length: %li\n"
			"  value: %ls\n", type, PyUnicode_GET_LENGTH(p), value);
	PyMem_Free(value);
}
