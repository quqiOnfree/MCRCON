# MCRCON我的世界RCON管理器

## 前置

### Qt6
1. 需要在[CMakeLists.txt](./CMakeLists.txt)中修改Qt6路径

### Python3.9或以上

#### 安装
1. 把pip勾上
![image](./doc/python1.png)
2. 点击Customize installation
![image](./doc/python2.png)
3. 把debug勾上
![image](./doc/python3.png)
其他按自己喜好和需求修改

#### 修改
![image](./doc/python4.png)
1. 在[CMakeLists.txt](./CMakeLists.txt)中修改PYTHON_PATH为Python路径
2. 在[CMakeLists.txt](./CMakeLists.txt)中修改PYTHON_NAME为Python的名字加版本，例如`python39`

## 构建
直接无脑构建就完事了

## 运行

### 带界面版
不带界面版无法使用插件
直接点开即可

### 不带界面版
不带界面版可以使用插件
在cmd中使用`MCRCON.exe nogui`运行软件
