using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;
using System.Drawing;
using System.Drawing.Imaging;

namespace cSharpGetDll
{
    //[StructLayout(LayoutKind.Sequential)]
    //public struct sPointApi
    //{
    //    public int x;
    //    public int y;
    //}
    //[StructLayout(LayoutKind.Sequential)]
    //public struct SOneSeedDataApi
    //{
    //    //有效种子为true
    //    public int seedFlag;
    //    //有凸尖为true
    //    public int plumuleFlag;
    //    //中心
    //    //public sPointApi centerPt;
    //    public Point centerPt;
    //    //圆中心最远点
    //    public Point maxDistPt;
    //    //角点1
    //    public Point pt1;
    //    //角点2
    //    public Point pt2;
    //    //角点3
    //    public Point pt3;
    //    //角点4
    //    public Point pt4;  
    //    //该点轮廓大小
    //    public int cSize;
    //    //该点轮廓
    //    [MarshalAs(UnmanagedType.ByValArray, SizeConst = 50)] // 指定数组尺寸 
    //    public Point[] contour;    
    //}

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

    class cornSeedApi
    {


        //[DllImport("createDll.dll")]
        //public static extern int Add(int x, int y);
        //[DllImport("createDll.dll")]
        //public static extern int Sub(int x, int y);
        //[DllImport("createDll.dll", EntryPoint = "Obitmap2Mat", CallingConvention = CallingConvention.Cdecl)]
        //public static extern int Obitmap2Mat(IntPtr ImageBuffer, int width, int height);
        //[DllImport("createDll.dll", EntryPoint = "Omat2Bitmap")]
        //public static extern IntPtr Omat2Bitmap(ref int width, ref int height);

        // 种子大小排序
        [DllImport("SEEDSIZEDLL.dll", EntryPoint = "_getImage@28", CharSet = CharSet.Auto)]
        public static extern int getImage(int seedNum, byte[] dst_data, int dst_width, int dst_height, int dst_step, byte[] pfinal_pic, IntPtr SeedDataArr_out);


        //二值化接口
        [DllImport("createDll.dll", EntryPoint = "color2binary")]
        public static extern int color2binary(IntPtr src_in, int width_in, int height_in, float thresh_in, byte[] binary_out);
        //反色
        [DllImport("createDll.dll", EntryPoint = "reverseBinary")]
        public static extern int reverseBinary(IntPtr src_in, int width_in, int height_in, byte[] binary_out);
        //缩放
        [DllImport("createDll.dll", EntryPoint = "resizeImage")]
        public static extern int resizeImage(IntPtr src_in, int width_in, int height_in, int widthR_in, int heightR_in, byte[] src_out);
        //计数
        [DllImport("createDll.dll", EntryPoint = "calculateSeedData")]
        public static extern int calculateSeedData(IntPtr src_in, int width_in, int height_in, IntPtr SeedInfoArr_out, ref int arrlen_out, float thresh_in = 15.0f, int reverse_in = 0);
        //合并
        [DllImport("createDll.dll", EntryPoint = "mergeSeed")]
        public static extern int mergeSeed(ref Point pt1_in,ref Point pt2_in, IntPtr SeedInfoArr_out, ref int arrlen_out);
        //分离
        [DllImport("createDll.dll", EntryPoint = "separateSeed")]
        public static extern int separateSeed(ref Point pt1_in, ref Point pt2_in, IntPtr SeedInfoArr_out, ref int arrlen_out);
        //胚尖转换胚尖的有效性
        [DllImport("createDll.dll", EntryPoint = "convertPlumule")]
        public static extern int convertPlumule(ref Point mptStart_in, IntPtr SeedInfoArr_out, ref int arrlen_out);
        //转换种子的有效性
        [DllImport("createDll.dll", EntryPoint = "convertSeed")]
        public static extern int convertSeed(ref Point mptStart_in, IntPtr SeedInfoArr_out, ref int arrlen_out);
        //定位种子，返回种子序号
        [DllImport("createDll.dll", EntryPoint = "FindSeedNumber")]
        public static extern int FindSeedNumber(ref Point mptStart_in, ref int number_out);
        //旋转种子外面的rect方向
        [DllImport("createDll.dll", EntryPoint = "ChangeSeedPlumule")]
        public static extern int ChangeSeedPlumule(ref Point mptEnd_in, int Number_in, IntPtr SeedInfoArr_out,  ref int arrlen_out);
        //撤销与重复 flag_in -1撤销，1重复
        [DllImport("createDll.dll", EntryPoint = "seedRevokeRepeat")]
        public static extern int seedRevokeRepeat(IntPtr SeedInfoArr_out, ref int arrlen_out, int flag_in);
        //设置图片数据映射真实数据的比例
        [DllImport("createDll.dll", EntryPoint = "seedSetRatio")]
        public static extern int seedSetRatio(float flag_in);
        //选择种子 //种子类别 1玉米，大豆 ；2小麦；3：水稻
        [DllImport("createDll.dll", EntryPoint = "seedSetChoose")]
        public static extern int seedSetChoose(int Choose_in);
        //获得分割后的二值图
        [DllImport("createDll.dll", EntryPoint = "getSeedBinary")]
        public static extern int getSeedBinary(int width_in, int height_in, byte[] binary_out);

