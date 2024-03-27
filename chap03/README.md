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

# 有几个疑惑的地方
  + 即使`Spreadsheet`类没有申明和定义动作连接的对应的槽函数，编译也可以通过，不会提示编译报错或警告
    + 从效果上来说，只是未连接动作对应的信号-槽
  + 即使将`Spreadsheet`类的槽函数定义为私有，也不会编译报错，**信号-槽连接仍会建立成功**