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

        List<Heart> hearts = new List<Heart>();

        int score = 0;

        int ammo = 20;

        int timerTick = 0;

        Random random = new Random();

        List<GameObject> enemies = new List<GameObject>();

        event Action GameEnd;

        public MainGame()
        {
            InitializeComponent();

            closeButton.Left = Width - closeButton.Width - 15;
            closeButton.Top = 15;

            starShip = new StarShip(new Vector2(Width / 2 - StarShip.Width / 2, Height - StarShip.Height * 2));

            this.MouseDown += starShip.MouseDown;
            this.MouseMove += starShip.MouseMove;
            this.MouseUp += starShip.MouseUp;

            this.GameEnd += GameOver;

            for (int i = 0; i < starShip.hp; i++)
            {
                hearts.Add(new Heart(new Vector2(15 + (Heart.Width + 10) * i, Height - Heart.Height - 10)));
            }

        }

        private void GameOver()
        {
            FinalDialog form = new FinalDialog(score);
            timer.Stop();
            form.ShowDialog();
            Close();
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

            foreach (Heart heart in hearts)
            {
                heart.Draw(e.Graphics);
            }

            

        }

        private void timer_Tick(object sender, EventArgs e)
        {

            timerTick++;
            if (timerTick % 30 == 0)
            {
                enemies.Add(new Rocket(new Vector2(random.Next(Rocket.Width / 2, Width - Rocket.Width), 0)));

                if (random.Next(4) == 0)
                {
                    int direction = random.Next(2) == 0 ? 1 : -1;
                    enemies.Add(new EnemyShip(new Vector2(direction == 1 ? 0 : Width, EnemyShip.Height + 10), direction));
                }
            }
            if (timerTick % 20 == 0)
            {
                ammo++;
                DrawAmmo(); 
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

                if (enemies[i] is EnemyShip && timerTick % EnemyShip.FireRate == 0)
                {
                    EnemyBullet bullet1 = new EnemyBullet(new Vector2(enemies[i].coords.X + enemies[i].size.Width / 2 - 3, enemies[i].coords.Y + enemies[i].size.Height));
                    EnemyBullet bullet2 = new EnemyBullet(new Vector2(enemies[i].coords.X + enemies[i].size.Width / 2 + 3, enemies[i].coords.Y + enemies[i].size.Height));
                    bullets.Add(bullet1);
                    bullets.Add(bullet2);
                }

                if (enemies[i].coords.Y > Height)
                {
                    enemies.RemoveAt(i);
                }
            }

            for (int i = 0; i < bullets.Count; i++)
            {
                if (starShip.IsCollide(bullets[i]))
                {
                    bullets.RemoveAt(i);
                    IncreaseHp();
                }

                for (int j = 0; j < enemies.Count; j++)
                {
                    if (enemies[j].IsCollide(bullets[i]))
                    {
                        bullets.RemoveAt(i);
                        enemies[j].hp -= 1;
                        if (enemies[j].hp <= 0) {
                            score += enemies[j].score;
                            DrawScore();
                            enemies.RemoveAt(j);
                        }
                        break;
                    }
                }
            }

            for (int i = 0; i < enemies.Count; i++)
            {
                if (enemies[i].IsCollide(starShip))
                {
                    enemies.RemoveAt(i);
                    IncreaseHp();
                }
            }


            Refresh();
        }

        private void OnClose(object sender, EventArgs e)
        {
            Close();
        }

        private void IncreaseHp ()
        {
            starShip.hp -= 1;
            hearts.RemoveAt(starShip.hp);
            if (starShip.hp <= 0) GameEnd.Invoke();
        }

        private void DrawAmmo ()
        {
            AmmoCount.Text = "Патроны: " + ammo;
        }

        private void DrawScore ()
        {
            ScoreLabel.Text = "Счет: " + score;
        }


        private void OnKeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyData == Keys.Space && ammo > 0)
            {
                MyBullet bullet = new MyBullet(new Vector2(starShip.coords.X + starShip.size.Width / 2 - 5 / 2, starShip.coords.Y));
                bullets.Add(bullet);
                ammo--;
                DrawAmmo();
            }
        }

    }
}
