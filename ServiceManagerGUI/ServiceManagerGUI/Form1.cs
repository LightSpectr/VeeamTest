using System.Data;
namespace ServiceManagerGUI
{
    public partial class MainForm : Form
    {
        public MainForm()
        {
            InitializeComponent();
        }

        private void MainForm_Load(object sender, EventArgs e)
        { 
            DataTable sample = new DataTable(); //Sample Data
            sample.Columns.Add("id", typeof(string));
            sample.Columns.Add("name", typeof(string));
            sample.Rows.Add("1", "apple");
            sample.Rows.Add("2", "acer");
            foreach (DataRow row in sample.Rows)
            {
                dataGridView1.Rows.Add(row["id"], row["name"]);
            }     
        }

        private void StartButton_Click(object sender, EventArgs e)
        {

        }

        private void StopButton_Click(object sender, EventArgs e)
        {

        }

        private void ReloadButton_Click(object sender, EventArgs e)
        {

        }
    }
}