# gdal环境配置
## Linux
需要预先安装gcc/g++，make

先从gdal官网[下载源码](https://trac.osgeo.org/gdal/wiki/DownloadSource)

用make 安装：
```
$> cd gdal-2.2.4
$> ./configure
$> make
$> make install
```
## MacOS
直接用brew安装。这里装的是gdal2。gdal1.x是一样的安装方法
```bash
$> brew tap osgeo/osgeo4mac && brew tap --repair  #Tap into osgeo4mac
$> brew install jasper netcdf # gdal dependencies
$> brew install gdal2 --with-armadillo --with-complete --with-libkml --with-unsupported
$> brew link --force gdal2
```
可以用`brew info gdal2`查看安装参数。安装完成之后验证：
```
$> gdal-config --version
2.2.4
```
安装过程中会下载大量依赖，最后会调用make的方式安装。如果安装过程中提示一些依赖库版本过低的错误，直接把相应的库卸载重装（即使你的库版本是符合要求的）。

## C++代码调用，编译
写一个c++程序验证调用gdal
```c
#include "gdal_priv.h"
#include "iostream"

using namespace std;

int main(int argc, char* argv[]) {
    GDALAllRegister();         //利用GDAL读取图片，先要进行注册
    CPLSetConfigOption("GDAL_FILENAME_IS_UTF8","NO");   //设置支持中文路径

    //准备读取图片
    GDALDataset *ReadDataSet=(GDALDataset*)GDALOpen("/scratch/tmpfiles/volume_dsm.tif",GA_ReadOnly);

    int width=ReadDataSet->GetRasterXSize();  
    int height=ReadDataSet->GetRasterYSize();   
    int bandCount=ReadDataSet->GetRasterCount();

    cout<< width << " " << height << " " << bandCount << "\n";
}
```
用g++编译，指定gdal库
```
$> g++ main.cpp -lgdal -o main
```
试运行
```
$> ./main
619 818 1
```
