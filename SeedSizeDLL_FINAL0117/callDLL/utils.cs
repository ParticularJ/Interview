using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;
using System.Drawing.Imaging;
using System.Runtime.InteropServices;


/* 图片转换为C#所需的格式*/
namespace callDLL
{
    class utils
    {
        public class BitMapInfo
        {
            public byte[] Result { get; set; }
            public int Step { get; set; }
        }
        /*
        获取bitmap的信息
        src:bitmap图
        flag: flag == 1时，为24位
              flag == 0时，位8位
             
        */
        public static BitMapInfo bitmapToByteArray(Bitmap src, int flag)
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
            byte[] realValues;
            int offset;
            if (flag == 1)
            {
                realValues = new byte[iHeight * iWidth * 3];
                offset = step - iWidth * 3;
            }
            else
            {
                realValues = new byte[iHeight * iWidth];
                offset = step - iWidth;
            }
            int realValuesIndex = 0;
            int pixelValuesIndex = 0;
            for (int i = 0; i < iHeight; i++)
            {
                for (int j = 0; j < iWidth; j++)
                {
                    if (flag == 1)
                    {
                        realValues[realValuesIndex++] = pixelValues[pixelValuesIndex++];
                        realValues[realValuesIndex++] = pixelValues[pixelValuesIndex++];
                        realValues[realValuesIndex++] = pixelValues[pixelValuesIndex++];
                    }
                    else
                        realValues[realValuesIndex++] = pixelValues[pixelValuesIndex++];
                }
                pixelValuesIndex += offset;
            }
            result = realValues;
            BitMapInfo bi;
            if (flag == 1)
                bi = new BitMapInfo { Result = result, Step = iWidth * 3 };
            else
                bi = new BitMapInfo { Result = result, Step = iWidth };
            return bi;
        }
    }
}
