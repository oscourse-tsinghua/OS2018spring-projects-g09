
rot13-64：     文件格式 elf64-littleriscv


Disassembly of section .text:

0000000010010000 <main>:
    10010000:	100107b7          	lui	a5,0x10010
    10010004:	09c7a783          	lw	a5,156(a5) # 1001009c <wait>
    10010008:	2781                	sext.w	a5,a5
    1001000a:	fbfd                	bnez	a5,10010000 <main>
    1001000c:	4681                	li	a3,0
    1001000e:	a00d                	j	10010030 <main+0x30>
    10010010:	f927071b          	addiw	a4,a4,-110
    10010014:	0ff77713          	andi	a4,a4,255
    10010018:	4631                	li	a2,12
    1001001a:	00e66a63          	bltu	a2,a4,1001002e <main+0x2e>
    1001001e:	10010737          	lui	a4,0x10010
    10010022:	07870713          	addi	a4,a4,120 # 10010078 <text>
    10010026:	9736                	add	a4,a4,a3
    10010028:	37cd                	addiw	a5,a5,-13
    1001002a:	00f70023          	sb	a5,0(a4)
    1001002e:	2685                	addiw	a3,a3,1
    10010030:	100107b7          	lui	a5,0x10010
    10010034:	07878793          	addi	a5,a5,120 # 10010078 <text>
    10010038:	97b6                	add	a5,a5,a3
    1001003a:	0007c783          	lbu	a5,0(a5)
    1001003e:	c39d                	beqz	a5,10010064 <main+0x64>
    10010040:	0207e713          	ori	a4,a5,32
    10010044:	f9f7061b          	addiw	a2,a4,-97
    10010048:	0ff67613          	andi	a2,a2,255
    1001004c:	45b1                	li	a1,12
    1001004e:	fcc5e1e3          	bltu	a1,a2,10010010 <main+0x10>
    10010052:	10010737          	lui	a4,0x10010
    10010056:	07870713          	addi	a4,a4,120 # 10010078 <text>
    1001005a:	9736                	add	a4,a4,a3
    1001005c:	27b5                	addiw	a5,a5,13
    1001005e:	00f70023          	sb	a5,0(a4)
    10010062:	b7f1                	j	1001002e <main+0x2e>
    10010064:	100107b7          	lui	a5,0x10010
    10010068:	09c7a783          	lw	a5,156(a5) # 1001009c <wait>
    1001006c:	2781                	sext.w	a5,a5
    1001006e:	dbfd                	beqz	a5,10010064 <main+0x64>
    10010070:	4501                	li	a0,0
    10010072:	8082                	ret

Disassembly of section .data:

0000000010010078 <text>:
    10010078:	6156                	ld	sp,336(sp)
    1001007a:	6766                	ld	a4,88(sp)
    1001007c:	6865                	lui	a6,0x19
    1001007e:	6770                	ld	a2,200(a4)
    10010080:	6276                	ld	tp,344(sp)
    10010082:	2061                	0x2061
    10010084:	7266                	ld	tp,120(sp)
    10010086:	6a206667          	0x6a206667
    1001008a:	616e                	ld	sp,216(sp)
    1001008c:	62672067          	0x62672067
    10010090:	6f20                	ld	s0,88(a4)
    10010092:	2072                	fld	ft0,280(sp)
    10010094:	72726573          	csrrsi	a0,0x727,4
    10010098:	0021                	c.nop	8

Disassembly of section .sdata:

000000001001009c <wait>:
    1001009c:	0001                	nop
	...

Disassembly of section .debug_info:

