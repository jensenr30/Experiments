using System;
using System.Linq;
using System.Collections.Generic;
using System.Drawing;

namespace GravityChaos
{
    class Particle
    {
        // define parameters of the particle        // units
        public double PositionX     { get; set; }   // meters
        public double PositionY     { get; set; }   // meters
        public double VelocityX     { get; set; }   // meters / second
        public double VelocityY     { get; set; }   // meters / second
        public double ForceX        { get; set; }   // newtons (kg * m / s^2)
        public double ForceY        { get; set; }   // newtons (kg * m / s^2)
        public double Mass          { get; set; }   // kilograms
        public double Radius        { get; set; }   // meters
        public bool   Fixed         { get; set; }   // true/false. A fixed particle does not move.
        public Color  Color         { get; set; }   // the color of the particle.
        private bool DeleteMe       { get; set; }   // indicates whether or not the particle should be removed from the simulation.

        // for simplicity, I normalize the gravitational constant to 1.
        public const double G = 1;

        // when you create a new Particle, these are the default values of the member variables.
        public Particle()
        {
            this.PositionX = 0;
            this.PositionY = 0;
            this.VelocityX = 0;
            this.VelocityY = 0;
            this.ForceX = 0;
            this.ForceY = 0;
            this.Mass = 1;
            this.Radius = 5;
            this.Fixed = false;
            this.Color = Color.Black;
            this.DeleteMe = false;
        }


        //======================================================================
        // calculates and updates the velocity and position of each of the [Particles].
        // [Time] (in seconds) can be either positive or negative. If [Time] is negative.
        // Negative values for [Time] will effectively run the simulation backwards.
        // this function will not move fixed particles.
        //======================================================================
        public static void Update(List<Particle> Particles, double Time)
        {
            // perform collision check on all particles
            CollisionCheckAll(Particles);

            //------------------------------------------------------------------
            // calculate the net forces acting on all particles
            //------------------------------------------------------------------
            // return all particles' forces to zero before recalculating
            foreach (Particle p in Particles)
            {
                p.ForceX = 0;
                p.ForceY = 0;
            }
            // calculate net forces acting on all particles
            int c = Particles.Count();
            for (int p1 = 0; p1 < c-1; p1++)
            {
                for(int p2 = p1+1; p2 < c; p2++)
                {
                    CalculateForcesBetweenTwoParticlesAndSum(Particles, Particles[p1], Particles[p2]);
                }
            }

            //------------------------------------------------------------------
            // calculate the new velocity of each particle
            //------------------------------------------------------------------
            foreach (Particle p in Particles)
            {
                p.VelocityX += Time * p.ForceX / p.Mass;
                p.VelocityY += Time * p.ForceY / p.Mass;
            }

            //------------------------------------------------------------------
            // calculate the new positions of each particle
            //------------------------------------------------------------------
            foreach (Particle p in Particles)
            {
                if (!p.Fixed)
                {
                    p.PositionX += Time * p.VelocityX;
                    p.PositionY += Time * p.VelocityY;
                }
            }
        }


        //======================================================================
        // this calculates the forces between two particles, and adds those
        // forces to the ForceX and ForceY components in both Particle objects.
        //======================================================================
        public static void CalculateForcesBetweenTwoParticlesAndSum(List<Particle> Particles, Particle p1, Particle p2)
        {
            // calculate the distance between the objects squared
            double dist_squared =
                Math.Pow(p1.PositionX - p2.PositionX, 2) +
                Math.Pow(p1.PositionY - p2.PositionY, 2);

            double force;
            // calculate the magnitude of the force normally.
            force = Particle.G * p1.Mass * p2.Mass / dist_squared;

            // calculate the angle (relative to positive x direction, A.K.A. the i unit vector)
            double angle = Math.Atan2(
                p1.PositionY - p2.PositionY,
                p1.PositionX - p2.PositionX);

            // calculate the x- and y-components of the force.
            double FX = Math.Cos(angle) * force;
            double FY = Math.Sin(angle) * force;
            // apply forces to particle 2
            p2.ForceX += FX;
            p2.ForceY += FY;
            // forces are equal and opposite on particle 1
            p1.ForceX += -FX;
            p1.ForceY += -FY;
        }


