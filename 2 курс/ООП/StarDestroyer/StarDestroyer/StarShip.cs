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
        // вспомогательные поля для отслеживания перемещения мышкой
        private Point offset;
        private bool isDragging = false;

        public static int Width = 70; // ширина

        public static int Height = 70; // высота

        public StarShip(Vector2 coords) : base(coords, new Size(Width, Height))
        {
            Sprite = Resources.starship; // установка спрайта
            hp = 3; // установка очков зхдоровья
        }

        public void MouseDown (object sender, MouseEventArgs e)
        {
            if (e.X > coords.X && e.X < coords.X + size.Width && e.Y > coords.Y && coords.Y < coords.Y + size.Height)
            {
                offset = new Point(e.X - (int) coords.X, e.Y - (int) coords.Y);
                isDragging = true;
            }
        } // событие нажатия кнопки мыши

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
        } // событие перемещения мышью
        public void MouseUp(object sender, MouseEventArgs e)
        {
            isDragging = false;
        } // событие отпускания кнопки мыши

        public override void Fly() { }

    }
}
