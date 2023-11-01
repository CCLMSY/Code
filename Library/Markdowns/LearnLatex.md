# Latex公式语法规则

## 希腊字母（常用）
小写：$1.\alpha，2.\beta，3.\gamma，4.\eta，5.\theta，6.\lambda，7.\mu，8.\xi，9.\pi，10.\rho，11.\omega，12.\phi$
大写：$1.\Sigma，2.\Pi，3.\Delta，4.\Omega，5.\Phi$
变体：$1.\varepsilon，2.\varphi，3.\varSigma，4.\varPi，5.\varDelta$
希腊字母使用英文注音转义，变体在前加var(variant)

## 上下标：^，_
上标：$\alpha^2$
下标：$\beta_2$

## 作用域：{}
多字符上下标：$a_{i,j}$

## 斜体和罗马体
一般来说，斜体英文表示变量，罗马体英文表示常量。默认情况下为斜体
\rm作用到公式末尾：$\rm hello world!$
\text只作用于后一个字符：$\text hello world!$
\text可以解释空格：$\text{hello world!}$

## 增加间距
$a \, a$
$a \  a$
$a \quad a$
$a \qquad a$

## 分式和根式
\frac(fraction，分数)：$\frac{\alpha}{2\pi}$
\dfrac(display，展示)：$\dfrac{\alpha}{2\pi}$
\sqrt(square root，平方根)：$\sqrt\dfrac{\alpha}{2\pi}$
\sqrt(n次方根)：$\sqrt[3]{\dfrac{\alpha}{2\pi}}$

## 小型算符
### 基本算符
$1.加+，2.减-，3.乘\times，4.除\div，5.点乘\cdot$ 
$6.正负\pm，7.负正\mp$
### 比较算符
$1.大于>，2.小于<，3.等于=，4.不等于\ne$
$5.大于等于\ge，6.小于等于\le，7.远大于\gg，8.远小于\ll$
$9.约等于\approx，10.恒等于\equiv$
### 集合算符
$1.交\cap，2.并\cup，3.属于\in，4.不属于\notin$
$5.子集\subseteq，6.真子集\subsetneqq，7.空集\varnothing$
### 谓词
$1.任意\forall，2.存在\exists，3.不存在\nexists$
### 因为所以
$1.因为\because，2.所以\therefore$
### 数集
$1.实数集\R，2.自然数集\N，3.整数集\Z，4.正整数集\Z_+$
### 数学字体
$1.数学集合\mathbb R，2.数学书法\mathcal{F}，3.数学手迹\mathscr{F}$
### 省略号
$1.横向\cdots，2.纵向\vdots，3.斜向\ddots$
### 三角函数/反三角函数
$1.\sin x，2.\cos x,3.\arctan x ……$
### 对数
$1.\log_2 x，2.\ln x，3.\lg x$
### 极限
$\lim\limits_{x \to 0} \frac {x} {\sin x}$
**\limits用于将条件强制显示于符号上下方**
### 其他
$1.无穷\infty，2.偏微分\partial，3.梯度\nabla，4.正比于\propto，5.角度\degree$

## 大型算符
### 求和、求积
$求和：\sum\limits_{i=0}^N a_i$
$求积：\prod\limits_{i=0}^N a_i$
### 积分
$1.一重积分\int，2.二重积分\iint，3.三重积分\iiint，4.回路积分\oint$
$\int_{-\infty}^0 f(x) \text d x$

## 标注符号
$向量：\vec x，\overrightarrow{AB}$
$平均：\bar x，\overline{AB}$
$箭头：\leftarrow，\Rightarrow，\Leftrightarrow，\longrightarrow$
$括号与界定符：()，[]，\{\}，\lceil\rceil，\lfloor\rfloor，||$
\left和\right可以使括号和界定符自适应：$\left( \sum\limits_{i=0}^N a_i \right)，\left. \frac{\partial f}{\partial x} \right| _{x=0}$

## 多行公式：
等值演算对齐
$$\begin{align}
    |\lambda \bf E-A|
    &=-3+2\lambda+6+(\lambda+2)[(\lambda-2)(\lambda+3)+5]\\
    &=2\lambda+3+(\lambda+2)(\lambda^2+\lambda-1)\\
    &=\lambda^3+3\lambda^2+3\lambda+1\\
    &=(\lambda+1)^3
\end{align}$$
分段函数/分类讨论 大括号
$$\begin{cases}
    x^2 , x \le -\pi \\
    \sin x , -\pi \le x \le \pi \\
    \log_2 x , x \ge \pi
\end{cases}$$

## 矩阵
无括号
$$\begin{matrix}
    a & b & \cdots & c \\
    d & e & \cdots & f \\
    \vdots & \vdots & \ddots & \vdots \\
    g & h & \cdots & i
\end{matrix}$$
方括号 barket
$$\begin{bmatrix}
    a & b & \cdots & c \\
    d & e & \cdots & f \\
    \vdots & \vdots & \ddots & \vdots \\
    g & h & \cdots & i
\end{bmatrix}$$
圆括号 parenthesis
$$\begin{pmatrix}
    a & b & \cdots & c \\
    d & e & \cdots & f \\
    \vdots & \vdots & \ddots & \vdots \\
    g & h & \cdots & i
\end{pmatrix}$$
竖直线（行列式） vertical
$$\begin{vmatrix}
    a & b & \cdots & c \\
    d & e & \cdots & f \\
    \vdots & \vdots & \ddots & \vdots \\
    g & h & \cdots & i
\end{vmatrix}$$
矩阵表示规范：
$\bf A,\bf E,\bf A^{\rm T}$