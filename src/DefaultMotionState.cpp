#include "pybulletphysics.h"

static void
DefaultMotionState_dealloc(bulletphysics_DefaultMotionStateObject* self)
{
	// do not fre it !!!
        //delete(self->motionState);
        self->ob_type->tp_free((PyObject*)self);
}

static PyObject*
DefaultMotionState_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
	PyObject *py_transform = NULL;
	if (!PyArg_ParseTuple(args, "O", &py_transform)) {
        	return NULL;
    	}

        bulletphysics_DefaultMotionStateObject *self = (bulletphysics_DefaultMotionStateObject *)type->tp_alloc(type, 0);
        if (self != NULL) {
		bulletphysics_TransformObject *transform = (bulletphysics_TransformObject *) py_transform;
                self->motionState = new btDefaultMotionState(*(transform->transform));
        }
        return (PyObject *)self;
}

PyTypeObject bulletphysics_DefaultMotionStateType = {
    PyObject_HEAD_INIT(NULL)
    0,                         /*ob_size*/
    "bulletphysics.DefaultMotionState", /*tp_name*/
    sizeof(bulletphysics_DefaultMotionStateObject), /*tp_basicsize*/
    0,                         /*tp_itemsize*/
    (destructor)DefaultMotionState_dealloc,    /*tp_dealloc*/
    0,                         /*tp_print*/
    0,                         /*tp_getattr*/
    0,                         /*tp_setattr*/
    0,                         /*tp_compare*/
    0,                         /*tp_repr*/
    0,                         /*tp_as_number*/
    0,                         /*tp_as_sequence*/
    0,                         /*tp_as_mapping*/
    0,                         /*tp_hash */
    0,                         /*tp_call*/
    0,                         /*tp_str*/
    0,                         /*tp_getattro*/
    0,                         /*tp_setattro*/
    0,                         /*tp_as_buffer*/
    Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE, /*tp_flags*/
    "DefaultMotionState object",           /* tp_doc */
};

PyObject *new_motionstate_from_motionstate(btMotionState* motionState) {
        bulletphysics_DefaultMotionStateObject *py_motionstate = (bulletphysics_DefaultMotionStateObject *)bulletphysics_DefaultMotionStateType.tp_alloc(&bulletphysics_DefaultMotionStateType, 0);
        if (py_motionstate) {
		py_motionstate->motionState = motionState;
                Py_INCREF(py_motionstate);
        }
        return (PyObject *)py_motionstate;
}

static PyObject *
DefaultMotionState_getWorldTransform(bulletphysics_DefaultMotionStateObject *self, PyObject *args, PyObject *kwds) {
        PyObject *py_transform = NULL;
        if (!PyArg_ParseTuple(args, "O", &py_transform)) {
                return NULL;
        }

        bulletphysics_TransformObject *transform = (bulletphysics_TransformObject *) py_transform;
        self->motionState->getWorldTransform(*(transform->transform));

        Py_INCREF(Py_None);
        return Py_None;
}

static PyObject *
DefaultMotionState_setWorldTransform(bulletphysics_DefaultMotionStateObject *self, PyObject *args, PyObject *kwds) {
        PyObject *py_transform = NULL;
        if (!PyArg_ParseTuple(args, "O", &py_transform)) {
                return NULL;
        }

        bulletphysics_TransformObject *transform = (bulletphysics_TransformObject *) py_transform;
        self->motionState->setWorldTransform(*(transform->transform));

        Py_INCREF(Py_None);
        return Py_None;
}


static PyMethodDef DefaultMotionState_methods[] = {
    {"getWorldTransform", (PyCFunction)DefaultMotionState_getWorldTransform, METH_VARARGS, NULL },
    {"setWorldTransform", (PyCFunction)DefaultMotionState_setWorldTransform, METH_VARARGS, NULL },
    {NULL, NULL, 0, NULL}
};

void pybulletphysics_add_DefaultMotionState(PyObject *module) {
	bulletphysics_DefaultMotionStateType.tp_methods = DefaultMotionState_methods;
	bulletphysics_DefaultMotionStateType.tp_new = DefaultMotionState_new;

        if (PyType_Ready(&bulletphysics_DefaultMotionStateType) < 0)
                return;	

	Py_INCREF(&bulletphysics_DefaultMotionStateType);

        PyModule_AddObject(module, "DefaultMotionState", (PyObject *)&bulletphysics_DefaultMotionStateType);
}