0000000000000000 <.debug_info>:
   0:	00bc                	addi	a5,sp,72
   2:	0000                	unimp
   4:	0004                	0x4
   6:	0000                	unimp
   8:	0000                	unimp
   a:	0108                	addi	a0,sp,128
   c:	002a                	c.slli	zero,0xa
   e:	0000                	unimp
  10:	000c                	0xc
  12:	0000                	unimp
  14:	6700                	ld	s0,8(a4)
  16:	0000                	unimp
  18:	0000                	unimp
  1a:	0100                	addi	s0,sp,128
  1c:	0010                	0x10
  1e:	0000                	unimp
  20:	7400                	ld	s0,40(s0)
	...
  2a:	0000                	unimp
  2c:	0200                	addi	s0,sp,256
  2e:	0044                	addi	s1,sp,4
  30:	0000                	unimp
  32:	003d                	c.nop	15
  34:	0000                	unimp
  36:	00003d03          	ld	s10,0(zero) # 0 <main-0x10010000>
  3a:	2100                	fld	fs0,0(a0)
  3c:	0400                	addi	s0,sp,512
  3e:	0708                	addi	a0,sp,896
  40:	0008                	0x8
  42:	0000                	unimp
  44:	0104                	addi	s1,sp,128
  46:	6208                	ld	a0,0(a2)
  48:	0000                	unimp
  4a:	0500                	addi	s0,sp,640
  4c:	0020                	addi	s0,sp,8
  4e:	0000                	unimp
  50:	0101                	addi	sp,sp,0
  52:	002d                	c.nop	11
  54:	0000                	unimp
  56:	0309                	addi	t1,t1,2
  58:	0078                	addi	a4,sp,12
  5a:	1001                	c.nop	-32
  5c:	0000                	unimp
  5e:	0000                	unimp
  60:	5d05                	li	s10,-31
  62:	0000                	unimp
  64:	0100                	addi	s0,sp,128
  66:	7c04                	ld	s1,56(s0)
  68:	0000                	unimp
  6a:	0900                	addi	s0,sp,144
  6c:	01009c03          	lh	s8,16(ra)
  70:	0010                	0x10
  72:	0000                	unimp
  74:	0600                	addi	s0,sp,768
  76:	0504                	addi	s1,sp,640
  78:	6e69                	lui	t3,0x1a
  7a:	0074                	addi	a3,sp,12
  7c:	00007507          	0x7507
  80:	0800                	addi	s0,sp,16
  82:	0025                	c.nop	9
  84:	0000                	unimp
  86:	0601                	addi	a2,a2,0
  88:	0075                	c.nop	29
  8a:	0000                	unimp
  8c:	0000                	unimp
  8e:	1001                	c.nop	-32
  90:	0000                	unimp
  92:	0000                	unimp
  94:	0074                	addi	a3,sp,12
  96:	0000                	unimp
  98:	0000                	unimp
  9a:	0000                	unimp
  9c:	9c01                	subw	s0,s0,s0
  9e:	6909                	lui	s2,0x2
  a0:	0100                	addi	s0,sp,128
  a2:	750c                	ld	a1,40(a0)
  a4:	0000                	unimp
  a6:	0100                	addi	s0,sp,128
  a8:	0a5d                	addi	s4,s4,23
  aa:	0000                	unimp
  ac:	0000                	unimp
  ae:	00001a0b          	0x1a0b
  b2:	0100                	addi	s0,sp,128
  b4:	440e                	lw	s0,192(sp)
	...

Disassembly of section .debug_abbrev:

0000000000000000 <.debug_abbrev>:
   0:	1101                	addi	sp,sp,-32
   2:	2501                	sext.w	a0,a0
   4:	130e                	slli	t1,t1,0x23
   6:	1b0e030b          	0x1b0e030b
   a:	110e                	slli	sp,sp,0x23
   c:	1201                	addi	tp,tp,-32
   e:	00171007          	0x171007
  12:	0200                	addi	s0,sp,256
  14:	0101                	addi	sp,sp,0
  16:	1349                	addi	t1,t1,-14
  18:	1301                	addi	t1,t1,-32
  1a:	0000                	unimp
  1c:	49002103          	lw	sp,1168(zero) # 490 <main-0x1000fb70>
  20:	000b2f13          	slti	t5,s6,0
  24:	0400                	addi	s0,sp,512
  26:	0024                	addi	s1,sp,8
  28:	0b3e0b0b          	0xb3e0b0b
  2c:	00000e03          	lb	t3,0(zero) # 0 <main-0x10010000>
  30:	3405                	addiw	s0,s0,-31
  32:	0300                	addi	s0,sp,384
  34:	3a0e                	fld	fs4,224(sp)
  36:	490b3b0b          	0x490b3b0b
  3a:	02193f13          	sltiu	t5,s2,33
  3e:	0018                	0x18
  40:	0600                	addi	s0,sp,768
  42:	0024                	addi	s1,sp,8
  44:	0b3e0b0b          	0xb3e0b0b
  48:	00000803          	lb	a6,0(zero) # 0 <main-0x10010000>
  4c:	49003507          	fld	fa0,1168(zero) # 490 <main-0x1000fb70>
  50:	08000013          	li	zero,128
  54:	012e                	slli	sp,sp,0xb
  56:	0e03193f 0b3b0b3a 	0xb3b0b3a0e03193f
  5e:	1349                	addi	t1,t1,-14
  60:	0111                	addi	sp,sp,4
  62:	0712                	slli	a4,a4,0x4
  64:	1840                	addi	s0,sp,52
  66:	00194297          	auipc	t0,0x194
  6a:	0900                	addi	s0,sp,144
  6c:	0034                	addi	a3,sp,8
  6e:	0b3a0803          	lb	a6,179(s4)
  72:	13490b3b          	0x13490b3b
  76:	1802                	slli	a6,a6,0x20
  78:	0000                	unimp
  7a:	0b0a                	slli	s6,s6,0x2
  7c:	5501                	li	a0,-32
  7e:	0b000017          	auipc	zero,0xb000
  82:	0034                	addi	a3,sp,8
  84:	0b3a0e03          	lb	t3,179(s4)
  88:	13490b3b          	0x13490b3b
  8c:	1702                	slli	a4,a4,0x20
  8e:	0000                	unimp
	...

