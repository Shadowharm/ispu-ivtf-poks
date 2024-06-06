using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Runtime.Serialization.Formatters.Binary;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace StarDestroyer
{
    [Serializable]
    public struct GameRecord
    {
        public string Name;
        public int Score;

        public GameRecord(string name, int score)
        {
            Name = name;
            Score = score;
        }
    }


    public partial class FinalDialog : Form
    {
        public FinalDialog(int score)
        {
            InitializeComponent();
            this.score = score;
            ScoreLabel.Text = "Вы набрали " + score.ToString() + " очков";   
        }

        private readonly int score;

        public string filePath = "records.dat";

        public GameRecord[] LoadRecords() // функция получения списка рекордов из файла
        {
            if (!File.Exists(filePath)) // если файла нет, возвращаем пустой список
                return new GameRecord[0];

            using (FileStream fs = new FileStream(filePath, FileMode.Open))
            {
                BinaryFormatter formatter = new BinaryFormatter();
                return (GameRecord[])formatter.Deserialize(fs); // десериализуем файл
            }
        }
        public void SaveRecords(GameRecord[] records) // функция сохранения рекордов
        {
            using (FileStream fs = new FileStream(filePath, FileMode.Create))
            {
                BinaryFormatter formatter = new BinaryFormatter();
                formatter.Serialize(fs, records);  // сериализация списка структур в файл
            }
        }

        public void AddOrUpdateRecord(string name) // функция добавления рекорда
        {
            GameRecord[] records = LoadRecords(); // получение рекордов

            bool recordExists = false;
            for (int i = 0; i < records.Length; i++) // цикл по рекордам
            {
                if (records[i].Name.Equals(name, StringComparison.OrdinalIgnoreCase)) // проверяем, сохранен ли у нас рекорд ранее по имени
                {
                    if (records[i].Score < score) records[i].Score = score; // замена старого рекорда, если новый больше
                    recordExists = true;
                    break;
                }
            }

            if (!recordExists) // иначе делаем новую запись с рекордом
            {
                Array.Resize(ref records, records.Length + 1);
                records[records.Length - 1] = new GameRecord(name, score);
            }

            Array.Sort(records, (x, y) => y.Score.CompareTo(x.Score)); // сортируем рекорды

            SaveRecords(records); // сохраняем рекорды в файл
        }

        private void Save_Click(object sender, EventArgs e)
        {

            string name = string.IsNullOrEmpty(NameLabel.Text) ? "Игрок1" : NameLabel.Text;

            AddOrUpdateRecord(name);

            Close();
        }
    }
}
