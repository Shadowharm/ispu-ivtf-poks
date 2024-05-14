using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace StarDestroyer
{
    public partial class FinalDialog : Form
    {
        public FinalDialog(int score)
        {
            InitializeComponent();
            this.score = score;
            ScoreLabel.Text = "Вы набрали " + score.ToString() + " очков";
        }

        private readonly int score;

        private void Save_Click(object sender, EventArgs e)
        {
            var name = string.IsNullOrEmpty(NameLabel.Text) ? "Игрок1" : NameLabel.Text;

            using (StreamWriter sw = new StreamWriter("records.txt", append: true))
            {
                sw.WriteLine($"{name}: {score}");
            }

            Close();
        }
    }
}
