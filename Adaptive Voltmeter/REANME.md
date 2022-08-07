# 自适应电压表

**功能说明**

基于ATmega16单片机，电压表量程分为三档，电压表根据所测电压自动选择相应量程。

**具体要求**
1、量程分为“0-1V"、"0-5V"和"0-10V"三档; 
2、测量时单片机根据检测结果自动选择量程并调整电压放大倍数;
3、在数码管最终量程以及测量结果，并通过串口上传，自定义发送格式，避免一
次测量中相同数据重复发送; ;
4、测量结果精度:量程"0-1V"结果保留3位小数，"0- 5V"保留两位小数，“0- 10V保
留一位小数;

**PCB硬件展示**

![image-20220806222223124](C:\Users\黄浩\AppData\Roaming\Typora\typora-user-images\image-20220806222223124.png)

![image-20220806222246117](C:\Users\黄浩\AppData\Roaming\Typora\typora-user-images\image-20220806222246117.png)

![image-20220806222425400](C:\Users\黄浩\AppData\Roaming\Typora\typora-user-images\image-20220806222425400.png)

![image-20220806222720055](C:\Users\黄浩\AppData\Roaming\Typora\typora-user-images\image-20220806222720055.png)