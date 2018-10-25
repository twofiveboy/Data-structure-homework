# Data-structure-homework
Data structure homework of ZJU MOOC
第二次作业中的一些蛋疼经验
关于reverse linkedlist
最后一个for 循环初始的控制一开始犯了想当然地错误，于是弄了个getsize（）获得有效的链表数据个数来控制流程，还好没有超时。
关于pop sequence：
参考https://blog.csdn.net/qq_40733911/article/details/80845154?utm_source=blogxgwz0
利用了堆栈性质：对于出栈序列的每一个元素，该元素后  比该元素先入栈的一定按照降序排列，一个比较偷懒的算法复杂度为O（N2）
也可以考虑另一种复杂度为O(N)方法，暂未实现
重要TIP:要输出的是YES和NO，不是Yes，No，我在这里呆了2个小时 T T
