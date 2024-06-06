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
        StarShip starShip; // корабль игрока

        List<Bullet> bullets = new List<Bullet>(); // массив пуль

        List<Heart> hearts = new List<Heart>(); // массив сердец

        int score = 0; // счет

        int ammo = 20; // боезапас

        int timerTick = 0; // счетчик тиков таймера

        Size initialSize; // начальные размеры окна

        Random random = new Random();

        List<GameObject> enemies = new List<GameObject>(); // список врагов

        event Action GameEnd; // событие завершения игры

        public MainGame()
        {
            InitializeComponent();

            initialSize = new Size(Width, Height);
            starShip = new StarShip(new Vector2(Width / 2 - StarShip.Width / 2, Height - StarShip.Height * 2)); // инициализация корабля игрока

            this.MouseDown += starShip.MouseDown; // добавление событий для урпавления кораблем
            this.MouseMove += starShip.MouseMove;
            this.MouseUp += starShip.MouseUp;

            this.GameEnd += GameOver; // добавление события завершения игры

            for (int i = 0; i < starShip.hp; i++)
            {
                hearts.Add(new Heart(new Vector2(15 + (Heart.Width + 10) * i, Height - Heart.Height - 50))); // заполнение сердечек для отрисовки
            }
        } // конструктор окна

        private void GameOver()
        {
            FinalDialog form = new FinalDialog(score); // инициализация итогового окна
            timer.Stop(); // остановка таймера
            form.ShowDialog(); // отображение окна
            Close(); // закрытие окна игры
        } // функция при завершении игры

        private void OnPaint(object sender, PaintEventArgs e)
        { 
            starShip.Draw(e.Graphics); // отрисовка нашего корабля
            foreach (Bullet bullet in bullets)
            {
                bullet.Draw(e.Graphics); // отрисовка пуль
            }

            foreach (GameObject enemy in enemies)
            {
                enemy.Draw(e.Graphics); // отрисовка противников
            }

            foreach (Heart heart in hearts)
            {
                heart.Draw(e.Graphics); // отрисовка сердец здоровья
            }
        } // функция отрисовки объектов

        private void timer_Tick(object sender, EventArgs e)
        {
           
            timerTick++;
            if (timerTick % 30 == 0)
            {
                enemies.Add(new Rocket(new Vector2(random.Next(Rocket.Width / 2, Width - Rocket.Width), 0))); // добавление ракеты

                if (random.Next(4) == 0) // с вероятностью 0.25
                {
                    int direction = random.Next(2) == 0 ? 1 : -1;
                    enemies.Add(new EnemyShip(new Vector2(direction == 1 ? 0 : Width, EnemyShip.Height + 10), direction)); // добавление вражеского корабля
                }
            }
            if (timerTick % 20 == 0)
            {
                ammo++; // добавление пули
                DrawAmmo(); 
            }

            for (int i = 0; i < enemies.Count; i++)
            {
                enemies[i].Fly(); // пример полиморфизма - метод Fly по разному реализован у классов Rocket и EnemyShip

                if (enemies[i] is EnemyShip && timerTick % EnemyShip.FireRate == 0) // если враг - это космический корабль и тик таймера делится на скорострельность
                {
                    EnemyBullet bullet1 = new EnemyBullet(new Vector2(enemies[i].coords.X + enemies[i].size.Width / 2 - 3, enemies[i].coords.Y + enemies[i].size.Height));
                    EnemyBullet bullet2 = new EnemyBullet(new Vector2(enemies[i].coords.X + enemies[i].size.Width / 2 + 3, enemies[i].coords.Y + enemies[i].size.Height));
                    bullets.Add(bullet1);
                    bullets.Add(bullet2); // создание и добавление вражеских пуль в массив
                }

                if (enemies[i].coords.Y > Height)
                {
                    enemies.RemoveAt(i); // удаление элементов массива врагов, если они вышли за пределы экрана
                    continue;
                }

                if (enemies[i].IsCollide(starShip)) // если сталкиваемся с противником
                {
                    enemies.RemoveAt(i); // удаляем из списка
                    DecreaseHp(); // уменьшаем наши очки здоровья
                }
            }

            for (int i = 0; i < bullets.Count; i++) // цикл по списку пуль
            {
                bullets[i].Fly(); // изменение координат пули
                if (bullets[i].coords.Y < 0 || bullets[i].coords.Y > Height) // если пуля вылетает за пределы экрана, удаляем из списка
                {
                    bullets.RemoveAt(i);
                    continue;
                }

                if (bullets[i] is EnemyBullet) // если это вражеская пуля
                {
                    if (starShip.IsCollide(bullets[i])) // если вражеская пуля сталкивается с нашим кораблем, удаляем из массива и уменьшаем наше hp
                    {
                        bullets.RemoveAt(i);
                        DecreaseHp();
                    }
                    continue;
                }

                for (int j = 0; j < enemies.Count; j++) // цикл по списку противников
                {
                    if (enemies[j].IsCollide(bullets[i])) // если наша пуля попадает в противника
                    {
                        bullets.RemoveAt(i);
                        enemies[j].hp -= 1; // вычитаем у противника 1 очко здоровья
                        if (enemies[j].hp <= 0) { // если очков здоровья у противника не осталось, удаляем его из списка и увеличиваем счет
                            score += enemies[j].score;
                            DrawScore();
                            enemies.RemoveAt(j);
                        }
                        break;
                    }
                }
            }

            Refresh(); // обновление экрана
        } // функция для каждого тика таймера

        private void DecreaseHp ()
        {
            starShip.hp -= 1;
            hearts.RemoveAt(starShip.hp);
            if (starShip.hp <= 0) GameEnd.Invoke();
        } // функция уменшения количества очков здоровья

        private void DrawAmmo ()
        {
            AmmoCount.Text = "Патроны: " + ammo;
        } // функция отрисовки количества боезапаса

        private void DrawScore ()
        {
            ScoreLabel.Text = "Счет: " + score;
        } // функция отрисовки количества набранных очков

        private void OnKeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyData == Keys.Space && ammo > 0) // если нажат ПРОБЕЛ и боезапас не пуст
            {
                MyBullet bullet = new MyBullet(new Vector2(starShip.coords.X + starShip.size.Width / 2 - 5 / 2, starShip.coords.Y)); // создание пули
                bullets.Add(bullet); // добавление в список пуль
                ammo--;
                DrawAmmo();
            }
        } // функция для обработки нажатия клавиши ПРОБЕЛ

        private void OnResize(object sender, EventArgs e)
        {
            starShip.coords = new Vector2(starShip.coords.X * Width / initialSize.Width, starShip.coords.Y * Height / initialSize.Height);
            foreach (GameObject enemy in enemies)
            {
                enemy.coords = new Vector2(enemy.coords.X * Width / initialSize.Width, enemy.coords.Y * Height / initialSize.Height);
            }

            foreach (Bullet bullet in bullets)
            {
                bullet.coords = new Vector2(bullet.coords.X * Width / initialSize.Width, bullet.coords.Y * Height / initialSize.Height);
            }


            initialSize = new Size(Width, Height);
            if (starShip != null)
            {
                foreach (Heart heart in hearts)
                {
                    heart.coords.Y = Height - Heart.Height - 50;
                }
            }
        } // функиция для обработк масштабирования

        private void Pause_Click(object sender, EventArgs e)
        {
            this.ActiveControl = null; // сброс фокуса на кнопку
            if (Pause.Text == "❚❚")
            {
                timer.Stop(); // остановка таймера
                Pause.Text = "▶️"; // изменение содержимого кнопки
            }
            else 
            {
                timer.Start(); // возобновление таймера
                Pause.Text = "❚❚"; // изменение содержимого кнопки
            }
        } // функция нажатия на паузу

        private void MainGame_FormClosed(object sender, FormClosedEventArgs e)
        {
            timer.Stop();
        } // функция при закрытии окна крестиком
    }
}
