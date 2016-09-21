  .global doSomething
  .global _doSomething
  /* void doSomething(long newSp, long *oldSp) */
doSomething:
_doSomething:
  push %rbx
  push %rbp
  push %r12
  push %r13
  push %r14
  push %r15

  mov %rsp,(%rsi)
  mov %rdi,%rsp

  pop %r15
  pop %r14
  pop %r13
  pop %r12
  pop %rbp
  pop %rbx
  ret
