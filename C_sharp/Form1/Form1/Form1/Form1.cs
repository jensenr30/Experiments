using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using GravityChaos;


namespace Form1
{
    public partial class Form1 : Form
    {

        private int counter;
        private List<Particle> Particles;

        public Form1()
        {
            InitializeComponent();
            this.Width = 1280;
            this.Height = 720;
            this.counter = 0;
            //this.Particles = new List<Particle>
            //{
            //    new Particle { PositionX = 300, PositionY = 400, Mass = 100, VelocityX = +0, VelocityY = -1},
            //    new Particle { PositionX = 400, PositionY = 300, Mass = 100, VelocityX = +1, VelocityY = +0},
            //    new Particle { PositionX = 500, PositionY = 400, Mass = 100, VelocityX = +0, VelocityY = +1},
            //    new Particle { PositionX = 400, PositionY = 500, Mass = 100, VelocityX = -1, VelocityY = +0}
            //};

            double x = 1000;
            double y = 500;

            //this.Particles = new List<Particle>
            //{
            //    new Particle { PositionX = x, PositionY = y, Mass = 1000, Fixed = false},
            //};

            //double r, v, x_p, y_p, x_v, y_v;
            //for (int i = 0; i < 100; i++)
            //{
            //    r = 100 + 1 * i;
            //    v = 500 / Math.Pow(r, 2);
            //    x_p = r * Math.Cos(i * 2 * Math.PI / 7.34);
            //    y_p = r * Math.Sin(i * 2 * Math.PI / 7.34);

            //    x_v = -y_p * v;
            //    y_v = x_p * v;

            //    this.Particles.Add(new Particle { PositionX = x + x_p, PositionY = y + y_p, Mass = 10, VelocityX = x_v, VelocityY = y_v });
            //}

            this.Particles = new List<Particle>
            {
                //new Particle { PositionX = x, PositionY = y, Mass = 100*m, Fixed = false},
            };

            double r, v, x_p, y_p, x_v, y_v, m;
            Random random = new Random();
            for (int i = 0; i < 100; i++)
            {
                r = 200;
                v = 2;
                x_p = r * (random.Next(-1000, 1000) / 1000.0);
                y_p = r * (random.Next(-1000, 1000) / 1000.0);

                x_v = v * (random.Next(-1000, 1000) / 1000.0);
                y_v = v * (random.Next(-1000, 1000) / 1000.0);
                m = Math.Max(1,(10*random.Next(1, 1000) / 1000));

                this.Particles.Add(new Particle { PositionX = x + x_p, PositionY = y + y_p, Mass = m, VelocityX = x_v, VelocityY = y_v });
            }

            foreach (Particle p in Particles)
            {
                p.CalculateRadius();
            }

            this.DoubleBuffered = true;
        }


        private void Form1_Paint(object sender, PaintEventArgs e)
        {
            // draw the new position of the particles on the screen
            Particle.Draw(Particles, e.Graphics);
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            // force the screen to be updated
            // simulate where the particles will go, given their parameters
            Particle.Update(Particles, .5);

            Invalidate();
        }
    }
}
