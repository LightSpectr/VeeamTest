using ServiceControlCOMLib;
using System.Runtime.InteropServices;
using System.ServiceProcess;

namespace ServiceManagerGUI
{
    public partial class MainForm : Form
    {
        ServiceManager serviceManager;
        public MainForm()
        {
            InitializeComponent();
            serviceManager = new ServiceManager();
        }

        private void MainForm_Load(object sender, EventArgs e)
        {
            UpdateService();
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

        private void UpdateButton_Click(object sender, EventArgs e)
        {
            dataGridView1.Rows.Clear();
            dataGridView1.Refresh();
            UpdateService();
        }
        
        private void UpdateService()
        {
            ServiceController[] services = ServiceController.GetServices(); ;
            foreach (ServiceController service in services)
            {
                serviceManager.ServiceName = service.ServiceName;
                byte status = 100;
                string statusSting = "";
                try
                {
                    serviceManager.chkStatus(out status);
                }
                catch (COMException comEx)
                {
                    status = 100;
                }
                switch (status)
                {
                    case 100: statusSting = "Ошибка"; 
                        break;

                    case 0: statusSting = "Остановлено";
                        break;

                    case 2:
                        statusSting = "Выполняется";
                        break;

                }
                dataGridView1.Rows.Add(service.DisplayName, statusSting);
              
            }
            /*
            DataTable sample = new DataTable(); //Sample Data
            sample.Columns.Add("id", typeof(string));
            sample.Columns.Add("name", typeof(string));
            sample.Rows.Add("1", "apple");
            sample.Rows.Add("2", "acer");
            foreach (DataRow row in sample.Rows)
            {
                dataGridView1.Rows.Add(row["id"], row["name"]);
            }
            */

        }
    }
}