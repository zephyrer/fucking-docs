all: prog1 prog2 prog3
.PHONY : all #all��������������Ŀ�꣬��αĿ�����ǻᱻִ�У�����������������Ŀ�����ǲ��硾all�����Ŀ����
	     #����������Ŀ��Ĺ������ǻᱻ����(resolve),Ҳ�ʹﵽһ�������ɶ��Ŀ���Ŀ��.

prog1 : prog1.o utils.o
	cc -o prog1 prog1.o utils.o #��Ҫutils.o��prog1.o�����ļ���ͬ����prog1.

prog2 : prog2.o
	cc -o prog2 prog2.o

prog3 : prog3.o sort.o utils.o
	cc -o prog3 prog3.o sort.o utils.o

###########################################################
# ��Ŀ��
bigoutput littleoutput : text.g
	generate text.g -$(subst output,,$@) > $@ #'$'��ʾִ��һ��Makefile�ĺ�����������Ϊsubst,���沿��Ϊ����
					  #
#��������ȼ���:
bigoutput : test.g
	generate text.g -big > bigoutput #ע���������׵ġ�tab��
littleoutput : text.g
	generate text.g -little > littleoutput)
##########################################################
#��̬ģʽ
objects = foo.o bar.o

all : $(objects) #Ŀ���$object�л�ȡ

$(objects) : %.o:%.c #%.o����Ҫ������.o��β��Ŀ�꣬Ҳ����foo.o bar.o��Ҳ������$object���ϵ�ģʽ
		     #����ģʽ%.c��ȡģʽ%.o��%��Ҳ��foo bar����Ϊ�����.c�ĺ�׺����������Ŀ�����foo.c bar.c
$(CC) -c $(CFLAGS) $< -o $@ #$<��$@���Զ�������,$<��ʾ���е�����Ŀ�꼯(��foo.c bar.c), $@���ʾĿ�꼯(��foo.o bar.o)

#��������չ����ȼ���:
foo.o : foo.c
	$(CC) -c $(CFLAGS) foo.c -o foo.o
bar.o : bar.c
	$(CC) -c $(CFLAGS) bar.c -o bar.o

#��̬ģʽ����һ������
files = foo.elc bar.o lose.o

$(filter %.o, $(files)) : %.o : %.c
	$(CC) -c $(CCFLAGS) $< -o $@
$(filter %.elc, $(files)) : %.elc : %.el
	emacs -f batch-byte-compile $<