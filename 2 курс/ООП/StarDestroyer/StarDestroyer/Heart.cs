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
    internal class Heart : GameObject
    {


        public static int Width = 30; // ширина

        public static int Height = 30; // высота
        public Heart(Vector2 coords) : base(coords, new Size(Width, Height))
        {
            Sprite = Resources.heart; // установка спрайта
        }

        public override void Fly() { }
    }
}
