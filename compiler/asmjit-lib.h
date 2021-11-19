#ifndef __ASMJIT_LIB__
#define __ASMJIT_LIB__

#include <asmjit/asmjit.h>
using namespace asmjit;
using namespace x86;

extern "C" {
  struct MemPtr {
    Mem value;
  MemPtr(Mem data) : value(data) { }
  };
  JitRuntime* jit_runtime_new(void);
  void jit_runtime_delete(JitRuntime* rt);
  void* jit_runtime_add(JitRuntime* rt, CodeHolder *c);
  void jit_runtime_release(JitRuntime* rt, void *c);
  CodeHolder* code_holder_new(JitRuntime *rt);
  void code_holder_delete(CodeHolder *c);
  int code_holder_label_offset(CodeHolder *c, Label *f);
  Assembler* assembler_new(CodeHolder *c);
  Label* assembler_new_label(Assembler *a);
  void assembler_delete(Assembler *a);
  void assembler_bind(Assembler *a, Label *f);
  void assembler_push(Assembler *a, Gp *reg);
  void assembler_pop(Assembler *a, Gp *reg);
  void assembler_call_label(Assembler *a, Label *f);
  void assembler_call_reg(Assembler *a, Gp *reg);
  void assembler_je(Assembler *a, Label *x);
  void assembler_jne(Assembler *a, Label *x);
  void assembler_js(Assembler *a, Label *x);
  void assembler_jns(Assembler *a, Label *x);
  void assembler_jg(Assembler *a, Label *x);
  void assembler_jge(Assembler *a, Label *x);
  void assembler_jl(Assembler *a, Label *x);
  void assembler_jle(Assembler *a, Label *x);
  void assembler_ja(Assembler *a, Label *x);
  void assembler_jae(Assembler *a, Label *x);
  void assembler_jb(Assembler *a, Label *x);
  void assembler_jbe(Assembler *a, Label *x);
  void assembler_jmp_label(Assembler *a, Label *label);
  void assembler_jmp_mem(Assembler *a, MemPtr *mem);
  void assembler_jmp_reg(Assembler *a, Gp *reg);
  void assembler_ret(Assembler *a);
  void assembler_mov_reg(Assembler *a, const Gp *dst, const Gp *src);
  void assembler_mov_const(Assembler *a, const Gp *reg, uint64_t value);
  void assembler_mov_label(Assembler *a, const Gp *reg, Label *label);
  void assembler_lea_ptr(Assembler *a, const Gp *reg, MemPtr *mem);
  void assembler_mov_gp_ptr(Assembler *a, const Gp *reg, MemPtr* mem);
  void assembler_mov_ptr_gp(Assembler *a, const MemPtr* mem, Gp *reg);
  void assembler_add_reg(Assembler *a, const Gp *dst, const Gp *src);
  void assembler_add_int(Assembler *a, const Gp *dst, int);
  void assembler_sub_reg(Assembler *a, const Gp *dst, const Gp *src);
  void assembler_and_reg(Assembler *a, const Gp *dst, const Gp *src);
  void assembler_or_reg(Assembler *a, const Gp *dst, const Gp *src);
  void assembler_shl(Assembler *a, const Gp *dst, int src);
  void assembler_shr(Assembler *a, const Gp *dst, int src);
  void assembler_cmp(Assembler *a, const Gp *x, const Gp *y);
  void assembler_set_e(Assembler *a, const Gp *x);
  void assembler_set_ne(Assembler *a, const Gp *x);
  void assembler_set_s(Assembler *a, const Gp *x);
  void assembler_set_ns(Assembler *a, const Gp *x);
  void assembler_set_g(Assembler *a, const Gp *x);
  void assembler_set_ge(Assembler *a, const Gp *x);
  void assembler_set_l(Assembler *a, const Gp *x);
  void assembler_set_le(Assembler *a, const Gp *x);
  void assembler_set_a(Assembler *a, const Gp *x);
  void assembler_set_ae(Assembler *a, const Gp *x);
  void assembler_set_b(Assembler *a, const Gp *x);
  void assembler_set_be(Assembler *a, const Gp *x);

  typedef uint64_t (*Func)(void);
  uint64_t func_call(Func f);
  const MemPtr* x86_ptr_gp_base_const_offset_size(Gp *base, int32_t offset, int32_t size);
  const MemPtr* x86_ptr_gp_base_index_const_shift_offset_size
    (Gp *base, Gp* index, int32_t shift, int32_t offset, int32_t size);
  const MemPtr* x86_ptr_label_base_gp_index_const_shift_offset_size
    (Label *base, Gp* index, int32_t shift, int32_t offset, int32_t size);
  const MemPtr* x86_ptr_label_base_const_index_size (Label *base, int32_t index, int32_t size);
  const MemPtr* x86_ptr_label_base_index_const_shift_offset_size (Label *base, Gp* index, int32_t shift, int32_t offset, int32_t size);
  const Gp* x86_eax(void);
  const Gp* x86_rax(void);
  const Gp* x86_rcx(void);
  const Gp* x86_ecx(void);
  const Gp* x86_rdx(void);
  const Gp* x86_edx(void);
  const Gp* x86_rbx(void);
  const Gp* x86_ebx(void);
  const Gp* x86_rsi(void);
  const Gp* x86_rdi(void);
  const Gp* x86_rsp(void);
  const Gp* x86_rbp(void);
  const Gp* x86_r8(void);
  const Gp* x86_r9(void);
  const Gp* x86_r10(void);
  const Gp* x86_r11(void);
  const Gp* x86_r12(void);
  const Gp* x86_r13(void);
  const Gp* x86_r14(void);
  const Gp* x86_r15(void);
  void dump_registers (void);
  void dump_memory_64 (uint64_t* start, uint64_t n);
  void dump_memory_32 (uint32_t* start, uint64_t n);
  void dump_memory_8 (uint8_t* start, uint64_t n);
  void c_trampoline_stub (uint64_t fptr, uint64_t* registers, uint64_t* returns);
};

#endif