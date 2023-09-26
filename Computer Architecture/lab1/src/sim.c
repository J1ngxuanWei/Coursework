#include <stdio.h>
#include <string.h>
#include "shell.h"

uint32_t mpc[32];

uint32_t getdec(int start,int end)
{
    uint32_t res=0;
    uint32_t str=1;
    for(int i=end;i>=start;i--)
    {
        res+=mpc[i]*str;
        str*=2;
    }
    return res;
}

void op0()
{
    int rs=getdec(6,10);
    int rt=getdec(11,15);
    int rd=getdec(16,20);
    int sa=getdec(21,25);
    switch (getdec(26,31))
    {
    case 36:
        //AND
        NEXT_STATE.REGS[rd]=CURRENT_STATE.REGS[rs]&CURRENT_STATE.REGS[rt];
        break;
    case 37:
        //OR
        NEXT_STATE.REGS[rd]=CURRENT_STATE.REGS[rs]|CURRENT_STATE.REGS[rt];
        break;
    case 38:
        //XOR
        NEXT_STATE.REGS[rd]=CURRENT_STATE.REGS[rs]^CURRENT_STATE.REGS[rt];
        break;
    case 39:
        //NOR
        NEXT_STATE.REGS[rd]=CURRENT_STATE.REGS[rs]|CURRENT_STATE.REGS[rt];
        NEXT_STATE.REGS[rd]=~NEXT_STATE.REGS[rd];
        break;
    case 0:
        //SLL
        NEXT_STATE.REGS[rd]=CURRENT_STATE.REGS[rt]<<sa;
        break;
    case 2:
        //SRL
        NEXT_STATE.REGS[rd]=CURRENT_STATE.REGS[rt]>>sa;
        break;
    case 3:
        //SRA
        {
        uint32_t hi=CURRENT_STATE.REGS[rt]&0x80000000;
        if(hi==1)
        NEXT_STATE.REGS[rd]=(0xFFFFFFFF<<(32-sa))+(CURRENT_STATE.REGS[rt]>>sa);
        else
        NEXT_STATE.REGS[rd]=CURRENT_STATE.REGS[rt]>>sa;
        break;
        }
    case 4:
        //SLLV
        {
        uint32_t saa=CURRENT_STATE.REGS[rs]&0x1F;
        NEXT_STATE.REGS[rd]=CURRENT_STATE.REGS[rt]<<saa;
        break;
        }
    case 6:
        //SRLV
        {
        uint32_t saa=CURRENT_STATE.REGS[rs]&0x1F;
        NEXT_STATE.REGS[rd]=CURRENT_STATE.REGS[rt]>>saa;
        break;
        }
    case 7:
        //SRAV
        {
        uint32_t saa=CURRENT_STATE.REGS[rs]&0x1F;
        uint32_t hi=CURRENT_STATE.REGS[rt]&0x80000000;
        if(hi==1)
        NEXT_STATE.REGS[rd]=(0xFFFFFFFF<<(32-saa))+(CURRENT_STATE.REGS[rt]>>saa);
        else
        NEXT_STATE.REGS[rd]=CURRENT_STATE.REGS[rt]>>saa;
        break;
        }
    case 16:
        //MFHI
        NEXT_STATE.REGS[rd]=CURRENT_STATE.HI;
        break;
    case 17:
        //MTHI
        NEXT_STATE.HI=CURRENT_STATE.REGS[rs];
        break;
    case 18:
        //MFLO
        NEXT_STATE.REGS[rd]=CURRENT_STATE.LO;
        break;
    case 19:
        //MTLO
        NEXT_STATE.LO=CURRENT_STATE.REGS[rs];
        break;
    case 32:
        //ADD
        {
        uint32_t ans=CURRENT_STATE.REGS[rs]+CURRENT_STATE.REGS[rt];
        if(!(ans<CURRENT_STATE.REGS[rs]||ans<CURRENT_STATE.REGS[rt]))
        NEXT_STATE.REGS[rd]=CURRENT_STATE.REGS[rs]+CURRENT_STATE.REGS[rt];
        break;
        }
    case 33:
        //ADDU
        NEXT_STATE.REGS[rd]=CURRENT_STATE.REGS[rs]+CURRENT_STATE.REGS[rt];
        break;
    case 34:
        //SUB
        if(CURRENT_STATE.REGS[rs]>=CURRENT_STATE.REGS[rt])
        NEXT_STATE.REGS[rd]=CURRENT_STATE.REGS[rs]-CURRENT_STATE.REGS[rt];
        break;
    case 35:
        //SUBU
        NEXT_STATE.REGS[rd]=CURRENT_STATE.REGS[rs]-CURRENT_STATE.REGS[rt];
        break;
    case 42:
        //SLT
        {
        int rrs=CURRENT_STATE.REGS[rs];
        int rrt=CURRENT_STATE.REGS[rt];
        if(rrs<rrt)
        NEXT_STATE.REGS[rd]=(uint32_t)1;
        else
        NEXT_STATE.REGS[rd]=(uint32_t)0;
        break;
        }
    case 43:
        //SLTU
        {
        if(CURRENT_STATE.REGS[rs]<CURRENT_STATE.REGS[rt])
        NEXT_STATE.REGS[rd]=(uint32_t)1;
        else
        NEXT_STATE.REGS[rd]=(uint32_t)0;
        break;
        }
    case 24:
        //MULT
        {
        int rrs=CURRENT_STATE.REGS[rs];
        int rrt=CURRENT_STATE.REGS[rt];
        long long ans=rrs*rrt;
        uint64_t uans=ans;
        uint32_t anshigh=(uans&0xFFFFFFFF00000000)>>32;
        uint64_t myt=0xFFFFFFFF;
        uint32_t anslow=uans&myt;
        NEXT_STATE.HI=anshigh;
        NEXT_STATE.LO=anslow;
        break;
        }
    case 25:
        //MULTU
        {
        uint64_t ans=CURRENT_STATE.REGS[rs]*CURRENT_STATE.REGS[rt];
        uint32_t anshigh=(ans&0xFFFFFFFF00000000)>>32;
        uint64_t myt=0xFFFFFFFF;
        uint32_t anslow=ans&myt;
        NEXT_STATE.HI=anshigh;
        NEXT_STATE.LO=anslow;
        break;
        }
    case 26:
        //DIV
        {
        int rrs=CURRENT_STATE.REGS[rs];
        int rrt=CURRENT_STATE.REGS[rt];
        int ans=rrs/rrt;
        int aans=rrs%rrt;
        uint32_t uans=ans;
        uint32_t uaans=aans;
        NEXT_STATE.HI=uaans;
        NEXT_STATE.LO=uans;
        break;
        }
    case 27:
        //DIVU
        {
        uint32_t uans=CURRENT_STATE.REGS[rs]/CURRENT_STATE.REGS[rt];
        uint32_t uaans=CURRENT_STATE.REGS[rs]%CURRENT_STATE.REGS[rt];
        NEXT_STATE.HI=uaans;
        NEXT_STATE.LO=uans;
        break;
        }
    case 8:
        //JR
        NEXT_STATE.PC=CURRENT_STATE.REGS[rs];
        break;
    case 9:
        //JALR
        NEXT_STATE.PC=CURRENT_STATE.REGS[rs];
        NEXT_STATE.REGS[rd]=CURRENT_STATE.PC+4;
        break;
    case 12:
        //SYSCALL
        if(CURRENT_STATE.REGS[2]==10)RUN_BIT=0;
        break;
    default:
        break;
    }
}

