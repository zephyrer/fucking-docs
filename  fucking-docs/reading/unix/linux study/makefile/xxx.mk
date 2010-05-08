all: prog1 prog2 prog3
.PHONY : all #all依赖于其它三个目标，而伪目标总是会被执行，故其依赖的那三个目标总是不如【all】这个目标新
	     #故其它三个目标的规则总是会被决议(resolve),也就达到一口气生成多个目标的目的.

prog1 : prog1.o utils.o
	cc -o prog1 prog1.o utils.o #需要utils.o和prog1.o两个文件共同生成prog1.

prog2 : prog2.o
	cc -o prog2 prog2.o

prog3 : prog3.o sort.o utils.o
	cc -o prog3 prog3.o sort.o utils.o

###########################################################
# 多目标
bigoutput littleoutput : text.g
	generate text.g -$(subst output,,$@) > $@ #'$'表示执行一个Makefile的函数，函数名为subst,后面部分为参数
					  #
#上述规则等价于:
bigoutput : test.g
	generate text.g -big > bigoutput #注意命令行首的【tab】
littleoutput : text.g
	generate text.g -little > littleoutput)
##########################################################
#静态模式
objects = foo.o bar.o

all : $(objects) #目标从$object中获取

$(objects) : %.o:%.c #%.o表明要所有以.o结尾的目标，也就是foo.o bar.o，也即变量$object集合的模式
		     #依赖模式%.c则取模式%.o的%，也即foo bar，并为其加上.c的后缀，于是依赖目标就是foo.c bar.c
$(CC) -c $(CFLAGS) $< -o $@ #$<和$@是自动化变量,$<表示所有的依赖目标集(即foo.c bar.c), $@则表示目标集(即foo.o bar.o)

#上述规则展开后等价于:
foo.o : foo.c
	$(CC) -c $(CFLAGS) foo.c -o foo.o
bar.o : bar.c
	$(CC) -c $(CFLAGS) bar.c -o bar.o

#静态模式的另一个例子
files = foo.elc bar.o lose.o

$(filter %.o, $(files)) : %.o : %.c
	$(CC) -c $(CCFLAGS) $< -o $@
$(filter %.elc, $(files)) : %.elc : %.el
	emacs -f batch-byte-compile $<