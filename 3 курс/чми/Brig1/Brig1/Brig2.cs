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
    public partial class Brig2 : Form
    {
        public Brig2()
        {
            InitializeComponent();
        }
        private void Brig2Form_Load(object sender, EventArgs e)
        {
            // Настройка размеров формы
            this.Width = 800;
            this.Height = 600;
            this.Text = "Brig2";

            Button button = new Button { Text = "Button", Width = 100, Height = 30 };
            ComboBox comboBox = new ComboBox { Width = 100, Height = 30 };
            comboBox.Items.AddRange(new string[] { "Item 1", "Item 2" });
            Label label = new Label { Text = "Label", Width = 100, Height = 30 };
            RadioButton radioButton = new RadioButton { Text = "Radiobutton", Width = 120, Height = 30 };

            DataGridView dataGridView = CreateTable();

            PlaceInTwoColumns(button, comboBox, 0);
            PlaceInTwoColumns(label, radioButton, 1);

            UpdateTableDistances(dataGridView, button, comboBox, label, radioButton);

            dataGridView.Left = (this.ClientSize.Width - dataGridView.Width) / 2;
            dataGridView.Top = this.ClientSize.Height - dataGridView.Height - 20;

            this.Controls.Add(button);
            this.Controls.Add(comboBox);
            this.Controls.Add(label);
            this.Controls.Add(radioButton);
            this.Controls.Add(dataGridView);
        }

        private void PlaceInTwoColumns(Control leftControl, Control rightControl, int row)
        {
            int formWidth = this.ClientSize.Width;
            int formHeight = this.ClientSize.Height;

            int columnWidth = formWidth / 2;
            int rowHeight = 50;

            int leftColumnX = (columnWidth - leftControl.Width) / 2;
            int rightColumnX = columnWidth + (columnWidth - rightControl.Width) / 2;

            int topPosition = (formHeight - rowHeight * 3) / 2 + row * rowHeight;

            // Установка позиций
            leftControl.Left = leftColumnX;
            leftControl.Top = topPosition;

            rightControl.Left = rightColumnX;
            rightControl.Top = topPosition;
        }

        private DataGridView CreateTable()
        {
            // Создание DataGridView
            DataGridView dataGridView = new DataGridView
            {
                Width = 700,
                Height = 200,
                AllowUserToAddRows = false,
                ReadOnly = true,
                ColumnCount = 3,
                RowHeadersVisible = false
            };

            // Настройка колонок
            dataGridView.Columns[0].HeaderText = "Имя элемента";
            dataGridView.Columns[1].HeaderText = "Имя элемента";
            dataGridView.Columns[2].HeaderText = "Расстояние в пикселах";

            // Добавление строк
            dataGridView.Rows.Add("Левая сторона экрана", "Левая сторона первого элемента первого столбца", "");
            dataGridView.Rows.Add("Правая сторона первого столбца", "Левая сторона второго столбца", "");
            dataGridView.Rows.Add("Правая сторона второго столбца", "Правая сторона экрана", "");

            return dataGridView;
        }
        private void UpdateTableDistances(DataGridView dataGridView, Control left1, Control right1, Control left2, Control right2)
        {
            int leftScreen = 0;
            int rightScreen = this.ClientSize.Width;

            // Вычисление расстояний
            int distanceLeftToFirst = left1.Left - leftScreen;
            int distanceBetweenColumns = right1.Left - (left1.Left + left1.Width);
            int distanceRightToScreen = rightScreen - (right2.Left + right2.Width);

            // Обновление таблицы
            dataGridView.Rows[0].Cells[2].Value = $"{distanceLeftToFirst} px";
            dataGridView.Rows[1].Cells[2].Value = $"{distanceBetweenColumns} px";
            dataGridView.Rows[2].Cells[2].Value = $"{distanceRightToScreen} px";
        }
    }
}
