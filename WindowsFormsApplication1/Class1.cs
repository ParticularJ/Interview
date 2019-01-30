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
        [DllImport("SEEDSIZEDLL.dll", EntryPoint = "_getImage@24", CharSet = CharSet.Auto)]
        public static extern int getImage(int seedNum, IntPtr dst_data, int dst_width, int dst_height, byte[] pfinal_pic, IntPtr SeedDataArr_out);


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
        public static extern int mergeSeed(ref Point pt1_in, ref Point pt2_in, IntPtr SeedInfoArr_out, ref int arrlen_out);
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
        public static extern int ChangeSeedPlumule(ref Point mptEnd_in, int Number_in, IntPtr SeedInfoArr_out, ref int arrlen_out);
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

        public Bitmap bmp = null;
        public IntPtr SeedDataArr_out;

        public int cornseed(string file)
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
            cornSeedApi.seedSetRatio(2.0f * 25.4f / 300.0f);
            //设置种子类型
            cornSeedApi.seedSetChoose(1);// 1代表玉米粒 2代表小麦

            //  Bitmap bmp = (Bitmap)Image.FromFile("G:\\17_玉米考种\\7_CshapGetCDll\\2_测试图\\原图\\TMP0017.jpg");"D:\\Myself\\Dataset\\20190121\\20190121\\D5.jpg"
            bmp = (Bitmap)Image.FromFile(file);
            //  utils.BitMapInfo bi_dst = utils.bitmapToByteArray(bmp, 1);
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
            SeedDataArr_out = Marshal.AllocHGlobal(msize); // 直接分配2000个元素的空间,保存计数参数  

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
            bmp.UnlockBits(bmpData);
            return 1;

        }
    }
}

