using cSharpGetDll;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Imaging;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApplication1
{
    public partial class Form1 : Form
    {
        cornSeedApi c1 = new cornSeedApi();
        public Form1()
        {
            InitializeComponent();
            count();
        }

        private void count()
        {            
            c1.cornseed("D:\\Myself\\Dataset\\20190121\\20190121\\D0.jpg");

         //   c1
        }

        private void action()
        {
            /*
             * 
             seedNum : 统计种子数
             bi_dst.Result: 原图片信息
             bi_dst.width : 原图片的宽
             bi_dst.height: 原图片的高             
             pfinal_pic： 最终的显示图片               
             SeedDataArr_out : 种子的结构体信息         
             */
            try
            {
                // Bitmap bmp = SEED_ACTION.m_doc.m_SourceBmp.Clone(new Rectangle(0, 0, SEED_ACTION.m_doc.m_SourceBmp.Width, SEED_ACTION.m_doc.m_SourceBmp.Height), SEED_ACTION.m_doc.m_SourceBmp.PixelFormat);
                Bitmap bmp = c1.bmp;
                int width = bmp.Width;
                int height = bmp.Height;

                int widthTmp = 3469;
                int heightTmp = 2518;

                byte[] pfinal_pic = new byte[widthTmp * heightTmp * 4];
                //BitMapInfo bi = AutoRatioApi.getImagePixel(bmp);
                /// int res = AutoRatioApi.getImage(int.Parse(cmbCount.Text), bi.Result, width, height, bi.Step, pfinal_pic, SEED_ACTION.SeedDataArrOut);

                Rectangle rect = new Rectangle(0, 0, width, height);
                BitmapData bmpData = bmp.LockBits(rect, ImageLockMode.ReadWrite, PixelFormat.Format32bppArgb);

                int res = cornSeedApi.getImage(int.Parse(comboBox1.Text), bmpData.Scan0, width, height, pfinal_pic, c1.SeedDataArr_out);
                if (res == -1)
                {
                    MessageBox.Show("对比失败");
                    return;
                }
                bmp.UnlockBits(bmpData);
                // 获得图片所需空间，并保存至本地
                GCHandle hObject = GCHandle.Alloc(pfinal_pic, GCHandleType.Pinned);
                IntPtr pBGRAData = hObject.AddrOfPinnedObject();
                Bitmap SeedSizeImg = new Bitmap(widthTmp, heightTmp, widthTmp * 4, PixelFormat.Format32bppArgb, pBGRAData);
                if (hObject.IsAllocated)
                    hObject.Free();
                SeedSizeImg.Save("end.bmp", ImageFormat.Bmp);
                // bmp.Dispose();
                SeedSizeImg.Dispose();

            }
            catch (Exception ex)
            {
                MessageBox.Show("种子对比失败");
                return;
            }

        }

        private void comboBox1_TextChanged(object sender, EventArgs e)
        {
            ComboBox control = (ComboBox)sender;
            if (control.Text.Trim().Equals(""))
            {
                return;
            }
            try
            {
                if (int.Parse(control.Text.Trim()) > 20 ||
                    int.Parse(control.Text.Trim()) < 1)
                {
                    return;
                }
            }
            catch (Exception ex)
            {
                return;
            }
            action();
        }
    }
}
