using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace callDLL
{
    class callAPI
    {
        [DllImport("SEEDSIZEDLL.dll", EntryPoint = "_getImage@36", CharSet = CharSet.Auto)]
        public static extern int getImage(byte[] src_data, int src_width, int src_height, int src_step, byte[] dst_data, int dst_width, int dst_height, int dst_step, byte[] pfinal_pic);
    }
}
