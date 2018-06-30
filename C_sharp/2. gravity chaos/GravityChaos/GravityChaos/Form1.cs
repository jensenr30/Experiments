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
        // this is a list of all the particles we will use to make the gravity map
        private List<Particle> Particles;


        //------------------------------------------------------------------
        // Define bitmap size for rendering the image of gravity chaos
        //------------------------------------------------------------------
        int ImageHeight;
        int ImageWidth;
        // create new bitmap to which our image will be printed
        Bitmap Image;
        // x and y keep track of which pixel we are testing.
        // The pixels of the screen are evaluated from left to right, then
        // from top to bottom, like reading a book in english.
        int x;
        int y;
        int ScreenRefreshPeriodMs;


        //------------------------------------------------------------------
        // Define space for particles
        //------------------------------------------------------------------
        double AspectRatio;
        double SpaceHeight;
        double SpaceWidth;
        // calculates the scaling factor to translate between image space to particle space
        double ImageToParticleSpace(int pixel)
        {
            return (double)(pixel * SpaceHeight / ImageHeight);
        }


        //------------------------------------------------------------------
        // Add stationary particles that will act as targets
        //------------------------------------------------------------------
        double ParticleRadius;
        double ParticleMass;



        public Form1()
        {
            InitializeComponent();
            this.Particles = new List<Particle> { };


            //------------------------------------------------------------------
            // Define space for particles
            //------------------------------------------------------------------
            AspectRatio = 16.0 / 9.0;
            SpaceHeight = 720;
            SpaceWidth = SpaceHeight * AspectRatio;


            //------------------------------------------------------------------
            // Define bitmap size for rendering the image of gravity chaos
            //------------------------------------------------------------------
            ImageHeight = 1080;
            ImageWidth = (int)(ImageHeight * AspectRatio);
            // create new bitmap to which our image will be printed
            Image = new Bitmap(ImageWidth, ImageHeight);
            // x and y keep track of which pixel we are testing.
            // The pixels of the screen are evaluated from left to right, then
            // from top to bottom, like reading a book in english.
            x = 0;
            y = 0;
            ScreenRefreshPeriodMs = 250;


            //------------------------------------------------------------------
            // Add stationary particles that will act as targets
            //------------------------------------------------------------------
            ParticleRadius = SpaceHeight / 10.0;
            ParticleMass = Math.Pow(ParticleRadius, 2.0);


            //------------------------------------------------------------------
            // Add one particle that will be the projectile (free to move)
            //------------------------------------------------------------------
            this.Particles.Add(new Particle { Color = Color.White });


            

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


        // this timer happens every millisecond. This is my workaround to
        // always get control back to the map-generating routine.
        private void timer1_Tick(object sender, EventArgs e)
        {
            /*
            // record when you entered the loop
            DateTime TimeOfEntry = DateTime.Now;
            int ElapsedTimeMs;
            // work on the map
            do
            {
                // start the particle out at the current <x, y> coordinates
                Particles[0].PositionX = ImageToParticleSpace(x);
                Particles[0].PositionY = ImageToParticleSpace(y);
                // set the moving particle's initial velocity to 0.
                Particles[0].VelocityX = 0;
                Particles[0].VelocityY = 0;

                // run the simulation until the moving particle hits one of the stationary particles
                // have a timeout to prevent the programming from going in an endless loop
                bool collision = false;
                int iterations = 0, iterations_max = 10000;
                while((!collision) && (iterations < iterations_max))
                {
                    Particle.Update(Particles, .5);
                    Particle.CollisionCheckAll;
                    iterations++;
                }
                // depending on which target our moving particle hits, color the <x, y> pixel accordingly


                // increment x and y
                x++;
                // if you have gotten to the right edge of the bitmap,
                if (x >= ImageWidth)
                {
                    x = 0;
                    y++;
                }
                // if you have completed the image, close it.
                if (y >= ImageHeight)
                {
                    // TODO: save the image
                    // close the form
                    this.Close();
                }
                ElapsedTimeMs = (int)(DateTime.Now - TimeOfEntry).TotalMilliseconds;
            }
            // keep working on the map until you need to refresh the screen again
            while (0);//(ElapsedTimeMs < this.ScreenRefreshPeriodMs);
            */
            Particle.Update(Particles, 0.5);
            // force the screen to be redrawn
            Invalidate();
        }


        private void Form1_Load(object sender, EventArgs e)
        {

        }
    }
}
