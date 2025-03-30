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
    public partial class Brig1 : Form
    {
        public Brig1()
        {
            InitializeComponent();
        }
        private void Form1_Load(object sender, EventArgs e)
        {
            // Устанавливаем размеры формы
            this.Width = 400;
            this.Height = 500;

            // Центруем элементы
            CenterControl(button1, 50);
            CenterControl(textBox1, 100);
            CenterControl(label1, 150);
            CenterControl(checkBox1, 200);
            CenterControl(listBox1, 250);
        }

        private void CenterControl(Control control, int top, int offsetX = 0)
        {
            control.Left = (this.ClientSize.Width - control.Width) / 2 + offsetX;
            control.Top = top;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            listBox1.Items.Add("Button");
            listBox1.Items.Add("Textbox");
            listBox1.Items.Add("Label");
            listBox1.Items.Add("CheckBox");
        }
    }
}
