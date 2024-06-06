using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Numerics;
using System.Text;
using System.Threading.Tasks;

namespace StarDestroyer
{

    internal class EnemyBullet : Bullet
    {
        public EnemyBullet(Vector2 coords) : base(coords, Color.Red) { } // установка цвета пули

        public override void Fly() // метод полета вражеской пули
        {
            coords.Y += speed;
        }
    }
}
