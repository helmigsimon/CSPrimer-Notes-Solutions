#define PY_SSIZE_T_CLEAN
#include <Python.h>

static PyObject *cvarint_encode(PyObject *self, PyObject *args) {
    unsigned long long val = 0;
    
    if (!PyArg_ParseTuple(args, "K", &val)){
        return NULL;
    }
    char arr[10];
    int parts_length = 0;
    while (val > 0){
        int part = val & 0x7f;
        val >>= 7;
        int res = val ? 0x80 : 0x00;
        part |= res;
        arr[parts_length] = part;
        parts_length++;
    }
    return PyBytes_FromStringAndSize(byte_arr, parts_length);
}

static PyObject *cvarint_decode(PyObject *self, PyObject *args) {
    Py_buffer varn;

    if (!PyArg_ParseTuple(args, "y*", &varn)){
        return NULL;
    }
    char *data = varn.buf;
    Py_ssize_t length = varn.len;
    unsigned long long n = 0;
    for (int i=length-1; i>=0; i--){
        n <<= 7;
        n |= (data[i] & 0x7f);
    }
    return PyLong_FromUnsignedLongLong(n);
}

static PyMethodDef CVarintMethods[] = {
    {"encode", cvarint_encode, METH_VARARGS, "Encode an integer as varint."},
    {"decode", cvarint_decode, METH_VARARGS,
     "Decode varint bytes to an integer."},
    {NULL, NULL, 0, NULL}};

static struct PyModuleDef cvarintmodule = {
    PyModuleDef_HEAD_INIT, "cvarint",
    "A C implementation of protobuf varint encoding", -1, CVarintMethods};

PyMODINIT_FUNC PyInit_cvarint(void) { 
    return PyModule_Create(&cvarintmodule); 
}
