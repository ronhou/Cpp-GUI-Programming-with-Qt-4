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