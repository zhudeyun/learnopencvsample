using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Emgu.CV;
using Emgu.CV.UI;

namespace HelloEmgu
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            

            InitializeComponent();


            
        }

        private void Form1_Load(object sender, EventArgs e)
        {
           

            ////创建一个显示窗口
            //CvInvoke.NamedWindow("Lena", Emgu.CV.CvEnum.NamedWindowType.AutoSize);
            ////显示图像
            //CvInvoke.Imshow("Lena", mat);

            ////等等按键输入
            //CvInvoke.WaitKey(0);
            ////销毁显示窗口
            //CvInvoke.DestroyWindow("Lena");

            ////释放资源
            //mat.Dispose();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            //从文件中读取图像
            var mat = new Mat("lena.jpg");
            imageBox1.Image = mat;
            //1.HistogramBox
            histogramBox1.GenerateHistograms(mat, 32);
            histogramBox1.Refresh();
            histogramBox1.Show();

            //2.使用HistogramViewer
            HistogramViewer.Show(mat, 32); //image[0] 顯示Blue,bin = 32
        }
    }
}
