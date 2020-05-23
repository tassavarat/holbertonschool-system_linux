#include <Python.h>

/**
 * print_python_int - print basic information about Python int objects
 * @p: Python object
 */
void print_python_int(PyObject *p)
{
	unsigned long n;
	ssize_t size, i;
	uint32_t *digit;

	if (!PyLong_Check(p))
	{
		puts("Invalid Int Object");
		return;
	}
	size = ((PyVarObject *) p)->ob_size;
	digit = ((PyLongObject *) p)->ob_digit;
	if (size > 3 || (size == 3 && digit[2] > 15))
	{
		puts("C unsigned long int overflow");
		return;
	}
	n = 0;
	for (i = 0; i < (size < 0 ? size * -1 : size); ++i)
		n += digit[i] * (1L << (PyLong_SHIFT * i));
	if (size < 0)
		putchar('-');
	printf("%lu\n", n);
}
