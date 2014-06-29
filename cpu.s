
.global raw_int_switch
.global port_task_switch
.global OS_CPU_SR_Save
.global OS_CPU_SR_Restore
.global raw_start_first_task


.equ SRCPND,    0x4a000000
.equ INTPND,    0x4a000010
.equ rEINTPEND, 0x560000a8
.equ INTOFFSET, 0x4a000014


#define USERMODE        0x10
#define FIQMODE         0x11
#define IRQMODE         0x12
#define SVCMODE         0x13
#define ABORTMODE       0x17
#define UNDEFMODE       0x1b
#define MODEMASK        0x1f
#define NOINT           0xc0


OS_CPU_SR_Save:
        MRS     R0, CPSR                                @ Set IRQ and FIQ bits in CPSR to disable all interrupts
        ORR     R1, R0, #0xC0
        MSR     CPSR_c, R1
        MRS     R1, CPSR                                @Confirm that CPSR contains the proper interrupt disable flags
        AND     R1, R1, #0xC0
        CMP     R1, #0xC0
        BNE     OS_CPU_SR_Save                          @ Not properly disabled (try again)
        MOV     PC, LR                                  @ Disabled, return the original CPSR contents in R0


OS_CPU_SR_Restore:
        MSR     CPSR_c, R0
        MOV     PC, LR



raw_start_first_task:
        MSR             CPSR_cxsf,#0x13|0xc0     @Switch to SVC mode with IRQ&FIQ disable
        BL              task_switch_hook            @Call user define Task switch hook


        @----------------------------------------------------------------------------------
        @               SP = raw_task_active->task_stack;
        @----------------------------------------------------------------------------------
        LDR     R0, =raw_task_active
        LDR     R0, [R0]
        LDR     SP, [R0]

        @----------------------------------------------------------------------------------
        @ Prepare to return to proper mode
        @----------------------------------------------------------------------------------
        LDMFD   SP!, {R0}
        MSR     SPSR_cxsf, R0
        LDMFD   SP!, {R0-R12, LR, PC}^


port_task_switch:
        STMFD   SP!, {LR}           @PC
        STMFD   SP!, {R0-R12, LR}   @R0-R12 LR
        MRS     R0,  CPSR       @Push CPSR
        STMFD   SP!, {R0}

        @----------------------------------------------------------------------------------
        @               raw_task_active->task_stack = SP
        @----------------------------------------------------------------------------------
        LDR             R0, =raw_task_active
        LDR             R0, [R0]
        STR             SP, [R0]

        @----------------------------------------------------------------------------------
        @ task_switch_hook();
        @---------------------------------------------------------------------------------
        BL              task_switch_hook

        @----------------------------------------------------------------------------------
        @ raw_task_active= high_ready_obj;
        @----------------------------------------------------------------------------------
        LDR             R0, =high_ready_obj
        LDR             R1, =raw_task_active
        LDR             R0, [R0]
        STR             R0, [R1]


        @----------------------------------------------------------------------------------
        @  high_ready_obj->task_stack;
        @----------------------------------------------------------------------------------
        LDR             R0, =high_ready_obj
        LDR             R0, [R0]
        LDR             SP, [R0]

        @----------------------------------------------------------------------------------
        @Restore New task context
        @----------------------------------------------------------------------------------
        LDMFD   SP!, {R0}               @POP CPSR
        MSR     SPSR_cxsf, R0
        LDMFD   SP!, {R0-R12, LR, PC}^



raw_int_switch:
        @BL             task_switch_hook

        @----------------------------------------------------------------------------------
        @ raw_task_active = high_ready_obj;
        @----------------------------------------------------------------------------------
        LDR             R0, =high_ready_obj
        LDR             R1, =raw_task_active
        LDR             R0, [R0]
        STR             R0, [R1]


        @----------------------------------------------------------------------------------
        @               SP = high_ready_obj->task_stack;
        @----------------------------------------------------------------------------------
        LDR             R0, =high_ready_obj
        LDR             R0, [R0]
        LDR             SP, [R0]

        @----------------------------------------------------------------------------------
        @ Restore New Task context
        @----------------------------------------------------------------------------------
        LDMFD   SP!, {R0}              @POP CPSR
        MSR     SPSR_cxsf, R0
        LDMFD   SP!, {R0-R12, LR, PC}^