void op1()
{
    int rs=getdec(6,10);
    uint32_t off=getdec(16,31);
    off=off<<2;
    if(mpc[16]==1)
    off+=0xFFFC0000;
    switch (getdec(11,15))
    {
    case 0:
        //BLTZ
        {
        int rrs=CURRENT_STATE.REGS[rs];
        if(rrs<0)
        NEXT_STATE.PC=CURRENT_STATE.PC+off+4;
        break;
        }
    case 1:
        //BGEZ
        {
        int rrs=CURRENT_STATE.REGS[rs];
        if(rrs>=0)
        NEXT_STATE.PC=CURRENT_STATE.PC+off+4;
        break;
        }
    case 16:
        //BLTZAL
        {
        int rrs=CURRENT_STATE.REGS[rs];
        if(rrs<0)
        {
            NEXT_STATE.PC=CURRENT_STATE.PC+off+4;
            NEXT_STATE.REGS[31]=CURRENT_STATE.PC+4;
        }
        break;
        }
    case 17:
        //BGEZAL
        {
        int rrs=CURRENT_STATE.REGS[rs];
        if(rrs>=0)
        {
            NEXT_STATE.PC=CURRENT_STATE.PC+off+4;
            NEXT_STATE.REGS[31]=CURRENT_STATE.PC+4;
        }
        break;
        }
    default:
        break;
    }
}

