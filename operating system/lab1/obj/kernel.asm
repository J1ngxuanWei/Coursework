
bin/kernel：     文件格式 elf64-littleriscv


Disassembly of section .text:

0000000080200000 <kern_entry>:
#include <memlayout.h>

    .section .text,"ax",%progbits
    .globl kern_entry
kern_entry:
    la sp, bootstacktop
    80200000:	00004117          	auipc	sp,0x4
    80200004:	00010113          	mv	sp,sp

    tail kern_init
    80200008:	0040006f          	j	8020000c <kern_init>

000000008020000c <kern_init>:
int kern_init(void) __attribute__((noreturn));
void grade_backtrace(void);

int kern_init(void) {
    extern char edata[], end[];
    memset(edata, 0, end - edata);
    8020000c:	00004517          	auipc	a0,0x4
    80200010:	00450513          	addi	a0,a0,4 # 80204010 <edata>
    80200014:	00004617          	auipc	a2,0x4
    80200018:	00460613          	addi	a2,a2,4 # 80204018 <end>
int kern_init(void) {
    8020001c:	1141                	addi	sp,sp,-16
    memset(edata, 0, end - edata);
    8020001e:	8e09                	sub	a2,a2,a0
    80200020:	4581                	li	a1,0
int kern_init(void) {
    80200022:	e406                	sd	ra,8(sp)
    memset(edata, 0, end - edata);
    80200024:	590000ef          	jal	ra,802005b4 <memset>

    cons_init();  // init the console
    80200028:	132000ef          	jal	ra,8020015a <cons_init>

    const char *message = "(THU.CST) os is loading ...\n";
    cprintf("%s\n\n", message);
    8020002c:	00001597          	auipc	a1,0x1
    80200030:	9cc58593          	addi	a1,a1,-1588 # 802009f8 <etext+0x2>
    80200034:	00001517          	auipc	a0,0x1
    80200038:	9e450513          	addi	a0,a0,-1564 # 80200a18 <etext+0x22>
    8020003c:	03e000ef          	jal	ra,8020007a <cprintf>

    print_kerninfo();
    80200040:	06e000ef          	jal	ra,802000ae <print_kerninfo>

    // grade_backtrace();

    idt_init();  // init interrupt descriptor table
    80200044:	126000ef          	jal	ra,8020016a <idt_init>

    // rdtime in mbare mode crashes
    clock_init();  // init clock interrupt
    80200048:	0f6000ef          	jal	ra,8020013e <clock_init>

    intr_enable();  // enable irq interrupt
    8020004c:	118000ef          	jal	ra,80200164 <intr_enable>


    asm(
    80200050:	9002                	ebreak
        "ebreak"
    );

    
    cprintf("end debug\n");
    80200052:	00001517          	auipc	a0,0x1
    80200056:	9ce50513          	addi	a0,a0,-1586 # 80200a20 <etext+0x2a>
    8020005a:	020000ef          	jal	ra,8020007a <cprintf>
    while (1)
        ;
    8020005e:	a001                	j	8020005e <kern_init+0x52>

0000000080200060 <cputch>:

/* *
 * cputch - writes a single character @c to stdout, and it will
 * increace the value of counter pointed by @cnt.
 * */
static void cputch(int c, int *cnt) {
    80200060:	1141                	addi	sp,sp,-16
    80200062:	e022                	sd	s0,0(sp)
    80200064:	e406                	sd	ra,8(sp)
    80200066:	842e                	mv	s0,a1
    cons_putc(c);
    80200068:	0f4000ef          	jal	ra,8020015c <cons_putc>
    (*cnt)++;
    8020006c:	401c                	lw	a5,0(s0)
}
    8020006e:	60a2                	ld	ra,8(sp)
    (*cnt)++;
    80200070:	2785                	addiw	a5,a5,1
    80200072:	c01c                	sw	a5,0(s0)
}
    80200074:	6402                	ld	s0,0(sp)
    80200076:	0141                	addi	sp,sp,16
    80200078:	8082                	ret

000000008020007a <cprintf>:
 * cprintf - formats a string and writes it to stdout
 *
 * The return value is the number of characters which would be
 * written to stdout.
 * */
int cprintf(const char *fmt, ...) {
    8020007a:	711d                	addi	sp,sp,-96
    va_list ap;
    int cnt;
    va_start(ap, fmt);
    8020007c:	02810313          	addi	t1,sp,40 # 80204028 <end+0x10>
int cprintf(const char *fmt, ...) {
    80200080:	f42e                	sd	a1,40(sp)
    80200082:	f832                	sd	a2,48(sp)
    80200084:	fc36                	sd	a3,56(sp)
    vprintfmt((void *)cputch, &cnt, fmt, ap);
    80200086:	862a                	mv	a2,a0
    80200088:	004c                	addi	a1,sp,4
    8020008a:	00000517          	auipc	a0,0x0
    8020008e:	fd650513          	addi	a0,a0,-42 # 80200060 <cputch>
    80200092:	869a                	mv	a3,t1
int cprintf(const char *fmt, ...) {
    80200094:	ec06                	sd	ra,24(sp)
    80200096:	e0ba                	sd	a4,64(sp)
    80200098:	e4be                	sd	a5,72(sp)
    8020009a:	e8c2                	sd	a6,80(sp)
    8020009c:	ecc6                	sd	a7,88(sp)
    va_start(ap, fmt);
    8020009e:	e41a                	sd	t1,8(sp)
    int cnt = 0;
    802000a0:	c202                	sw	zero,4(sp)
    vprintfmt((void *)cputch, &cnt, fmt, ap);
    802000a2:	590000ef          	jal	ra,80200632 <vprintfmt>
    cnt = vcprintf(fmt, ap);
    va_end(ap);
    return cnt;
}
    802000a6:	60e2                	ld	ra,24(sp)
    802000a8:	4512                	lw	a0,4(sp)
    802000aa:	6125                	addi	sp,sp,96
    802000ac:	8082                	ret

00000000802000ae <print_kerninfo>:
/* *
 * print_kerninfo - print the information about kernel, including the location
 * of kernel entry, the start addresses of data and text segements, the start
 * address of free memory and how many memory that kernel has used.
 * */
void print_kerninfo(void) {
    802000ae:	1141                	addi	sp,sp,-16
    extern char etext[], edata[], end[], kern_init[];
    cprintf("Special kernel symbols:\n");
    802000b0:	00001517          	auipc	a0,0x1
    802000b4:	98050513          	addi	a0,a0,-1664 # 80200a30 <etext+0x3a>
void print_kerninfo(void) {
    802000b8:	e406                	sd	ra,8(sp)
    cprintf("Special kernel symbols:\n");
    802000ba:	fc1ff0ef          	jal	ra,8020007a <cprintf>
    cprintf("  entry  0x%016x (virtual)\n", kern_init);
    802000be:	00000597          	auipc	a1,0x0
    802000c2:	f4e58593          	addi	a1,a1,-178 # 8020000c <kern_init>
    802000c6:	00001517          	auipc	a0,0x1
    802000ca:	98a50513          	addi	a0,a0,-1654 # 80200a50 <etext+0x5a>
    802000ce:	fadff0ef          	jal	ra,8020007a <cprintf>
    cprintf("  etext  0x%016x (virtual)\n", etext);
    802000d2:	00001597          	auipc	a1,0x1
    802000d6:	92458593          	addi	a1,a1,-1756 # 802009f6 <etext>
    802000da:	00001517          	auipc	a0,0x1
    802000de:	99650513          	addi	a0,a0,-1642 # 80200a70 <etext+0x7a>
    802000e2:	f99ff0ef          	jal	ra,8020007a <cprintf>
    cprintf("  edata  0x%016x (virtual)\n", edata);
    802000e6:	00004597          	auipc	a1,0x4
    802000ea:	f2a58593          	addi	a1,a1,-214 # 80204010 <edata>
    802000ee:	00001517          	auipc	a0,0x1
    802000f2:	9a250513          	addi	a0,a0,-1630 # 80200a90 <etext+0x9a>
    802000f6:	f85ff0ef          	jal	ra,8020007a <cprintf>
    cprintf("  end    0x%016x (virtual)\n", end);
    802000fa:	00004597          	auipc	a1,0x4
    802000fe:	f1e58593          	addi	a1,a1,-226 # 80204018 <end>
    80200102:	00001517          	auipc	a0,0x1
    80200106:	9ae50513          	addi	a0,a0,-1618 # 80200ab0 <etext+0xba>
    8020010a:	f71ff0ef          	jal	ra,8020007a <cprintf>
    cprintf("Kernel executable memory footprint: %dKB\n",
            (end - kern_init + 1023) / 1024);
    8020010e:	00004597          	auipc	a1,0x4
    80200112:	30958593          	addi	a1,a1,777 # 80204417 <end+0x3ff>
    80200116:	00000797          	auipc	a5,0x0
    8020011a:	ef678793          	addi	a5,a5,-266 # 8020000c <kern_init>
    8020011e:	40f587b3          	sub	a5,a1,a5
    cprintf("Kernel executable memory footprint: %dKB\n",
    80200122:	43f7d593          	srai	a1,a5,0x3f
}
    80200126:	60a2                	ld	ra,8(sp)
    cprintf("Kernel executable memory footprint: %dKB\n",
    80200128:	3ff5f593          	andi	a1,a1,1023
    8020012c:	95be                	add	a1,a1,a5
    8020012e:	85a9                	srai	a1,a1,0xa
    80200130:	00001517          	auipc	a0,0x1
    80200134:	9a050513          	addi	a0,a0,-1632 # 80200ad0 <etext+0xda>
}
    80200138:	0141                	addi	sp,sp,16
    cprintf("Kernel executable memory footprint: %dKB\n",
    8020013a:	f41ff06f          	j	8020007a <cprintf>

000000008020013e <clock_init>:
 * clock_init - initialize 8253 clock to interrupt 100 times per second,
 * and then enable IRQ_TIMER.
 * */
void clock_init(void) {
    // enable timer interrupt in sie
    set_csr(sie, MIP_STIP);
    8020013e:	02000793          	li	a5,32
    80200142:	1047a7f3          	csrrs	a5,sie,a5
    //clock_set_next_event();

    // initialize time counter 'ticks' to zero
    ticks = 0;

    cprintf("++ setup timer interrupts\n");
    80200146:	00001517          	auipc	a0,0x1
    8020014a:	9ba50513          	addi	a0,a0,-1606 # 80200b00 <etext+0x10a>
    ticks = 0;
    8020014e:	00004797          	auipc	a5,0x4
    80200152:	ec07b123          	sd	zero,-318(a5) # 80204010 <edata>
    cprintf("++ setup timer interrupts\n");
    80200156:	f25ff06f          	j	8020007a <cprintf>

000000008020015a <cons_init>:

/* serial_intr - try to feed input characters from serial port */
void serial_intr(void) {}

/* cons_init - initializes the console devices */
void cons_init(void) {}
    8020015a:	8082                	ret

000000008020015c <cons_putc>:

/* cons_putc - print a single character @c to console devices */
void cons_putc(int c) { sbi_console_putchar((unsigned char)c); }
    8020015c:	0ff57513          	andi	a0,a0,255
    80200160:	05f0006f          	j	802009be <sbi_console_putchar>

0000000080200164 <intr_enable>:
#include <intr.h>
#include <riscv.h>

/* intr_enable - enable irq interrupt */
void intr_enable(void) { set_csr(sstatus, SSTATUS_SIE); }
    80200164:	100167f3          	csrrsi	a5,sstatus,2
    80200168:	8082                	ret

000000008020016a <idt_init>:
 */
void idt_init(void) {
    extern void __alltraps(void);
    /* Set sscratch register to 0, indicating to exception vector that we are
     * presently executing in the kernel */
    write_csr(sscratch, 0);
    8020016a:	14005073          	csrwi	sscratch,0
    /* Set the exception vector address */
    write_csr(stvec, &__alltraps);
    8020016e:	00000797          	auipc	a5,0x0
    80200172:	36a78793          	addi	a5,a5,874 # 802004d8 <__alltraps>
    80200176:	10579073          	csrw	stvec,a5
}
    8020017a:	8082                	ret

000000008020017c <print_regs>:
    cprintf("  badvaddr 0x%08x\n", tf->badvaddr);
    cprintf("  cause    0x%08x\n", tf->cause);
}

void print_regs(struct pushregs *gpr) {
    cprintf("  zero     0x%08x\n", gpr->zero);
    8020017c:	610c                	ld	a1,0(a0)
void print_regs(struct pushregs *gpr) {
    8020017e:	1141                	addi	sp,sp,-16
    80200180:	e022                	sd	s0,0(sp)
    80200182:	842a                	mv	s0,a0
    cprintf("  zero     0x%08x\n", gpr->zero);
    80200184:	00001517          	auipc	a0,0x1
    80200188:	abc50513          	addi	a0,a0,-1348 # 80200c40 <etext+0x24a>
void print_regs(struct pushregs *gpr) {
    8020018c:	e406                	sd	ra,8(sp)
    cprintf("  zero     0x%08x\n", gpr->zero);
    8020018e:	eedff0ef          	jal	ra,8020007a <cprintf>
    cprintf("  ra       0x%08x\n", gpr->ra);
    80200192:	640c                	ld	a1,8(s0)
    80200194:	00001517          	auipc	a0,0x1
    80200198:	ac450513          	addi	a0,a0,-1340 # 80200c58 <etext+0x262>
    8020019c:	edfff0ef          	jal	ra,8020007a <cprintf>
    cprintf("  sp       0x%08x\n", gpr->sp);
    802001a0:	680c                	ld	a1,16(s0)
    802001a2:	00001517          	auipc	a0,0x1
    802001a6:	ace50513          	addi	a0,a0,-1330 # 80200c70 <etext+0x27a>
    802001aa:	ed1ff0ef          	jal	ra,8020007a <cprintf>
    cprintf("  gp       0x%08x\n", gpr->gp);
    802001ae:	6c0c                	ld	a1,24(s0)
    802001b0:	00001517          	auipc	a0,0x1
    802001b4:	ad850513          	addi	a0,a0,-1320 # 80200c88 <etext+0x292>
    802001b8:	ec3ff0ef          	jal	ra,8020007a <cprintf>
    cprintf("  tp       0x%08x\n", gpr->tp);
    802001bc:	700c                	ld	a1,32(s0)
    802001be:	00001517          	auipc	a0,0x1
    802001c2:	ae250513          	addi	a0,a0,-1310 # 80200ca0 <etext+0x2aa>
    802001c6:	eb5ff0ef          	jal	ra,8020007a <cprintf>
    cprintf("  t0       0x%08x\n", gpr->t0);
    802001ca:	740c                	ld	a1,40(s0)
    802001cc:	00001517          	auipc	a0,0x1
    802001d0:	aec50513          	addi	a0,a0,-1300 # 80200cb8 <etext+0x2c2>
    802001d4:	ea7ff0ef          	jal	ra,8020007a <cprintf>
    cprintf("  t1       0x%08x\n", gpr->t1);
    802001d8:	780c                	ld	a1,48(s0)
    802001da:	00001517          	auipc	a0,0x1
    802001de:	af650513          	addi	a0,a0,-1290 # 80200cd0 <etext+0x2da>
    802001e2:	e99ff0ef          	jal	ra,8020007a <cprintf>
    cprintf("  t2       0x%08x\n", gpr->t2);
    802001e6:	7c0c                	ld	a1,56(s0)
    802001e8:	00001517          	auipc	a0,0x1
    802001ec:	b0050513          	addi	a0,a0,-1280 # 80200ce8 <etext+0x2f2>
    802001f0:	e8bff0ef          	jal	ra,8020007a <cprintf>
    cprintf("  s0       0x%08x\n", gpr->s0);
    802001f4:	602c                	ld	a1,64(s0)
    802001f6:	00001517          	auipc	a0,0x1
    802001fa:	b0a50513          	addi	a0,a0,-1270 # 80200d00 <etext+0x30a>
    802001fe:	e7dff0ef          	jal	ra,8020007a <cprintf>
    cprintf("  s1       0x%08x\n", gpr->s1);
    80200202:	642c                	ld	a1,72(s0)
    80200204:	00001517          	auipc	a0,0x1
    80200208:	b1450513          	addi	a0,a0,-1260 # 80200d18 <etext+0x322>
    8020020c:	e6fff0ef          	jal	ra,8020007a <cprintf>
    cprintf("  a0       0x%08x\n", gpr->a0);
    80200210:	682c                	ld	a1,80(s0)
    80200212:	00001517          	auipc	a0,0x1
    80200216:	b1e50513          	addi	a0,a0,-1250 # 80200d30 <etext+0x33a>
    8020021a:	e61ff0ef          	jal	ra,8020007a <cprintf>
    cprintf("  a1       0x%08x\n", gpr->a1);
    8020021e:	6c2c                	ld	a1,88(s0)
    80200220:	00001517          	auipc	a0,0x1
    80200224:	b2850513          	addi	a0,a0,-1240 # 80200d48 <etext+0x352>
    80200228:	e53ff0ef          	jal	ra,8020007a <cprintf>
    cprintf("  a2       0x%08x\n", gpr->a2);
    8020022c:	702c                	ld	a1,96(s0)
    8020022e:	00001517          	auipc	a0,0x1
    80200232:	b3250513          	addi	a0,a0,-1230 # 80200d60 <etext+0x36a>
    80200236:	e45ff0ef          	jal	ra,8020007a <cprintf>
    cprintf("  a3       0x%08x\n", gpr->a3);
    8020023a:	742c                	ld	a1,104(s0)
    8020023c:	00001517          	auipc	a0,0x1
    80200240:	b3c50513          	addi	a0,a0,-1220 # 80200d78 <etext+0x382>
    80200244:	e37ff0ef          	jal	ra,8020007a <cprintf>
    cprintf("  a4       0x%08x\n", gpr->a4);
    80200248:	782c                	ld	a1,112(s0)
    8020024a:	00001517          	auipc	a0,0x1
    8020024e:	b4650513          	addi	a0,a0,-1210 # 80200d90 <etext+0x39a>
    80200252:	e29ff0ef          	jal	ra,8020007a <cprintf>
    cprintf("  a5       0x%08x\n", gpr->a5);
    80200256:	7c2c                	ld	a1,120(s0)
    80200258:	00001517          	auipc	a0,0x1
    8020025c:	b5050513          	addi	a0,a0,-1200 # 80200da8 <etext+0x3b2>
    80200260:	e1bff0ef          	jal	ra,8020007a <cprintf>
    cprintf("  a6       0x%08x\n", gpr->a6);
    80200264:	604c                	ld	a1,128(s0)
    80200266:	00001517          	auipc	a0,0x1
    8020026a:	b5a50513          	addi	a0,a0,-1190 # 80200dc0 <etext+0x3ca>
    8020026e:	e0dff0ef          	jal	ra,8020007a <cprintf>
    cprintf("  a7       0x%08x\n", gpr->a7);
    80200272:	644c                	ld	a1,136(s0)
    80200274:	00001517          	auipc	a0,0x1
    80200278:	b6450513          	addi	a0,a0,-1180 # 80200dd8 <etext+0x3e2>
    8020027c:	dffff0ef          	jal	ra,8020007a <cprintf>
    cprintf("  s2       0x%08x\n", gpr->s2);
    80200280:	684c                	ld	a1,144(s0)
    80200282:	00001517          	auipc	a0,0x1
    80200286:	b6e50513          	addi	a0,a0,-1170 # 80200df0 <etext+0x3fa>
    8020028a:	df1ff0ef          	jal	ra,8020007a <cprintf>
    cprintf("  s3       0x%08x\n", gpr->s3);
    8020028e:	6c4c                	ld	a1,152(s0)
    80200290:	00001517          	auipc	a0,0x1
    80200294:	b7850513          	addi	a0,a0,-1160 # 80200e08 <etext+0x412>
    80200298:	de3ff0ef          	jal	ra,8020007a <cprintf>
    cprintf("  s4       0x%08x\n", gpr->s4);
    8020029c:	704c                	ld	a1,160(s0)
    8020029e:	00001517          	auipc	a0,0x1
    802002a2:	b8250513          	addi	a0,a0,-1150 # 80200e20 <etext+0x42a>
    802002a6:	dd5ff0ef          	jal	ra,8020007a <cprintf>
    cprintf("  s5       0x%08x\n", gpr->s5);
    802002aa:	744c                	ld	a1,168(s0)
    802002ac:	00001517          	auipc	a0,0x1
    802002b0:	b8c50513          	addi	a0,a0,-1140 # 80200e38 <etext+0x442>
    802002b4:	dc7ff0ef          	jal	ra,8020007a <cprintf>
    cprintf("  s6       0x%08x\n", gpr->s6);
    802002b8:	784c                	ld	a1,176(s0)
    802002ba:	00001517          	auipc	a0,0x1
    802002be:	b9650513          	addi	a0,a0,-1130 # 80200e50 <etext+0x45a>
    802002c2:	db9ff0ef          	jal	ra,8020007a <cprintf>
    cprintf("  s7       0x%08x\n", gpr->s7);
    802002c6:	7c4c                	ld	a1,184(s0)
    802002c8:	00001517          	auipc	a0,0x1
    802002cc:	ba050513          	addi	a0,a0,-1120 # 80200e68 <etext+0x472>
    802002d0:	dabff0ef          	jal	ra,8020007a <cprintf>
    cprintf("  s8       0x%08x\n", gpr->s8);
    802002d4:	606c                	ld	a1,192(s0)
    802002d6:	00001517          	auipc	a0,0x1
    802002da:	baa50513          	addi	a0,a0,-1110 # 80200e80 <etext+0x48a>
    802002de:	d9dff0ef          	jal	ra,8020007a <cprintf>
    cprintf("  s9       0x%08x\n", gpr->s9);
    802002e2:	646c                	ld	a1,200(s0)
    802002e4:	00001517          	auipc	a0,0x1
    802002e8:	bb450513          	addi	a0,a0,-1100 # 80200e98 <etext+0x4a2>
    802002ec:	d8fff0ef          	jal	ra,8020007a <cprintf>
    cprintf("  s10      0x%08x\n", gpr->s10);
    802002f0:	686c                	ld	a1,208(s0)
    802002f2:	00001517          	auipc	a0,0x1
    802002f6:	bbe50513          	addi	a0,a0,-1090 # 80200eb0 <etext+0x4ba>
    802002fa:	d81ff0ef          	jal	ra,8020007a <cprintf>
    cprintf("  s11      0x%08x\n", gpr->s11);
    802002fe:	6c6c                	ld	a1,216(s0)
    80200300:	00001517          	auipc	a0,0x1
    80200304:	bc850513          	addi	a0,a0,-1080 # 80200ec8 <etext+0x4d2>
    80200308:	d73ff0ef          	jal	ra,8020007a <cprintf>
    cprintf("  t3       0x%08x\n", gpr->t3);
    8020030c:	706c                	ld	a1,224(s0)
    8020030e:	00001517          	auipc	a0,0x1
    80200312:	bd250513          	addi	a0,a0,-1070 # 80200ee0 <etext+0x4ea>
    80200316:	d65ff0ef          	jal	ra,8020007a <cprintf>
    cprintf("  t4       0x%08x\n", gpr->t4);
    8020031a:	746c                	ld	a1,232(s0)
    8020031c:	00001517          	auipc	a0,0x1
    80200320:	bdc50513          	addi	a0,a0,-1060 # 80200ef8 <etext+0x502>
    80200324:	d57ff0ef          	jal	ra,8020007a <cprintf>
    cprintf("  t5       0x%08x\n", gpr->t5);
    80200328:	786c                	ld	a1,240(s0)
    8020032a:	00001517          	auipc	a0,0x1
    8020032e:	be650513          	addi	a0,a0,-1050 # 80200f10 <etext+0x51a>
    80200332:	d49ff0ef          	jal	ra,8020007a <cprintf>
    cprintf("  t6       0x%08x\n", gpr->t6);
    80200336:	7c6c                	ld	a1,248(s0)
}
    80200338:	6402                	ld	s0,0(sp)
    8020033a:	60a2                	ld	ra,8(sp)
    cprintf("  t6       0x%08x\n", gpr->t6);
    8020033c:	00001517          	auipc	a0,0x1
    80200340:	bec50513          	addi	a0,a0,-1044 # 80200f28 <etext+0x532>
}
    80200344:	0141                	addi	sp,sp,16
    cprintf("  t6       0x%08x\n", gpr->t6);
    80200346:	d35ff06f          	j	8020007a <cprintf>

000000008020034a <print_trapframe>:
void print_trapframe(struct trapframe *tf) {
    8020034a:	1141                	addi	sp,sp,-16
    8020034c:	e022                	sd	s0,0(sp)
    cprintf("trapframe at %p\n", tf);
    8020034e:	85aa                	mv	a1,a0
void print_trapframe(struct trapframe *tf) {
    80200350:	842a                	mv	s0,a0
    cprintf("trapframe at %p\n", tf);
    80200352:	00001517          	auipc	a0,0x1
    80200356:	bee50513          	addi	a0,a0,-1042 # 80200f40 <etext+0x54a>
void print_trapframe(struct trapframe *tf) {
    8020035a:	e406                	sd	ra,8(sp)
    cprintf("trapframe at %p\n", tf);
    8020035c:	d1fff0ef          	jal	ra,8020007a <cprintf>
    print_regs(&tf->gpr);
    80200360:	8522                	mv	a0,s0
    80200362:	e1bff0ef          	jal	ra,8020017c <print_regs>
    cprintf("  status   0x%08x\n", tf->status);
    80200366:	10043583          	ld	a1,256(s0)
    8020036a:	00001517          	auipc	a0,0x1
    8020036e:	bee50513          	addi	a0,a0,-1042 # 80200f58 <etext+0x562>
    80200372:	d09ff0ef          	jal	ra,8020007a <cprintf>
    cprintf("  epc      0x%08x\n", tf->epc);
    80200376:	10843583          	ld	a1,264(s0)
    8020037a:	00001517          	auipc	a0,0x1
    8020037e:	bf650513          	addi	a0,a0,-1034 # 80200f70 <etext+0x57a>
    80200382:	cf9ff0ef          	jal	ra,8020007a <cprintf>
    cprintf("  badvaddr 0x%08x\n", tf->badvaddr);
    80200386:	11043583          	ld	a1,272(s0)
    8020038a:	00001517          	auipc	a0,0x1
    8020038e:	bfe50513          	addi	a0,a0,-1026 # 80200f88 <etext+0x592>
    80200392:	ce9ff0ef          	jal	ra,8020007a <cprintf>
    cprintf("  cause    0x%08x\n", tf->cause);
    80200396:	11843583          	ld	a1,280(s0)
}
    8020039a:	6402                	ld	s0,0(sp)
    8020039c:	60a2                	ld	ra,8(sp)
    cprintf("  cause    0x%08x\n", tf->cause);
    8020039e:	00001517          	auipc	a0,0x1
    802003a2:	c0250513          	addi	a0,a0,-1022 # 80200fa0 <etext+0x5aa>
}
    802003a6:	0141                	addi	sp,sp,16
    cprintf("  cause    0x%08x\n", tf->cause);
    802003a8:	cd3ff06f          	j	8020007a <cprintf>

00000000802003ac <interrupt_handler>:

void interrupt_handler(struct trapframe *tf) {
    intptr_t cause = (tf->cause << 1) >> 1;
    802003ac:	11853783          	ld	a5,280(a0)
    802003b0:	577d                	li	a4,-1
    802003b2:	8305                	srli	a4,a4,0x1
    802003b4:	8ff9                	and	a5,a5,a4
    switch (cause) {
    802003b6:	472d                	li	a4,11
    802003b8:	08f76563          	bltu	a4,a5,80200442 <interrupt_handler+0x96>
    802003bc:	00000717          	auipc	a4,0x0
    802003c0:	76070713          	addi	a4,a4,1888 # 80200b1c <etext+0x126>
    802003c4:	078a                	slli	a5,a5,0x2
    802003c6:	97ba                	add	a5,a5,a4
    802003c8:	439c                	lw	a5,0(a5)
    802003ca:	97ba                	add	a5,a5,a4
    802003cc:	8782                	jr	a5
            break;
        case IRQ_H_SOFT:
            cprintf("Hypervisor software interrupt\n");
            break;
        case IRQ_M_SOFT:
            cprintf("Machine software interrupt\n");
    802003ce:	00001517          	auipc	a0,0x1
    802003d2:	82250513          	addi	a0,a0,-2014 # 80200bf0 <etext+0x1fa>
    802003d6:	ca5ff06f          	j	8020007a <cprintf>
            cprintf("Hypervisor software interrupt\n");
    802003da:	00000517          	auipc	a0,0x0
    802003de:	7f650513          	addi	a0,a0,2038 # 80200bd0 <etext+0x1da>
    802003e2:	c99ff06f          	j	8020007a <cprintf>
            cprintf("User software interrupt\n");
    802003e6:	00000517          	auipc	a0,0x0
    802003ea:	7aa50513          	addi	a0,a0,1962 # 80200b90 <etext+0x19a>
    802003ee:	c8dff06f          	j	8020007a <cprintf>
            cprintf("Supervisor software interrupt\n");
    802003f2:	00000517          	auipc	a0,0x0
    802003f6:	7be50513          	addi	a0,a0,1982 # 80200bb0 <etext+0x1ba>
    802003fa:	c81ff06f          	j	8020007a <cprintf>
            break;
        case IRQ_U_EXT:
            cprintf("User software interrupt\n");
            break;
        case IRQ_S_EXT:
            cprintf("Supervisor external interrupt\n");
    802003fe:	00001517          	auipc	a0,0x1
    80200402:	82250513          	addi	a0,a0,-2014 # 80200c20 <etext+0x22a>
    80200406:	c75ff06f          	j	8020007a <cprintf>
void interrupt_handler(struct trapframe *tf) {
    8020040a:	1141                	addi	sp,sp,-16
    8020040c:	e022                	sd	s0,0(sp)
            ticks++;
    8020040e:	00004417          	auipc	s0,0x4
    80200412:	c0240413          	addi	s0,s0,-1022 # 80204010 <edata>
    80200416:	601c                	ld	a5,0(s0)
void interrupt_handler(struct trapframe *tf) {
    80200418:	e406                	sd	ra,8(sp)
            ticks++;
    8020041a:	0785                	addi	a5,a5,1
    8020041c:	00004717          	auipc	a4,0x4
    80200420:	bef73a23          	sd	a5,-1036(a4) # 80204010 <edata>
            if(ticks%TICK_NUM==0)print_ticks();
    80200424:	601c                	ld	a5,0(s0)
    80200426:	06400713          	li	a4,100
    8020042a:	02e7f7b3          	remu	a5,a5,a4
    8020042e:	cf81                	beqz	a5,80200446 <interrupt_handler+0x9a>
            if(ticks==1000)sbi_shutdown();
    80200430:	6018                	ld	a4,0(s0)
    80200432:	3e800793          	li	a5,1000
    80200436:	02f70163          	beq	a4,a5,80200458 <interrupt_handler+0xac>
            break;
        default:
            print_trapframe(tf);
            break;
    }
}
    8020043a:	60a2                	ld	ra,8(sp)
    8020043c:	6402                	ld	s0,0(sp)
    8020043e:	0141                	addi	sp,sp,16
    80200440:	8082                	ret
            print_trapframe(tf);
    80200442:	f09ff06f          	j	8020034a <print_trapframe>
    cprintf("%d ticks\n", TICK_NUM);
    80200446:	06400593          	li	a1,100
    8020044a:	00000517          	auipc	a0,0x0
    8020044e:	7c650513          	addi	a0,a0,1990 # 80200c10 <etext+0x21a>
    80200452:	c29ff0ef          	jal	ra,8020007a <cprintf>
    80200456:	bfe9                	j	80200430 <interrupt_handler+0x84>
}
    80200458:	6402                	ld	s0,0(sp)
    8020045a:	60a2                	ld	ra,8(sp)
    8020045c:	0141                	addi	sp,sp,16
            if(ticks==1000)sbi_shutdown();
    8020045e:	57c0006f          	j	802009da <sbi_shutdown>

0000000080200462 <exception_handler>:

void exception_handler(struct trapframe *tf) {
    switch (tf->cause) {
    80200462:	11853783          	ld	a5,280(a0)
    80200466:	472d                	li	a4,11
    80200468:	00f76b63          	bltu	a4,a5,8020047e <exception_handler+0x1c>
    8020046c:	4705                	li	a4,1
    8020046e:	00f71733          	sll	a4,a4,a5
    80200472:	6785                	lui	a5,0x1
    80200474:	17dd                	addi	a5,a5,-9
    80200476:	8ff9                	and	a5,a5,a4
    80200478:	e789                	bnez	a5,80200482 <exception_handler+0x20>
    8020047a:	8b21                	andi	a4,a4,8
    8020047c:	e701                	bnez	a4,80200484 <exception_handler+0x22>
        case CAUSE_HYPERVISOR_ECALL:
            break;
        case CAUSE_MACHINE_ECALL:
            break;
        default:
            print_trapframe(tf);
    8020047e:	ecdff06f          	j	8020034a <print_trapframe>
    80200482:	8082                	ret
void exception_handler(struct trapframe *tf) {
    80200484:	1141                	addi	sp,sp,-16
    80200486:	e022                	sd	s0,0(sp)
    80200488:	842a                	mv	s0,a0
            cprintf("Exception type:breakpoint\n");
    8020048a:	00000517          	auipc	a0,0x0
    8020048e:	6c650513          	addi	a0,a0,1734 # 80200b50 <etext+0x15a>
void exception_handler(struct trapframe *tf) {
    80200492:	e406                	sd	ra,8(sp)
            cprintf("Exception type:breakpoint\n");
    80200494:	be7ff0ef          	jal	ra,8020007a <cprintf>
            cprintf("ebreak caught at");
    80200498:	00000517          	auipc	a0,0x0
    8020049c:	6d850513          	addi	a0,a0,1752 # 80200b70 <etext+0x17a>
    802004a0:	bdbff0ef          	jal	ra,8020007a <cprintf>
            cprintf("0x%08x\n", tf->epc);
    802004a4:	10843583          	ld	a1,264(s0)
    802004a8:	00000517          	auipc	a0,0x0
    802004ac:	6e050513          	addi	a0,a0,1760 # 80200b88 <etext+0x192>
    802004b0:	bcbff0ef          	jal	ra,8020007a <cprintf>
            tf->epc+=32;
    802004b4:	10843783          	ld	a5,264(s0)
            break;
    }
}
    802004b8:	60a2                	ld	ra,8(sp)
            tf->epc+=32;
    802004ba:	02078793          	addi	a5,a5,32 # 1020 <BASE_ADDRESS-0x801fefe0>
    802004be:	10f43423          	sd	a5,264(s0)
}
    802004c2:	6402                	ld	s0,0(sp)
    802004c4:	0141                	addi	sp,sp,16
    802004c6:	8082                	ret

00000000802004c8 <trap>:

/* trap_dispatch - dispatch based on what type of trap occurred */
static inline void trap_dispatch(struct trapframe *tf) {
    if ((intptr_t)tf->cause < 0) {
    802004c8:	11853783          	ld	a5,280(a0)
    802004cc:	0007c463          	bltz	a5,802004d4 <trap+0xc>
        // interrupts
        interrupt_handler(tf);
    } else {
        // exceptions
        exception_handler(tf);
    802004d0:	f93ff06f          	j	80200462 <exception_handler>
        interrupt_handler(tf);
    802004d4:	ed9ff06f          	j	802003ac <interrupt_handler>

00000000802004d8 <__alltraps>:
    .endm

    .globl __alltraps
.align(2)
__alltraps:
    SAVE_ALL
    802004d8:	14011073          	csrw	sscratch,sp
    802004dc:	712d                	addi	sp,sp,-288
    802004de:	e002                	sd	zero,0(sp)
    802004e0:	e406                	sd	ra,8(sp)
    802004e2:	ec0e                	sd	gp,24(sp)
    802004e4:	f012                	sd	tp,32(sp)
    802004e6:	f416                	sd	t0,40(sp)
    802004e8:	f81a                	sd	t1,48(sp)
    802004ea:	fc1e                	sd	t2,56(sp)
    802004ec:	e0a2                	sd	s0,64(sp)
    802004ee:	e4a6                	sd	s1,72(sp)
    802004f0:	e8aa                	sd	a0,80(sp)
    802004f2:	ecae                	sd	a1,88(sp)
    802004f4:	f0b2                	sd	a2,96(sp)
    802004f6:	f4b6                	sd	a3,104(sp)
    802004f8:	f8ba                	sd	a4,112(sp)
    802004fa:	fcbe                	sd	a5,120(sp)
    802004fc:	e142                	sd	a6,128(sp)
    802004fe:	e546                	sd	a7,136(sp)
    80200500:	e94a                	sd	s2,144(sp)
    80200502:	ed4e                	sd	s3,152(sp)
    80200504:	f152                	sd	s4,160(sp)
    80200506:	f556                	sd	s5,168(sp)
    80200508:	f95a                	sd	s6,176(sp)
    8020050a:	fd5e                	sd	s7,184(sp)
    8020050c:	e1e2                	sd	s8,192(sp)
    8020050e:	e5e6                	sd	s9,200(sp)
    80200510:	e9ea                	sd	s10,208(sp)
    80200512:	edee                	sd	s11,216(sp)
    80200514:	f1f2                	sd	t3,224(sp)
    80200516:	f5f6                	sd	t4,232(sp)
    80200518:	f9fa                	sd	t5,240(sp)
    8020051a:	fdfe                	sd	t6,248(sp)
    8020051c:	14001473          	csrrw	s0,sscratch,zero
    80200520:	100024f3          	csrr	s1,sstatus
    80200524:	14102973          	csrr	s2,sepc
    80200528:	143029f3          	csrr	s3,stval
    8020052c:	14202a73          	csrr	s4,scause
    80200530:	e822                	sd	s0,16(sp)
    80200532:	e226                	sd	s1,256(sp)
    80200534:	e64a                	sd	s2,264(sp)
    80200536:	ea4e                	sd	s3,272(sp)
    80200538:	ee52                	sd	s4,280(sp)

    move  a0, sp
    8020053a:	850a                	mv	a0,sp
    jal trap
    8020053c:	f8dff0ef          	jal	ra,802004c8 <trap>

0000000080200540 <__trapret>:
    # sp should be the same as before "jal trap"

    .globl __trapret
__trapret:
    RESTORE_ALL
    80200540:	6492                	ld	s1,256(sp)
    80200542:	6932                	ld	s2,264(sp)
    80200544:	10049073          	csrw	sstatus,s1
    80200548:	14191073          	csrw	sepc,s2
    8020054c:	60a2                	ld	ra,8(sp)
    8020054e:	61e2                	ld	gp,24(sp)
    80200550:	7202                	ld	tp,32(sp)
    80200552:	72a2                	ld	t0,40(sp)
    80200554:	7342                	ld	t1,48(sp)
    80200556:	73e2                	ld	t2,56(sp)
    80200558:	6406                	ld	s0,64(sp)
    8020055a:	64a6                	ld	s1,72(sp)
    8020055c:	6546                	ld	a0,80(sp)
    8020055e:	65e6                	ld	a1,88(sp)
    80200560:	7606                	ld	a2,96(sp)
    80200562:	76a6                	ld	a3,104(sp)
    80200564:	7746                	ld	a4,112(sp)
    80200566:	77e6                	ld	a5,120(sp)
    80200568:	680a                	ld	a6,128(sp)
    8020056a:	68aa                	ld	a7,136(sp)
    8020056c:	694a                	ld	s2,144(sp)
    8020056e:	69ea                	ld	s3,152(sp)
    80200570:	7a0a                	ld	s4,160(sp)
    80200572:	7aaa                	ld	s5,168(sp)
    80200574:	7b4a                	ld	s6,176(sp)
    80200576:	7bea                	ld	s7,184(sp)
    80200578:	6c0e                	ld	s8,192(sp)
    8020057a:	6cae                	ld	s9,200(sp)
    8020057c:	6d4e                	ld	s10,208(sp)
    8020057e:	6dee                	ld	s11,216(sp)
    80200580:	7e0e                	ld	t3,224(sp)
    80200582:	7eae                	ld	t4,232(sp)
    80200584:	7f4e                	ld	t5,240(sp)
    80200586:	7fee                	ld	t6,248(sp)
    80200588:	6142                	ld	sp,16(sp)
    # return from supervisor call
    sret
    8020058a:	10200073          	sret

000000008020058e <strnlen>:
 * pointed by @s.
 * */
size_t
strnlen(const char *s, size_t len) {
    size_t cnt = 0;
    while (cnt < len && *s ++ != '\0') {
    8020058e:	c185                	beqz	a1,802005ae <strnlen+0x20>
    80200590:	00054783          	lbu	a5,0(a0)
    80200594:	cf89                	beqz	a5,802005ae <strnlen+0x20>
    size_t cnt = 0;
    80200596:	4781                	li	a5,0
    80200598:	a021                	j	802005a0 <strnlen+0x12>
    while (cnt < len && *s ++ != '\0') {
    8020059a:	00074703          	lbu	a4,0(a4)
    8020059e:	c711                	beqz	a4,802005aa <strnlen+0x1c>
        cnt ++;
    802005a0:	0785                	addi	a5,a5,1
    while (cnt < len && *s ++ != '\0') {
    802005a2:	00f50733          	add	a4,a0,a5
    802005a6:	fef59ae3          	bne	a1,a5,8020059a <strnlen+0xc>
    }
    return cnt;
}
    802005aa:	853e                	mv	a0,a5
    802005ac:	8082                	ret
    size_t cnt = 0;
    802005ae:	4781                	li	a5,0
}
    802005b0:	853e                	mv	a0,a5
    802005b2:	8082                	ret

00000000802005b4 <memset>:
memset(void *s, char c, size_t n) {
#ifdef __HAVE_ARCH_MEMSET
    return __memset(s, c, n);
#else
    char *p = s;
    while (n -- > 0) {
    802005b4:	ca01                	beqz	a2,802005c4 <memset+0x10>
    802005b6:	962a                	add	a2,a2,a0
    char *p = s;
    802005b8:	87aa                	mv	a5,a0
        *p ++ = c;
    802005ba:	0785                	addi	a5,a5,1
    802005bc:	feb78fa3          	sb	a1,-1(a5)
    while (n -- > 0) {
    802005c0:	fec79de3          	bne	a5,a2,802005ba <memset+0x6>
    }
    return s;
#endif /* __HAVE_ARCH_MEMSET */
}
    802005c4:	8082                	ret

00000000802005c6 <printnum>:
 * */
static void
printnum(void (*putch)(int, void*), void *putdat,
        unsigned long long num, unsigned base, int width, int padc) {
    unsigned long long result = num;
    unsigned mod = do_div(result, base);
    802005c6:	02069813          	slli	a6,a3,0x20
        unsigned long long num, unsigned base, int width, int padc) {
    802005ca:	7179                	addi	sp,sp,-48
    unsigned mod = do_div(result, base);
    802005cc:	02085813          	srli	a6,a6,0x20
        unsigned long long num, unsigned base, int width, int padc) {
    802005d0:	e052                	sd	s4,0(sp)
    unsigned mod = do_div(result, base);
    802005d2:	03067a33          	remu	s4,a2,a6
        unsigned long long num, unsigned base, int width, int padc) {
    802005d6:	f022                	sd	s0,32(sp)
    802005d8:	ec26                	sd	s1,24(sp)
    802005da:	e84a                	sd	s2,16(sp)
    802005dc:	f406                	sd	ra,40(sp)
    802005de:	e44e                	sd	s3,8(sp)
    802005e0:	84aa                	mv	s1,a0
    802005e2:	892e                	mv	s2,a1
    802005e4:	fff7041b          	addiw	s0,a4,-1
    unsigned mod = do_div(result, base);
    802005e8:	2a01                	sext.w	s4,s4

    // first recursively print all preceding (more significant) digits
    if (num >= base) {
    802005ea:	03067e63          	bleu	a6,a2,80200626 <printnum+0x60>
    802005ee:	89be                	mv	s3,a5
        printnum(putch, putdat, result, base, width - 1, padc);
    } else {
        // print any needed pad characters before first digit
        while (-- width > 0)
    802005f0:	00805763          	blez	s0,802005fe <printnum+0x38>
    802005f4:	347d                	addiw	s0,s0,-1
            putch(padc, putdat);
    802005f6:	85ca                	mv	a1,s2
    802005f8:	854e                	mv	a0,s3
    802005fa:	9482                	jalr	s1
        while (-- width > 0)
    802005fc:	fc65                	bnez	s0,802005f4 <printnum+0x2e>
    }
    // then print this (the least significant) digit
    putch("0123456789abcdef"[mod], putdat);
    802005fe:	1a02                	slli	s4,s4,0x20
    80200600:	020a5a13          	srli	s4,s4,0x20
    80200604:	00001797          	auipc	a5,0x1
    80200608:	b4478793          	addi	a5,a5,-1212 # 80201148 <error_string+0x38>
    8020060c:	9a3e                	add	s4,s4,a5
}
    8020060e:	7402                	ld	s0,32(sp)
    putch("0123456789abcdef"[mod], putdat);
    80200610:	000a4503          	lbu	a0,0(s4)
}
    80200614:	70a2                	ld	ra,40(sp)
    80200616:	69a2                	ld	s3,8(sp)
    80200618:	6a02                	ld	s4,0(sp)
    putch("0123456789abcdef"[mod], putdat);
    8020061a:	85ca                	mv	a1,s2
    8020061c:	8326                	mv	t1,s1
}
    8020061e:	6942                	ld	s2,16(sp)
    80200620:	64e2                	ld	s1,24(sp)
    80200622:	6145                	addi	sp,sp,48
    putch("0123456789abcdef"[mod], putdat);
    80200624:	8302                	jr	t1
        printnum(putch, putdat, result, base, width - 1, padc);
    80200626:	03065633          	divu	a2,a2,a6
    8020062a:	8722                	mv	a4,s0
    8020062c:	f9bff0ef          	jal	ra,802005c6 <printnum>
    80200630:	b7f9                	j	802005fe <printnum+0x38>

0000000080200632 <vprintfmt>:
 *
 * Call this function if you are already dealing with a va_list.
 * Or you probably want printfmt() instead.
 * */
void
vprintfmt(void (*putch)(int, void*), void *putdat, const char *fmt, va_list ap) {
    80200632:	7119                	addi	sp,sp,-128
    80200634:	f4a6                	sd	s1,104(sp)
    80200636:	f0ca                	sd	s2,96(sp)
    80200638:	e8d2                	sd	s4,80(sp)
    8020063a:	e4d6                	sd	s5,72(sp)
    8020063c:	e0da                	sd	s6,64(sp)
    8020063e:	fc5e                	sd	s7,56(sp)
    80200640:	f862                	sd	s8,48(sp)
    80200642:	f06a                	sd	s10,32(sp)
    80200644:	fc86                	sd	ra,120(sp)
    80200646:	f8a2                	sd	s0,112(sp)
    80200648:	ecce                	sd	s3,88(sp)
    8020064a:	f466                	sd	s9,40(sp)
    8020064c:	ec6e                	sd	s11,24(sp)
    8020064e:	892a                	mv	s2,a0
    80200650:	84ae                	mv	s1,a1
    80200652:	8d32                	mv	s10,a2
    80200654:	8ab6                	mv	s5,a3
            putch(ch, putdat);
        }

        // Process a %-escape sequence
        char padc = ' ';
        width = precision = -1;
    80200656:	5b7d                	li	s6,-1
        lflag = altflag = 0;

    reswitch:
        switch (ch = *(unsigned char *)fmt ++) {
    80200658:	00001a17          	auipc	s4,0x1
    8020065c:	95ca0a13          	addi	s4,s4,-1700 # 80200fb4 <etext+0x5be>
                for (width -= strnlen(p, precision); width > 0; width --) {
                    putch(padc, putdat);
                }
            }
            for (; (ch = *p ++) != '\0' && (precision < 0 || -- precision >= 0); width --) {
                if (altflag && (ch < ' ' || ch > '~')) {
    80200660:	05e00b93          	li	s7,94
            if (err > MAXERROR || (p = error_string[err]) == NULL) {
    80200664:	00001c17          	auipc	s8,0x1
    80200668:	aacc0c13          	addi	s8,s8,-1364 # 80201110 <error_string>
        while ((ch = *(unsigned char *)fmt ++) != '%') {
    8020066c:	000d4503          	lbu	a0,0(s10)
    80200670:	02500793          	li	a5,37
    80200674:	001d0413          	addi	s0,s10,1
    80200678:	00f50e63          	beq	a0,a5,80200694 <vprintfmt+0x62>
            if (ch == '\0') {
    8020067c:	c521                	beqz	a0,802006c4 <vprintfmt+0x92>
        while ((ch = *(unsigned char *)fmt ++) != '%') {
    8020067e:	02500993          	li	s3,37
    80200682:	a011                	j	80200686 <vprintfmt+0x54>
            if (ch == '\0') {
    80200684:	c121                	beqz	a0,802006c4 <vprintfmt+0x92>
            putch(ch, putdat);
    80200686:	85a6                	mv	a1,s1
        while ((ch = *(unsigned char *)fmt ++) != '%') {
    80200688:	0405                	addi	s0,s0,1
            putch(ch, putdat);
    8020068a:	9902                	jalr	s2
        while ((ch = *(unsigned char *)fmt ++) != '%') {
    8020068c:	fff44503          	lbu	a0,-1(s0)
    80200690:	ff351ae3          	bne	a0,s3,80200684 <vprintfmt+0x52>
    80200694:	00044603          	lbu	a2,0(s0)
        char padc = ' ';
    80200698:	02000793          	li	a5,32
        lflag = altflag = 0;
    8020069c:	4981                	li	s3,0
    8020069e:	4801                	li	a6,0
        width = precision = -1;
    802006a0:	5cfd                	li	s9,-1
    802006a2:	5dfd                	li	s11,-1
        switch (ch = *(unsigned char *)fmt ++) {
    802006a4:	05500593          	li	a1,85
                if (ch < '0' || ch > '9') {
    802006a8:	4525                	li	a0,9
        switch (ch = *(unsigned char *)fmt ++) {
    802006aa:	fdd6069b          	addiw	a3,a2,-35
    802006ae:	0ff6f693          	andi	a3,a3,255
    802006b2:	00140d13          	addi	s10,s0,1
    802006b6:	20d5e563          	bltu	a1,a3,802008c0 <vprintfmt+0x28e>
    802006ba:	068a                	slli	a3,a3,0x2
    802006bc:	96d2                	add	a3,a3,s4
    802006be:	4294                	lw	a3,0(a3)
    802006c0:	96d2                	add	a3,a3,s4
    802006c2:	8682                	jr	a3
            for (fmt --; fmt[-1] != '%'; fmt --)
                /* do nothing */;
            break;
        }
    }
}
    802006c4:	70e6                	ld	ra,120(sp)
    802006c6:	7446                	ld	s0,112(sp)
    802006c8:	74a6                	ld	s1,104(sp)
    802006ca:	7906                	ld	s2,96(sp)
    802006cc:	69e6                	ld	s3,88(sp)
    802006ce:	6a46                	ld	s4,80(sp)
    802006d0:	6aa6                	ld	s5,72(sp)
    802006d2:	6b06                	ld	s6,64(sp)
    802006d4:	7be2                	ld	s7,56(sp)
    802006d6:	7c42                	ld	s8,48(sp)
    802006d8:	7ca2                	ld	s9,40(sp)
    802006da:	7d02                	ld	s10,32(sp)
    802006dc:	6de2                	ld	s11,24(sp)
    802006de:	6109                	addi	sp,sp,128
    802006e0:	8082                	ret
    if (lflag >= 2) {
    802006e2:	4705                	li	a4,1
    802006e4:	008a8593          	addi	a1,s5,8
    802006e8:	01074463          	blt	a4,a6,802006f0 <vprintfmt+0xbe>
    else if (lflag) {
    802006ec:	26080363          	beqz	a6,80200952 <vprintfmt+0x320>
        return va_arg(*ap, unsigned long);
    802006f0:	000ab603          	ld	a2,0(s5)
    802006f4:	46c1                	li	a3,16
    802006f6:	8aae                	mv	s5,a1
    802006f8:	a06d                	j	802007a2 <vprintfmt+0x170>
            goto reswitch;
    802006fa:	00144603          	lbu	a2,1(s0)
            altflag = 1;
    802006fe:	4985                	li	s3,1
        switch (ch = *(unsigned char *)fmt ++) {
    80200700:	846a                	mv	s0,s10
            goto reswitch;
    80200702:	b765                	j	802006aa <vprintfmt+0x78>
            putch(va_arg(ap, int), putdat);
    80200704:	000aa503          	lw	a0,0(s5)
    80200708:	85a6                	mv	a1,s1
    8020070a:	0aa1                	addi	s5,s5,8
    8020070c:	9902                	jalr	s2
            break;
    8020070e:	bfb9                	j	8020066c <vprintfmt+0x3a>
    if (lflag >= 2) {
    80200710:	4705                	li	a4,1
    80200712:	008a8993          	addi	s3,s5,8
    80200716:	01074463          	blt	a4,a6,8020071e <vprintfmt+0xec>
    else if (lflag) {
    8020071a:	22080463          	beqz	a6,80200942 <vprintfmt+0x310>
        return va_arg(*ap, long);
    8020071e:	000ab403          	ld	s0,0(s5)
            if ((long long)num < 0) {
    80200722:	24044463          	bltz	s0,8020096a <vprintfmt+0x338>
            num = getint(&ap, lflag);
    80200726:	8622                	mv	a2,s0
    80200728:	8ace                	mv	s5,s3
    8020072a:	46a9                	li	a3,10
    8020072c:	a89d                	j	802007a2 <vprintfmt+0x170>
            err = va_arg(ap, int);
    8020072e:	000aa783          	lw	a5,0(s5)
            if (err > MAXERROR || (p = error_string[err]) == NULL) {
    80200732:	4719                	li	a4,6
            err = va_arg(ap, int);
    80200734:	0aa1                	addi	s5,s5,8
            if (err < 0) {
    80200736:	41f7d69b          	sraiw	a3,a5,0x1f
    8020073a:	8fb5                	xor	a5,a5,a3
    8020073c:	40d786bb          	subw	a3,a5,a3
            if (err > MAXERROR || (p = error_string[err]) == NULL) {
    80200740:	1ad74363          	blt	a4,a3,802008e6 <vprintfmt+0x2b4>
    80200744:	00369793          	slli	a5,a3,0x3
    80200748:	97e2                	add	a5,a5,s8
    8020074a:	639c                	ld	a5,0(a5)
    8020074c:	18078d63          	beqz	a5,802008e6 <vprintfmt+0x2b4>
                printfmt(putch, putdat, "%s", p);
    80200750:	86be                	mv	a3,a5
    80200752:	00001617          	auipc	a2,0x1
    80200756:	aa660613          	addi	a2,a2,-1370 # 802011f8 <error_string+0xe8>
    8020075a:	85a6                	mv	a1,s1
    8020075c:	854a                	mv	a0,s2
    8020075e:	240000ef          	jal	ra,8020099e <printfmt>
    80200762:	b729                	j	8020066c <vprintfmt+0x3a>
            lflag ++;
    80200764:	00144603          	lbu	a2,1(s0)
    80200768:	2805                	addiw	a6,a6,1
        switch (ch = *(unsigned char *)fmt ++) {
    8020076a:	846a                	mv	s0,s10
            goto reswitch;
    8020076c:	bf3d                	j	802006aa <vprintfmt+0x78>
    if (lflag >= 2) {
    8020076e:	4705                	li	a4,1
    80200770:	008a8593          	addi	a1,s5,8
    80200774:	01074463          	blt	a4,a6,8020077c <vprintfmt+0x14a>
    else if (lflag) {
    80200778:	1e080263          	beqz	a6,8020095c <vprintfmt+0x32a>
        return va_arg(*ap, unsigned long);
    8020077c:	000ab603          	ld	a2,0(s5)
    80200780:	46a1                	li	a3,8
    80200782:	8aae                	mv	s5,a1
    80200784:	a839                	j	802007a2 <vprintfmt+0x170>
            putch('0', putdat);
    80200786:	03000513          	li	a0,48
    8020078a:	85a6                	mv	a1,s1
    8020078c:	e03e                	sd	a5,0(sp)
    8020078e:	9902                	jalr	s2
            putch('x', putdat);
    80200790:	85a6                	mv	a1,s1
    80200792:	07800513          	li	a0,120
    80200796:	9902                	jalr	s2
            num = (unsigned long long)va_arg(ap, void *);
    80200798:	0aa1                	addi	s5,s5,8
    8020079a:	ff8ab603          	ld	a2,-8(s5)
            goto number;
    8020079e:	6782                	ld	a5,0(sp)
    802007a0:	46c1                	li	a3,16
            printnum(putch, putdat, num, base, width, padc);
    802007a2:	876e                	mv	a4,s11
    802007a4:	85a6                	mv	a1,s1
    802007a6:	854a                	mv	a0,s2
    802007a8:	e1fff0ef          	jal	ra,802005c6 <printnum>
            break;
    802007ac:	b5c1                	j	8020066c <vprintfmt+0x3a>
            if ((p = va_arg(ap, char *)) == NULL) {
    802007ae:	000ab603          	ld	a2,0(s5)
    802007b2:	0aa1                	addi	s5,s5,8
    802007b4:	1c060663          	beqz	a2,80200980 <vprintfmt+0x34e>
            if (width > 0 && padc != '-') {
    802007b8:	00160413          	addi	s0,a2,1
    802007bc:	17b05c63          	blez	s11,80200934 <vprintfmt+0x302>
    802007c0:	02d00593          	li	a1,45
    802007c4:	14b79263          	bne	a5,a1,80200908 <vprintfmt+0x2d6>
            for (; (ch = *p ++) != '\0' && (precision < 0 || -- precision >= 0); width --) {
    802007c8:	00064783          	lbu	a5,0(a2)
    802007cc:	0007851b          	sext.w	a0,a5
    802007d0:	c905                	beqz	a0,80200800 <vprintfmt+0x1ce>
    802007d2:	000cc563          	bltz	s9,802007dc <vprintfmt+0x1aa>
    802007d6:	3cfd                	addiw	s9,s9,-1
    802007d8:	036c8263          	beq	s9,s6,802007fc <vprintfmt+0x1ca>
                    putch('?', putdat);
    802007dc:	85a6                	mv	a1,s1
                if (altflag && (ch < ' ' || ch > '~')) {
    802007de:	18098463          	beqz	s3,80200966 <vprintfmt+0x334>
    802007e2:	3781                	addiw	a5,a5,-32
    802007e4:	18fbf163          	bleu	a5,s7,80200966 <vprintfmt+0x334>
                    putch('?', putdat);
    802007e8:	03f00513          	li	a0,63
    802007ec:	9902                	jalr	s2
            for (; (ch = *p ++) != '\0' && (precision < 0 || -- precision >= 0); width --) {
    802007ee:	0405                	addi	s0,s0,1
    802007f0:	fff44783          	lbu	a5,-1(s0)
    802007f4:	3dfd                	addiw	s11,s11,-1
    802007f6:	0007851b          	sext.w	a0,a5
    802007fa:	fd61                	bnez	a0,802007d2 <vprintfmt+0x1a0>
            for (; width > 0; width --) {
    802007fc:	e7b058e3          	blez	s11,8020066c <vprintfmt+0x3a>
    80200800:	3dfd                	addiw	s11,s11,-1
                putch(' ', putdat);
    80200802:	85a6                	mv	a1,s1
    80200804:	02000513          	li	a0,32
    80200808:	9902                	jalr	s2
            for (; width > 0; width --) {
    8020080a:	e60d81e3          	beqz	s11,8020066c <vprintfmt+0x3a>
    8020080e:	3dfd                	addiw	s11,s11,-1
                putch(' ', putdat);
    80200810:	85a6                	mv	a1,s1
    80200812:	02000513          	li	a0,32
    80200816:	9902                	jalr	s2
            for (; width > 0; width --) {
    80200818:	fe0d94e3          	bnez	s11,80200800 <vprintfmt+0x1ce>
    8020081c:	bd81                	j	8020066c <vprintfmt+0x3a>
    if (lflag >= 2) {
    8020081e:	4705                	li	a4,1
    80200820:	008a8593          	addi	a1,s5,8
    80200824:	01074463          	blt	a4,a6,8020082c <vprintfmt+0x1fa>
    else if (lflag) {
    80200828:	12080063          	beqz	a6,80200948 <vprintfmt+0x316>
        return va_arg(*ap, unsigned long);
    8020082c:	000ab603          	ld	a2,0(s5)
    80200830:	46a9                	li	a3,10
    80200832:	8aae                	mv	s5,a1
    80200834:	b7bd                	j	802007a2 <vprintfmt+0x170>
    80200836:	00144603          	lbu	a2,1(s0)
            padc = '-';
    8020083a:	02d00793          	li	a5,45
        switch (ch = *(unsigned char *)fmt ++) {
    8020083e:	846a                	mv	s0,s10
    80200840:	b5ad                	j	802006aa <vprintfmt+0x78>
            putch(ch, putdat);
    80200842:	85a6                	mv	a1,s1
    80200844:	02500513          	li	a0,37
    80200848:	9902                	jalr	s2
            break;
    8020084a:	b50d                	j	8020066c <vprintfmt+0x3a>
            precision = va_arg(ap, int);
    8020084c:	000aac83          	lw	s9,0(s5)
            goto process_precision;
    80200850:	00144603          	lbu	a2,1(s0)
            precision = va_arg(ap, int);
    80200854:	0aa1                	addi	s5,s5,8
        switch (ch = *(unsigned char *)fmt ++) {
    80200856:	846a                	mv	s0,s10
            if (width < 0)
    80200858:	e40dd9e3          	bgez	s11,802006aa <vprintfmt+0x78>
                width = precision, precision = -1;
    8020085c:	8de6                	mv	s11,s9
    8020085e:	5cfd                	li	s9,-1
    80200860:	b5a9                	j	802006aa <vprintfmt+0x78>
            goto reswitch;
    80200862:	00144603          	lbu	a2,1(s0)
            padc = '0';
    80200866:	03000793          	li	a5,48
        switch (ch = *(unsigned char *)fmt ++) {
    8020086a:	846a                	mv	s0,s10
            goto reswitch;
    8020086c:	bd3d                	j	802006aa <vprintfmt+0x78>
                precision = precision * 10 + ch - '0';
    8020086e:	fd060c9b          	addiw	s9,a2,-48
                ch = *fmt;
    80200872:	00144603          	lbu	a2,1(s0)
        switch (ch = *(unsigned char *)fmt ++) {
    80200876:	846a                	mv	s0,s10
                if (ch < '0' || ch > '9') {
    80200878:	fd06069b          	addiw	a3,a2,-48
                ch = *fmt;
    8020087c:	0006089b          	sext.w	a7,a2
                if (ch < '0' || ch > '9') {
    80200880:	fcd56ce3          	bltu	a0,a3,80200858 <vprintfmt+0x226>
            for (precision = 0; ; ++ fmt) {
    80200884:	0405                	addi	s0,s0,1
                precision = precision * 10 + ch - '0';
    80200886:	002c969b          	slliw	a3,s9,0x2
                ch = *fmt;
    8020088a:	00044603          	lbu	a2,0(s0)
                precision = precision * 10 + ch - '0';
    8020088e:	0196873b          	addw	a4,a3,s9
    80200892:	0017171b          	slliw	a4,a4,0x1
    80200896:	0117073b          	addw	a4,a4,a7
                if (ch < '0' || ch > '9') {
    8020089a:	fd06069b          	addiw	a3,a2,-48
                precision = precision * 10 + ch - '0';
    8020089e:	fd070c9b          	addiw	s9,a4,-48
                ch = *fmt;
    802008a2:	0006089b          	sext.w	a7,a2
                if (ch < '0' || ch > '9') {
    802008a6:	fcd57fe3          	bleu	a3,a0,80200884 <vprintfmt+0x252>
    802008aa:	b77d                	j	80200858 <vprintfmt+0x226>
            if (width < 0)
    802008ac:	fffdc693          	not	a3,s11
    802008b0:	96fd                	srai	a3,a3,0x3f
    802008b2:	00ddfdb3          	and	s11,s11,a3
    802008b6:	00144603          	lbu	a2,1(s0)
    802008ba:	2d81                	sext.w	s11,s11
        switch (ch = *(unsigned char *)fmt ++) {
    802008bc:	846a                	mv	s0,s10
    802008be:	b3f5                	j	802006aa <vprintfmt+0x78>
            putch('%', putdat);
    802008c0:	85a6                	mv	a1,s1
    802008c2:	02500513          	li	a0,37
    802008c6:	9902                	jalr	s2
            for (fmt --; fmt[-1] != '%'; fmt --)
    802008c8:	fff44703          	lbu	a4,-1(s0)
    802008cc:	02500793          	li	a5,37
    802008d0:	8d22                	mv	s10,s0
    802008d2:	d8f70de3          	beq	a4,a5,8020066c <vprintfmt+0x3a>
    802008d6:	02500713          	li	a4,37
    802008da:	1d7d                	addi	s10,s10,-1
    802008dc:	fffd4783          	lbu	a5,-1(s10)
    802008e0:	fee79de3          	bne	a5,a4,802008da <vprintfmt+0x2a8>
    802008e4:	b361                	j	8020066c <vprintfmt+0x3a>
                printfmt(putch, putdat, "error %d", err);
    802008e6:	00001617          	auipc	a2,0x1
    802008ea:	90260613          	addi	a2,a2,-1790 # 802011e8 <error_string+0xd8>
    802008ee:	85a6                	mv	a1,s1
    802008f0:	854a                	mv	a0,s2
    802008f2:	0ac000ef          	jal	ra,8020099e <printfmt>
    802008f6:	bb9d                	j	8020066c <vprintfmt+0x3a>
                p = "(null)";
    802008f8:	00001617          	auipc	a2,0x1
    802008fc:	8e860613          	addi	a2,a2,-1816 # 802011e0 <error_string+0xd0>
            if (width > 0 && padc != '-') {
    80200900:	00001417          	auipc	s0,0x1
    80200904:	8e140413          	addi	s0,s0,-1823 # 802011e1 <error_string+0xd1>
                for (width -= strnlen(p, precision); width > 0; width --) {
    80200908:	8532                	mv	a0,a2
    8020090a:	85e6                	mv	a1,s9
    8020090c:	e032                	sd	a2,0(sp)
    8020090e:	e43e                	sd	a5,8(sp)
    80200910:	c7fff0ef          	jal	ra,8020058e <strnlen>
    80200914:	40ad8dbb          	subw	s11,s11,a0
    80200918:	6602                	ld	a2,0(sp)
    8020091a:	01b05d63          	blez	s11,80200934 <vprintfmt+0x302>
    8020091e:	67a2                	ld	a5,8(sp)
    80200920:	2781                	sext.w	a5,a5
    80200922:	e43e                	sd	a5,8(sp)
                    putch(padc, putdat);
    80200924:	6522                	ld	a0,8(sp)
    80200926:	85a6                	mv	a1,s1
    80200928:	e032                	sd	a2,0(sp)
                for (width -= strnlen(p, precision); width > 0; width --) {
    8020092a:	3dfd                	addiw	s11,s11,-1
                    putch(padc, putdat);
    8020092c:	9902                	jalr	s2
                for (width -= strnlen(p, precision); width > 0; width --) {
    8020092e:	6602                	ld	a2,0(sp)
    80200930:	fe0d9ae3          	bnez	s11,80200924 <vprintfmt+0x2f2>
            for (; (ch = *p ++) != '\0' && (precision < 0 || -- precision >= 0); width --) {
    80200934:	00064783          	lbu	a5,0(a2)
    80200938:	0007851b          	sext.w	a0,a5
    8020093c:	e8051be3          	bnez	a0,802007d2 <vprintfmt+0x1a0>
    80200940:	b335                	j	8020066c <vprintfmt+0x3a>
        return va_arg(*ap, int);
    80200942:	000aa403          	lw	s0,0(s5)
    80200946:	bbf1                	j	80200722 <vprintfmt+0xf0>
        return va_arg(*ap, unsigned int);
    80200948:	000ae603          	lwu	a2,0(s5)
    8020094c:	46a9                	li	a3,10
    8020094e:	8aae                	mv	s5,a1
    80200950:	bd89                	j	802007a2 <vprintfmt+0x170>
    80200952:	000ae603          	lwu	a2,0(s5)
    80200956:	46c1                	li	a3,16
    80200958:	8aae                	mv	s5,a1
    8020095a:	b5a1                	j	802007a2 <vprintfmt+0x170>
    8020095c:	000ae603          	lwu	a2,0(s5)
    80200960:	46a1                	li	a3,8
    80200962:	8aae                	mv	s5,a1
    80200964:	bd3d                	j	802007a2 <vprintfmt+0x170>
                    putch(ch, putdat);
    80200966:	9902                	jalr	s2
    80200968:	b559                	j	802007ee <vprintfmt+0x1bc>
                putch('-', putdat);
    8020096a:	85a6                	mv	a1,s1
    8020096c:	02d00513          	li	a0,45
    80200970:	e03e                	sd	a5,0(sp)
    80200972:	9902                	jalr	s2
                num = -(long long)num;
    80200974:	8ace                	mv	s5,s3
    80200976:	40800633          	neg	a2,s0
    8020097a:	46a9                	li	a3,10
    8020097c:	6782                	ld	a5,0(sp)
    8020097e:	b515                	j	802007a2 <vprintfmt+0x170>
            if (width > 0 && padc != '-') {
    80200980:	01b05663          	blez	s11,8020098c <vprintfmt+0x35a>
    80200984:	02d00693          	li	a3,45
    80200988:	f6d798e3          	bne	a5,a3,802008f8 <vprintfmt+0x2c6>
    8020098c:	00001417          	auipc	s0,0x1
    80200990:	85540413          	addi	s0,s0,-1963 # 802011e1 <error_string+0xd1>
            for (; (ch = *p ++) != '\0' && (precision < 0 || -- precision >= 0); width --) {
    80200994:	02800513          	li	a0,40
    80200998:	02800793          	li	a5,40
    8020099c:	bd1d                	j	802007d2 <vprintfmt+0x1a0>

000000008020099e <printfmt>:
printfmt(void (*putch)(int, void*), void *putdat, const char *fmt, ...) {
    8020099e:	715d                	addi	sp,sp,-80
    va_start(ap, fmt);
    802009a0:	02810313          	addi	t1,sp,40
printfmt(void (*putch)(int, void*), void *putdat, const char *fmt, ...) {
    802009a4:	f436                	sd	a3,40(sp)
    vprintfmt(putch, putdat, fmt, ap);
    802009a6:	869a                	mv	a3,t1
printfmt(void (*putch)(int, void*), void *putdat, const char *fmt, ...) {
    802009a8:	ec06                	sd	ra,24(sp)
    802009aa:	f83a                	sd	a4,48(sp)
    802009ac:	fc3e                	sd	a5,56(sp)
    802009ae:	e0c2                	sd	a6,64(sp)
    802009b0:	e4c6                	sd	a7,72(sp)
    va_start(ap, fmt);
    802009b2:	e41a                	sd	t1,8(sp)
    vprintfmt(putch, putdat, fmt, ap);
    802009b4:	c7fff0ef          	jal	ra,80200632 <vprintfmt>
}
    802009b8:	60e2                	ld	ra,24(sp)
    802009ba:	6161                	addi	sp,sp,80
    802009bc:	8082                	ret

00000000802009be <sbi_console_putchar>:

int sbi_console_getchar(void) {
    return sbi_call(SBI_CONSOLE_GETCHAR, 0, 0, 0);
}
void sbi_console_putchar(unsigned char ch) {
    sbi_call(SBI_CONSOLE_PUTCHAR, ch, 0, 0);
    802009be:	00003797          	auipc	a5,0x3
    802009c2:	64278793          	addi	a5,a5,1602 # 80204000 <bootstacktop>
    __asm__ volatile (
    802009c6:	6398                	ld	a4,0(a5)
    802009c8:	4781                	li	a5,0
    802009ca:	88ba                	mv	a7,a4
    802009cc:	852a                	mv	a0,a0
    802009ce:	85be                	mv	a1,a5
    802009d0:	863e                	mv	a2,a5
    802009d2:	00000073          	ecall
    802009d6:	87aa                	mv	a5,a0
}
    802009d8:	8082                	ret

00000000802009da <sbi_shutdown>:
}


void sbi_shutdown(void)
{
    sbi_call(SBI_SHUTDOWN,0,0,0);
    802009da:	00003797          	auipc	a5,0x3
    802009de:	62e78793          	addi	a5,a5,1582 # 80204008 <SBI_SHUTDOWN>
    __asm__ volatile (
    802009e2:	6398                	ld	a4,0(a5)
    802009e4:	4781                	li	a5,0
    802009e6:	88ba                	mv	a7,a4
    802009e8:	853e                	mv	a0,a5
    802009ea:	85be                	mv	a1,a5
    802009ec:	863e                	mv	a2,a5
    802009ee:	00000073          	ecall
    802009f2:	87aa                	mv	a5,a0
    802009f4:	8082                	ret
