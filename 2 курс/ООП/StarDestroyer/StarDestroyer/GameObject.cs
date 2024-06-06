using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Numerics;
using System.Text;
using System.Threading.Tasks;

namespace StarDestroyer
{
    abstract class GameObject // базовый класс для игровых объектов
    {
        public GameObject(Vector2 coords, Size size)
        {
            this.coords = coords; // установка координат
            this.size = size; // установка размеров
        }

        public int speed; // скорость

        public int hp = 1; // очки здоровья

        public Bitmap Sprite; // спрайт 

        public Vector2 coords; // кординаты

        public Size size; // размеры

        public int score; // очки

        abstract public void Fly(); // функция перемещения объекта

        public virtual void Draw(Graphics g)
        {
            g.DrawImage(Sprite, coords.X, coords.Y, size.Width, size.Height);
        } // функция отрисовки объекта

        public bool IsCollide(GameObject gameObject)
        {
            Rectangle object1 = new Rectangle((int) coords.X, (int) coords.Y, size.Width, size.Height);
            Rectangle object2 = new Rectangle((int) gameObject.coords.X, (int) gameObject.coords.Y, gameObject.size.Width, gameObject.size.Height);
            return object1.IntersectsWith(object2);
        } // функция, проеряющая столкновение

    }
}
