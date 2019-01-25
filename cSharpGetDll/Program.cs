using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;
using System.Drawing.Imaging;
using System.Runtime.InteropServices;

namespace cSharpGetDll
{
    class Program
    {
        static void Main(string[] args)
        {
            //散粒计数
           cornSeedApi.cornseed();
            //果穗测量
            //cornEarApi.cornEar();
            //横截面测量
            //cornSecApi.cornSec();
        }
    }
}
