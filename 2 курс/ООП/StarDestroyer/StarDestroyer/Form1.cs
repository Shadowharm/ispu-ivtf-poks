using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Numerics;
using System.Reflection.Emit;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace StarDestroyer
{
    public partial class MainGame : Form
    {
        StarShip starShip;

        List<Bullet> bullets = new List<Bullet>();

        const int enemyInterval = 30;

        int enemyCounter = 0;

        Random random = new Random();

        List<GameObject> enemies = new List<GameObject>();

        public MainGame()
        {
            InitializeComponent();

            closeButton.Left = Width - closeButton.Width - 15;
            closeButton.Top = 15;

            starShip = new StarShip(new Vector2(Width / 2 - 25, Height - 100));

            this.MouseDown += starShip.MouseDown;
            this.MouseMove += starShip.MouseMove;
            this.MouseUp += starShip.MouseUp;
        }



        private void OnPaint(object sender, PaintEventArgs e)
        {
            starShip.Draw(e.Graphics);
            foreach (Bullet bullet in bullets)
            {
                bullet.Draw(e.Graphics);
            }

            foreach (GameObject enemy in enemies)
            {
                enemy.Draw(e.Graphics);
            }
        }

        private void timer_Tick(object sender, EventArgs e)
        {

            enemyCounter++;
            if (enemyCounter >= enemyInterval)
            {
                enemyCounter = 0;

                if (random.Next(100) % 5 == 0)

                    enemies.Add(new Rocket(new Vector2(random.Next(0, Width - 30), 0)));

                else
                    enemies.Add(new Rocket(new Vector2(random.Next(0, Width - 30), 0)));

            }

            for (int i = 0; i < bullets.Count; i++)
            {
               bullets[i].Fly();
                if (bullets[i].coords.Y < 0 || bullets[i].coords.Y > Height)
                {
                    bullets.RemoveAt(i);
                }
            }

            for (int i = 0; i < enemies.Count; i++)
            {
                enemies[i].Fly();
                if (enemies[i].coords.Y > Height)
                {
                    enemies.RemoveAt(i);
                }
            }

            for (int i = 0; i < bullets.Count; i++)
            {

                for (int j = 0; j < enemies.Count; j++)
                {
                    if (enemies[j].IsCollide(bullets[i]))
                    {
                        bullets.RemoveAt(i);
                        enemies[j].hp -= 1;
                        if (enemies[j].hp <= 0) enemies.RemoveAt(j);
                        break;
                    }
                }
            }


            Refresh();
        }

        private void OnClose(object sender, EventArgs e)
        {
            Close();
        }

        private void OnKeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyData == Keys.Space)
            {
                MyBullet bullet = new MyBullet(new Vector2(starShip.coords.X + starShip.size.Width / 2 - 5 / 2, starShip.coords.Y));
                bullets.Add(bullet);

            }
        }


    }
}
