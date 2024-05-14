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
    internal class EnemyShip : GameObject
    {
        public static int Width = 70;

        public static int Height = 50;

        public static int FireRate = 15;

        public EnemyShip(Vector2 coords, int direction) : base(coords, new Size(Width, Height))
        {
            Sprite = Resources.tie;
            this.direction = direction;
            this.speed = 5;
            score = 20;
        }

        private int direction;

        public override void Fly() {
            coords.X += speed * direction;
        }
    }
}
