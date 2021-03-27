### step0 

在windows上查找：

cache1:64k 

cache2:256k

cache3:1m

### step1

![image-20210321014145518](/home/peichen/.config/Typora/typora-user-images/image-20210321014145518.png)

![image-20210321103324660](/home/peichen/.config/Typora/typora-user-images/image-20210321103324660.png)

可以看出在64kb和256kb的时候有明显上升。

### step2

![image-20210321020237861](/home/peichen/.config/Typora/typora-user-images/image-20210321020237861.png)

可以看到在32b到64b上出现了不正常增长

### step3

尝试了三种不同的算法，实验效果都不明显。发现测试后隔一段时间再测会有较好效果，但多次实验n=4时和n=5时的时间差距最明显，因此可能是八路组相连。

