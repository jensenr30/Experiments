using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Drawing;

namespace TestForm
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            //Application.EnableVisualStyles();
            //Application.SetCompatibleTextRenderingDefault(false);
            //Application.Run(new Form1());

            int width = 1280, height = 720;
            var gravMap = new Bitmap(width, height);
            int a = 255, r = 0, g = 0, b = 0;

            for(int x = 0; x < width; x++)
            {
                for (int y = 0; y < height; y++)
                {
                    r = (int)(128 + 127 * Math.Sin(2 * Math.PI * x / 30));
                    g = (int)(128 + 127 * Math.Sin(2 * Math.PI * y / 57));
                    b = (int)(128 + 127 * Math.Sin(2 * Math.PI * x * y / 10000));
                    gravMap.SetPixel(x, y, Color.FromArgb(a, r, g, b));
                }
            }


            Form form = new Form();
            form.Text = "Gravity Chaos Map";
            form.Height = height+50;
            form.Width = width+50;
            PictureBox pictureBox = new PictureBox();
            pictureBox.Image = gravMap;
            pictureBox.Dock = DockStyle.Fill;
            pictureBox.SizeMode = PictureBoxSizeMode.Normal;
            form.Controls.Add(pictureBox);
            Application.Run(form);
        }
    }
}
