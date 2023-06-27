#include <Python.h>
#include <stdio.h>

void print_python_bytes(PyObject *pObj) {
    PyBytesObject *pBytesObj = (PyBytesObject *)pObj;

    printf("[.] bytes object info\n");
    printf("  size: %ld\n", PyBytes_Size(pObj));
    printf("  trying string: %s\n", PyBytes_AsString(pObj));
    printf("  first %ld bytes:", PyBytes_Size(pObj) + 1);
    for (Py_ssize_t i = 0; i <= PyBytes_Size(pObj); i++) {
        printf(" %02x", (unsigned char)pBytesObj->ob_sval[i]);
    }
    printf("\n");
}

void print_python_list(PyObject *pObj) {
    PyListObject *pListObj = (PyListObject *)pObj;

    printf("[*] Python list info\n");
    printf("[*] Size of the Python List = %ld\n", PyList_Size(pObj));
    printf("[*] Allocated = %ld\n", pListObj->allocated);

    for (Py_ssize_t i = 0; i < PyList_Size(pObj); i++) {
        PyObject *pItem = PyList_GetItem(pObj, i);
        printf("Element %ld: ", i);

        if (PyBytes_Check(pItem)) {
            printf("bytes\n");
            print_python_bytes(pItem);
        } else if (PyFloat_Check(pItem)) {
            printf("float\n");
            printf("[.] float object info\n");
            printf("  value: %f\n", PyFloat_AsDouble(pItem));
        } else if (PyList_Check(pItem)) {
            printf("list\n");
            print_python_list(pItem);
        } else if (PyTuple_Check(pItem)) {
            printf("tuple\n");
        } else if (PyLong_Check(pItem)) {
            printf("int\n");
        } else if (PyUnicode_Check(pItem)) {
            printf("str\n");
        } else {
            printf("[ERROR] Invalid Object\n");
        }
    }
}

void print_python_list_info(PyObject *pObj) {
    PyListObject *pListObj = (PyListObject *)pObj;

    printf("[*] Python list info\n");
    printf("[*] Size of the Python List = %ld\n", PyList_Size(pObj));
    printf("[*] Allocated = %ld\n", pListObj->allocated);
}

void print_python_float(PyObject *pObj) {
    PyFloatObject *pFloatObj = (PyFloatObject *)pObj;

    printf("[.] float object info\n");
    printf("  value: %f\n", pFloatObj->ob_fval);
}

int main(void) {
    PyObject *pList;
    PyObject *pValue;

    Py_Initialize();

    pList = PyList_New(0);

    pValue = PyBytes_FromStringAndSize("Hello", 5);
    PyList_Append(pList, pValue);
    Py_DECREF(pValue);

    pValue = PyBytes_FromStringAndSize("World", 5);
    PyList_Append(pList, pValue);
    Py_DECREF(pValue);

    pValue = PyList_New(0);
    PyList_Append(pValue, pValue);
    PyList_Append(pList, pValue);
    Py_DECREF(pValue);

    pValue = PyFloat_FromDouble(3.14);
    PyList_Append(pList, pValue);
    Py_DECREF(pValue);

    printf("[*] Python list info\n");
    printf("[*] Size of the Python List = %ld\n", PyList_Size(pList));
    printf("[*] Allocated = %ld\n", ((PyListObject *)pList)->allocated);

    for (Py_ssize_t i = 0; i < PyList_Size(pList); i++) {
        PyObject *pItem = PyList_GetItem(pList, i);
        printf("Element %ld: ", i);

        if (PyBytes_Check(pItem)) {
            printf("bytes\n");
            print_python_bytes(pItem);
        } else if (PyFloat_Check(pItem)) {
            printf("float\n");
            print_python_float(pItem);
        } else if (PyList_Check(pItem)) {
            printf("list\n");
            print_python_list_info(pItem);
        } else if (PyTuple_Check(pItem)) {
            printf("tuple\n");
        } else if (PyLong_Check(pItem)) {
            printf("int\n");
        } else if (PyUnicode_Check(pItem)) {
            printf("str\n");
        } else {
            printf("[ERROR] Invalid Object\n");
        }
    }

    Py_Finalize();

    return 0;
}
