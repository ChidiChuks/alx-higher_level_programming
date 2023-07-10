#include <Python.h>

void print_python_string(PyObject *p);

void print_python_string(PyObject *p) {
    Py_ssize_t length;
    Py_UCS4 max;
    Py_UCS4 codepoint;

    printf("[.] string object info\n");

    if (!PyUnicode_Check(p)) {
        printf("  [ERROR] Invalid String Object\n");
        return;
    }

    length = PyUnicode_GET_LENGTH(p);
    max = PyUnicode_MAX_CHAR_VALUE(p);

    printf("  type: %s\n", (max <= 127) ? "compact ascii" : "compact unicode object");
    printf("  length: %ld\n", length);
    printf("  value: %ls\n", PyUnicode_AsWideCharString(p, NULL));
}
