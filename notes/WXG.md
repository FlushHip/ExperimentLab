# liteapp

## ios example 运行

conan 需要1.62版本。

### demo工程运行

```bash
cd shared/wxa_lite_app/example/ios
flutter pub get
pod install
open Runner.xcworkspace
```

### 源码编译wechatlv

```bash
cd shared/wxa_lite_app/third_party/luggage-view
python3 build_ios.py -g -withYoga -withJSbinding
```

`shared/wxa_lite_app/third_party/luggage-view/cmake_build/iOS` 下生成`wechatlv.xcodeproj/wechatlv.framework`

拉入ios explame项目中，记得删除Conan的原依赖

### 源码编译dart2cpp

```bash
shared/wxa_lite_app/third_party/dart2cpp
python3 build.py -g
```

同上

### 编译过程中遇到的问题

#### 库的架构`arm64`, `arm64e`

解决方法，统一使用`arm64`，使用`lipo -thin`操作库的架构，去除`arm64e`
