using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Numerics;
using System.Text;
using System.Threading.Tasks;
using StarDestroyer.Properties;

namespace StarDestroyer
{
    internal class Rocket : GameObject
    {
        public Rocket(Vector2 coords) : base(coords, new Size(50, 100))
        {
            Sprite = Resources.rocket;
            hp = 1;
            speed = 7;
        }

        public override void Fly() {
            coords.Y += speed;
        }
    }
}
