

CC=arm-linux-gcc
LD=arm-linux-ld
OBJCOPY=arm-linux-objcopy

CFLAGS= -O2 -g
ASFLAGS= -O2 -g
LDFLAGS=-Trtos.lds -Ttext 30000000 

OBJS=   init.o start.o boot.o abnormal.o mmu.o print.o interrupt.o \
	raw_block.o raw_byte.o raw_event.o raw_idle.o  raw_idle_event.o raw_mqueue.o raw_mutex.o raw_obj.o raw_pend.o \
	raw_queue_buffer.o raw_queue.o raw_queue_size.o raw_sched.o raw_sem.o raw_stm.o raw_system.o raw_task.o raw_task_0.o \
	raw_task_queue_size.o raw_task_sem.o raw_tick.o raw_timer.o \
	test_task.o  test_sem.o  test_mutex.o test_timer.o test_block.o test_byte.o\
	port.o trace.o cpu.o

.c.o:
	$(CC) $(CFLAGS) -c -I. $<
.s.o:
	$(CC) $(ASFLAGS) -c $<

rtos:$(OBJS)
	$(CC) -static -nostartfiles -nostdlib $(LDFLAGS) $? -o $@ -lgcc
	$(OBJCOPY) -O binary $@ rtos.bin
	arm-linux-objdump -h -S -D rtos > rtos.txt

clean:
	rm *.o rtos rtos.bin rtos.txt -f
