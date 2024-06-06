using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Numerics;
using System.Text;
using System.Threading.Tasks;

namespace StarDestroyer
{
    internal class MyBullet : Bullet
    {
        public MyBullet(Vector2 coords) : base(coords, Color.Green) { } // установка цвета пули

        public override void Fly() // метод полета своей пули
        {
            coords.Y -= speed;
        }

    }
}
