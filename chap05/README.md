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