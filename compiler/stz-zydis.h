#ifndef __STZ_ZYDIS__
#define __STZ_ZYDIS__

#include <Zydis/Zydis.h>

extern "C" {
  struct StzDecoder {
    ZydisDecoder decoder;
    ZydisFormatter formatter;
    ZydisDecodedInstruction instruction;
    ZydisDecodedOperand operands[ZYDIS_MAX_OPERAND_COUNT_VISIBLE];
    char buffer[256];
    ZyanUSize offset;
    ZyanU64 runtime_address;
    ZyanU8 *data;
    uint64_t length;
  StzDecoder(ZyanU8* data, uint64_t length) : data(data), length(length), runtime_address(0x007FFFFFFF400000), offset(0) { }
  };
  StzDecoder* zydis_new_decoder (ZyanU8* code, uint64_t len);
  int zydis_decode (StzDecoder* dec);
  char* zydis_buffer (StzDecoder* dec);
  void zydis_delete (StzDecoder* dec);
};

#endif