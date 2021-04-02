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

算法大同小异，目的是为了以步长大于block size，远小于总大小（不会超出一个组）的方式反复访问一个数组。当访问个数正好是联通度两倍时，每次访问都会是miss，因此时间应该最长。以实验手册的算法为例，因为只访问奇数块，所以最后是块数除4。

![image-20210327151024512](/home/peichen/.config/Typora/typora-user-images/image-20210327151024512.png)

### 矩阵加速

试了两个办法

重排循环顺序：

~~~c++
for(int register i = 0; i < MAXSIZE; i ++){
		for(int register k = 0; k < MAXSIZE; k ++){
			int register num = a[i][k];
			for(int register j = 0; j < k; j ++){
				d[i][j] += num * b[k][j];
			}
		}
	}
~~~

![image-20210327171315864](/home/peichen/.config/Typora/typora-user-images/image-20210327171315864.png)

分块：

~~~c++
for(int register jj = 0; jj < MAXSIZE; jj += blockSize){
		int register jjMaxSize = min(jj + blockSize, MAXSIZE);
		for(int register kk =jj; kk < MAXSIZE; kk += blockSize){
			int register kkMaxSize = min(kk + blockSize, MAXSIZE);
			for(int register i = 0; i < MAXSIZE; i ++){
				for(int register j = jj; j < jjMaxSize; j ++){
					sum = 0;
					for (int register k = kkMaxSize; k > kk ; k --){
						if(k==j){break;}
						sum += a[i][k] * b[k][j];
					}
					//write, do it once
					d[i][j] += sum;
				}
			}
		}
	}
~~~

![image-20210327172708104](/home/peichen/.config/Typora/typora-user-images/image-20210327172708104.png)

虽然最优下分块快，但平均看起来分块比重排要慢，可能是因为矩阵不够大。











































