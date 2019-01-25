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
    [StructLayout(LayoutKind.Sequential)]
    struct seedRectPt
    {
        public Point upPt1;
        public Point upPt2;
        public Point downPt3;
        public Point downPt4;
        public float high;
    };
    [StructLayout(LayoutKind.Sequential)]
    struct ScornOneEarApi
    {
        //原图籽粒四角点坐标 Y列籽粒数
        public int sYArrLen;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 100)]
        public seedRectPt[] sOrignaleYRectArr;
        //原图籽粒四角点坐标 X籽粒行数
        public int sXArrLen;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 50)]
        public seedRectPt[] sOrignaleXRectArr;
        //胚尖四角点
        public seedRectPt sOrignaleTopRect;
        //穗缘角两两端点坐标
        public seedRectPt sOrignaleEageAnglePt;
        //果穗外界矩形四角点坐标
        public seedRectPt sRotatedrect;

        //---参数---
        //穗长
        public float sLength;
        //穗粗
        public float sDiameter;
        //穗缘角1
        public float sEageAngle1;
        //穗缘角2
        public float sEageAngle2;
        //颜色
        public float sB;
        public float sG;
        public float sR;
        //穗行角
        public float sRowAngle;
        //测量粒数
        public int sCountNumber;
        //平均粒高？？？
        public float sSeedHigh;
        //行粒数
        public int sRowSeedNumber;
        //穗行数
        public int sRowNumber;

    };
    class cornEarApi
    {
        //[DllImport("createDll.dll")]
        //public static extern int Add2(int x, int y);
        //自动一键分析接口
        [DllImport("createDll.dll")]
        public static extern int efcornEarProcess(IntPtr src_in, int width_in, int height_in, IntPtr EarDataArr_out, ref int arrlen_out, float thresh_in = 5.0f);
        //手动测量接口
        [DllImport("createDll.dll")]
        public static extern int efHandcornEarProcess(Point[] ptArr_in, int ptArrlen_in, IntPtr EarDataArr_out, ref int arrlen_out);
        //------移动 X Y方向分割线---------------------
        [DllImport("createDll.dll")]
        public static extern int efMoveEarXYLineProcess(ref Point pt1_in, ref Point pt2_in, IntPtr EarDataArr_out, ref int arrlen_out);
        //添加和删除短线flag_in==1是添加，flag_in==0为删除
        [DllImport("createDll.dll")]
        public static extern int efAddDeleteEarXYLineProcess(ref Point pt1_in, ref Point pt2_in, IntPtr EarDataArr_out, ref int arrlen_out,int flag_in=1);

        //撤销与重复 flag_in -1撤销，1重复,其他数不变
        [DllImport("createDll.dll")]
        public static extern int efRevokeRepeat(IntPtr SeedDataApi_out, ref int arrlen_out, int flag_in = 0);
        //图参数向真实参数的映射比例
        [DllImport("createDll.dll")]
        public static extern int efSetRatio(float flag_in);
        //点击指定果穗
        [DllImport("createDll.dll")]
        public static extern int efFindCornEar(ref Point pt_in, ref int number_out);
        public static int cornEar()
        {
            //int r1 = cornEarApi.Add2(12, 2);

            //散粒图像参数向真实参数映射
            cornEarApi.efSetRatio(2.0f * 25.4f / 300.0f);


            //读取图
            // Bitmap bmp = (Bitmap)Image.FromFile("G:\\17_玉米考种\\7_CshapGetCDll\\2_测试图\\原图\\02.png");
            Bitmap bmp = (Bitmap)Image.FromFile("D://Myself//Dataset//20190121//20190121//D5.jpg");
            Rectangle rect = new Rectangle(0, 0, bmp.Width, bmp.Height);
            BitmapData bmpData = bmp.LockBits(rect, ImageLockMode.ReadWrite, PixelFormat.Format32bppArgb);//Format32ppRgb

             //----------自动执行分析接口  处理玉米穗函数--------------
            int size1 = Marshal.SizeOf(typeof(ScornOneEarApi)) * 50;
            IntPtr earDataArr_out = Marshal.AllocHGlobal(size1); // 分配50个元素的空间,即最大玉米穗个数  
            float thresh_in = 5.0f;
            int arrlen_out = 0;
            int ret = cornEarApi.efcornEarProcess(bmpData.Scan0, bmp.Width, bmp.Height, earDataArr_out, ref arrlen_out, thresh_in);
            if (ret == 0)
            {
                return 0;
            }
            //获取参数
            ScornOneEarApi[] pClass = new ScornOneEarApi[arrlen_out];
            for (int i = 0; i < arrlen_out; i++)
            {
                IntPtr ptr = new IntPtr(earDataArr_out.ToInt64() + Marshal.SizeOf(typeof(ScornOneEarApi)) * i);
                pClass[i] = (ScornOneEarApi)Marshal.PtrToStructure(ptr, typeof(ScornOneEarApi));
            }
            Marshal.FreeHGlobal(earDataArr_out); // 释放内存  

            //---------手动测量接口-------------------
            int size2 = Marshal.SizeOf(typeof(ScornOneEarApi)) * 50;
            IntPtr EarDataArr_out2 = Marshal.AllocHGlobal(size2); // 分配50个元素的空间,即最大玉米穗个数  

            Point[] ptArr_in = new Point[4];
            ptArr_in[0] = new Point(330, 270);
            ptArr_in[1] = new Point(500, 350);
            ptArr_in[2] = new Point(620, 236);
            ptArr_in[3] = new Point(950, 245);
      
            int ptArrlen_in2 = 4;
            int arrlen_out2 = 0;

            ret = cornEarApi.efHandcornEarProcess(ptArr_in, ptArrlen_in2, EarDataArr_out2, ref arrlen_out2);
            if (ret == 0)
            {
                return 0;
            }
            //获取参数
            ScornOneEarApi[] pClass2 = new ScornOneEarApi[arrlen_out2];
            for (int i = 0; i < arrlen_out2; i++)
            {
                IntPtr ptr = new IntPtr(EarDataArr_out2.ToInt64() + Marshal.SizeOf(typeof(ScornOneEarApi)) * i);
                pClass2[i] = (ScornOneEarApi)Marshal.PtrToStructure(ptr, typeof(ScornOneEarApi));
            }
            Marshal.FreeHGlobal(EarDataArr_out2); // 释放内存  

            //---------移动分割线接口-------------------
            int size3 = Marshal.SizeOf(typeof(ScornOneEarApi)) * 50;
            IntPtr EarDataArr_out3 = Marshal.AllocHGlobal(size3); // 分配50个元素的空间,即最大玉米穗个数  
            Point pt1_in = new Point(175,651);
            Point pt2_in = new Point(150,653);
            int arrlen_out3 = 0;
            ret = cornEarApi.efMoveEarXYLineProcess(ref pt1_in, ref pt2_in, EarDataArr_out3, ref arrlen_out3);
            if (ret == 0)
            {
                return 0;
            }
            //获取参数
            ScornOneEarApi[] pClass3 = new ScornOneEarApi[arrlen_out3];
            for (int i = 0; i < arrlen_out3; i++)
            {
                IntPtr ptr = new IntPtr(EarDataArr_out3.ToInt64() + Marshal.SizeOf(typeof(ScornOneEarApi)) * i);
                pClass3[i] = (ScornOneEarApi)Marshal.PtrToStructure(ptr, typeof(ScornOneEarApi));
            }
            Marshal.FreeHGlobal(EarDataArr_out3); // 释放内存  

            //---------增加或删除分割线接口-------------------
            int size4 = Marshal.SizeOf(typeof(ScornOneEarApi)) * 50;
            IntPtr EarDataArr_out4 = Marshal.AllocHGlobal(size4); // 分配50个元素的空间,即最大玉米穗个数  
            Point pt1_in4 = new Point(397, 369);
            Point pt2_in4 = new Point(424, 371);
            int arrlen_out4 = 0;
            //添加和删除短线flag_in==1是添加，flag_in==0为删除
            ret = cornEarApi.efAddDeleteEarXYLineProcess(ref pt1_in4, ref pt2_in4, EarDataArr_out4, ref arrlen_out4,0);
            if (ret == 0)
            {
                return 0;
            }
            //获取参数
            ScornOneEarApi[] pClass4 = new ScornOneEarApi[arrlen_out4];
            for (int i = 0; i < arrlen_out4; i++)
            {
                IntPtr ptr = new IntPtr(EarDataArr_out4.ToInt64() + Marshal.SizeOf(typeof(ScornOneEarApi)) * i);
                pClass4[i] = (ScornOneEarApi)Marshal.PtrToStructure(ptr, typeof(ScornOneEarApi));
            }
            Marshal.FreeHGlobal(EarDataArr_out4); // 释放内存  

            //-----------撤销与重复------------------
            int size5 = Marshal.SizeOf(typeof(ScornOneEarApi)) * 50;
            IntPtr EarDataArr_out5 = Marshal.AllocHGlobal(size4); // 分配50个元素的空间,即最大玉米穗个数  
            int arrlen_out5 = 0;
            //撤销与重复 flag_in -1撤销，1重复
            ret = cornEarApi.efRevokeRepeat(EarDataArr_out5, ref arrlen_out5, -1);
            ret = cornEarApi.efRevokeRepeat(EarDataArr_out5, ref arrlen_out5, 1);
            if (ret == 0)
            {
                return 0;
            }
            //获取参数
            ScornOneEarApi[] pClass5 = new ScornOneEarApi[arrlen_out5];
            for (int i = 0; i < arrlen_out5; i++)
            {
                IntPtr ptr = new IntPtr(EarDataArr_out5.ToInt64() + Marshal.SizeOf(typeof(ScornOneEarApi)) * i);
                pClass5[i] = (ScornOneEarApi)Marshal.PtrToStructure(ptr, typeof(ScornOneEarApi));
            }
            Marshal.FreeHGlobal(EarDataArr_out5); // 释放内存  

            //----------------------点击指定果穗---------------
            Point pt1_6 = new Point(397, 369);
            int number_out6 = -1;
            ret = cornEarApi.efFindCornEar(ref pt1_6, ref number_out6);

            return 1;
        }
    }
}