void op2()
{
    //J
    uint32_t instr=getdec(6,31);
    instr=instr<<2;
    uint32_t npc=CURRENT_STATE.PC+4;
    uint32_t unpc=npc&0xF0000000;
    uint32_t instr_index=instr+unpc;
    NEXT_STATE.PC=instr_index;
}

void op3()
{
    //JAL
    uint32_t instr=getdec(6,31);
    instr=instr<<2;
    uint32_t npc=CURRENT_STATE.PC+4;
    uint32_t unpc=npc&0xF0000000;
    uint32_t instr_index=instr+unpc;
    NEXT_STATE.PC=instr_index;
    NEXT_STATE.REGS[31]=CURRENT_STATE.PC+4;
}

void op4()
{
    //BEQ
    int rs=getdec(6,10);
    int rt=getdec(11,15);
    uint32_t off=getdec(16,31);
    off=off<<2;
    if(mpc[16]==1)
    off+=0xFFFC0000;
    if(CURRENT_STATE.REGS[rs]==CURRENT_STATE.REGS[rt])
    NEXT_STATE.PC=CURRENT_STATE.PC+off+4;
}

void op5()
{
    //BNE
    int rs=getdec(6,10);
    int rt=getdec(11,15);
    uint32_t off=getdec(16,31);
    off=off<<2;
    if(mpc[16]==1)
    off+=0xFFFC0000;
    if(CURRENT_STATE.REGS[rs]!=CURRENT_STATE.REGS[rt])
    NEXT_STATE.PC=CURRENT_STATE.PC+off+4;
}

void op6()
{
    //BLEZ
    int rs=getdec(6,10);
    uint32_t off=getdec(16,31);
    off=off<<2;
    if(mpc[16]==1)
    off+=0xFFFC0000;
    int rrs=CURRENT_STATE.REGS[rs];
    if(CURRENT_STATE.REGS[rs]==0x0||rrs<0)
    NEXT_STATE.PC=CURRENT_STATE.PC+off+4;
}

void op7()
{
    //BGTZ
    int rs=getdec(6,10);
    uint32_t off=getdec(16,31);
    off=off<<2;
    if(mpc[16]==1)
    off+=0xFFFC0000;
    int rrs=CURRENT_STATE.REGS[rs];
    if(rrs>0)
    NEXT_STATE.PC=CURRENT_STATE.PC+off+4;
}

void op8()
{
    //ADDI
    int rs=getdec(6,10);
    int rt=getdec(11,15);
    uint32_t imm=getdec(16,31);
    if(mpc[16]==1)
    imm+=0xFFFF0000;  
    uint32_t ans=CURRENT_STATE.REGS[rs]+imm;
    if(!(ans<CURRENT_STATE.REGS[rs]||ans<imm))
    NEXT_STATE.REGS[rt]=CURRENT_STATE.REGS[rs]+imm;
}

