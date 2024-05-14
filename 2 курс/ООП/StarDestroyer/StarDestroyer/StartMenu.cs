using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.IO;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace StarDestroyer
{
    public partial class StartMenu : Form
    {
        public StartMenu()
        {
            InitializeComponent();
        }

        private void Start_Click(object sender, EventArgs e)
        {
            MainGame mainGame = new MainGame();
            this.Hide();
            mainGame.ShowDialog();
            this.Show();
        }

        private void Records_Click(object sender, EventArgs e)
        {
            if (!File.Exists("records.txt"))
            {
                MessageBox.Show("Рекорды не найдены!");
                return;
            }

            string[] lines = File.ReadAllLines("records.txt");
            string sortedRecords = string.Join("\n", lines.OrderByDescending(x => int.Parse(x.Split(':')[1])));
            MessageBox.Show(sortedRecords);
        }
    }
}
