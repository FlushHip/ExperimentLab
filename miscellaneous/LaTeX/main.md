# CaptchaGG：基于卷积神经网络的简单验证码识别模型

## 摘要

这篇文章提出了一种识别简单验证码的方案GaptchaGG，该方案基于卷积神经网络对验证码进行特征提取和分类。
神经网络太深会导致难以训练和梯度消失等问题，太浅会导致模型的欠拟合。
对于简单验证码识别问题，需要搭建合适的特征提取层来提取数字和字母的基本特征，同时也要选择合适的分类层来分类。
本文提出的模型能在较低的复杂度下达到准确率为90%以上的识别度。

关键词: 简单验证码、卷积神经网络、特征提取

## 介绍

验证码的定义为Completely Automated Public Turing test to tell Computers and Humans Apart，简称CAPTCHA。
在CAPTCHA测试中，作为服务器的计算机会自动生成一个问题由用户来解答。这个问题可以由计算机生成并评判，但是必须只有人类才能解答。由于机器无法解答CAPTCHA的问题，回答出问题的用户即可视为人类。
这些验证码可以由数字，大小写字母、汉字等相关元素组成，用户需要识别出图片中包含的元素并正确回答这些元素才能通过验证，高级一点的验证码，会通过数字组成等式，这种验证码需要用户计算出等式的值，值正确后方可通过测试。
本文研究的验证码为简单验证码，它的定义为一幅70*180的RGB图片，图片中只包含4个拍成一排的数字或大写字母，如下图所示。
这种验证码比较简单，适用于大部分安全性需求不高的网站。

2012年，AlexNet在ImageNet获得冠军，使得人们对图像处理问题的方法大幅转向深度神经网络。目前，基于卷积的深度神经网络已经是图像识别分类的基本做法，区别与传统的图像识别分类，基于卷积的深度神经网络可以把特征提取和分类结合在一起，过去需要人工提取特征来做分类，而神经网络不需要这样，它就像一个黑盒，给出输入，通过设计的模型，然后输出，就是这么简洁。

然而卷积深度神经网络的设计是目前最火的技术，不同的搭建方式会导致不同的特征组合方式以及性能差异。对于特定领域的问题，卷积深度学习的模型设计往往都是不同的，因此，需要具体问题具体分析，对特定问题选择合适的模型。

为此，我们依据前人的经验，结合简单验证码的特点设计了一种复杂度低，且准确率高的卷积深度神经网络模型CaptchaGG，该模型能以媲美肉眼识别的准确率识别简单验证码。

## 相关工作

视觉的经典问题是判定一组图像数据中是否包含某个特定的物体，图像特征或运动状态。这一问题通常可以通过机器自动解决，但是到目前为止，还没有某个单一的方法能够广泛的对各种情况进行判定：在任意环境中识别任意物体。现有技术能够也只能够很好地解决特定目标的识别，比如简单几何图形识别，人脸识别，印刷或手写文件识别或者车辆识别。而且这些识别需要在特定的环境中，具有指定的光照，背景和目标姿态要求。

在深度学习算法出来之前，对于视觉算法来说，大致可以分为以下5个步骤：特征感知，图像预处理，特征提取，特征筛选，推理预测与识别。早期的机器学习中，占优势的统计机器学习群体中，对特征是不大关心的。特征或者视觉特征，就是把这些数值给综合起来用统计或非统计的形式，把想识别或检测的部件或者整体对象表现出来。深度学习的流行之前，大部分的设计图像特征就是基于此，即把一个区域内的像素级别的信息综合表现出来，利于后面的分类学习。手工设计特征需要大量的经验，需要对这个领域和数据特别了解，并且设计出来特征还需要大量的调试工作。

于是，学术界开始研究开发不需手动设计特征、不挑选分类器的机器视觉系统，希望机器视觉系统同时学习特征和分类器，即输入某一个模型的时候，输入只是图片，输出就是它自己的标签。随着深度学习迅猛发展，卷积神经网络（CNN）的出现使得该设想得以实现，基于深度学习的计算机视觉研究发展迅速。LeNet在1998年提出了深度学习网络的最初原型LeNet，它第一次定义的CNN的网络结构，是深度学习网络的开山鼻祖。2012年，AlexNet横空出世，它启发了人们更大，更深的网络可以更好地拟合问题，2014年， VGG系列模型被提出，它启发了人们可以在网络中加入块的概念来扩展网络，因此后续的GoogleNet，ResNet都借鉴了VGG的思想。2015年，ResNet的提出又是一枚重磅炸弹，此网络提出了残差结构，使得神经网络的深度可以很深很深，这样可以很高地提取高纬度的特征，同时又避免的出现梯度消失问题。这些网络结构都是图像识别领域内经典且优秀的网络结构。

GAN是非监督式学习的一种方法，它通过让两个神经网络相互博弈的方式进行学习，SimGAN正是这一方法的代表。

可以说，我们提出的CaptchaGG是站在巨人的肩膀上提出来的。

## CaptchaGG

下图是CaptchaGG的总体网络架构结构，CaptchaGG的特征提取层参考了VGG16的特征提取层，并对简单验证码的图形输入大小进行了卷积层的定制。

## 实验数据

## 总结

## 引用