     lw x3, 0x0(x0)  #��ȡx0�Ĵ�������ֵ����0x0���ڴ��ַ��0x0000���е���ֵ��x3�Ĵ�����
     ori x1, x0,0x1       #x1�Ĵ�����ֵ1����ʼi
     ori x2, x0,0x1       #x2�Ĵ�����ֵ1,����Ϊ1
loop:
     add x4, x4, x1      #x4�Ĵ��������ۼӺ�
     beq x1, x3,finish   # x1=n ��ת
     add x1, x1, x2      #x1=x1+1
     jal x0, loop
finish:
     sw x4, 0x4(x0)
     jal x0,finish