void op9()
{
    //ADDIU
    int rs=getdec(6,10);
    int rt=getdec(11,15);
    uint32_t imm=getdec(16,31);
    if(mpc[16]==1)
    imm+=0xFFFF0000;
    NEXT_STATE.REGS[rt]=CURRENT_STATE.REGS[rs]+imm;
}

void op10()
{
    //SLTI
    int rs=getdec(6,10);
    int rt=getdec(11,15);
    uint32_t imm=getdec(16,31);
    if(mpc[16]==1)
    imm+=0xFFFF0000;
    int rrs=CURRENT_STATE.REGS[rs];
    int rimm=imm;
    if(rrs<rimm)
    NEXT_STATE.REGS[rt]=(uint32_t)1;
    else
    NEXT_STATE.REGS[rt]=(uint32_t)0;
}

void op11()
{
    //SLTIU
    int rs=getdec(6,10);
    int rt=getdec(11,15);
    uint32_t imm=getdec(16,31);
    if(mpc[16]==1)
    imm+=0xFFFF0000;
    if(CURRENT_STATE.REGS[rs]<imm)
    NEXT_STATE.REGS[rt]=(uint32_t)1;
    else
    NEXT_STATE.REGS[rt]=(uint32_t)0;
}

void op12()
{
    //ANDI
    int rs=getdec(6,10);
    int rt=getdec(11,15);
    uint32_t imm=getdec(16,31);
    uint32_t high=CURRENT_STATE.REGS[rs]&0xFFFF0000;
    uint32_t low=CURRENT_STATE.REGS[rs]&0xFFFF;
    uint32_t ans=low&imm;
    NEXT_STATE.REGS[rt]=high+ans;
}

void op13()
{
    //ORI
    int rs=getdec(6,10);
    int rt=getdec(11,15);
    uint32_t imm=getdec(16,31);
    uint32_t high=CURRENT_STATE.REGS[rs]&0xFFFF0000;
    uint32_t low=CURRENT_STATE.REGS[rs]&0xFFFF;
    uint32_t ans=low|imm;
    NEXT_STATE.REGS[rt]=high+ans;
}

void op14()
{
    //XORI
    int rs=getdec(6,10);
    int rt=getdec(11,15);
    uint32_t imm=getdec(16,31);
    uint32_t high=CURRENT_STATE.REGS[rs]&0xFFFF0000;
    uint32_t low=CURRENT_STATE.REGS[rs]&0xFFFF;
    uint32_t ans=low^imm;
    NEXT_STATE.REGS[rt]=high+ans;
}

void op15()
{
    //LUI
    int rt=getdec(11,15);
    uint32_t imm=getdec(16,31);
    imm=imm<<16;
    NEXT_STATE.REGS[rt]=imm;
}

void op32()
{
    //LB
    int base=getdec(6,10);
    int rt=getdec(11,15);
    uint32_t off=getdec(16,31);
    if(mpc[16]==1)
    off+=0xFFFF0000;
    uint32_t add=CURRENT_STATE.REGS[base]+off;
    uint32_t mem=mem_read_32(add);
    uint32_t data=mem&0xFF;
    if(data>=128)
    data+=0xFFFFFF00;
    NEXT_STATE.REGS[rt]=data;
}

void op33()
{
    //LH
    int base=getdec(6,10);
    int rt=getdec(11,15);
    uint32_t off=getdec(16,31);
    if(mpc[16]==1)
    off+=0xFFFF0000;
    uint32_t add=CURRENT_STATE.REGS[base]+off;
    uint32_t mem=mem_read_32(add);
    uint32_t data=mem&0xFFFF;
    if(data>=0x8000)
    data+=0xFFFF0000;
    NEXT_STATE.REGS[rt]=data;
}

void op35()
{
    //LW
    int base=getdec(6,10);
    int rt=getdec(11,15);
    uint32_t off=getdec(16,31);
    if(mpc[16]==1)
    off+=0xFFFF0000;
    NEXT_STATE.REGS[rt]=mem_read_32(CURRENT_STATE.REGS[base]+off);
}

