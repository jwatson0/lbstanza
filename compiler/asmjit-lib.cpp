#include <asmjit/asmjit.h>
#include "asmjit-lib.h"
#include <stdio.h>

using namespace asmjit;
using namespace x86;

JitRuntime* jit_runtime_new(void) {
  return new JitRuntime();
}
void jit_runtime_delete(JitRuntime* rt) {
  
  delete rt;
}
void* jit_runtime_add(JitRuntime* rt, CodeHolder *c) {
  void* fn;
  rt->_add(&fn, c);
  return fn;
}
void jit_runtime_release(JitRuntime* rt, void *c) {
  rt->_release(c);
}
CodeHolder* code_holder_new(JitRuntime *rt) {
  auto c = new CodeHolder();
  c->init(rt->codeInfo());
  return c;
}
int code_holder_label_offset(CodeHolder *c, Label *f) {
  return c->labelOffset(*f);
}
void code_holder_delete(CodeHolder *c) {
  delete c;
}
Assembler* assembler_new(CodeHolder *c) {
  return new Assembler(c);
}
void assembler_delete(Assembler *a) {
  delete a;
}
Label* assembler_new_label(Assembler *a) {
  Label label = a->newLabel();
  return new Label(label);
}
void assembler_bind(Assembler *a, Label *label) {
  a->bind(*label);
}
void assembler_jne(Assembler *a, Label *label) {
  a->jne(*label);
}
void assembler_jmp_label(Assembler *a, Label *label) {
  a->jmp(*label);
}
void assembler_jmp_mem(Assembler *a, MemPtr *mem) {
  a->jmp(mem->value);
}
void assembler_jmp_reg(Assembler *a, Gp *reg) {
  a->jmp(*reg);
}
void assembler_add_reg(Assembler *a, const Gp *dst, const Gp *src) {
  a->add(*dst, *src);
}
void assembler_add_int(Assembler *a, const Gp *dst, int src) {
  a->add(*dst, src);
}
void assembler_shl(Assembler *a, const Gp *dst, int src) {
  a->shl(*dst, src);
}
void assembler_push(Assembler *a, Gp *reg) {
  a->push(*reg);
}
void assembler_pop(Assembler *a, Gp *reg) {
  a->pop(*reg);
}  
void assembler_call_label(Assembler *a, Label *f) {
  a->call(*f);
}
void assembler_call_reg(Assembler *a, Gp *reg) {
  a->call(*reg);
}
void assembler_ret(Assembler *a) {
  a->ret();
}
void assembler_mov_reg(Assembler *a, const Gp *dst, const Gp *src) {
  a->mov(*dst, *src);
}
void assembler_mov_const(Assembler *a, const Gp *reg, uint64_t value) {
  a->mov(*reg, uint64_t(value));
}
void assembler_mov_label(Assembler *a, const Gp *reg, Label *value) {
  a->mov(*reg, uint64_t(value));
}
void assembler_mov_gp_ptr(Assembler *a, const Gp *reg, MemPtr* mem) {
  a->mov(*reg, mem->value);
}
void assembler_mov_ptr_gp(Assembler *a, const MemPtr* mem, Gp *reg) {
  a->mov(mem->value, *reg);
}
uint64_t func_call(Func f) {
  return f();
}
const Gp* x86_eax(void) {
  return &eax;
}
const Gp* x86_rax(void) {
  return &rax;
}
const Gp* x86_rcx(void) {
  return &rcx;
}
const Gp* x86_rdx(void) {
  return &rdx;
}
const Gp* x86_rbx(void) {
  return &rbx;
}
const Gp* x86_rsi(void) {
  return &rsi;
}
const Gp* x86_rdi(void) {
  return &rdi;
}
const Gp* x86_rsp(void) {
  return &rsp;
}
const Gp* x86_rbp(void) {
  return &rbp;
}
const Gp* x86_r8(void) {
  return &r8;
}
const Gp* x86_r9(void) {
  return &r9;
}
const Gp* x86_r10(void) {
  return &r10;
}
const Gp* x86_r11(void) {
  return &r11;
}
const Gp* x86_r12(void) {
  return &r12;
}
const Gp* x86_r13(void) {
  return &r13;
}
const Gp* x86_r14(void) {
  return &r14;
}
const Gp* x86_r15(void) {
  return &r15;
}
const MemPtr* x86_ptr_gp_base_const_offset_size(Gp *base_ptr, int32_t offset, int32_t size) {
  auto base = *base_ptr;
  return new MemPtr(ptr(base, offset, size));
}
const MemPtr* x86_ptr_gp_base_index_const_shift_offset_size
    (Gp *base_ptr, Gp* index_ptr, int32_t shift, int32_t offset, int32_t size) {
  auto base = *base_ptr;
  auto index = *index_ptr;
  return new MemPtr(ptr(base, index, shift, offset, size));
}
const MemPtr* x86_ptr_label_base_index_const_shift_offset_size (Label *base_ptr, Gp* index_ptr, int32_t shift, int32_t offset, int32_t size) {
  auto base = *base_ptr;
  auto index = *index_ptr;
  return new MemPtr(ptr(base, index, shift, offset, size));
}
const MemPtr* x86_ptr_label_base_const_index_size (Label *base_ptr, int32_t index, int32_t size) {
  auto base = *base_ptr;
  return new MemPtr(ptr(base, index, size));
}
void dump_registers (void) {
  uint64_t rax;
  asm("\t movq %%rax,%0" : "=r"(rax));  
  printf("RAX = %llx\n", rax);
  uint64_t rcx;
  asm("\t movq %%rcx,%0" : "=r"(rcx));  
  printf("RCX = %llx\n", rcx);
  uint64_t rdx;
  asm("\t movq %%rdx,%0" : "=r"(rdx));  
  printf("RDX = %llx\n", rdx);
  uint64_t rbx;
  asm("\t movq %%rbx,%0" : "=r"(rbx));  
  printf("RBX = %llx\n", rbx);
  uint64_t r8;
  asm("\t movq %%r8,%0" : "=r"(r8));  
  printf("R8 = %llx\n", r8);
  uint64_t r9;
  asm("\t movq %%r9,%0" : "=r"(r9));  
  printf("R9 = %llx\n", r9);
}
void dump_memory (uint64_t* start, uint64_t n) {
  uint64_t i = 0;
  for (uint64_t* ptr = start; i < n; ptr += 1, i += 1) {
    printf("%llx: %llx\n", ptr, *ptr);
  }
}
void c_trampoline_stub (uint64_t fptr, uint64_t* registers, uint64_t* returns) {
  printf("FPTR %llx\n", fptr);
  printf("REGS %llx\n", registers);
  printf("RETS %llx\n", returns);
}