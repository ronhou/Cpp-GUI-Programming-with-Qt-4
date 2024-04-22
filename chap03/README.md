# 前言
> 再次说明下环境，
> 虽然是学习 Qt4 编程，但是实际使用的是 Qt 5.14.2，IDE使用的是 Qt Creator 12.0.2，
> 所以在某些使用习惯上可能和书上不一样，
> 比如`QtGui`头文件，在 Qt5 版本里面，其内并没有预期的部件的头文件，而我个人刚好又偏向于用到了什么类就包含哪个头文件

# 3.1 子类化 QMainWindow
+ 创建spreadsheet项目：该项目的主窗口是我们自定义的子类化 QMainWindow，其成员变量和方法使用空实现，或者不进行申明和定义，等后面真正用到的时候再一一添加；先保证项目能跑起来。
+ 创建一个`Spreadsheet`窗口部件，并且把它设置为主窗口的中央窗口部件。`Spreadsheet`类是`QTableWidget`类的一个子类，具有一些电子制表软件的功能。
+ 添加资源：通过 Qt Creator 添加 qrc 资源管理文件，并向其中添加图片等资源文件。通过 Qt Creator 操作，会将这些都自动添加到项目文件中。

# 3.2 创建菜单和工具栏
## 动作（`action`）
动作（`action`）是一个可以添加到菜单和工具栏的项。
+ 动作可以设置文本，图片，快捷键和状态提示等。
  + 大多数窗口系统都有用于特定动作的标准化的键盘快捷键。通过使用适当的`QKeySequence::StandardKey`枚举值，可以确保 Qt 能够为应用程序在其运行的平台上提供正确的快捷键。
  + 设置自定义快捷键时，我原本想着快捷键不需要使用`tr`进行翻译，结果编译的时候报错了，因为不能将裸字符串转为`QKeySequence`类型。
  + *动作的状态提示将会在后面添加了状态栏后体现出来*
+ 为动作建立信号-槽连接。本节主要介绍了动作的两个信号：
  + `void triggered(bool checked = false);`
  + `void toggled(bool);`（checkable 时使用）

## 菜单栏（`MenuBar`）
+ `QMainWindow::menuBar()`函数返回一个指向`QMenuBar`的指针。在第一次调用`menubar()`函数的时候会将菜单栏创建出来。
+ 在 Qt 中，菜单都是`QMenu`的实例。`QMenuBar::addMenu()`函数可以创建一个`QMenu`窗口部件，并且会把它添加到菜单栏中。
+ 菜单（`QMenu`）
  + 菜单可以通过`QMenu::addAction`添加动作作为菜单项
  + 菜单可以通过`QMenu::addMenu`添加子菜单，达到多层级菜单的效果
  + 菜单可以通过`QMenu::addSeparator`添加间隔器（我有时候习惯叫它分隔符）
    + 查看`addSeparator`方法的返回值可以发现，间隔器实际上也是动作
+ 菜单栏也可以向菜单与菜单之间添加间隔器

## 上下文菜单（`ContextMenu`）
+ 任何 Qt 窗口部件都可以有一个与之相关联的`QActions`列表。（`QWidget`上就有`addAction`和`addActions`方法添加动作。）
+ 将上下文菜单策略（`context menu policy`）设置为显示这些动作的上下文菜单（`Qt::ActionsContextMenu`）。
  + *暂时还不知道其它枚举值的作用效果*

## 工具栏（`ToolBar`）
+ 通过`QMainWindow::addToolBar`添加工具栏；然后向工具栏直接添加动作或间隔器
  + 菜单栏只有一个，通过`menuBar()`添加并获取；而工具栏可以添加多个。
  + 向菜单栏中添加菜单，然后向菜单中添加动作；而工具栏则是直接添加动作。

# 3.3 设置状态栏
状态栏和菜单栏相似，由`QMainWindow::statusBar()`提供，可以通过`QStatusBar::addWidget`等方法向状态栏添加部件。
  + **当hover选择了菜单或工具的项时，状态栏会展示对应动作（`action`）上设置的状态提示（StatusTip）**
  + `QStatusBar::addWidget`等添加部件的方法可通过参数指定部件的“伸展因子”
    + *暂时不明白“伸展因子”的效果，等后续完成整个项目之后应该就能看到效果了*

