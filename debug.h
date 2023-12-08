#pragma once
#include "chunk.h"

// disassembleInstruction() returns the number of bytes in the instruction
int disassembleInstruction(Chunk* chunk, int offset);

// disassembleChunk() returns nothing
void disassembleChunk(Chunk* chunk, char* name);
