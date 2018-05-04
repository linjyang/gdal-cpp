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
