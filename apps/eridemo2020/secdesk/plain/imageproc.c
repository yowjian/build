#include "imageproc.h"

#undef __STUBBED  // TODO: remove

#ifndef __STUBBED
#define error(msg) do { printf("%s\n", msg); PyErr_Print(); return(0); } while (1)

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
    setenv("PYTHONPATH", ".", 1);
    Py_Initialize();

    PyObject *pModule = PyImport_ImportModule(RECOGNIZER_MODULE);
    if (pModule == NULL)
        error("Can't load module");

    PyObject *pFunc = PyObject_GetAttrString(pModule, "calcEncodings");
    Py_DECREF(pModule);
    if (pFunc == NULL)
        error("Can't fetch method");

    if (!PyCallable_Check(pFunc))
        error("not callable");

    PyObject *pArgs = PyTuple_New(2);
    PyObject *arg1 = Py_BuildValue("s#", imagefile, strlen(imagefile));
    PyTuple_SetItem(pArgs, 0, arg1);

    char t[32] = "cnn";
    PyObject *arg2 = Py_BuildValue("s#", t, strlen(t));
    PyTuple_SetItem(pArgs, 1, arg2);
   
    PyObject *pValue = PyObject_CallObject(pFunc, pArgs);
    Py_DECREF(pFunc);
    Py_DECREF(pArgs);
    if (!PyList_Check(pValue))
        error("return value not a list!");
    
    int countArgs = (int) PyList_Size(pValue);
    if (countArgs != 3)
        error("number of return values != 3");

    PyObject *encodings = PyList_GetItem(pValue, 0);
    if (!PyList_Check(encodings))
        error("encodings is not a list");
    
    int count = (int) PyList_Size(encodings);
    if (count <= 0)
        error("number of encodings < 0");

    PyObject *enc = PyList_GetItem(encodings, 0);
    if (!PyList_Check(enc))
        error("enc is not a list");

    int countIn = (int) PyList_Size(enc);
    if (countIn != 128)
        error("number of entries in an encoding is not 128");
    
    for (int j = 0; j < countIn; j++) {
        PyObject *pObj = PyList_GetItem(enc, j);

        PyObject *objRepIn = PyObject_Repr(pObj);
        PyObject* str = PyUnicode_AsEncodedString(objRepIn, "utf-8", "~E~");
        const char *bytes = PyBytes_AS_STRING(str);
        embedding[j] = (float) strtod(bytes, NULL);
    }
    Py_DECREF(pValue);

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

    setenv("PYTHONPATH", ".", 1);
    Py_Initialize();

    PyObject *pModule = PyImport_ImportModule(RECOGNIZER_MODULE);
    if (!pModule) {
        PyErr_Print();
        goto out1;
    }

    int dataReady = init_recognizer(pModule);
    if (!dataReady) {
        goto out1;
    }

    PyObject *pFunc = PyObject_GetAttrString(pModule, "recognize_one");
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
    
    PyObject *pArgs = PyTuple_New(2);
    PyTuple_SetItem(pArgs, 0, listEnc);
    PyTuple_SetItem(pArgs, 1, data);    

    if (!PyCallable_Check(pFunc)) {
        PyErr_Print();
        goto out3;
    }

    PyObject* pName = PyObject_CallObject(pFunc, pArgs);

    char *cstr;
    PyArg_Parse(pName, "s", &cstr);  /* convert to C */
    id = strtol(cstr, NULL, 10);
    printf("recognized %s, ID=%d\n", cstr, id);

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


