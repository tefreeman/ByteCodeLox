#pragma once

#include "common.h"
#include "value.h"

// OpCode is an enum of all the possible opcodes that can be used in the
typedef enum {
  OP_TRUE,
  OP_FALSE,
  OP_CONSTANT,
  OP_NIL,
  OP_POP,
  OP_GET_LOCAL,
  OP_SET_LOCAL,
  OP_GET_GLOBAL,
  OP_DEFINE_GLOBAL,
  OP_SET_GLOBAL,
  OP_GET_UPVALUE,
  OP_SET_UPVALUE,
  OP_GET_PROPERTY,
  OP_SET_PROPERTY,
  OP_GET_SUPER,
  OP_EQUAL,
  OP_GREATER,
  OP_ADD,
  OP_LESS,
  OP_SUBTRACT,
  OP_MULTIPLY,
  OP_DIVIDE,
  OP_NOT,
  OP_NEGATE,
  OP_PRINT,
  OP_JUMP,
  OP_JUMP_IF_FALSE,
  OP_LOOP,
  OP_CALL,
  OP_INVOKE,
  OP_CLOSURE,
  OP_SUPER_INVOKE,
  OP_CLOSE_UPVALUE,
  OP_RETURN,
  OP_CLASS,
  OP_INHERIT,
  OP_METHOD
} OpCode;

typedef struct {
  int capacity;
  int count;
  int* lines;
  uint8_t* code;
  ValueArray constants;
} Chunk;

void initalizeChunk(Chunk* chunk);
void writeChunk(Chunk* chunk, uint8_t byte, int line);
void deallocateChunk(Chunk* chunk);
int addConstant(Chunk* chunk, Value value);

