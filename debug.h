#pragma once
#include "chunk.h"

int disassembleInstruction(Chunk* chunk, int offset);
void disassembleChunk(Chunk* chunk, char* name);


