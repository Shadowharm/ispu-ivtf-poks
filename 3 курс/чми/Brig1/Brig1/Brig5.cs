using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Brig1
{
    public partial class Brig5 : Form
    {
        public Brig5()
        {
            InitializeComponent();
            CreateInterface();
        }

        private void CreateInterface()
        {
            // Размеры и отступы
            int labelWidth = 100;
            int labelHeight = 30;
            int buttonWidth = 100;
            int buttonHeight = 30;
            int margin = 10;

            // Создание первого столбца с Label
            for (int i = 0; i < 8; i++)
            {
                Label label = new Label
                {
                    Text = $"Label {i + 1}",
                    Width = labelWidth,
                    Height = labelHeight,
                    Left = margin,
                    Top = margin + i * (labelHeight + margin)
                };
                this.Controls.Add(label);
            }

            // Создание второго столбца с Button
            for (int i = 0; i < 8; i++)
            {
                Button button = new Button
                {
                    Text = $"Button {i + 1}",
                    Width = buttonWidth,
                    Height = buttonHeight,
                    Left = 2 * margin + labelWidth,
                    Top = margin + i * (buttonHeight + margin)
                };
                this.Controls.Add(button);
                button.MouseClick += CalculateHickTime;
            }
        }

        private void CalculateHickTime(object sender, MouseEventArgs e)
        {
            // Константы закона Хика
            double a = 200; // мс
            double b = 100; // мс
            int n = 16;     // количество элементов

            // Расчет времени доступа
            double time = a + b * Math.Log(n + 1, 2);

            // Вывод результата
            MessageBox.Show($"Время доступа к элементу по закону Хика: {time:F1} мс",
                            "Результат", MessageBoxButtons.OK, MessageBoxIcon.Information);
        }
    }
}

