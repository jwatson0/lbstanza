#include <Zydis/Zydis.h>
#include "stz-zydis.h"
#include <stdio.h>

StzDecoder* zydis_new_decoder (ZyanU8* code, uint64_t len) {
  auto dec = new StzDecoder(code, len);
  ZydisDecoderInit(&dec->decoder, ZYDIS_MACHINE_MODE_LONG_64, ZYDIS_STACK_WIDTH_64);
  ZydisFormatterInit(&dec->formatter, ZYDIS_FORMATTER_STYLE_INTEL);
  return dec;
}

int zydis_decode (StzDecoder* dec) {
  auto res = ZYAN_SUCCESS(ZydisDecoderDecodeFull(&dec->decoder, dec->data + dec->offset,
                                                 dec->length - dec->offset,
                                                 &dec->instruction, dec->operands,
                                                 ZYDIS_MAX_OPERAND_COUNT_VISIBLE, 
                                                 ZYDIS_DFLAG_VISIBLE_OPERANDS_ONLY));
  if (res) {
    auto n = sprintf(dec->buffer, "0x%016llX  ", dec->runtime_address);
    ZydisFormatterFormatInstruction(&dec->formatter, &dec->instruction, dec->operands,
                                    dec->instruction.operand_count_visible, dec->buffer + n,
                                    sizeof(dec->buffer), dec->runtime_address);
    dec->offset += dec->instruction.length;
    dec->runtime_address += dec->instruction.length;
  }
  return res;
}

char* zydis_buffer (StzDecoder* dec) {
  return dec->buffer;
}

void zydis_delete (StzDecoder* dec) {
  delete dec;
}