void op36()
{
    //LBU
    int base=getdec(6,10);
    int rt=getdec(11,15);
    uint32_t off=getdec(16,31);
    if(mpc[16]==1)
    off+=0xFFFF0000;
    uint32_t add=CURRENT_STATE.REGS[base]+off;
    uint32_t mem=mem_read_32(add);
    uint32_t data=mem&0xFF;
    NEXT_STATE.REGS[rt]=data;
}

void op37()
{
    //LHU
    int base=getdec(6,10);
    int rt=getdec(11,15);
    uint32_t off=getdec(16,31);
    if(mpc[16]==1)
    off+=0xFFFF0000;
    uint32_t add=CURRENT_STATE.REGS[base]+off;
    uint32_t mem=mem_read_32(add);
    uint32_t data=mem&0xFFFF;
    NEXT_STATE.REGS[rt]=data;
}

void op40()
{
    //SB
    int base=getdec(6,10);
    int rt=getdec(11,15);
    uint32_t off=getdec(16,31);
    if(mpc[16]==1)
    off+=0xFFFF0000;
    uint32_t add=CURRENT_STATE.REGS[base]+off;
    uint32_t data=mem_read_32(add);
    data=data&0xFFFFFF00;
    uint32_t mydata=CURRENT_STATE.REGS[rt];
    mydata=mydata&0xFF;
    mydata+=data;
    mem_write_32(add,mydata);
}

void op41()
{
    //SH
    int base=getdec(6,10);
    int rt=getdec(11,15);
    uint32_t off=getdec(16,31);
    if(mpc[16]==1)
    off+=0xFFFF0000;
    uint32_t add=CURRENT_STATE.REGS[base]+off;
    uint32_t data=mem_read_32(add);
    data=data&0xFFFF0000;
    uint32_t mydata=CURRENT_STATE.REGS[rt];
    mydata=mydata&0xFFFF;
    mydata+=data;
    mem_write_32(add,mydata);
}

void op43()
{
    //SW
    int base=getdec(6,10);
    int rt=getdec(11,15);
    uint32_t off=getdec(16,31);
    if(mpc[16]==1)
    off+=0xFFFF0000;
    uint32_t add=CURRENT_STATE.REGS[base]+off;
    mem_write_32(add,CURRENT_STATE.REGS[rt]);
}

void process_instruction()
{
    /* execute one instruction here. You should use CURRENT_STATE and modify
     * values in NEXT_STATE. You can call mem_read_32() and mem_write_32() to
     * access memory. */
    //获取指令
    uint32_t mypc=mem_read_32(CURRENT_STATE.PC);
    //转换指令为二进制形式
    char *pt = (char*)&mypc;
    for(int i=0;i<32;i++)
    {
        mpc[31-i]=mypc&1;
        mypc/=2;
    }
    //执行指令
    NEXT_STATE=CURRENT_STATE;
    NEXT_STATE.PC+=4;
    switch (getdec(0,5))//按照op进行导向
    {
    case 0:
        op0();
        break;
    case 12:
        op12();
        break;
    case 13:
        op13();
        break;
    case 14:
        op14();
        break;
    case 15:
        op15();
        break;
    case 8:
        op8();
        break;
    case 9:
        op9();
        break;
    case 10:
        op10();
        break;
    case 11:
        op11();
        break;
    case 2:
        op2();
        break;
    case 3:
        op3();
        break;
    case 4:
        op4();
        break;
    case 5:
        op5();
        break;
    case 6:
        op6();
        break;
    case 7:
        op7();
        break;
    case 1:
        op1();
        break;
    case 32:
        op32();
        break;
    case 33:
        op33();
        break;
    case 35:
        op35();
        break;
    case 36:
        op36();
        break;
    case 37:
        op37();
        break;
    case 40:
        op40();
        break;
    case 41:
        op41();
        break;
    case 43:
        op43();
        break;
    default:
        break;
    }
    //指令清0
    memset(mpc,0,sizeof(mpc));
}
