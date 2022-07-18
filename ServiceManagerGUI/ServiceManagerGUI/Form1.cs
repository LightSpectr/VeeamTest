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

                    case 0: statusSting = "Остановлен";
                        break;

                    case 2:
                        statusSting = "Выполняется";
                        break;

                }
                dataGridView1.Rows.Add(service.DisplayName, serviceManager.ServiceName, statusSting);
              
            }
       

        }

        private void dataGridView1_SelectionChanged(object sender, EventArgs e)
        {
            if (dataGridView1.SelectedRows.Count == 0)
            {
                StartButton.Enabled = false;
                StopButton.Enabled = false;
                ReloadButton.Enabled = false;
            }
            else
            {
                if (dataGridView1.SelectedRows[0].Cells[2].Value.ToString() == "Остановлен")
                {
                    StartButton.Enabled = true;
                    StopButton.Enabled = false;
                    ReloadButton.Enabled = false;

                }
                else if (dataGridView1.SelectedRows[0].Cells[2].Value.ToString() == "Выполняется")
                {
                    StartButton.Enabled = false;
                    StopButton.Enabled = true;
                    ReloadButton.Enabled = true;
                }
            }
            
        }
    }
}