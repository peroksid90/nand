@17
D=A
@SP
A=M
M=D
@SP
M=M+1
@17
D=A
@SP
A=M
M=D
@SP
M=M+1
@SP
M=M-1
A=M
D=M
@SP
M=M-1
A=M
D=M-D
@TRUE0
D;JEQ
@FALSE0
0;JMP
(TRUE0)
@SP
A=M
M=-1
@DONE0
0;JMP
(FALSE0)
@SP
A=M
M=0
(DONE0)
@SP
M=M+1
@17
D=A
@SP
A=M
M=D
@SP
M=M+1
@16
D=A
@SP
A=M
M=D
@SP
M=M+1
@SP
M=M-1
A=M
D=M
@SP
M=M-1
A=M
D=M-D
@TRUE1
D;JEQ
@FALSE1
0;JMP
(TRUE1)
@SP
A=M
M=-1
@DONE1
0;JMP
(FALSE1)
@SP
A=M
M=0
(DONE1)
@SP
M=M+1
@16
D=A
@SP
A=M
M=D
@SP
M=M+1
@17
D=A
@SP
A=M
M=D
@SP
M=M+1
@SP
M=M-1
A=M
D=M
@SP
M=M-1
A=M
D=M-D
@TRUE2
D;JEQ
@FALSE2
0;JMP
(TRUE2)
@SP
A=M
M=-1
@DONE2
0;JMP
(FALSE2)
@SP
A=M
M=0
(DONE2)
@SP
M=M+1
@892
D=A
@SP
A=M
M=D
@SP
M=M+1
@891
D=A
@SP
A=M
M=D
@SP
M=M+1
@SP
M=M-1
A=M
D=M
@SP
M=M-1
A=M
D=M-D
@TRUE3
D;JLT
@FALSE3
0;JMP
(TRUE3)
@SP
A=M
M=-1
@DONE3
0;JMP
(FALSE3)
@SP
A=M
M=0
(DONE3)
@SP
M=M+1
@891
D=A
@SP
A=M
M=D
@SP
M=M+1
@892
D=A
@SP
A=M
M=D
@SP
M=M+1
@SP
M=M-1
A=M
D=M
@SP
M=M-1
A=M
D=M-D
@TRUE4
D;JLT
@FALSE4
0;JMP
(TRUE4)
@SP
A=M
M=-1
@DONE4
0;JMP
(FALSE4)
@SP
A=M
M=0
(DONE4)
@SP
M=M+1
@891
D=A
@SP
A=M
M=D
@SP
M=M+1
@891
D=A
@SP
A=M
M=D
@SP
M=M+1
@SP
M=M-1
A=M
D=M
@SP
M=M-1
A=M
D=M-D
@TRUE5
D;JLT
@FALSE5
0;JMP
(TRUE5)
@SP
A=M
M=-1
@DONE5
0;JMP
(FALSE5)
@SP
A=M
M=0
(DONE5)
@SP
M=M+1
@32767
D=A
@SP
A=M
M=D
@SP
M=M+1
@32766
D=A
@SP
A=M
M=D
@SP
M=M+1
@SP
M=M-1
A=M
D=M
@SP
M=M-1
A=M
D=M-D
@TRUE6
D;JGT
@FALSE6
0;JMP
(TRUE6)
@SP
A=M
M=-1
@DONE6
0;JMP
(FALSE6)
@SP
A=M
M=0
(DONE6)
@SP
M=M+1
@32766
D=A
@SP
A=M
M=D
@SP
M=M+1
@32767
D=A
@SP
A=M
M=D
@SP
M=M+1
@SP
M=M-1
A=M
D=M
@SP
M=M-1
A=M
D=M-D
@TRUE7
D;JGT
@FALSE7
0;JMP
(TRUE7)
@SP
A=M
M=-1
@DONE7
0;JMP
(FALSE7)
@SP
A=M
M=0
(DONE7)
@SP
M=M+1
@32766
D=A
@SP
A=M
M=D
@SP
M=M+1
@32766
D=A
@SP
A=M
M=D
@SP
M=M+1
@SP
M=M-1
A=M
D=M
@SP
M=M-1
A=M
D=M-D
@TRUE8
D;JGT
@FALSE8
0;JMP
(TRUE8)
@SP
A=M
M=-1
@DONE8
0;JMP
(FALSE8)
@SP
A=M
M=0
(DONE8)
@SP
M=M+1
@57
D=A
@SP
A=M
M=D
@SP
M=M+1
@31
D=A
@SP
A=M
M=D
@SP
M=M+1
@53
D=A
@SP
A=M
M=D
@SP
M=M+1
@SP
M=M-1
A=M
D=M
@SP
M=M-1
A=M
M=M+D
@SP
M=M+1
@112
D=A
@SP
A=M
M=D
@SP
M=M+1
@SP
M=M-1
A=M
D=M
@SP
M=M-1
A=M
M=M-D
@SP
M=M+1
@SP
M=M-1
A=M
M=!M
@SP
M=M+1
@SP
M=M-1
A=M
D=M
@SP
M=M-1
A=M
M=M&D
@SP
M=M+1
@82
D=A
@SP
A=M
M=D
@SP
M=M+1
@SP
M=M-1
A=M
D=M
@SP
M=M-1
A=M
M=M|D
@SP
M=M+1
@SP
M=M-1
A=M
M=!M
M=M+1
@SP
M=M+1
