# 创建自定义窗口部件
创建自定义窗口部件的两种方式：
+ 对一个已经存在的 Qt 窗口部件进行子类化
+ 直接对`QWidget`进行子类化

## 1. 自定义 Qt 窗口部件
自定义 Qt 窗口部件可以遵循相同的模式：选择一个合适的 Qt 窗口部件，对它进行子类化，并且通过重新实现一些虚函数来改变它的行为即可。
+ `QSpinBox`的默认设置值范围是从0到99
+ validate
  + 检查用户输入文本的合法性
  + `validate`并非父类`QSpinBox`的虚函数，而是祖先类`QAbstractSpinBox`的虚函数
  + `QRegExpValidator`有一个合适的`validate()`函数；有三种结果可能出现：
    + `Invalid`：无效，输入的文本与正则表达式不匹配
    + `Intermediate`：部分有效，部分无效，输入的文本是一个有效值中似是而非的一部分
    + `Accepttable`：可以接收，输入的文本合法有效
+ `int QString::toInt(bool *ok = nullptr, int base = 10) const`
  + QString 转 int 型整数，返回整数
  + 第一个参数可用来反馈转换是否成功
  + 第二个参数指定进制
+ `static QString QString::number`
  + 静态方法，数字转 QString，第二个参数指定进制

## 2. 子类化 QWidget
通过子类化 QWidget，创建自定义窗口部件，重新实现该部件的相关事件：比如绘制事件和鼠标事件等。
+ `Q_PROPERTY`
  + 声明自定义属性：`Q_PROPERTY(QColor penColor READ getPenColor WRITE setPenColor)`
    + 数据类型： `QColor`。（这些属性可以是由`QVariant`所支持的任何类型。）
    + 属性名：`penColor`
    + “读”函数：`getPenColor`。（书中并没有使用 get，我这里只是特意用来区分属性名和读函数名）
    + 可选的“写”函数：`setPenColor`
  + 用处：当我们在 Qt 设计师中使用这个自定义窗口部件时，在 Qt 设计师属性编辑器里，将会显示这些自定义属性
  + 对于定义了属性的类，`Q_OBJECT`宏是必需的

+ `QImage`类使用一种与硬件无关的方式来存储图像。可以把它设置成使用 1 位、8 位或者 32 位色深。

+ `QRgb`
  + 32 位色深的颜色各使用 8 位来存储它的红、绿、蓝分量，剩余的 8 位存储这个像素的 alpha 分量（即不透明度）。
  + `QRgb`只是`unsigned int`类型的一个`typedef`（类型别名），可以通过内联函数`qRgba()`和`qRgb()`（不透明）来组合一个`QRgb`颜色。
    + 也可以直接赋值一个 32 位的整数，高 8 位是 alpha 分量，由高到低每 8 位分别是红、绿、蓝色分量。

+ `QColor` 是一个具有许多有用函数并且在 Qt 中广泛用于存储颜色的类。

+ `sizeHint()`函数是从`QWidget`中重新实现的（重写），并且可以返回一个窗口部件的理想大小。
  + 在和布局联合使用时，窗口部件的大小提示非常有用。当 Qt 的布局管理器摆放一个窗体的子窗口部件时，它会尽可能多地考虑这些窗口部件的***大小提示***。

+ 窗口的大小策略（SizePolicy）
  + SizePolicy 会告诉布局系统是否可以对这个窗口部件进行拉长或者缩短
    + `QSizePolicy::Minimum`：告诉管理这个窗口部件的任意布局管理器，这个窗口部件的大小提示（`sizeHint()`）就是它的**最小**尺寸大小。

+ 当产生一个绘制事件并且调用`paintEvent()`函数的时候，会出现如下几种情况：
  + 在窗口部件第一次显示时，系统会自动产生一个绘制事件，从而强制绘制这个窗口部件本身。
  + 当重新调整窗口部件大小的时候，系统也会产生一个绘制事件。
  + 当窗口部件被其它窗口部件遮挡，然后又再次显示出来的时候，就会对那些隐藏的区域产生一个绘制事件（除非这个窗口系统存储了整个区域）
  + 也可以通过调用`QWidget::update()`或者`QWidget::repaint()`来强制产生一个绘制事件。（如果窗口部件在屏幕上是不可见的，那么这两个函数会什么也不做。）
    + `repaint()`函数会强制产生一个**即时**的重绘事件
    + `update()`函数则只是在 Qt 下一次处理事件时才简单地调用一个绘制事件
      + 如果多次调用`update()`，Qt 就会把连续多次的绘制事件压缩成一个单一的绘制事件，这样就可以避免闪烁现象。

+ 每一个窗口部件都会配备一个调色板（palette），由它来确定做什么事应该使用什么颜色。
  + 一个窗口哦部件的调色板由三个颜色组构成：激活组（Active）、非激活组（Inactive）和不可用组（Disable）。应该使用哪一个颜色组取决于该窗口部件的当前状态。

+ 在窗口部件上构建一个`QPainter`对象
  + `QPainter::drawLine()`：绘制线段
  + `QPainter::fillRect()`：绘制填充矩形区域

+ 窗口部件的属性
  + 设置窗口部件的属性：`QWidget::setAttribute`
  + `Qt::WA_StaticContents`
    + 这个属性告诉 Qt，当重新改变窗口部件的大小时，这个窗口部件的内容并没有发生变化，而且它的内容仍旧保留从窗口部件左上角开始的特性。
    + 当重新定义窗口部件的大小时，通过使用这个信息，Qt 就可以避免对已经显示区域的重新绘制。
    + 绘制事件的区域会被严格限定在之前没有被显示的像素部分上。这也就意味着，如果重新把窗口部件改变为比原来还要小的尺寸，那么就根本不会产生任何绘制事件。