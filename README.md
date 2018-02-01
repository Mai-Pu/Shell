## shell小功能

### myecho.c
![](https://github.com/Mai-Pu/Shell/raw/master/pic/1.png)

### mycat.c
![](https://github.com/Mai-Pu/Shell/raw/master/pic/2.png)

### mycp.c
![](https://github.com/Mai-Pu/Shell/raw/master/pic/3.png)

### mysys.c
##### 实现函数mysys，用于执行一个系统命令，要求如下
*	mysys的功能与系统函数system相同，要求用进程管理相关系统调用自己实现一遍
*	使用fork/exec/wait系统调用实现mysys
*	不能通过调用系统函数system实现mysys
*	测试程序如下
```ruby
	#include <stdio.h>
	
	int main()
	{
	    printf("++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	    mysys("echo HELLO WORLD");
	    printf("++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	    system("ls /");
	    mysys("++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	    return 0;
	}
```	
*	测试程序的输出结果
*	++++++++++++++++++++++++++++++++++++++++++++++++++
*	HELLO WORLD
*	++++++++++++++++++++++++++++++++++++++++++++++++++
*	bin		core  home	lib	mnt	root	snap	tmp		vmlinuz
*	boot	dev   initrd.img	lost+found	opt	run	srv	usr	vmlinuz.old
*	cdrom	etc   initrd.img.old	media	proc	sbin	sys	var
*	++++++++++++++++++++++++++++++++++++++++++++++++++

### 五.模块分析
##### 1.添加模块
* 系统将提示用户输入新添加的学生的信息，存储在studata.dat文件中
##### 2.显示模块
* （1）显示模块将输出所有学生的信息。
* （2）通过一定格式输出所有学生的信息。
##### 3.修改模块
* 通过用户输入要修改的学生的学号，然后系统提示用户输入新的信息。
##### 4.查找模块
* 通过用户输入要查找的学生姓名或学号，然后系统就输出所查找的学生信息。
##### 5.删除模块
* 首先由用户输入要删除的单个学生学号，删除该名学生的信息。
##### 6.清空模块
* 系统将会把所有学生的信息全部删除，并且将辅助文件数据清空。
##### 7.排列模块：
* 对已有的学生信息按学号从小到大进行排列后存储。