Disassembly of section .debug_loc:

0000000000000000 <.debug_loc>:
   0:	0010                	0x10
   2:	0000                	unimp
   4:	0000                	unimp
   6:	0000                	unimp
   8:	0014                	0x14
   a:	0000                	unimp
   c:	0000                	unimp
   e:	0000                	unimp
  10:	0001                	nop
  12:	145e                	slli	s0,s0,0x37
  14:	0000                	unimp
  16:	0000                	unimp
  18:	0000                	unimp
  1a:	2a00                	fld	fs0,16(a2)
  1c:	0000                	unimp
  1e:	0000                	unimp
  20:	0000                	unimp
  22:	0600                	addi	s0,sp,768
  24:	7f00                	ld	s0,56(a4)
  26:	0800                	addi	s0,sp,16
  28:	2120                	fld	fs0,64(a0)
  2a:	2a9f 0000 0000      	0x2a9f
  30:	0000                	unimp
  32:	2e00                	fld	fs0,24(a2)
  34:	0000                	unimp
  36:	0000                	unimp
  38:	0000                	unimp
  3a:	1500                	addi	s0,sp,672
  3c:	7d00                	ld	s0,56(a0)
  3e:	0300                	addi	s0,sp,384
  40:	0078                	addi	a4,sp,12
  42:	1001                	c.nop	-32
  44:	0000                	unimp
  46:	0000                	unimp
  48:	9422                	add	s0,s0,s0
  4a:	0801                	addi	a6,a6,0
  4c:	1aff                	0x1aff
  4e:	2008                	fld	fa0,0(s0)
  50:	9f21                	addw	a4,a4,s0
  52:	0044                	addi	s1,sp,4
  54:	0000                	unimp
  56:	0000                	unimp
  58:	0000                	unimp
  5a:	0056                	c.slli	zero,0x15
  5c:	0000                	unimp
  5e:	0000                	unimp
  60:	0000                	unimp
  62:	0001                	nop
  64:	565e                	lw	a2,244(sp)
  66:	0000                	unimp
  68:	0000                	unimp
  6a:	0000                	unimp
  6c:	5e00                	lw	s0,56(a2)
  6e:	0000                	unimp
  70:	0000                	unimp
  72:	0000                	unimp
  74:	0600                	addi	s0,sp,768
  76:	7f00                	ld	s0,56(a4)
  78:	0800                	addi	s0,sp,16
  7a:	2120                	fld	fs0,64(a0)
  7c:	5e9f 0000 0000      	0x5e9f
  82:	0000                	unimp
  84:	6200                	ld	s0,0(a2)
  86:	0000                	unimp
  88:	0000                	unimp
  8a:	0000                	unimp
  8c:	0b00                	addi	s0,sp,400
  8e:	7e00                	ld	s0,56(a2)
  90:	9400                	0x9400
  92:	0801                	addi	a6,a6,0
  94:	1aff                	0x1aff
  96:	2008                	fld	fa0,0(s0)
  98:	9f21                	addw	a4,a4,s0
	...

Disassembly of section .debug_aranges:

0000000000000000 <.debug_aranges>:
   0:	002c                	addi	a1,sp,8
   2:	0000                	unimp
   4:	0002                	c.slli	zero,0x0
   6:	0000                	unimp
   8:	0000                	unimp
   a:	0008                	0x8
   c:	0000                	unimp
   e:	0000                	unimp
  10:	0000                	unimp
  12:	1001                	c.nop	-32
  14:	0000                	unimp
  16:	0000                	unimp
  18:	0074                	addi	a3,sp,12
	...

Disassembly of section .debug_ranges:

0000000000000000 <.debug_ranges>:
   0:	0010                	0x10
   2:	0000                	unimp
   4:	0000                	unimp
   6:	0000                	unimp
   8:	0030                	addi	a2,sp,8
   a:	0000                	unimp
   c:	0000                	unimp
   e:	0000                	unimp
  10:	0040                	addi	s0,sp,4
  12:	0000                	unimp
  14:	0000                	unimp
  16:	0000                	unimp
  18:	0064                	addi	s1,sp,12
	...

Disassembly of section .debug_line:

0000000000000000 <.debug_line>:
   0:	0080                	addi	s0,sp,64
   2:	0000                	unimp
   4:	0002                	c.slli	zero,0x0
   6:	001e                	c.slli	zero,0x7
   8:	0000                	unimp
   a:	0101                	addi	sp,sp,0
   c:	000d0efb          	0xd0efb
  10:	0101                	addi	sp,sp,0
  12:	0101                	addi	sp,sp,0
  14:	0000                	unimp
  16:	0100                	addi	s0,sp,128
  18:	0000                	unimp
  1a:	0001                	nop
  1c:	6f72                	ld	t5,280(sp)
  1e:	3174                	fld	fa3,224(a0)
  20:	00632e33          	slt	t3,t1,t1
  24:	0000                	unimp
  26:	0000                	unimp
  28:	0900                	addi	s0,sp,144
  2a:	0002                	c.slli	zero,0x0
  2c:	0100                	addi	s0,sp,128
  2e:	0010                	0x10
  30:	0000                	unimp
  32:	1800                	addi	s0,sp,48
  34:	0200                	addi	s0,sp,256
  36:	0104                	addi	s1,sp,128
  38:	00090103          	lb	sp,0(s2) # 2000 <main-0x1000e000>
  3c:	0100                	addi	s0,sp,128
  3e:	0c090403          	lb	s0,192(s2)
  42:	0100                	addi	s0,sp,128
  44:	04090503          	lb	a0,64(s2)
  48:	0100                	addi	s0,sp,128
  4a:	0e090103          	lb	sp,224(s2)
  4e:	0100                	addi	s0,sp,128
  50:	10090103          	lb	sp,256(s2)
  54:	0100                	addi	s0,sp,128
  56:	02097a03          	0x2097a03
  5a:	0100                	addi	s0,sp,128
  5c:	10090103          	lb	sp,256(s2)
  60:	0100                	addi	s0,sp,128
  62:	04090103          	lb	sp,64(s2)
  66:	0100                	addi	s0,sp,128
  68:	0e090103          	lb	sp,224(s2)
  6c:	0100                	addi	s0,sp,128
  6e:	0200                	addi	s0,sp,256
  70:	0104                	addi	s1,sp,128
  72:	12090603          	lb	a2,288(s2)
  76:	0100                	addi	s0,sp,128
  78:	0c090203          	lb	tp,192(s2)
  7c:	0100                	addi	s0,sp,128
  7e:	0409                	addi	s0,s0,2
  80:	0000                	unimp
  82:	0101                	addi	sp,sp,0

Disassembly of section .debug_str:

0000000000000000 <.debug_str>:
   0:	6f72                	ld	t5,280(sp)
   2:	3174                	fld	fa3,224(a0)
   4:	00632e33          	slt	t3,t1,t1
   8:	6f6c                	ld	a1,216(a4)
   a:	676e                	ld	a4,216(sp)
   c:	7520                	ld	s0,104(a0)
   e:	736e                	ld	t1,248(sp)
  10:	6769                	lui	a4,0x1a
  12:	656e                	ld	a0,216(sp)
  14:	2064                	fld	fs1,192(s0)
  16:	6e69                	lui	t3,0x1a
  18:	0074                	addi	a3,sp,12
  1a:	6f6c                	ld	a1,216(a4)
  1c:	00726577          	0x726577
  20:	6574                	ld	a3,200(a0)
  22:	7478                	ld	a4,232(s0)
  24:	6d00                	ld	s0,24(a0)
  26:	6961                	lui	s2,0x18
  28:	006e                	c.slli	zero,0x1b
  2a:	20554e47          	fmsub.s	ft8,fa0,ft5,ft4,rmm
  2e:	20313143          	fmadd.s	ft2,ft2,ft3,ft4,rup
  32:	2e322e37          	lui	t3,0x2e322
  36:	2030                	fld	fa2,64(s0)
  38:	6d2d                	lui	s10,0xb
  3a:	7261                	lui	tp,0xffff8
  3c:	723d6863          	bltu	s10,gp,76c <main-0x1000f894>
  40:	3676                	fld	fa2,376(sp)
  42:	6934                	ld	a3,80(a0)
  44:	616d                	addi	sp,sp,240
  46:	6466                	ld	s0,88(sp)
  48:	6d2d2063          	0x6d2d2063
  4c:	6261                	lui	tp,0x18
  4e:	3d69                	addiw	s10,s10,-6
  50:	706c                	ld	a1,224(s0)
  52:	3436                	fld	fs0,360(sp)
  54:	2064                	fld	fs1,192(s0)
  56:	672d                	lui	a4,0xb
  58:	2d20                	fld	fs0,88(a0)
  5a:	7700674f          	fnmadd.q	fa4,ft0,fa6,fa4,unknown
  5e:	6961                	lui	s2,0x18
  60:	0074                	addi	a3,sp,12
  62:	72616863          	bltu	sp,t1,792 <main-0x1000f86e>
  66:	2f00                	fld	fs0,24(a4)
  68:	6f68                	ld	a0,216(a4)
  6a:	656d                	lui	a0,0x1b
  6c:	3779712f          	0x3779712f
  70:	3734                	fld	fa3,104(a4)
  72:	3239                	addiw	tp,tp,-18
  74:	3739                	addiw	a4,a4,-18
  76:	3139                	addiw	sp,sp,-18
  78:	3930672f          	0x3930672f
  7c:	675f 7469 7568      	0x75687469675f
  82:	2f62                	fld	ft10,24(sp)
  84:	3032534f          	fnmadd.s	ft6,ft4,ft3,ft6,unknown
  88:	3831                	addiw	a6,a6,-20
  8a:	69727073          	csrci	0x697,4
  8e:	676e                	ld	a4,216(sp)
  90:	702d                	c.lui	zero,0xfffeb
  92:	6f72                	ld	t5,280(sp)
  94:	656a                	ld	a0,152(sp)
  96:	2d737463          	bleu	s7,t1,35e <main-0x1000fca2>
  9a:	2f393067          	0x2f393067
  9e:	6574                	ld	a3,200(a0)
  a0:	732f7473          	csrrci	s0,0x732,30
  a4:	6970                	ld	a2,208(a0)
  a6:	672d656b          	0x672d656b
  aa:	6264                	ld	s1,192(a2)
  ac:	742d                	lui	s0,0xfffeb
  ae:	7365                	lui	t1,0xffff9
  b0:	0074                	addi	a3,sp,12

Disassembly of section .comment:

0000000000000000 <.comment>:
   0:	3a434347          	fmsub.d	ft6,ft6,ft4,ft7,rmm
   4:	2820                	fld	fs0,80(s0)
   6:	29554e47          	fmsub.s	ft8,fa0,fs5,ft5,rmm
   a:	3720                	fld	fs0,104(a4)
   c:	322e                	fld	ft4,232(sp)
   e:	302e                	fld	ft0,232(sp)
	...

Disassembly of section .debug_frame:

0000000000000000 <.debug_frame>:
   0:	000c                	0xc
   2:	0000                	unimp
   4:	ffff                	0xffff
   6:	ffff                	0xffff
   8:	0001                	nop
   a:	7c01                	lui	s8,0xfffe0
   c:	0d01                	addi	s10,s10,0
   e:	0002                	c.slli	zero,0x0
  10:	0014                	0x14
	...
  1a:	1001                	c.nop	-32
  1c:	0000                	unimp
  1e:	0000                	unimp
  20:	0074                	addi	a3,sp,12
  22:	0000                	unimp
  24:	0000                	unimp
	...
