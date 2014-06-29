
.equ DISABLE_IRQ,0x80
.equ DISABLE_FIQ,0x40
.equ SYS_MOD,0x1f
.equ IRQ_MOD,0x12
.equ FIQ_MOD,0x11
.equ SVC_MOD,0x13
.equ ABT_MOD,0x17
.equ UND_MOD,0x1b
.equ MOD_MASK,0x1f


.macro CHANGE_TO_SVC
        msr     cpsr_c,#(DISABLE_FIQ|DISABLE_IRQ|SVC_MOD)
.endm

.macro CHANGE_TO_IRQ
        msr     cpsr_c,#(DISABLE_FIQ|DISABLE_IRQ|IRQ_MOD)
.endm



.global	__vector_undefined
.global	__vector_swi
.global	__vector_prefetch_abort
.global	__vector_data_abort
.global	__vector_reserved
.global	__vector_irq
.global	__vector_fiq

.text
.code 32


.extern  raw_task_active
.extern  high_ready_obj
.extern raw_os_active
.extern common_irq_handler
.extern raw_finish_int


__vector_undefined:
	nop

__vector_swi:
	nop

__vector_prefetch_abort:	
	nop

__vector_data_abort:
	nop

__vector_reserved:
	nop

__vector_irq:

       STMFD   SP!, {R1-R3}                    @ We will use R1-R3 as temporary registers
@----------------------------------------------------------------------------
@   R1--SP
@       R2--PC
@   R3--SPSR
@------------------------------------------------------------------------
        MOV     R1, SP
        ADD     SP, SP, #12             @Adjust IRQ stack pointer
        SUB     R2, LR, #4             @Adjust PC for return address to task

        MRS     R3, SPSR                                @ Copy SPSR (Task CPSR)



        MSR     CPSR_cxsf, #0x13|0xc0   @Change to SVC mode

                                                                        @ SAVE TASK''S CONTEXT ONTO OLD TASK''S STACK

        STMFD   SP!, {R2}                               @ Push task''s PC
        STMFD   SP!, {R4-R12, LR}               @ Push task''s LR,R12-R4

        LDMFD   R1!, {R4-R6}                    @Load Task''s R1-R3 from IRQ stack
        STMFD   SP!, {R4-R6}                    @ Push Task''s R1-R3 to SVC stack
        STMFD   SP!, {R0}                           @ Push Task''s R0 to SVC stack

        STMFD   SP!, {R3}                               @ Push task''s CPSR

        LDR     R0,=raw_int_nesting        @raw_int_nesting++
        LDRB    R1,[R0]
        ADD     R1,R1,#1
        STRB    R1,[R0]

        CMP     R1,#1                   @if(raw_int_nesting==1){
        BNE     1f
        LDR     R4,=raw_task_active            @high_ready_obj->task_stack=SP;
        LDR     R5,[R4]
        STR     SP,[R5]                 @}

1:
        MSR    CPSR_c,#0x12|0xc0    @Change to IRQ mode to use IRQ stack to handle interrupt
	
	bl common_irq_handler

    	MSR         CPSR_c,#0x13|0xc0   @Change to SVC mode
    	BL          raw_finish_int           @Call raw_finish_int

    	LDMFD   SP!,{R4}               @POP the task''s CPSR
    	MSR         SPSR_cxsf,R4
    	LDMFD   SP!,{R0-R12,LR,PC}^    @POP new Task''s context


__vector_fiq:
	nop

