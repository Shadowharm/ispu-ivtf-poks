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
        public Rocket(Vector2 coords) : base(coords, new Size(Width, Height))
        {
            Sprite = Resources.rocket; // установка спрайта
            hp = 1; // установка очков здоровья
            speed = 7; // установка скорости
            score = 10; // установка очков за уничтожение
        }

        public static int Width = 50; // ширина

        public static int Height = 100; // высота

        public override void Fly() { // метод полета ракеты
            coords.Y += speed;
        }
    }
}
