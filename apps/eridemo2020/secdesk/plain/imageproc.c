#include "imageproc.h"

#ifndef __STUBBED
PyObject *pName, *pModule, *pDict, *pFunc, *pArgs;
#endif

int start_imageprocessor(void) {
   return 0;
}

int stop_imageprocessor(void) {
   return 0;
}

int start_recognizer(void) { 
   /* XXX: need to call model load here and save to global var */
   return 0;
}

int stop_recognizer(void) { 
   /* XXX: ought to free model resources */
   return 0;
}

int get_features(char *imagefile, double embedding[static 128]) {
    memset(embedding, 0, 128 * sizeof(double)); /* Cue for GEDL */
#ifndef __STUBBED
    setenv("PYTHONPATH", ".", 1);
    Py_Initialize();

    pName = PyUnicode_FromString(RECOGNIZER_MODULE);
    if (!pName) {
        PyErr_Print();
        goto out;
    }

    pModule = PyImport_Import(pName);
    if (!pModule) {
        PyErr_Print();
        goto out1;
    }

    pFunc = PyObject_GetAttrString(pModule, "calcEncodings");
    if (!pFunc) {
        PyErr_Print();
        goto out2;
    }

    pArgs = PyTuple_New(2);

    PyObject *obj = Py_BuildValue("s#", imagefile, strlen(imagefile));
    PyTuple_SetItem(pArgs, 0, obj);

    char t[32] = "cnn";
    PyObject *obj2 = Py_BuildValue("s#", t, strlen(t));
    PyTuple_SetItem(pArgs, 1, obj2);

    if (!PyCallable_Check(pFunc)) {
        printf("Function calEncodings not callable !\n");
        goto out3;
    }

    PyObject* pValue = PyObject_CallObject(pFunc, pArgs);
    if (!PyList_Check(pValue)) {
        printf("return value not a list!\n");
        goto out3;
    }

    int countArgs = (int) PyList_Size(pValue);
    if (countArgs != 3) {
        printf("return value not a list!\n");
        goto out3;
    }

    PyObject *encodings = PyList_GetItem(pValue, 0);

    int count = (int) PyList_Size(encodings);
    for (int i = 0; i < 1; i++) {
        PyObject *ptemp = PyList_GetItem(pValue, i);
        if (!PyList_Check(ptemp)) {
            printf("encoding is not a list: %d\n", i);
            continue;
        }

        int countIn = (int) PyList_Size(ptemp);
        if (countIn != 128) {
            printf("unexpectd number of entries in an encoding: %d:%d\n", i, countIn);
            continue;
        }
        for (int j = 0; j < countIn; j++) {
            PyObject *pObj = PyList_GetItem(ptemp, j);

            PyObject *objRepIn = PyObject_Repr(pObj);
            PyObject* str = PyUnicode_AsEncodedString(objRepIn, "utf-8", "~E~");
            const char *bytes = PyBytes_AS_STRING(str);
            embedding[j] = (float) strtod(bytes, NULL);
        }
    }

out3:
    Py_DECREF(pFunc);
out2:
    Py_DECREF(pModule);
out1:
    Py_DECREF(pName);
out:
    Py_FinalizeEx();

#endif /* __STUBBED */
  return 0;
}

int recognize(double embedding[static 128]) {
    int id = 666; /* When stubbed, always return 666 */
    memcpy(embedding, embedding, 128 * sizeof (double)); /* Cue for GEDL */

#ifndef __STUBBED
    id = -1; 

    // Closure: invoke the python recognize method at the remote site
//    PyObject *pName, *pModule, *pDict, *pFunc, *pArgs;
    npy_intp dims[2] = { 1, 128 };
    PyObject *py_array;


//    setenv("PYTHONPATH", ".", 1);
//    Py_Initialize();

//    pName = PyUnicode_FromString("local");
//    if (!pName) {
//        PyErr_Print();
//        goto out;
//    }
//
//    pModule = PyImport_Import(pName);
//    if (!pModule) {
//        PyErr_Print();
//        goto out1;
//    }

    pFunc = PyObject_GetAttrString(pModule, "recognize");
    if (!pFunc) {
        PyErr_Print();
        goto out2;
    }

    pDict = PyModule_GetDict(pModule);
    if (!pDict) {
        PyErr_Print();
        goto out3;
    }

    double encodings[1][128];
    for (int i = 0; i < 128; i++)
        encodings[0][i] = embedding[i];

    // Required for the C-API : http://docs.scipy.org/doc/numpy/reference/c-api.array.html#importing-the-api
    import_array();
    py_array = PyArray_SimpleNewFromData(2, dims, NPY_DOUBLE, encodings);
    if (!py_array) {
        PyErr_Print();
        goto out4;
    }

    pArgs = PyTuple_New(1);
    PyTuple_SetItem(pArgs, 0, py_array);

    if (!PyCallable_Check(pFunc)) {
        PyErr_Print();
        goto out5;
    }

    // Closure: collect and return a list, len=length(encodings) of names of recognized faces
    // 'send' the list back to the local site.
    PyObject* pNames = PyObject_CallObject(pFunc, pArgs);
    if (!PyList_Check(pNames)) {
        printf("names are not a list:\n");
        goto out5;
    }

    int count = (int) PyList_Size(pNames);
    // char *names = malloc(sizeof(char *) * count);
    for (int i = 0; i < count; i++) {
        PyObject *ptemp = PyList_GetItem(pNames, i);

        char *cstr;
        PyArg_Parse(ptemp, "s", &cstr);  /* convert to C */

        id = strtol(cstr, NULL, 10);
        printf("recognized %s, ID=%d\n", cstr, id);
    }

out5:
    Py_DECREF(py_array);
out4:
    Py_DECREF(pDict);
out3:
    Py_DECREF(pFunc);
out2:
//    Py_DECREF(pModule);
out1:
//    Py_DECREF(pName);
out:

//    Py_FinalizeEx();

#endif

  return id;
}

