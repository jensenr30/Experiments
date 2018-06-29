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

        private List<Particle> Particles;

        public Form1()
        {
            InitializeComponent();
            this.Particles = new List<Particle> { };

            //------------------------------------------------------------------
            // Define space for particles
            //------------------------------------------------------------------
            double AspectRatio = 16.0 / 9.0;
            double SpaceHeight = 720;
            double SpaceWidth = SpaceHeight * AspectRatio;


            //------------------------------------------------------------------
            // Define bitmap size for rendering the image of gravity chaos
            //------------------------------------------------------------------
            int ImageHeight = 1080;
            int ImageWidth = (int)(ImageHeight * AspectRatio);
            // create new bitmap to which our image will be printed
            Bitmap Image = new Bitmap(ImageWidth, ImageHeight);


            //------------------------------------------------------------------
            // Add one particle that will be the projectile (free to move)
            //------------------------------------------------------------------
            this.Particles.Add(new Particle { Color = Color.White });


            //------------------------------------------------------------------
            // Add stationary particles that will act as targets
            //------------------------------------------------------------------
            double ParticleRadius = SpaceHeight / 10.0;
            double ParticleMass = Math.Pow(ParticleRadius, 2.0);

            // stationary particle 1
            this.Particles.Add(
                new Particle
                {
                    Color = Color.Red,
                    PositionX = SpaceWidth / 3.0,
                    PositionY = SpaceHeight / 2.0,
                    Fixed = true,
                    Mass = ParticleMass
                }
            );
            // stationary particle 2
            this.Particles.Add(
                new Particle
                {
                    Color = Color.Red,
                    PositionX = SpaceWidth * 2.0 / 3.0,
                    PositionY = SpaceHeight / 2.0,
                    Fixed = true,
                    Mass = ParticleMass
                }
            );


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

        private void Form1_Load(object sender, EventArgs e)
        {

        }
    }
}
