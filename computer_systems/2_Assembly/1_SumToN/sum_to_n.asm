; -----------------------------------------------------------------------------
; A 64-bit MacOS application that returns the sum of a number from 1 to n inclusive
; -----------------------------------------------------------------------------

; Useful Commands:
; add - felixcloutier.com/x86/add
; jcc - felixcloutier.com/x86/jcc
;           jumps happen on the basis of flag bits
; cmp - felixclouter.com/x86/cmp
; Arg goes into RDI
; Return Value into RAX

            global      sum_to_n
            section     .text

sum_to_n:
            mov r10, rdi
            mov rax, 0

iterate:
            cmp r10, 0
            je done
            add rax, r10
            dec r10
            cmp r10, 0
            jne iterate
done:
            ret 