        // returns if it found a collision or not.
        public static void CollisionCheckAll(List<Particle> Particles)
        {
            bool FoundCollision;
            do
            {
                FoundCollision = false;
                // calculate net forces acting on all particles
                int c = Particles.Count();
                if(c > 1)
                {
                    for (int p1 = 0; ((p1 < c - 1) && (!FoundCollision)); p1++)
                    {
                        for (int p2 = p1 + 1; ((p2 < c) && (!FoundCollision)); p2++)
                        {
                            // calculate the distance between the objects squared
                            double dist_squared =
                                Math.Pow(Particles[p1].PositionX - Particles[p2].PositionX, 2) +
                                Math.Pow(Particles[p1].PositionY - Particles[p2].PositionY, 2);
                            // if the particles touch, or are overlapping
                            if (dist_squared <= Math.Pow(Particles[p1].Radius + Particles[p2].Radius, 2))
                            {
                                Particle.Collision(Particles, Particles[p1], Particles[p2]);
                                FoundCollision = true;
                            }
                        }
                    }
                }
            }
            while (FoundCollision);
        }


        // call this function when two particles collide!
        public static void Collision(List<Particle> Particles, Particle p1, Particle p2)
        {
            // p1 becomes the combination of p1 and p2 in terms of mass, position, and momentum.
            // (p1 + p2) -> p1

            if(p1.Fixed)
            {
                p1.Mass += p2.Mass;
                p1.CalculateRadius();
                Particles.Remove(p2);
            }
            else if(p2.Fixed)
            {
                p2.Mass += p1.Mass;
                p2.CalculateRadius();
                Particles.Remove(p1);
            }
            // if neither particle is fixed,
            else
            {
                // calculate the net position of the combined particle
                double p1m = p1.Mass / (p1.Mass + p2.Mass);
                double p2m = p2.Mass / (p1.Mass + p2.Mass);
                p1.PositionX = p1m * p1.PositionX + p2m * p2.PositionX;
                p1.PositionY = p1m * p1.PositionY + p2m * p2.PositionY;

                // calculate net momentum from two particles
                double momentum_x = p1.VelocityX * p1.Mass + p2.VelocityX * p2.Mass;
                double momentum_y = p1.VelocityY * p1.Mass + p2.VelocityY * p2.Mass;

                // combine the masses of the two particles
                p1.Mass = p1.Mass + p2.Mass;

                // calculate new velocity of combined particle
                p1.VelocityX = momentum_x / p1.Mass;
                p1.VelocityY = momentum_y / p1.Mass;

                p1.CalculateRadius();

                Particles.Remove(p2);
            }
        }



        // this draws all the particles in the list on the graphics object.
        public static void Draw(List<Particle> Particles, Graphics screen)
        {
            Pen myPen;
            float x, y, w, h;
            foreach (Particle p in Particles)
            {
                myPen = new Pen(p.Color);
                x = (float)(p.PositionX - p.Radius);
                y = (float)(p.PositionY - p.Radius);
                w = (float)(2 * p.Radius);
                h = (float)(2 * p.Radius);
                screen.DrawEllipse(myPen, x, y, w, h);

                double force_mag = Math.Sqrt(p.ForceX * p.ForceX + p.ForceY * p.ForceY);
                double force_x_norm = p.ForceX / force_mag;
                double force_y_norm = p.ForceY / force_mag;
                screen.DrawLine(myPen, (float)p.PositionX, (float)p.PositionY, (float)(p.PositionX + 2 * p.Radius * force_x_norm), (float)(p.PositionY + 2 * p.Radius * force_y_norm));

                myPen.Dispose();
            }
        }




        // calcualte (and update) the radius of a particle
        public void CalculateRadius()
        {
            this.Radius = Math.Sqrt(this.Mass);
        }

    }
}