        //将参数计数成用户需要参数
        // [DllImport("createDll.dll", EntryPoint = "seedData2Result")]
        // public static extern int seedData2Result(IntPtr SeedDataArr_in, int arrlen_in, IntPtr SeedInfoArr_out, float ratio_in);


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
            public static int cornseed()
        {
            //int r1 = DllApi.Add(3, 2);
            //int r2 = DllApi.Sub(5, 2);
            //Console.WriteLine("test01结果：" + r1.ToString());
            //Console.WriteLine("test02结果：" + r2.ToString());
            //Console.ReadKey();
            //Bitmap bmp = (Bitmap)Image.FromFile("G:\\17_玉米考种\\7_CshapGetCDll\\2_测试图\\1.jpg");
            //Rectangle rect = new Rectangle(0, 0, bmp.Width, bmp.Height);
            //BitmapData bmpData = bmp.LockBits(rect, ImageLockMode.ReadWrite, PixelFormat.Format32bppArgb);//Format32ppRgb
            //int width = bmp.Width;
            //int height = bmp.Height;
            //------------------图片从c#传给C++  --------------------------
            //DllApi.Obitmap2Mat(bmpData.Scan0, bmp.Width, bmp.Height);
            // Unlock the bits.
            //--------------------------图片从c++传给C#--------------------------
            //IntPtr ImageBuffer = DllApi.Omat2Bitmap(ref width, ref height);
            //Bitmap mat2bmp = new Bitmap(width, height, width * 4, PixelFormat.Format32bppArgb, ImageBuffer);
            //mat2bmp.Save("G:\\17_玉米考种\\7_CshapGetCDll\\2_测试图\\5.jpg", System.Drawing.Imaging.ImageFormat.Jpeg);

            //散粒图像参数向真实参数映射
            cornSeedApi.seedSetRatio(2.0f*25.4f / 300.0f);
            //设置种子类型
            cornSeedApi.seedSetChoose(3);// 1代表玉米粒 2代表小麦

            //  Bitmap bmp = (Bitmap)Image.FromFile("G:\\17_玉米考种\\7_CshapGetCDll\\2_测试图\\原图\\TMP0017.jpg");
            Bitmap bmp = (Bitmap)Image.FromFile("D:\\Myself\\Dataset\\20190121\\20190121\\D2.jpg");
            utils.BitMapInfo bi_dst = utils.bitmapToByteArray(bmp, 1);
            Rectangle rect = new Rectangle(0, 0, bmp.Width, bmp.Height);
            BitmapData bmpData = bmp.LockBits(rect, ImageLockMode.ReadWrite, PixelFormat.Format32bppArgb);//Format32ppRgb
            int width = bmp.Width;
            int height = bmp.Height;
            //--------------------- 1 color2binary-------------------------------
            float thresh_in = 80.0f;
            byte[] BGRAData = new byte[width * height * 4];
            //二值化
            int ret = cornSeedApi.color2binary(bmpData.Scan0, bmp.Width, bmp.Height, thresh_in, BGRAData);
            if (ret == 0)
            {
                return 0;
            }
            GCHandle hObject = GCHandle.Alloc(BGRAData, GCHandleType.Pinned);
            IntPtr pBGRAData = hObject.AddrOfPinnedObject();
            Bitmap binaryImg = new Bitmap(width, height, width * 4, PixelFormat.Format32bppArgb, pBGRAData);
            if (hObject.IsAllocated)
                hObject.Free();
       //     binaryImg.Save("7.jpg", System.Drawing.Imaging.ImageFormat.Jpeg);

            //--------------------- 2 反色-------------------------------

            Rectangle rect2 = new Rectangle(0, 0, binaryImg.Width, binaryImg.Height);
            BitmapData bmpData2 = binaryImg.LockBits(rect, ImageLockMode.ReadWrite, PixelFormat.Format32bppArgb);//Format32ppRgb

            byte[] binary_out2 = new byte[width * height * 4];
            //反色
            ret = cornSeedApi.reverseBinary(bmpData2.Scan0, bmpData2.Width, bmpData2.Height, binary_out2);
            if (ret == 0)
            {
                return 0;
            }
            GCHandle hObject2 = GCHandle.Alloc(binary_out2, GCHandleType.Pinned);
            IntPtr pBGRAData2 = hObject2.AddrOfPinnedObject();
            Bitmap binaryImg2 = new Bitmap(width, height, width * 4, PixelFormat.Format32bppArgb, pBGRAData2);
            if (hObject.IsAllocated)
                hObject.Free();
       //    binaryImg2.Save("8.jpg", System.Drawing.Imaging.ImageFormat.Jpeg);

            //--------------------------------------缩放----------------------------- 
            float mresize = 0.5f;
            int widthR_in = (int)(mresize * (float)bmp.Width);
            int heightR_in = (int)(mresize * (float)bmp.Height);
            byte[] src3_out = new byte[widthR_in * heightR_in * 4];

            resizeImage(bmpData.Scan0, bmp.Width, bmp.Height, widthR_in, heightR_in, src3_out);

            GCHandle hObject3 = GCHandle.Alloc(src3_out, GCHandleType.Pinned);
            IntPtr pBGRAData3 = hObject3.AddrOfPinnedObject();
            Bitmap srcImg3 = new Bitmap(widthR_in, heightR_in, widthR_in * 4, PixelFormat.Format32bppArgb, pBGRAData3);
            if (hObject.IsAllocated)
                hObject.Free();
         //   srcImg3.Save("9.jpg", System.Drawing.Imaging.ImageFormat.Jpeg);

            //--------------------------------------计数----------------------------- 

            int msize = Marshal.SizeOf(typeof(sOneSeedInfoApi)) * 2000;
            IntPtr SeedDataArr_out = Marshal.AllocHGlobal(msize); // 直接分配2000个元素的空间,保存计数参数  

            // thresh_in = 30.0f;
            // thresh_in = 80.0f;
            int arrlen_out = 0;
            int reverse_in = 1;
            //计数
            ret = cornSeedApi.calculateSeedData(bmpData.Scan0, bmp.Width, bmp.Height, SeedDataArr_out, ref arrlen_out, thresh_in, reverse_in);
            if (ret == 0)
            {
                return 0;
            }

            //获取参数
            //      sOneSeedInfoApi[] pClass = new sOneSeedInfoApi[arrlen_out];
            //      for (int i = 0; i < arrlen_out; i++)
            //     {
            //         IntPtr ptr = new IntPtr(SeedDataArr_out.ToInt64() + Marshal.SizeOf(typeof(sOneSeedInfoApi)) * i);
            //        pClass[i] = (sOneSeedInfoApi)Marshal.PtrToStructure(ptr, typeof(sOneSeedInfoApi));

            //       Console.WriteLine(pClass[i].ID);

            //  }

            // ------------------种子排序-------------------------------

            
                Console.WriteLine(1);
                int final_width = 3469;
                int final_height = 2518;
                byte[] pfinal_pic = new byte[final_width * final_height * 4];
                int res = cornSeedApi.getImage(20, bi_dst.Result, bmp.Width, bmp.Height, bi_dst.Step, pfinal_pic, SeedDataArr_out);


                // 获得图片所需空间，并保存至本地
                GCHandle hObject1 = GCHandle.Alloc(pfinal_pic, GCHandleType.Pinned);
                IntPtr pBGRAData1 = hObject1.AddrOfPinnedObject();
                Bitmap SeedSizeImg = new Bitmap(final_width, final_height, final_width * 4, PixelFormat.Format32bppArgb, pBGRAData1);
                if (hObject1.IsAllocated)
                    hObject1.Free();
                SeedSizeImg.Save("D://Myself//Dataset//20190121//final//F2_20_2.jpg", System.Drawing.Imaging.ImageFormat.Jpeg);
                Console.WriteLine(2);
            Marshal.FreeHGlobal(SeedDataArr_out); // 释放内存
            return 0;
            
            //--------------------------合并------------------------------
            IntPtr SeedDataArr_out5 = Marshal.AllocHGlobal(msize); // 直接分配2000个元素的空间,保存计数参数  
            int arrlen5 = 0;
            Point pt1 = new Point();
            Point pt2 = new Point();

            pt1.X = 0;
            pt1.Y = 0;
            pt2.X = width;
            pt2.Y = height;
            //合并
            ret = cornSeedApi.mergeSeed( ref pt1, ref pt2, SeedDataArr_out5, ref arrlen5);
            if (ret == 0)
            {
                return 0;
            }
            //获取参数
            sOneSeedInfoApi[] pbinarydata5 = new sOneSeedInfoApi[arrlen5];
            for (int i = 0; i < arrlen5; i++)
            {
                IntPtr ptr = new IntPtr(SeedDataArr_out5.ToInt64() + Marshal.SizeOf(typeof(sOneSeedInfoApi)) * i);
                pbinarydata5[i] = (sOneSeedInfoApi)Marshal.PtrToStructure(ptr, typeof(sOneSeedInfoApi));
            }
            Marshal.FreeHGlobal(SeedDataArr_out5); // 释放内存  
            //--------------------------分离------------------------------
            IntPtr SeedDataArr_out6 = Marshal.AllocHGlobal(msize); // 直接分配3000个元素的空间,保存计数参数  

            int arrlen6 = 0;

            pt1.X = 0;
            pt1.Y = height;
            pt2.X = width;
            pt2.Y = 0;
            //分离
            ret = cornSeedApi.separateSeed(ref pt1, ref pt2, SeedDataArr_out6, ref arrlen6);
            if (ret == 0)
            {
                return 0;
            }
            //获取参数
            sOneSeedInfoApi[] pbinarydata6 = new sOneSeedInfoApi[arrlen6];
            for (int i = 0; i < arrlen6; i++)
            {
                IntPtr ptr = new IntPtr(SeedDataArr_out6.ToInt64() + Marshal.SizeOf(typeof(sOneSeedInfoApi)) * i);
                pbinarydata6[i] = (sOneSeedInfoApi)Marshal.PtrToStructure(ptr, typeof(sOneSeedInfoApi));
            }
            Marshal.FreeHGlobal(SeedDataArr_out6); // 释放内存  
           

            //-----------------------------------转换胚尖的有效性-------------------------------------
            IntPtr SeedDataArr_out7 = Marshal.AllocHGlobal(msize);
            int arrlen7 = 0;
            pt1.X = pbinarydata6[70].centerPt.X;
            pt1.Y = pbinarydata6[70].centerPt.Y;
            ret = cornSeedApi.convertPlumule(ref pt1, SeedDataArr_out7, ref arrlen7);
            //获取参数
            sOneSeedInfoApi[] pbinarydata7 = new sOneSeedInfoApi[arrlen7];
            for (int i = 0; i < arrlen7; i++)
            {
                IntPtr ptr = new IntPtr(SeedDataArr_out7.ToInt64() + Marshal.SizeOf(typeof(sOneSeedInfoApi)) * i);
                pbinarydata7[i] = (sOneSeedInfoApi)Marshal.PtrToStructure(ptr, typeof(sOneSeedInfoApi));
            }
             Marshal.FreeHGlobal(SeedDataArr_out7); // 释放内存

            //-----------------------------------转换种子的有效性-------------------------------------
            IntPtr SeedDataArr_out8 = Marshal.AllocHGlobal(msize);
            int arrlen8 = 0;
            pt1.X = pbinarydata6[20].centerPt.X;
            pt1.Y = pbinarydata6[20].centerPt.Y;
            ret = cornSeedApi.convertSeed(ref pt1, SeedDataArr_out8, ref arrlen8);
            if (ret == 0)
            {
                return 0;
            }
            //获取参数
            sOneSeedInfoApi[] pbinarydata8 = new sOneSeedInfoApi[arrlen8];
            for (int i = 0; i < arrlen8; i++)
            {
                IntPtr ptr = new IntPtr(SeedDataArr_out8.ToInt64() + Marshal.SizeOf(typeof(sOneSeedInfoApi)) * i);
                pbinarydata8[i] = (sOneSeedInfoApi)Marshal.PtrToStructure(ptr, typeof(sOneSeedInfoApi));
            }
            Marshal.FreeHGlobal(SeedDataArr_out8); // 释放内存
            //-----------------------------------找种子 返回种子序号-------------------------------------
            pt1.X = pbinarydata6[50].maxDistPt.X;
            pt1.Y = pbinarydata6[50].maxDistPt.Y;
            int number9 = -1;
            ret = cornSeedApi.FindSeedNumber(ref pt1, ref number9);
            
            if (ret == 0)
            {
                return 0;
            }

            //-----------------------------------旋转种子rect的方向-------------------------------------
            IntPtr SeedDataArr_out9 = Marshal.AllocHGlobal(msize); // 直接分配3000个元素的空间,保存计数参数  
            int arrlen9 = 0;
            pt2.X = width;
            pt2.Y = height;
            //旋转
            ret = cornSeedApi.ChangeSeedPlumule(ref pt2, number9, SeedDataArr_out9, ref arrlen9);
            //获取参数
            sOneSeedInfoApi[] pbinarydata9 = new sOneSeedInfoApi[arrlen6];
            for (int i = 0; i < arrlen9; i++)
            {
                IntPtr ptr = new IntPtr(SeedDataArr_out9.ToInt64() + Marshal.SizeOf(typeof(sOneSeedInfoApi)) * i);
                pbinarydata9[i] = (sOneSeedInfoApi)Marshal.PtrToStructure(ptr, typeof(sOneSeedInfoApi));
            }
            Marshal.FreeHGlobal(SeedDataArr_out9); // 释放内存

            //-----------撤销与重复------------------
            IntPtr SeedDataArr_out10 = Marshal.AllocHGlobal(msize); // 直接分配2000个元素的空间,保存计数参数  
            int arrlen_out10 = 0;
            //撤销与重复 flag_in -1撤销，1重复
            ret = seedRevokeRepeat(SeedDataArr_out10, ref arrlen_out10, -1);
            ret = seedRevokeRepeat(SeedDataArr_out10, ref arrlen_out10, 1);
            if (ret == 0)
            {
                return 0;
            }
            //获取参数
            sOneSeedInfoApi[] pClass10 = new sOneSeedInfoApi[arrlen_out10];
            for (int i = 0; i < arrlen_out10; i++)
            {
                IntPtr ptr = new IntPtr(SeedDataArr_out10.ToInt64() + Marshal.SizeOf(typeof(sOneSeedInfoApi)) * i);
                pClass10[i] = (sOneSeedInfoApi)Marshal.PtrToStructure(ptr, typeof(sOneSeedInfoApi));
            }
            Marshal.FreeHGlobal(SeedDataArr_out10); //释放内存  


            //--------------------- 获得二值图-------------------------------
            byte[] binary_out11 = new byte[width * height * 4];
            //反色
            ret = cornSeedApi.getSeedBinary(width, height, binary_out11);
            if (ret == 0)
            {
                return 0;
            }
            GCHandle hObject11 = GCHandle.Alloc(binary_out11, GCHandleType.Pinned);
            IntPtr pBGRAData11 = hObject11.AddrOfPinnedObject();
            Bitmap binaryImg11 = new Bitmap(width, height, width * 4, PixelFormat.Format32bppArgb, pBGRAData11);
            if (hObject11.IsAllocated)
                hObject11.Free();
            binaryImg11.Save("11.jpg", System.Drawing.Imaging.ImageFormat.Jpeg);
            //int getSeedBinary(int width_in, int height_in, byte[] binary_out);
            return 0;
        }   
    }
}