# 3.4 实现 File 菜单
> 由于`Spreadsheet`中央窗口部件在下一章才会真正实现，因此目前还看不到电子表的实际效果，其中读写文件函数只能先给一个空实现，可以通过日志大致了解一下`File`菜单的实现。
> 
> 或者先去把[源码](https://ptgmedia.pearsoncmg.com/images/9780132354165/examples/qt-book-examples.zip)的实现拷贝过来，本节先看效果，下一章再学习相关内容。
+ `QWidget`支持设置和获取`windowModified`属性。比如我们修改了文件但未保存时，文件名后面会跟着一个星号（*）。
+ 可以通过`QMessageBox`提供的静态函数弹出`Information`，`Warning`，`Critical`和`Question`四种消息对话框。
  + `QMessageBox`提供了许多标准按钮，可以对按钮进行组合，也可以自定义按钮。
+ 状态栏（`statusBar()`）可通过`showMessage`方法在状态栏显示一个`timeout`毫秒的消息。
+ `QFileDialog::getOpenFileName`静态函数可以弹出打开文件的对话框，让用户选择一个文件，并且返回这个文件名。
+ `QFileDialog::getSaveFileName`静态函数则可以弹出保存文件的对话框，并返回相应的文件名。
+ 当窗口关闭时，将调用`QWidget::close()`槽函数，该槽会给这个窗口部件发射一个“close”事件；我们通过重新实现`QWidget::closeEvent()`函数，就可以中途截取对这个主窗口的关闭操作。
+ `QString::arg()`函数将会使用自己的参数替换最小数字的“%n”参数，并且会用它的参数返回结果“%n”字符和最终的结果字符串（链式调用）。
  + Qt Creator 对此作出了警告：“`Use multi-arg instead [clazy-qstring-arg]`”，于是我将其改成了多参数的形式调用`arg()`。
+ 每一个动作（`action`）都可以带一个与之相关的`QVariant`型`data`项
  + `QVariant`类型可以保存许多C++和Qt型变量
  + 可以通过`QVariant::toString()`等方法将其转换成相应的目标类型
+ `qobject_cast<T>()`函数可在 Qt 的 moc（meta-object compiler，元对象编译器）所生成的元信息基础上执行动态类型强制转换（dynamic cast）。它返回一个指向所需 Object 子类的指针，或者是在该对象不能被转换成所需的类型时返回空指针。
  + 与标准的 C++ 的`dynamic_cast<T>()`不同，Qt 的 `qobject_cast<T>()` 可正确地跨越动态库边界。

# 3.5 使用对话框
+ **非模态（modeless）窗口和模态（modal）窗口**
  + **非模态（modeless）窗口**就是运行在应用程序中对于任何其它窗口都独立的窗口。用户可以在非模态窗口和其它窗口之间进行切换。
  + **模态（modal）窗口**就是一个在得到调用可以弹出并可以阻塞应用程序得窗口，从而会从调用发生开始起妨碍其它的任意处理或者交互操作，直到关闭该窗口为止。
  + 通过`show()`调起的是非模态窗口
  + 通过`exec()`调起的是模态窗口

+ 本节用到的其它方法介绍
  + `QWidget::show()`：显示部件
  + `QWidget::raise()`：提升部件到顶层
  + `QWidget::activateWindow()`：激活部件
  + `QDialog::setModal(bool)`：在窗口使用`show()`弹出**前**，使用该方法可设置窗口是模态的还是非模态的；*对`exec()`弹出的模态窗口设置无效*
  + `QMessageBox::about`和`QMessageBox::aboutQt`:除了上一节中提到的四种消息对话框，`QMessageBox`还同样提供了方便的静态函数来获得About和AboutQt对话框。

+ UI类嵌入方式  
  在上一章中有提到，书中UI类嵌入方式采用的是“多重继承”的方式，而我使用的是“以指针成员方式集成”。
  因此，当外部使用对话框的UI部件的时候，书中可以以public公有成员的方式直接使用，而我需要将UI指针成员改为public，包含相应的UI头文件，然后才能通过该UI成员使用其成员部件。

# 3.6 存储设置
这一节主要介绍了如何使用`QSettings`设置（写）和获取（读）应用级别的配置。
```C++
class QSettings {
    // constructor
    explicit QSettings(const QString &organization, const QString &application = QString(), QObject *parent = nullptr);

    // 设置（写）配置
    void setValue(const QString &key, const QVariant &value);
    // 获取（读）配置
    QVariant value(const QString &key, const QVariant &defaultValue = QVariant()) const;
};
```
+ 本节中用到的`QSettings`的构造函数如上所示，主要指定了“组织机构”和“应用程序”的名称，（Windows系统下）查看注册表可以发现，其读写位置位于`HKEY_CURRENT_USER\SOFTWARE\Software Inc.\Spreadsheet`。
+ `QSettings`把设置信息存储为键值对（`key-value pair`）的形式。
  + 键（key）与文件系统的路径相似，可以使用路径形式的语法（例如：`findDialog/matchCase`）来指定子键（subkey）的值，或者也可以使用`beginGroup()`和`endGroup()`的形式。
  + 值（value）可以是`QVariant`所支持的任意类型，包括那些已经注册过的自定义类型。

# 3.7 多文档
这一节并没有详细介绍如何做好多文档，只是简单介绍了如何通过多窗口的形式实现多文档的效果。
+ `main`函数中需改为使用`new`的方式创建首个窗口
  + **为什么要改成`new`?** 该窗口的的内存管理由谁负责，`QApplication`？
  + **假如不修改这里的话，为什么关闭这个窗口的时候会出错？**
+ `newFile`的逻辑改成了`newMainWindow`
  + 同上，这里创建的窗口的内存管理也是由`QApplication`负责吗？
+ 新增了`closeAction`，相应的将`exitAction`改为绑定`closeAllWinidows`槽

# 有几个疑惑的地方
  + 即使`Spreadsheet`类没有申明和定义动作连接的对应的槽函数，编译也可以通过，不会提示编译报错或警告
    + 从效果上来说，只是未连接动作对应的信号-槽
  + 即使将`Spreadsheet`类的槽函数定义为私有，也不会编译报错，**信号-槽连接仍会建立成功**