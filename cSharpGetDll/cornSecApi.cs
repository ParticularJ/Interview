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
    struct ScornOneSectionApi
    {
        //横截面中心
        Point center;
        //外界圆半径
        float radius;
        //外圈半径 胚载入线
        float CRadius1;
        //中圈半径 胚尖位置线
        float CRadius2;
        //内圈半径 轴线
        float CRadius3;

        //轴心色
        int sR;
        int sG;
        int sB;

        //籽粒中心
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 50)]
        Point[] seedCenterArr;
        //籽粒个数
        int sArrLen;

        //穗粗
        float sEarRadius;
        //轴粗
        float sRollerRadius;
        //粒长
        float sSeedlength;
        //粒宽
        float sSeedWidth;
    };
    class cornSecApi
    {
        [DllImport("createDll.dll")]
        public static extern int Add3(int x, int y);
        //一键执行
        [DllImport("createDll.dll")]
        public static extern int hfCornSectionProcessApi(IntPtr src_in, int width_in, int height_in, IntPtr SectionDataArr_out, ref int arrlen_out, float thresh_in = 45.0f);
        //添加籽粒
        [DllImport("createDll.dll")]
        public static extern int hfAddSeedApi(ref Point pt_in, IntPtr SectionDataArr_out, ref int arrlen_out);
        //减少籽粒
        [DllImport("createDll.dll")]
        public static extern int hfReduceSeedApi(ref Point pt_in, IntPtr SectionDataArr_out, ref int arrlen_out);
        //定位圈圈
        [DllImport("createDll.dll")]
        public static extern int hfFindCircleLineApi(ref Point pt_in, ref int i_out, ref int j_out);
        //缩放圈圈
        [DllImport("createDll.dll")]
        public static extern int hfResizeCircleApi(float scale_in, int i_in, int j_in, IntPtr SectionDataArr_out, ref int arrlen_out);

        //撤销与重复 flag_in 为 -1撤销 1重复 ，其他数不变
        [DllImport("createDll.dll")]
        public static extern int hfRevokeRepeat(IntPtr SectionDataArr_out, ref int arrlen_out, int flag_in = 0);
        //设置图片数据映射真实数据的比例
        [DllImport("createDll.dll", EntryPoint = "hfSetRatio")]
        public static extern int hfSetRatio(float flag_in);
        public static int cornSec()
        {
            //int r1 = cornSecApi.Add3(12, 2);

            //散粒图像参数向真实参数映射
            cornSecApi.hfSetRatio(2.0f * 25.4f / 300.0f);

            //读取图
            Bitmap bmp = (Bitmap)Image.FromFile("img.jpg");
            Rectangle rect = new Rectangle(0, 0, bmp.Width, bmp.Height);
            BitmapData bmpData = bmp.LockBits(rect, ImageLockMode.ReadWrite, PixelFormat.Format32bppArgb);//Format32ppRgb
            //bmp.Save("qqq.jpg", System.Drawing.Imaging.ImageFormat.Jpeg);
            //----------一键执行--------------
            int size1 = Marshal.SizeOf(typeof(ScornOneSectionApi)) * 100;
            IntPtr earDataArr_out = Marshal.AllocHGlobal(size1); 
            float thresh_in = 45.0f;
            int arrlen_out = 0;
            int ret = cornSecApi.hfCornSectionProcessApi(bmpData.Scan0, bmp.Width, bmp.Height, earDataArr_out, ref arrlen_out, thresh_in);
            if (ret == 0)
            {
                return 0;
            }
            //获取参数
            ScornOneSectionApi[] pClass = new ScornOneSectionApi[arrlen_out];
            for (int i = 0; i < arrlen_out; i++)
            {
                IntPtr ptr = new IntPtr(earDataArr_out.ToInt64() + Marshal.SizeOf(typeof(ScornOneSectionApi)) * i);
                pClass[i] = (ScornOneSectionApi)Marshal.PtrToStructure(ptr, typeof(ScornOneSectionApi));
            }
            Marshal.FreeHGlobal(earDataArr_out); // 释放内存 

            //----------添加籽粒--------------
            IntPtr earDataArr2 = Marshal.AllocHGlobal(size1);
            Point pt_in2 = new Point(478,938);
            int arrlen2 = 0;
            ret = cornSecApi.hfAddSeedApi(ref  pt_in2, earDataArr2, ref arrlen2);
            if (ret == 0)
            {
                return 0;
            }
            //获取参数
            ScornOneSectionApi[] pClass2 = new ScornOneSectionApi[arrlen2];
            for (int i = 0; i < arrlen2; i++)
            {
                IntPtr ptr = new IntPtr(earDataArr2.ToInt64() + Marshal.SizeOf(typeof(ScornOneSectionApi)) * i);
                pClass2[i] = (ScornOneSectionApi)Marshal.PtrToStructure(ptr, typeof(ScornOneSectionApi));
            }

            //----------删除籽粒--------------
            IntPtr earDataArr3= Marshal.AllocHGlobal(size1);
            Point pt_in3 = new Point(478, 938);
            int arrlen3 = 0;
            ret = cornSecApi.hfReduceSeedApi(ref pt_in3, earDataArr3, ref arrlen3);
            if (ret == 0)
            {
                return 0;
            }
            //获取参数
            ScornOneSectionApi[] pClass3 = new ScornOneSectionApi[arrlen3];
            for (int i = 0; i < arrlen3; i++)
            {
                IntPtr ptr = new IntPtr(earDataArr3.ToInt64() + Marshal.SizeOf(typeof(ScornOneSectionApi)) * i);
                pClass3[i] = (ScornOneSectionApi)Marshal.PtrToStructure(ptr, typeof(ScornOneSectionApi));
            }

            //----------定位圈圈--------------
            Point pt_in4 = new Point(478, 938);
            int i_out = -1;//第几个横截面
            int j_out = -1;//第几个圈圈
            ret = cornSecApi.hfFindCircleLineApi(ref pt_in4, ref i_out, ref j_out);
            if (ret == 0)
            {
                return 0;
            }
            //--------------缩放圈圈---------------
            IntPtr earDataArr5 = Marshal.AllocHGlobal(size1);
            int arrlen5 = 0;
            float scale5 = 1.02f;//缩放倍数
            int i_in5 = i_out;
            int j_in5 = j_out; 
            ret = cornSecApi.hfResizeCircleApi(scale5, i_in5, j_in5, earDataArr5, ref arrlen5);
            if (ret == 0)
            {
                return 0;
            }
            //获取参数
            ScornOneSectionApi[] pClass5 = new ScornOneSectionApi[arrlen5];
            for (int i = 0; i < arrlen3; i++)
            {
                IntPtr ptr = new IntPtr(earDataArr5.ToInt64() + Marshal.SizeOf(typeof(ScornOneSectionApi)) * i);
                pClass5[i] = (ScornOneSectionApi)Marshal.PtrToStructure(ptr, typeof(ScornOneSectionApi));
            }

            //撤销重复
            IntPtr earDataArr6 = Marshal.AllocHGlobal(size1);
            int arrlen6 = 0;
            ret = cornSecApi.hfRevokeRepeat(earDataArr6, ref arrlen6, -1);
            ret = cornSecApi.hfRevokeRepeat(earDataArr6, ref arrlen6, 1);
            if (ret == 0)
            {
                return 0;
            }
            //获取参数
            ScornOneSectionApi[] pClass6 = new ScornOneSectionApi[arrlen6];
            for (int i = 0; i < arrlen6; i++)
            {
                IntPtr ptr = new IntPtr(earDataArr6.ToInt64() + Marshal.SizeOf(typeof(ScornOneSectionApi)) * i);
                pClass6[i] = (ScornOneSectionApi)Marshal.PtrToStructure(ptr, typeof(ScornOneSectionApi));
            }
            return 1;
        }
    }
   
}
