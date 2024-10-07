using System;
using System.Data;
using System.Windows.Forms;
using Npgsql;

namespace Sqlwin
{
    public partial class Form1 : Form
    {
        private NpgsqlConnection connection;
        private NpgsqlDataAdapter adapter;
        private DataSet dataSet;
        static string connectionString = "Server=localhost:5432;Database=db_ivtf;User Id=postgres;Password=admin;";
        public Form1()
        {
            InitializeComponent();
            InitializeDatabase();
        }

        private void InitializeDatabase()
        {
            connection = new NpgsqlConnection(connectionString);
            adapter = new NpgsqlDataAdapter();


            connection.Open();
        }
        private void toolStripComboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            string selectedTable = toolStripComboBox1.SelectedItem.ToString();
            string sqlQuery = "SELECT * FROM " + selectedTable;
            dataSet = new DataSet();

            // Очистка DataGridView перед загрузкой новых данных
            dataGridView2.DataSource = null;
            for (int i = 0; i < dataGridView2.Columns.Count; i++)
            {
                for (int j = 0; j < dataGridView2.Rows.Count; j++)
                {
                    dataGridView2.Rows[j].Cells[i].Value = DBNull.Value;
                }
            }

            adapter.SelectCommand = new NpgsqlCommand(sqlQuery, connection);
            adapter.Fill(dataSet);

            dataGridView2.DataSource = dataSet.Tables[0];

        }


        private void setGrid(String sql)
        {
            dataSet = new DataSet();

            // Очистка DataGridView перед загрузкой новых данных
            dataGridView2.DataSource = null;
            for (int i = 0; i < dataGridView2.Columns.Count; i++)
            {
                for (int j = 0; j < dataGridView2.Rows.Count; j++)
                {
                    dataGridView2.Rows[j].Cells[i].Value = DBNull.Value;
                }
            }

            adapter.SelectCommand = new NpgsqlCommand(sql, connection);
            adapter.Fill(dataSet);

            dataGridView2.DataSource = dataSet.Tables[0];

        }

        private void toolStripTextBox1_Click(object sender, EventArgs e)
        {
            string sqlQuery = @"SELECT 
    t.name AS teacher_name,
    s.name AS subject_name,
    f.name AS faculty_name,
    dept.name AS department_name
FROM 
    public.reading reading
JOIN 
    public.teacher t ON reading.teacher_id = t.id
JOIN 
    public.subject s ON reading.subject_id = s.id
JOIN 
    public.department dept ON t.department_id = dept.id
JOIN 
    public.faculty f ON dept.faculty_id = f.id;";
            setGrid(sqlQuery);

        }
        private void toolStripTextBox2_Click(object sender, EventArgs e)
        {
            string selectedTable = toolStripTextBox2.Text.ToString();
            string sqlQuery = "SELECT * FROM " + selectedTable;
            setGrid(sqlQuery);
        }

        private void toolStripTextBox2_Click_1(object sender, EventArgs e)
        {
            string sqlQuery = @"SELECT 
    f.id AS faculty_id,
    f.name AS faculty_name,
    COUNT(DISTINCT t.id) AS total_teachers,
    COUNT(DISTINCT rd.subject_id) AS total_disciplines
FROM 
    public.faculty f
JOIN 
    public.department d ON f.id = d.faculty_id
JOIN 
    public.teacher t ON d.id = t.department_id
JOIN 
    public.reading rd ON t.id = rd.teacher_id
GROUP BY 
    f.id, f.name
ORDER BY 
    f.name;";
            setGrid(sqlQuery);

        }
    }
}
