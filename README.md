# AStar
A*算法研究，从入门到进阶

###v1.0
仅仅实现了一个最简单的形式，地图为方形栅格，无障碍物，取与目标点的欧几里得距离为启发式估价函数。设相邻状态对角的cost为14，直线的cost为10。

这里的open表我采用的是list，其实有一种更好的方法就是采用优先级队列。这种方式实现起来会更简单，而且效率也会较高。
