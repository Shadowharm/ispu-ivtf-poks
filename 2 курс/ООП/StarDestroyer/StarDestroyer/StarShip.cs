using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Numerics;
using System.Security.Policy;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using StarDestroyer.Properties;

namespace StarDestroyer
{
    class StarShip : GameObject
    {

        private Point offset;
        private bool isDragging = false;

        public static int Width = 70;

        public static int Height = 70;

        public StarShip(Vector2 coords) : base(coords, new Size(Width, Height))
        {
            Sprite = Resources.starship;
            hp = 3;
        }

        public void MouseDown (object sender, MouseEventArgs e)
        {
            if (e.X > coords.X && e.X < coords.X + size.Width && e.Y > coords.Y && coords.Y < coords.Y + size.Height)
            {
                offset = new Point(e.X - (int) coords.X, e.Y - (int) coords.Y);
                isDragging = true;
            }
        }

        public void MouseMove(object sender, MouseEventArgs e)
        {
            MainGame parentForm = (sender as MainGame);
            if (isDragging)
            {
                coords.X = e.X - offset.X;
                coords.Y = e.Y - offset.Y;
                if (e.X - offset.X < 0) coords.X = 0;
                if (e.Y - offset.Y < 0) coords.Y = 0;
                if (e.X - offset.X + size.Width > parentForm.Width) coords.X = parentForm.Width - size.Width;
                if (e.Y - offset.Y + size.Height > parentForm.Height) coords.Y = parentForm.Height - size.Height;
            }
        }
        public void MouseUp(object sender, MouseEventArgs e)
        {
            isDragging = false;
        }

        public override void Fly() { }

    }
}
