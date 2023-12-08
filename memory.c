#include <stdlib.h>
#include "compiler.h"
#include "memory.h"
#include "vm.h"

#define GC_HEAP_GROW_FACTOR 2

void* reallocate(void* pointer, size_t oldSize, size_t newSize) {
  vm.bytesAllocated += newSize - oldSize;
  if (newSize > oldSize) {
    if (vm.bytesAllocated > vm.gcThreshold) {
      collectGarbage();
    }
  }


  if (newSize == 0) {
    free(pointer);
    return NULL;
  }

  void* result = realloc(pointer, newSize);
  if (result == NULL) exit(1);
  return result;
}
void markObject(Obj* object) {
  if (object == NULL) return;
  if (object->isMarked) return;

  object->isMarked = true;

  if (vm.grayCapacity < vm.grayCount + 1) {
    vm.grayCapacity = GROW_CAPACITY(vm.grayCapacity);
    vm.grayStack = (Obj**)realloc(vm.grayStack,
      sizeof(Obj*) * vm.grayCapacity);

    if (vm.grayStack == NULL) exit(1);
  }

  vm.grayStack[vm.grayCount++] = object;
}
void markValue(Value value) {
  if (IS_OBJ(value)) markObject(AS_OBJ(value));
}
static void markArray(ValueArray* array) {
  for (int i = 0; i < array->count; i++) {
    markValue(array->values[i]);
  }
}
static void blackenObject(Obj* object) {

  switch (object->type) {
  case OBJ_BOUND_METHOD: {
    ObjBoundMethod* bound = (ObjBoundMethod*)object;
    markValue(bound->receiver);
    markObject((Obj*)bound->method);
    break;
  }
  case OBJ_CLASS: {
    ObjClass* klass = (ObjClass*)object;
    markObject((Obj*)klass->name);
    markTable(&klass->methods);
    break;
  }
  case OBJ_CLOSURE: {
    ObjClosure* currentClosure = (ObjClosure*)object;
    markObject((Obj*)currentClosure->function);
    for (int i = 0; i < currentClosure->upvalueCount; i++) {
      markObject((Obj*)currentClosure->upvalues[i]);
    }
    break;
  }
  case OBJ_FUNCTION: {
    ObjFunction* function = (ObjFunction*)object;
    markObject((Obj*)function->name);
    markArray(&function->chunk.constants);
    break;
  }
  case OBJ_INSTANCE: {
    ObjInstance* instance = (ObjInstance*)object;
    markObject((Obj*)instance->klass);
    markTable(&instance->fields);
    break;
  }
  case OBJ_UPVALUE:
    markValue(((ObjUpvalue*)object)->closed);
    break;
  case OBJ_NATIVE:
  case OBJ_STRING:
    break;
  }
}
static void freeObject(Obj* object) {

  switch (object->type) {
  case OBJ_BOUND_METHOD:
    FREE(ObjBoundMethod, object);
    break;
  case OBJ_FUNCTION: {
    ObjFunction* function = (ObjFunction*)object;
    deallocateChunk(&function->chunk);
    FREE(ObjFunction, object);
    break;
  }
  case OBJ_CLASS: {
    ObjClass* klass = (ObjClass*)object;
    deallocateTable(&klass->methods);
    FREE(ObjClass, object);
    break;
  }   case OBJ_CLOSURE: {
    ObjClosure* currentClosure = (ObjClosure*)object;
    FREE_ARRAY(ObjUpvalue*, currentClosure->upvalues,
      currentClosure->upvalueCount);
    FREE(ObjClosure, object);
    break;
  }
  case OBJ_NATIVE:
    FREE(ObjNative, object);
    break;

  case OBJ_INSTANCE: {
    ObjInstance* instance = (ObjInstance*)object;
    deallocateTable(&instance->fields);
    FREE(ObjInstance, object);
    break;
  }
  case OBJ_STRING: {
    ObjString* string = (ObjString*)object;
    FREE_ARRAY(char, string->chars, string->length + 1);
    FREE(ObjString, object);
    break;
  }
  case OBJ_UPVALUE:
    FREE(ObjUpvalue, object);
    break;
  }
}
static void markRoots() {
  for (Value* slot = vm.stack; slot < vm.stackTop; slot++) {
    markValue(*slot);
  }

  for (int i = 0; i < vm.frameCount; i++) {
    markObject((Obj*)vm.frames[i].currentClosure);
  }

  for (ObjUpvalue* upvalue = vm.openUpvalues;
    upvalue != NULL;
    upvalue = upvalue->next) {
    markObject((Obj*)upvalue);
  }

  markTable(&vm.globalsVars);
  markCompilerRoots();
  markObject((Obj*)vm.initString);
}
static void traceReferences() {
  while (vm.grayCount > 0) {
    Obj* object = vm.grayStack[--vm.grayCount];
    blackenObject(object);
  }
}
static void sweep() {
  Obj* previous = NULL;
  Obj* object = vm.objects;
  while (object != NULL) {
    if (object->isMarked) {
      object->isMarked = false;
      previous = object;
      object = object->next;
    }
    else {
      Obj* unreached = object;
      object = object->next;
      if (previous != NULL) {
        previous->next = object;
      }
      else {
        vm.objects = object;
      }
      freeObject(unreached);
    }
  }
}
void collectGarbage() {
  markRoots();
  traceReferences();
  tableRemoveWhite(&vm.strings);
  sweep();

  vm.gcThreshold = vm.bytesAllocated * GC_HEAP_GROW_FACTOR;

}
void freeObjects() {
  Obj* object = vm.objects;
  while (object != NULL) {
    Obj* next = object->next;
    freeObject(object);
    object = next;
  }

  free(vm.grayStack);
}
