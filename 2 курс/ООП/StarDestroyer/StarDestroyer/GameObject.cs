using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Numerics;
using System.Text;
using System.Threading.Tasks;

namespace StarDestroyer
{
    abstract class GameObject
    {
        public GameObject(Vector2 coords, Size size)
        {
            this.coords = coords;
            this.size = size;
        }

        public int speed;

        public int hp = 1;

        public Bitmap Sprite;

        public Vector2 coords;

        public Size size;

        abstract public void Fly();

        public virtual void Draw(Graphics g)
        {
            g.DrawImage(Sprite, coords.X, coords.Y, size.Width, size.Height);
        }

        public bool IsCollide(GameObject gameObject)
        {
            Rectangle object1 = new Rectangle((int) coords.X, (int) coords.Y, size.Width, size.Height);
            Rectangle object2 = new Rectangle((int) gameObject.coords.X, (int) gameObject.coords.Y, gameObject.size.Width, gameObject.size.Height);
            return object1.IntersectsWith(object2);
        }

    }
}
