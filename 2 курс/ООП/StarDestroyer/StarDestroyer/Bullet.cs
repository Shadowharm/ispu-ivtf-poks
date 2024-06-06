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
        private Color color; // цвет пули

        public Bullet(Vector2 coords, Color color) : base(coords, new Size(5, 17))
        {
            this.color = color; // установка цвета пули
            speed = 20; // установка скорости
        }
        public override void Draw(Graphics g) // переопределение метода отрисовки
        {
            g.FillEllipse(new SolidBrush(color), coords.X, coords.Y, size.Width, size.Height);
        }
    }
}
