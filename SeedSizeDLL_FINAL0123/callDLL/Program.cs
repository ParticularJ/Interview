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
        [StructLayout(LayoutKind.Sequential)]
        struct sOneSeedInfoApi
        {
            //编号
            public int ID;
            //面积
            public float sArea;
            //周长
            public float sPerimeter;
            //长
            public float sLength;
            //宽
            public float sWide;
            //长/宽
            public float sL1Wratio;
            //增加RGB颜色参数
            int sR;
            int sG;
            int sB;

            //有效种子为true
            public int seedFlag;
            //有凸尖为true
            public int plumuleFlag;
            //中心
            public Point centerPt;
            //圆中心最远点
            public Point maxDistPt;
            //角点1
            public Point pt1;
            //角点2
            public Point pt2;
            //角点3
            public Point pt3;
            //角点4
            public Point pt4;
            //该点轮廓大小
            public int cSize;
            //该点轮廓
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 250)] // 指定数组尺寸 
            public Point[] contour;

        };

        static void Main(string[] args)
        {
            // 种子原图
            Bitmap bmpobj_dst = (Bitmap)Image.FromFile("D:\\Myself\\Dataset\\seed\\D5.jpg");
            // 图片的宽和高
            int width = bmpobj_dst.Width;
            int height = bmpobj_dst.Height;
            // 转化成位bitmap
            utils.BitMapInfo bi_dst = utils.bitmapToByteArray(bmpobj_dst, 1); 
            // 建立显示图片
            byte[] pfinal_pic = new byte[width*height*4];


            // 建立结构体所需内存大小

            int msize = Marshal.SizeOf(typeof(sOneSeedInfoApi)) * 2000;
            IntPtr SeedDataArr_out = Marshal.AllocHGlobal(msize); // 直接分配2000个元素的空间,保存计数参数 

            // 模拟struct
            sOneSeedInfoApi[] pClass = new sOneSeedInfoApi[2000];
            // 模拟struct

            int simu = callAPI.simuStr(SeedDataArr_out);
            int seedNum = 5;

           





            // 调用dll获取处理后的图片
            /*
             * seedNum : 统计种子数
             bi_src.Result: 二值图图片信息
             bi_src.width : 二值图图片的宽
             bi_src.height: 二值图图片的高

             bi_dst.Result: 原图片信息
             bi_dst.width : 原图片的宽
             bi_dst.height: 原图片的高
             
             pfinal_pic： 最终的显示图片  
             
             SeedDataArr_out : 种子的结构体信息         
             */
            int res = callAPI.getImage(seedNum, bi_dst.Result, bmpobj_dst.Width, bmpobj_dst.Height, bi_dst.Step, pfinal_pic, SeedDataArr_out);


            for (int i = 0; i < 10; i++)
            {
                IntPtr pPonitor = new IntPtr(SeedDataArr_out.ToInt64() + Marshal.SizeOf(typeof(sOneSeedInfoApi)) * i);
                pClass[i] = (sOneSeedInfoApi)Marshal.PtrToStructure(pPonitor, typeof(sOneSeedInfoApi));

                Console.WriteLine("barcode:{0}; num:{1}", pClass[i].sLength, pClass[i].sWide);

            }
            Marshal.FreeHGlobal(SeedDataArr_out);

            // 获得图片所需空间，并保存至本地
            GCHandle hObject = GCHandle.Alloc(pfinal_pic, GCHandleType.Pinned);
            IntPtr pBGRAData = hObject.AddrOfPinnedObject();
            Bitmap SeedSizeImg = new Bitmap(width, height, width * 4, PixelFormat.Format32bppArgb, pBGRAData);
            if (hObject.IsAllocated)
                hObject.Free();
            SeedSizeImg.Save(".//7.jpg", System.Drawing.Imaging.ImageFormat.Jpeg);

             // 回收bitmap的内存
            bmpobj_dst.Dispose();  
            bmpobj_dst = null;
        }
    }
}
