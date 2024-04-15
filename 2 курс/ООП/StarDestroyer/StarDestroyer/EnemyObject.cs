using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Numerics;
using System.Text;
using System.Threading.Tasks;

namespace StarDestroyer
{
    abstract class EnemyObject : GameObject
    {
        public int speed;
        public EnemyObject(Vector2 coords, Size size, int speed, int hp = 1) : base(coords, size) {
            this.speed = speed;
        }
    }
}
