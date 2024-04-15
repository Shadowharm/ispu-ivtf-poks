using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using StarDestroyer;
using System.Numerics;

namespace StarDestroyer
{
    abstract class Bullet : GameObject
    {

        private Color color;

        public Bullet(Vector2 coords, Color color) : base(coords, new Size(5, 15))
        {
            this.color = color;
            speed = 10;
        }
        public override void Draw(Graphics g)
        {
            g.FillEllipse(new SolidBrush(color), coords.X, coords.Y, size.Width, size.Height);
        }


    }
}
