; We want to add the context of a function to the stack as we 
; recurse
; We get very good cache utilization with the stack
; We're storing register values to the stack
; We need to do this to avoid having our registers clobbered
; by the next function call
; f(g(x))
; Caller Saved -> f saves teh register values before calling g
; Callee Saved -> g saves the register values onto the stack, assuming that the caller might need them
; Theoretically -> You should align teh stack before you issue the call instruction
;	Technically -> this is a general requirement
;	In practice -> Often isn't too important
; In this case we will need to align the stack
; Stack alignment can be a cause for a bug and you may get poor performance
; Stack starts out of alignment b/c of what `call` does
	; `call` -> jump to start of the function and pushing the return address to the stack; such that when the function is completed, it can `ret`
	; `ret` -> pops return address off the task from the stack, and jumping to it
; Looking at a function in assembly
	; Once it starts executing, the stack is out of alignment b/c of return address being on it. You need to push 8 bytes on it.


; def fib(i):
; if i in (0,1): return i
; return fib(i-1) + fib(i-2)


section .text
global fib
fib:
	mov rax, rdi ; Move rdi into rax
	cmp rax, 0   ; Compare to zero
	je _exit     ; If zero -> Exit
	cmp rax, 1   ; Compare to one
	je _exit     ; If one -> Exit
	sub rdi, 1      ; Decrement RDI by 1
	call fib     ; Call fib(i-1)
	mov rbx, rax ; Move result into rbx
	push rbx     ; Push rbx onto the stack
	sub rdi, 1     ; Decrement RDI by 1 again
	call fib     ; Call fib(i-2)
    pop rbx      ; Pop topmost value from stack into register rbx
	add rax, rbx ; Add previous result to rax

_exit:
	ret



