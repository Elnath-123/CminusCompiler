词法分析：
- 关键字:
实验指导书中关键字 “if”, “while”, “else”,
Cminus中扩展：“return”, “int”, “float”, “void”
- 运算符:
实验指导书中运算符：
“+”
“-”
“*”
“/”
“>”
“<”
“;”
“(”
“)”
“{”
“}”
Cminus扩展：
“[”
“]”
“=”
“<=”
“>=”
“==”
“!=”
“,”

- 支持十进制小数整数，八进制小数整数，十六进制小数整数

语法分析：
支持语法：
实验指导书中所有语法

Cminus扩展语法：
函数定义(void, float, int)
函数调用
返回语句(return)
空语句( ; )
变量定义(int , float)
数组定义(int , float)


三地址代码：
实验指导书要求的三地址代码 

Cminus扩展：
函数调用三地址代码
函数返回(return)
数组访问三地址代码
逻辑运算符作为表达式

语义分析：（留一张ppt插图）

1. 函数/变量/数组重定义 （标识符name相同即为重定义，不管是否是相同类型）
2. 函数/变量/数组未定义 
3. 表达式求值
4. 数组索引越界
5. 函数返回值与实际不匹配（void不能有返回值， 非void不能没有返回值）
6. 表达式求值中自动类型转换（int和float可以自动转换）
7. 函数参数类型/个数不匹配
8. 数组索引不能为非整数类型

原本的C语言是不检查数组越界的，我们为了使程序员编写语言时更加安全，添加了数组越界检查，因此我们在语义检查阶段对访问数组的表达式进行了求值，以检查数组是否越界

文件结构：
```                     
|                       # 根目录
├── Makefile                # make
├── README.md               # README
├── bison.y                 # 用于语法分析
├── lex.l                   # 用于词法分析
├── driver.cpp              # 用于启动编译程序
│
├── header              # 目录：头文件
│   ├── ast.h               # 抽象语法树节点	
│   ├── codegen.h           # 三地址代码类（静态类）
│   ├── symbol.h            # 符号表数据结构
│   └── visitor.h           # 观察者定义
|
├── output              # 目录:编译程序输出
│   ├── TAC.txt             # 三地址代码输出
│   ├── task1.txt           # 实验要求一：输出识别到的符号
│   └── task2.txt           # 实验要求二：输出抽象语法树
│
├── src                 # 目录：头文件的具体实现
│   ├── ast.cpp             # 空，相应函数均在ast.h中实现
│   ├── codegen.cpp         # 实现了三地址代码的生成
│   ├── symbol.cpp          # 实现了符号表的数据结构
│   └── visitor.cpp         # 实现了每一个具体的观察者
│
└── test                      # 目录：测试程序
    ├── binary.c                  # 二元运算测试 (包括float和int之间的类型转换)
    ├── dup_func.c                # 函数重定义测试
    ├── dup_var.c                 # 变量重定义测试
    ├── dup_arr.c                 # 数组重定义测试
    ├── func_define.c             # 函数未定义测试
    ├── var_define.c              # 变量未定义测试
    ├── arr_define.c              # 数组未定义测试
    ├── arr_index.c               # 数组越界测试
    ├── arr_index_non_int.c       # 数组索引非整数类型测试
    ├── func_invoke.c             # 函数调用测试（是否有返回值决定三地址代码的生成）
    ├── func_invoke_param_num.c   # 函数调用参数个数不匹配测试
    ├── func_invoke_param_type.c  # 函数调用参数类型不匹配
    ├── while.c                   # while语句测试
    ├── selection.c               # if-else语句测试
    ├── simple.c                  # 较简单的测试程序
    └── code.c                    # 较复杂的测试程序 
```
程序采用c++语言实现， 使用面向对象编程，
使用设计模式中的观察者模式对抽象语法树节点进行操作。
类结构设计清晰。

抽象语法节点类继承关系如下:
- AstNode
&emsp;&emsp;Statement
&emsp;&emsp;&emsp;&emsp;IfStmt
&emsp;&emsp;&emsp;&emsp;WhileStmt
&emsp;&emsp;&emsp;&emsp;BlockStmt
&emsp;&emsp;&emsp;&emsp;EmptyStmt
&emsp;&emsp;&emsp;&emsp;ReturnStmt
&emsp;&emsp;&emsp;&emsp;ExpStmt
&emsp;&emsp;&emsp;&emsp;Variable
&emsp;&emsp;&emsp;&emsp;ArrayVariable
&emsp;&emsp;Expression
&emsp;&emsp;&emsp;&emsp;Identifier
&emsp;&emsp;&emsp;&emsp;BinOp
&emsp;&emsp;&emsp;&emsp;FunctionInvoke
&emsp;&emsp;&emsp;&emsp;Int10
&emsp;&emsp;&emsp;&emsp;Real10
&emsp;&emsp;AccessVar
&emsp;&emsp;PrimitiveType

符号类继承关系如下:
- Symbol
&emsp;&emsp;KeyWordSymbol
&emsp;&emsp;FuncSymbol
&emsp;&emsp;IdSymbol
&emsp;&emsp;&emsp;&emsp;ArraySymbol

符号表采用hash映射实现，使用C++ STL库中的map，设置四种不同类型的符号表，分别为关键字符号map，函数符号map，变量符号map，数组符号map，其key-value设为<符号名称， 对应符号>。
提供相应的插入操作

三地址代码类使用静态类来实现
