using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Security.Cryptography.X509Certificates;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace arcanoid
{
    public partial class Form1 : Form
    {
        const int mapWidth = 20;
        const int mapHeight = 30;

        public int[,] map = new int[mapHeight, mapWidth];
        public int dirX = 0;
        public int dirY = 0;

        public int platformX;
        public int platformY;

        public Image arcanoidSet;

        public Form1()
        {
            InitializeComponent();
            timer1.Tick += new EventHandler(Update);
            Init();
        }

        private void Update(object sender, EventArgs e)
        {
            Invalidate();
        }

        public void Init ()
        {
            string executablePath = Path.GetDirectoryName(System.Reflection.Assembly.GetExecutingAssembly().Location);

            // Относительный путь к файлу изображения относительно папки Images в корне проекта
            string relativePath = @"images\arcanoid.png";

            // Конструируем абсолютный путь к файлу изображения
            string absolutePath = Path.Combine(executablePath, relativePath);

            arcanoidSet = new Bitmap(absolutePath);
            timer1.Interval = 50;
            platformX = mapWidth/2;
            platformY = mapHeight-1;

            for (int i = 0; i < mapHeight; i++)
            {
                for (int j = 0; j < mapWidth; j++)
                {
                    map[i, j] = 0;
                }
            }

            map[platformY, platformX] = 9;
            map[platformY, platformX+1] = 9;
        }

        public void DrawMap ()
        {
            for (int i = 0; i < mapHeight; i++)
            {
                for (int j = 0; j < mapWidth; j++)
                {
                    
                }
            }
        }

        private void OnPaint(object sender, PaintEventArgs e)
        {

        }
    }
}
