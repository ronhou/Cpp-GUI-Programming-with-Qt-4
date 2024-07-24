# 第 8 章 二维图形
Qt 的二维图形引擎是基于 QPainter 类的。

## 8.1 用 QPainter 绘图
使用 QPainter 的 `draw...()` 函数，可以绘制各种各样的形状。常用的的绘制函数有：
+ `drawPoint()`
+ `drawLine()`
+ `drawPolyline()`
+ `drawPoints()`
+ `drawLines()`
+ `drawPolygon()`
+ `drawRect()`
+ `drawRoundRect()`
+ `drawEllipse()`
+ `drawArc()`
+ `drawChord()`
+ `drawPie()`
+ `drawText()`
+ `drawPixmap()`
+ `drawPath()`

绘制的效果取决于 QPainter 的设置。三个主要的设置是画笔、画刷和字体：
+ `setPen(const QPen&)`：画笔用来画线和边缘。它包含颜色、宽度、线型、拐点风格以及连接风格。
  + 拐点风格（端点样式）：FlatCap、SquareCap、RoundCap
  + 连接风格（拐点连接风格）：MiterJoin、BevelJoin、RoundJoin
  + 线型风格：SolidLine、DashLine、DotLine、DashDotLine、DashDotDotLine、NoPen
+ `setBrush(const QBrush&)`：画刷用来填充几何形状的图案。它一般由颜色和风格组成，但同时也可以是纹理（一个不断重复的图案）或者是一个渐变。
  + 各种预定义的画刷风格：SolidPattern、Dense1Pattern、Dense2Pattern、Dense3Pattern、Dense4Pattern、Dense5Pattern、Dense6Pattern、Dense7Pattern、HorPattern、VerPattern、CrossPattern、BDiagPattern、FDiagPattern、DiagCrossPattern、NoBrush
+ `setFont(const QFont&)`：字体用来绘制文本。字体有很多属性，包括字体族和磅值大小。

QPainterPath 类可以通过连接基本的图形元素来确定任意的矢量形状：直线、椭圆、多边形、弧形、贝塞尔曲线和其他的绘制路径。

渐变填充利用颜色插值使得两个或更多颜色之间能够平滑过渡。Qt 支持三种类型的渐变：
+ 线性渐变（`QLinearGradient`）
+ 辐射渐变（`QRadialGradient`）
+ 锥形渐变（`QConicalGradient`）
