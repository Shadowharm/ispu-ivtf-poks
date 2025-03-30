using System;
using System.Diagnostics;
using System.Drawing;
using System.Windows.Forms;

namespace Brig1
{
    public partial class Brig3 : Form
    {
        private ComboBox comboBox;
        private DataGridView dataGridView;
        private Stopwatch stopwatch;
        public Brig3()
        {
            InitializeComponent();
        }

        private void Brig3Form_Load(object sender, EventArgs e)
        {
            // Настройка формы
            this.Width = 800;
            this.Height = 600;
            this.Text = "ComboBox Experiments";

            // Создание ComboBox
            comboBox = new ComboBox
            {
                Text = "ComboBox",
                Width = 150,
                Height = 30,
                DropDownStyle = ComboBoxStyle.DropDownList,
                Location = new Point(100, 100)
            };
            comboBox.Items.AddRange(new string[] { "Item 1", "Item 2", "Item 3" });

            // Создание DataGridView
            dataGridView = CreateTable();

            // Таймер для замеров времени
            stopwatch = new Stopwatch();

            // Добавление элементов на форму
            this.Controls.Add(comboBox);
            this.Controls.Add(dataGridView);

            // Включение режима перетаскивания
            comboBox.MouseDown += ComboBox_MouseDown;
            comboBox.MouseMove += ComboBox_MouseMove;
            comboBox.MouseUp += ComboBox_MouseUp;
        }


        private DataGridView CreateTable()
        {
            // Создание DataGridView
            DataGridView dataGridView = new DataGridView
            {
                Width = 700,
                Height = 300,
                AllowUserToAddRows = false,
                ReadOnly = true,
                ColumnCount = 7,
                RowHeadersVisible = false,
                Location = new Point(50, 200)
            };

            // Настройка колонок
            dataGridView.Columns[0].HeaderText = "Размер визуального элемента (горизонталь)";
            dataGridView.Columns[1].HeaderText = "Размер визуального элемента (вертикаль)";
            dataGridView.Columns[2].HeaderText = "Координаты центра элемента";
            dataGridView.Columns[3].HeaderText = "Начальные координаты курсора относительно визуального элемента";
            dataGridView.Columns[4].HeaderText = "Расстояние до центра элемента";
            dataGridView.Columns[5].HeaderText = "Время попадания курсора по Фиттсу";
            dataGridView.Columns[6].HeaderText = "Фактическое время попадания курсора";

            return dataGridView;
        }

        private Point initialCursorPosition;
        private bool isDragging = false;

        private void ComboBox_MouseDown(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                isDragging = true;
                initialCursorPosition = e.Location;
                stopwatch.Restart(); // Начало замера времени
            }
        }

        private void ComboBox_MouseMove(object sender, MouseEventArgs e)
        {
            if (isDragging)
            {
                // Изменение положения ComboBox
                comboBox.Left += e.X - initialCursorPosition.X;
                comboBox.Top += e.Y - initialCursorPosition.Y;
            }
        }

        private void ComboBox_MouseUp(object sender, MouseEventArgs e)
        {
            if (isDragging)
            {
                isDragging = false;
                stopwatch.Stop(); // Конец замера времени

                // Вычисление значений для таблицы
                int width = comboBox.Width;
                int height = comboBox.Height;
                Point comboBoxCenter = new Point(comboBox.Left + comboBox.Width / 2, comboBox.Top + comboBox.Height / 2);
                Point cursorPosition = this.PointToClient(Cursor.Position);
                double distanceToCenter = Math.Sqrt(Math.Pow(cursorPosition.X - comboBoxCenter.X, 2) +
                                                    Math.Pow(cursorPosition.Y - comboBoxCenter.Y, 2));

                double a = 200; // Константа времени (мс)
                double b = 150; // Скорость движения (мс)
                double fittsTime = a + b * Math.Log(distanceToCenter / width + 1, 2);

                dataGridView.Rows.Add(
                    $"{width} px",
                    $"{height} px",
                    $"{comboBoxCenter.X}, {comboBoxCenter.Y}",
                    $"{initialCursorPosition.X}, {initialCursorPosition.Y}",
                    $"{distanceToCenter:F1} px",
                    $"{fittsTime:F1} ms",
                    $"{stopwatch.ElapsedMilliseconds} ms"
                );
            }
        }
    }
}
