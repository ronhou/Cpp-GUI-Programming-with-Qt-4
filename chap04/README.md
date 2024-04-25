# 实现应用程序的功能
接着上一章的内容，我们在实现了主窗口的相应功能之后，接着完成这个程序。

## 1. 中央窗口部件
对于我们这个 Spreadsheet 应用程序，会使用一个`QTableWidget`子类作为它的中央敞口部件。
上一章，为了让应用程序能够跑起来，我们已经简单实现了 Spreadsheet，不过主要是申明和空实现。

`QMainWindow`的中央区域可以被任意种类的窗口部件所占用。先了解下：
+ 使用一个标准的 Qt 窗口部件
+ 使用一个自定义窗口部件
+ 使用一个带布局管理器的普通 QWidget
+ 使用切分窗口（splitter）
+ 使用多文档界面工作空间

## 2. 子类化 QTableWidget
### `QTableWidget`
`QTableWidget`是一组格子，可以非常有效地用来表达二维稀疏数组。我们的`Spreadsheet`类即继承自它。
+ `setItemPrototype()`：将表格的单元格项的原型设置为指定的`QTableWidgetItem`派生类型，比如我们自定义的`Cell`类
+ `setSelectionMode()`：设置选择（选区）模式，模式枚举值包括：`NoSelection`，`SingleSelection`，`MultiSelection`，`ExtendedSelection`和`ContiguousSelection`。
+ `QTableWidget`由多个子窗口部件构成
  + 它的顶部有一个水平的`QHeaderView`，左侧有一个垂直的`QHeaderView`
    + `setHorizontalHeaderItem()/setVerticalHeaderItem()`：设置顶部/左侧`QHeaderView`的项（也是`QTableWidgetItem`）
  + 底部和右侧各有一个`QScrollBar`
  + 它的中间视口（`viewport`）区域被特殊窗口部件所占用，`QTableWidget`可以在上面绘制单元格。
+ `item()/setItem()`：获取/设置 对应行列位置的单元格项
+ `setRowCount()/setColumnCount()/rowCount()/columnCount`：设置&获取行列数

### `QTableWidgetItem`
+ 当用户在一个空单元格内输入一些文本的时候，`QTableWidget`会自动创建一个用来存储这些文本的`QTableWidgetItem`。
+ `QTableWidgetItem`不是一个窗口部件类，而是一个纯粹的数据类。
+ `text()/setText()`：获取/设置 单元格内文本

## 3. 载入和保存
这一节介绍了如何通过`QFile`和`QDataStream`打开（读）和保存（写）自定义的二进制数据格式的 Spreadsheet 文件。
+ `QFile::open`：打开文件，`QFile`构造时可传入文件路径，`open`参数传入相应的打开模式（权限），比如`ReadOnly`（只读）和`WriteOnly`（只写）等。
+ `QDataStream`：数据流，类似标准库的`std::basic_fstream`
  + 构造`QDataStream`可传入`QIODevice*`指针，比如上面的`QFile`
  + `QDataStream::setVersion`：设置二进制数格式的版本。*（个人理解是因为标准一直在变，所以需要指定，避免兼容问题）*
  + 各种数据类型的二进制格式由`QDataStream`决定
    + `quint16`按照高字节在后的顺序存储为两个字节。*（为什么我看到的是高位在前，低位在后，是我高低前后理解有误吗？）*
    + `QString`则被存储为字符串的长度（四个字节）后跟 Unicode 字符。
+ OverrideCursor
  + `QApplication::setOverrideCursor(Qt::WaitCursor)`：在输出数据之前，把应用程序的光标修改为标准的等待光标。
  + `QApplication::restoreOverrideCursor()`：数据输出完毕，需要把应用程序的光标重新恢复为普通光标。

## 4. 实现 Edit 菜单
+ copy（复制）：将选区内的文本（`text()`或者`formula()`）序列化，写入到系统剪贴板。
  + 序列化：遍历当前选区，将每个单元格的公式追加到文本串中，行与行之间使用换行符“\n”分隔，单元格之间则以制表符“\t”来分割。
  + 写入系统剪贴板：`QApplication::clipboard()->setText(text)`。
+ paste（粘贴）：取出剪切板的文本，将其反序列化，按照上面的规则分解后设置到选区内的每一个单元格。 
  + 取系统剪切版的文本：`QApplication::clipboard()->text()`。
  + 这里缺少数据校验和容错等机制，从剪贴板取出的文本并不一定符合上面的规范，可能会导致应用程序崩溃。
+ 选择模式设置为`QAbstractItemView::ContiguousSelection`时，选择范围不会超过1。
+ `findNext/findPrev`（查找）：从当前行列的位置向后/向前搜索
  + 需略过当前单元格，需从下一个/上一个位置开始搜索，否则如果当前单元格满足条件，则会一直停留在当前单元格位置
  + `QString::contains`：判断字符串是否包含查找串
+ `QTableWidget::selectedItems()`：获取选区内的所有item项
+ `QTableWidget::selectedRanges()`：返回选择范围（选区）列表
+ `QTableWidget:: currentRow()/currentColumn()`：返回当前所在的行列索引
+ `QTableWidget:: selectRow(int)/selectColumn(int)`：选择对应行/列
+ `QAbstractItemView::clearSelection`：取消选择（选区）
+ `QTableWidget::setCurrentCell(int,int)`：设置当前单元格
+ `QWidget::activateWindow()`：激活窗口
+ `QApplication::beep()`：让应用程序发出“哔”的一声

## 5. 实现其它菜单
+ `viewport()->update()`：视口更新
+ 仿函数（functor）：STL六大部件之一，它是一种重载了函数调用运算符（`operator()`）的类对象，它可以像函数一样被调用。
+ `qStableSort()`和`qSort()`的区别在于：当比较的两者相等时，`qStableSort()`能保持两者的原有顺序。

## 6. 子类化 QTableWidgetItem
+ 在`const`方法中可以修改`mutable`关键字修饰的成员变量
  + 因为`Cell::data() const`方法是重写自基类，且在其实现逻辑中需要修改到这两个成员变量，因此使用`mutable`修饰了这两个成员变量。
+ 表达式求值（`evalExpression`）
  + 递归渐降解析器（recursive-descent parser）
  + 在表达式求值之前，在字符串的末尾添加`QChar::Null`字符，调试的时候可以发现，这个字符可以起到“**哨兵**”的作用
  + `evalExpression`：该函数处理 double 类型数据的加减法，将表达式拆解成：`term1+term2+...`的形式。
  + `evalTerm`：同上，该函数处理 double类型的乘除法，将表达式解析成`factor1*factor2*...`的形式，代码风格也可以进行类似的改进。
    + 和`evalExpression`流程上相似，可以尝试将其合并成一个
  + `evalFactor`：解析因子