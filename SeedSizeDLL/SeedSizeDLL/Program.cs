using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;
using System.IO;
using System.Drawing;
using System.Drawing.Imaging;
namespace testDllInCShape
{
    class Program
    {
        public class BitMapInfo
        {
            public byte[] Result { get; set; }
            public int Step{ get;set;}
         }
        public static BitMapInfo bitmapToByteArray(Bitmap src)
        {
            byte[] result;
            int step;
            int iWidth = src.Width;
            int iHeight = src.Height;
            Rectangle rect = new Rectangle(0, 0, iWidth, iHeight);
            BitmapData bmpData = src.LockBits(rect, ImageLockMode.ReadWrite, src.PixelFormat);
            IntPtr iPtr = bmpData.Scan0;
            step = bmpData.Stride;
            int iBytes = iHeight * step;
            byte[] pixelValues = new byte[iBytes];
            Marshal.Copy(iPtr, pixelValues, 0, iBytes);
            src.UnlockBits(bmpData);
            byte[] realValues = new byte[iHeight * iWidth * 3];
            int offset = step - iWidth * 3;
            int realValuesIndex = 0;
            int pixelValuesIndex = 0;
            for (int i = 0;i < iHeight;i++)
            {
                for(int j = 0;j < iWidth;j++)
                {
                    realValues[realValuesIndex++] = pixelValues[pixelValuesIndex++];
                    realValues[realValuesIndex++] = pixelValues[pixelValuesIndex++];
                    realValues[realValuesIndex++] = pixelValues[pixelValuesIndex++];
                }
                pixelValuesIndex += offset;
            }
            result = realValues;
            BitMapInfo bi = new BitMapInfo { Result = result, Step = iWidth * 3 };
            return bi;
        }
        public static Bitmap byteToGrayBitmap(byte[] rawValues, int width, int height)
        {
            //// 申请目标位图的变量，并将其内存区域锁定  
            Bitmap bmp = new Bitmap(width, height, PixelFormat.Format24bppRgb);
            BitmapData bmpData = bmp.LockBits(new Rectangle(0, 0, width, height),
             ImageLockMode.WriteOnly, PixelFormat.Format24bppRgb);

            //// 获取图像参数  
            int stride = bmpData.Stride;  // 扫描线的宽度  
            int offset = stride - width * 3;  // 显示宽度与扫描线宽度的间隙  
            IntPtr iptr = bmpData.Scan0;  // 获取bmpData的内存起始位置  
            int scanBytes = stride * height;// 用stride宽度，表示这是内存区域的大小  
            //Console.WriteLine(stride);
            //// 下面把原始的显示大小字节数组转换为内存中实际存放的字节数组  
            int posScan = 0, posReal = 0;// 分别设置两个位置指针，指向源数组和目标数组  
            byte[] pixelValues = new byte[scanBytes];  //为目标数组分配内存  

            for (int x = 0; x < height; x++)
            {
                //// 下面的循环节是模拟行扫描  
                for (int y = 0; y < width; y++)
                {
                    pixelValues[posScan++] = rawValues[posReal++];
                    pixelValues[posScan++] = rawValues[posReal++];
                    pixelValues[posScan++] = rawValues[posReal++];
                }
                posScan += offset;  //行扫描结束，要将目标位置指针移过那段“间隙”  
            }

            //// 用Marshal的Copy方法，将刚才得到的内存字节数组复制到BitmapData中  
            Marshal.Copy(pixelValues, 0, iptr, scanBytes);
            bmp.UnlockBits(bmpData);  // 解锁内存区域  

            //// 下面的代码是为了修改生成位图的索引表，从伪彩修改为灰度  
            ColorPalette tempPalette;
            using (Bitmap tempBmp = new Bitmap(1, 1, PixelFormat.Format8bppIndexed))
            {
                tempPalette = tempBmp.Palette;
            }
            for (int i = 0; i < 256; i++)
            {
                tempPalette.Entries[i] = Color.FromArgb(i, i, i);
            }

            bmp.Palette = tempPalette;

            //// 算法到此结束，返回结果  
            return bmp;
        }

        [DllImport("lineCalibrationDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern float findCalibartionRatio(byte[] data,int width,int height,int step, /*int index,*/ float phycialSize);
        static void Main(string[] args)
        {
            DirectoryInfo dir = new DirectoryInfo("E:\\work\\picture\\test");
            FileInfo[] fileInfo = dir.GetFiles();
            //List<string> fileNames = new List<string>();
            //int index = 0;
            foreach (FileInfo item in fileInfo)
            {
                Bitmap bmpobj = (Bitmap)Image.FromFile("E:\\work\\picture\\test\\" + item);
                BitMapInfo bi = bitmapToByteArray(bmpobj);
                float ratio = findCalibartionRatio(bi.Result, bmpobj.Width, bmpobj.Height, bi.Step, /*index++,*/ 300);
                Bitmap bitmap = byteToGrayBitmap(bi.Result, bmpobj.Width, bmpobj.Height);
                bmpobj.Dispose();  // 回收bitmap的内存
                bmpobj = null;
                bitmap.Save("bitmap.jpeg", ImageFormat.Jpeg);
                Console.Write("E:\\work\\picture\\test\\" + item.Name + ":");
                Console.WriteLine(ratio);
            }
            
        }
    }
}
