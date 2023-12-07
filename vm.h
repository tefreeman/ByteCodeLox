#pragma once
#include "object.h"
#include "table.h"
#include "value.h"

#define FRAMES_MAX_SIZE 64
#define STACK_MAX_SIZE (FRAMES_MAX_SIZE * UINT8_COUNT)

typedef struct {
  ObjClosure* currentClosure;
  uint8_t* instructionPointer;
  Value* frameSlots;
} CallFrame;


// Virtual machine structure
typedef struct {
  CallFrame frames[FRAMES_MAX_SIZE];
  int frameCount;
  Value stack[STACK_MAX_SIZE];
  Value* stackTop;
  Table globalsVars;
  Table strings;
  ObjString* initString;
  ObjUpvalue* openUpvalues;
  size_t bytesAllocated;
  size_t gcThreshold;       // Garbage collection threshold.
  Obj* objects;

  // Gray = Object just discovered waiting to be processed.
  int grayCount;
  int grayCapacity;
  Obj** grayStack;
} VM;

// InterpretResult Ok, CompileError, RuntimeError
typedef enum {
  INTERPRET_OK,
  INTERPRET_COMPILE_ERROR,
  INTERPRET_RUNTIME_ERROR
} InterpretResult;

// check later
extern VM vm;

void initVM();
void freeVM();

InterpretResult interpret(const char* source);
Value pop();
void push(Value value);
