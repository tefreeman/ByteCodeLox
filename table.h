#pragma once
#include "value.h"


typedef struct {
  ObjString* key;
  Value value;
} Entry;

typedef struct {
  int count;
  int capacity;
  Entry* entries;
} Table;

void initializeTable(Table* table);
void deallocateTable(Table* table);
bool findTableEntry(Table* table, ObjString* key, Value* value);
bool getValueFromTable(Table* table, ObjString* key, Value value);
bool tableDelete(Table* table, ObjString* key);
void tableAddAll(Table* from, Table* to);
ObjString* findStringInTable(Table* table, const char* chars, int length, uint32_t hash);
void tableRemoveWhite(Table* table);
void markTable(Table* table);


