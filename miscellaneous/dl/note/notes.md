## AlexNet

![](http://mmbiz.qpic.cn/mmbiz_png/KmXPKA19gW9icjxYpwfgNYty0FDQN53O4AESmABFqm12MIowxRcweDqibCTRlzv8NjbG47c1al9IDFibuSJVyyY3w/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)

![](https://zh-v2.d2l.ai/_images/alexnet.svg)

它包括 5 个卷积层、3 个全连接层

- ReLu
- Dropout

## VGG

![VGG16](https://www.researchgate.net/profile/Max-Ferguson/publication/322512435/figure/fig3/AS:697390994567179@1543282378794/Fig-A1-The-standard-VGG-16-network-architecture-as-proposed-in-32-Note-that-only.png)

它通过相继使用多个 3x3 卷积核大小的滤波器取代大尺寸卷积核滤波器（第一个和第二个卷积层分别有 11 个和 5 个滤波器）实现了优于 AlexNet 的性能。给定感受野（输出所依赖的输入图像有效区域大小），利用多个堆叠的更小尺寸的卷积核取得的效果优于使用更大尺寸的卷积核，因为多个非线性层会增加网络的深度，从而允许其学习更复杂的特征，并且计算成本更低。

![](https://zh-v2.d2l.ai/_images/vgg.svg)

## GoogleNet

inception 模块

卷积层中仅有少数神经元是有效的，因此特定卷积核大小的卷积滤波器数或者宽度将保持小值。并且，它还使用了不同大小的卷积核来捕捉不同规模的细节特征（5x5、3x3、1x1）；该模块的另一个重要特点是它拥有一个所谓的瓶颈层（图中的 1x1 卷积），它可以大幅减少计算开销。inception 模块在应用更大的卷积核之前使用 1x1 卷积以降低输入通道的维度。

![](http://mmbiz.qpic.cn/mmbiz_png/KmXPKA19gW9icjxYpwfgNYty0FDQN53O457lfs4SZpUvj6nocEvJvPYic6MHicZ7SZUJcW1C9AZef1br0LXuKWjEQ/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)

GoogLeNet 做出的另一个改变是，使用一个简单的全局平均池化层（global average pooling，对 2D 特征图的通道值取平均）取代网络末端的全连接层（在最后的卷积层之后）。这大大地减少了参数的总数。

![](https://img-blog.csdn.net/20180530220844573?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3UwMTQyNjQzNzM=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)

## ResNet

增加深度应该能够提升网络的准确率，同时也会导致过拟合。但增加深度的问题在于，在网络末端通过预测值和真值比较得到的权重修改信号，到了之前的层会变得很微弱。这基本上意味着网络之前的层几乎没有进行学习。这被称为梯度消失现象

![](https://img-blog.csdnimg.cn/20181111233323302.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM0ODg2NDAz,size_16,color_FFFFFF,t_70)
