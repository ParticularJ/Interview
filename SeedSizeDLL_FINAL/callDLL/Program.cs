using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;
using System.IO;
using System.Drawing;
using System.Drawing.Imaging;


namespace callDLL
{
    class Program
    {
        public class BitMapInfo
        {
            public byte[] Result { get; set; }
            public int Step { get; set; }
            public int Stride { get; set; }
        }
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
                bi = new BitMapInfo { Result = result, Step = iWidth * 3 , Stride = step};
            else
                bi = new BitMapInfo { Result = result, Step = iWidth, Stride = step };
            return bi;
        }


        static void Main(string[] args)
        {
           
            Bitmap bmpobj_src = (Bitmap)Image.FromFile("D:\\Myself\\Dataset\\Rice\\E3.jpg");
            Bitmap bmpobj_dst = (Bitmap)Image.FromFile("D:\\Myself\\Dataset\\seed\\D3.jpg");
            int width = bmpobj_dst.Width;
            int height = bmpobj_dst.Height;

            BitMapInfo bi_src = bitmapToByteArray(bmpobj_src, 0);
            BitMapInfo bi_dst = bitmapToByteArray(bmpobj_dst, 1);


            byte[] pfinal_pic = new byte[width*height*4];

            int res = callAPI.getImage(bi_src.Result, bmpobj_src.Width, bmpobj_src.Height, bi_src.Step, bi_dst.Result, bmpobj_dst.Width, bmpobj_dst.Height, bi_dst.Step, pfinal_pic);
      

      
            GCHandle hObject = GCHandle.Alloc(pfinal_pic, GCHandleType.Pinned);
            IntPtr pBGRAData = hObject.AddrOfPinnedObject();
            Bitmap SeedSizeImg = new Bitmap(width, height, width * 4, PixelFormat.Format32bppArgb, pBGRAData);
            if (hObject.IsAllocated)
                hObject.Free();
            SeedSizeImg.Save("D:\\Myself\\Dataset\\7.jpg", System.Drawing.Imaging.ImageFormat.Jpeg);
            bmpobj_src.Dispose();  // 回收bitmap的内存
            bmpobj_dst.Dispose();
            bmpobj_src = null;
            bmpobj_dst = null;
        }
    }
}
