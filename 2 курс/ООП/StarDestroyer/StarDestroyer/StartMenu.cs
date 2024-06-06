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
using System.Runtime.Serialization.Formatters.Binary;

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

        public GameRecord[] LoadRecords()
        {
            using (FileStream fs = new FileStream("records.dat", FileMode.Open))
            {
                BinaryFormatter formatter = new BinaryFormatter();
                return (GameRecord[])formatter.Deserialize(fs);
            }
        }

        public static void DisplayRecords(GameRecord[] records)
        {
            string message = "Рекорды игроков:\n";
            foreach (var record in records)
            {
                message += $"{record.Name}: {record.Score}\n";
            }

            MessageBox.Show(message, "Список рекордов", MessageBoxButtons.OK, MessageBoxIcon.Information);
        }

        private void Records_Click(object sender, EventArgs e)
        {
            if (!File.Exists("records.dat"))
            {
                MessageBox.Show("Рекорды не найдены!");
                return;
            }
            DisplayRecords(LoadRecords());
        }

        private void About_Click(object sender, EventArgs e)
        {
            MessageBox.Show("Разработчик: студент ИГЭУ Прохоров Максим, гр. 2-41хх\n\n" +
                "Игра \"Звездный разрушитель\" - это игра, в которой необходимо управлять космическим кораблем с помощью мыши, уворачиваться от вражеских объектов и уничтожать их с помощью пушки, нажимая на ПРОБЕЛ",
                "О программе", MessageBoxButtons.OK, MessageBoxIcon.Information);
        }
    }
}
