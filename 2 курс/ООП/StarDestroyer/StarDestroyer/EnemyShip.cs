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
        public static int Width = 70; // ширина

        public static int Height = 50; // высота

        public static int FireRate = 15; // скорострельность

        public EnemyShip(Vector2 coords, int direction) : base(coords, new Size(Width, Height))
        {
            Sprite = Resources.tie; // установка спрайта
            this.direction = direction; // установка направления движения
            this.speed = 5; // установка скорости
            score = 20; // установка очков за уничтожение
            hp = 1; // установка очков здоровья
        }

        private int direction; // направление движения

        public override void Fly() { // метод полета корабля, зависит от скорости и направлеения
            coords.X += speed * direction;
        }
    }
}
