#include "imageproc.h"

#ifndef __STUBBED
PyObject *data;
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
    PyObject *pName, *pModule, *pDict, *pFunc, *pArgs;

    setenv("PYTHONPATH", ".", 1);
    Py_Initialize();

    pModule = PyImport_ImportModule(RECOGNIZER_MODULE);
    if (!pModule) {
        PyErr_Print();
        goto out;
    }

    pFunc = PyObject_GetAttrString(pModule, "calcEncodings");
    if (!pFunc) {
        PyErr_Print();
        goto out;
    }

    PyObject* pValue;
    PyObject* arg1, *arg2;
    if (!PyCallable_Check(pFunc)) {
        printf("Function calEncodings not callable !\n");
    }
    else {
        pArgs = PyTuple_New(2);

        arg1 = Py_BuildValue("s#", imagefile, strlen(imagefile));
        PyTuple_SetItem(pArgs, 0, arg1);

        char t[32] = "cnn";
        arg2 = Py_BuildValue("s#", t, strlen(t));
        PyTuple_SetItem(pArgs, 1, arg2);
   
        pValue = PyObject_CallObject(pFunc, pArgs);
        if (!PyList_Check(pValue)) {
            printf("return value not a list!\n");
        }
    }
    
    int countArgs = (int) PyList_Size(pValue);
    if (countArgs != 3) {
        printf("number of return values != 3: %d\n", countArgs);
        goto out;
    }

    PyObject *encodings = PyList_GetItem(pValue, 0);
    
    int count = (int) PyList_Size(encodings);
    if (count != 1) {
        printf("number of encodings != 1: %d\n", count);
        goto out;
    }

    PyObject *enc = PyList_GetItem(encodings, 0);
    if (!PyList_Check(enc)) {
        printf("encoding is not a list\n");
        goto out;
    }

    int countIn = (int) PyList_Size(enc);
    if (countIn != 128) {
        printf("unexpectd number of entries in an encoding: %d\n", countIn);
        goto out;
    }
    
    for (int j = 0; j < countIn; j++) {
        PyObject *pObj = PyList_GetItem(enc, j);

        PyObject *objRepIn = PyObject_Repr(pObj);
        PyObject* str = PyUnicode_AsEncodedString(objRepIn, "utf-8", "~E~");
        const char *bytes = PyBytes_AS_STRING(str);
        embedding[j] = (float) strtod(bytes, NULL);
    }
    
out:
/*
    Py_DECREF(pModule);
    Py_DECREF(arg1);
    Py_DECREF(arg2);
    Py_DECREF(pArgs);
    Py_DECREF(pFunc);
    //    Py_DECREF(enc);
    Py_DECREF(pValue);
    Py_DECREF(encodings);
//    Py_Finalize();  ///////////////////////////////////////////////////
    printf("XXXXXXXXXXXXXX 2 \n");
*/
#endif /* __STUBBED */
  return 0;
}

#ifndef __STUBBED
int init_recognizer(PyObject *pModule) {
    int ret = 0;

    PyObject *pFunc = PyObject_GetAttrString(pModule, "init_recognizer");
    if (!pFunc) {
        PyErr_Print();
        return ret;
    }
    if (!PyCallable_Check(pFunc)) {
        PyErr_Print();
        goto out;
    }

    PyObject *pArgs = PyTuple_New(0);
    data = PyObject_CallObject(pFunc, pArgs);
    if (!data) {
        printf("data null\n");
	goto out;
    }
    ret = 1;

out:
//    Py_DECREF(pFunc);

    return ret;
}
#endif

int recognize(double embedding[static 128]) {
    int id = 666; /* When stubbed, always return 666 */
    memcpy(embedding, embedding, 128 * sizeof (double)); /* Cue for GEDL */

#ifndef __STUBBED
    id = -1; 

    // Closure: invoke the python recognize method at the remote site
    PyObject *pName, *pModule, *pFunc, *pArgs;

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

    int dataReady = init_recognizer(pModule);
    if (!dataReady) {
        goto out1;
    }

    pFunc = PyObject_GetAttrString(pModule, "recognize_one");
    if (!pFunc) {
        PyErr_Print();
        goto out2;
    }

    PyObject *listEnc = PyList_New(0);
    for (int i = 0; i < 128; i++) {
        PyObject *element = PyFloat_FromDouble(embedding[i]);
        if (PyList_Append(listEnc, element) == -1) {
            PyErr_Print();
	}
    }
    
    pArgs = PyTuple_New(2);
    PyTuple_SetItem(pArgs, 0, listEnc);
    PyTuple_SetItem(pArgs, 1, data);    

    if (!PyCallable_Check(pFunc)) {
        PyErr_Print();
        goto out3;
    }

    // Closure: collect and return a list, len=length(encodings) of names of recognized faces
    // 'send' the list back to the local site.
    PyObject* pNames = PyObject_CallObject(pFunc, pArgs);
/*
    if (!PyList_Check(pNames)) {
        printf("names are not a list:\n");
        goto out3;
    }

    int count = (int) PyList_Size(pNames);
    // char *names = malloc(sizeof(char *) * count);
    for (int i = 0; i < count; i++) {
        PyObject *ptemp = PyList_GetItem(pNames, i);
*/
        char *cstr;
        PyArg_Parse(pNames, "s", &cstr);  /* convert to C */

        id = strtol(cstr, NULL, 10);
        printf("recognized %s, ID=%d\n", cstr, id);
//    }
out3:
//    Py_DECREF(pFunc);
out2:
//    Py_DECREF(pModule);
out1:
//    Py_DECREF(pName);
out:

//    Py_FinalizeEx();

#endif

  return id;
}

