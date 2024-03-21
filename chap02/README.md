# 本章Qt学习笔记
### 对于所有定义了信号和槽的类，在类定义开始处的Q_OBJECT宏都是必需的。
+ 只能在QObject类内定义信号和槽
+ QObject派生类需要在类定义开始处使用`Q_OBJECT`宏

### 深入介绍信号和槽
#### 建立信号-槽连接：
`QObject::connect(sender, SIGNAL(signal), receiver, SLOT(slot))`
+ `sender`和`receiver`是指向QObject对象的指针，`signal`和`slot`是不带参数名的信号和槽函数
+ 可以通过`signals`宏自定义信号；可以通过`slots`宏自定义槽函数
+ 使用`QObject::connect`连接信号和槽函数的时候，需要使用`SIGNAL`包含信号，使用`SLOT`宏包含槽函数
  + `SIGNAL()`宏和`SLOT()`宏会将其转换成相应的字符串

#### 信号与槽函数
  + 一个信号可以连接多个槽
  + 多个信号可以连接同一个槽
  + 一个信号可以与另外一个信号连接
  + 连接可以被移除
  + 要把信号成功连接到槽，它们的参数必须具有相同的顺序和类型
    + 如果信号的参数比它所连接的槽的参数多，那么多余的参数将会被简单地忽略掉

#### 自动建立信号槽连接
> 官方文档介绍：[Automatic Connections](https://doc.qt.io/archives/qt-4.8/designer-using-a-ui-file.html#automatic-connections)

QWidget窗体类内，可以通过`void on_<object name>_<signal name>(<signal parameters>);`格式自定义槽函数，自动建立信号-槽连接到该槽函数，它等同于我们主动通过如下方式建立信号-槽连接：  
`QObject::connect(<object name>, SIGNAL(signal name), this, on_<object name>__<signal_name>)`

### UI
#### .ui界面文件
.ui文件是一种基于XML格式的文件。
使用Qt Creator或者Qt Designer，在.ui界面文件上，能方便，自由且直观地设计出我们想要的UI界面。
设计时，我们可以添加各种组件，设置布局，调整tab顺序，建立UI内的信号-槽连接等。

### ui_头文件
通过uic工具可以把.ui界面文件转换成C++头文件，打开该头文件，我们可以看到：
#### 以`Ui_`开头的工具类
+ 类内公有（public）成员包含了前面设计时添加的所有组件和布局，外部可以自由使用。
+ `setupUi`方法对窗体进行初始化，其内就是之前设计ui时做的动作相对应的代码逻辑，就像本章的`find`对话框构造函数内，我们主动做的事情一样，`setupUi`方法自动帮我们做好了这些事情。
  + 设置控件，布局，tab顺序等
  + 建立窗体内控件之间的信号-槽连接
  + 通过`QMetaObject::connectSlotsByName(this);`建立控件信号与窗体的槽函数连接
+ `retranslateUi`即将用到的文本翻译成其它语言（暂时还为学习到这部分）

#### UI类嵌入方式
细心的可以发现，书籍内使用UI类是通过多继承上面的UI类的方式使用，而Qt Creator则是通过指针数据成员的方式使用。
实际上，Qt Creator可以通过设置修改UI类嵌入方式，入口在`选项 -- C++ -- Qt Class Generation -- UI类嵌入方式`，它们分别是：
+ 以指针成员方式集成
+ 集成
+ 多重继承

Qt Creator默认使用的是第一种方式，书籍内使用的是第三种方式。实际上还有第四种方式，在`gotocell1`项目中的main函数内，我们在外部直接使用相应的UI类。这四种方式在Qt的官方文档中也有介绍和对比：[Compile Time Form Processing](https://doc.qt.io/archives/qt-4.8/designer-using-a-ui-file.html#compile-time-form-processing)，文档中也是推荐使用“以指针成员方式集成”。

---
# 本章C++学习笔记
### 建议：使用`ifndef/define/endif`包含头文件
+ `#ifndef`，`#define`和`#endif`三者联用能够防止对这个头文件的多重包含。

### 建议：尽量在头文件中使用前置申明，而不是包含对应的头文件
+ 在头文件中前置声明类
  + 前置申明（forward declaration）会告诉C++编辑程序类的存在，而不用提供类定义中的所有细节。
  + 对于这些变量（变量，成员变量，函数参数等），我们使用了它们的类前置声明。这是可行的，因为它们都是指针，而且没有必要在头文件中就去访问它们，因而编译程序就无需这些类的完整定义。我们没有包含与这几个类相关的头文件，而是使用了前置声明，这可以使编译过程更快一些。

---
# TODO
- 深入学习“Qt的元对象系统”（2.2节末尾）