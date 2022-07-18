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
            StartButton.Enabled = false;
            byte status = 100;
            try
            {
                serviceManager.ServiceName = dataGridView1.SelectedRows[0].Cells[1].Value.ToString();
                serviceManager.startSvc();
                serviceManager.chkStatus(out status);
            }
            catch (COMException comEx)
            {
                switch ((uint)comEx.ErrorCode)
                {
                    case 0x80004004: //E_ABORT
                        MessageBox.Show(Convert.ToString(serviceManager.CurrentState));
                        break;

                    case 0x80004005: //E_FAIL
                        MessageBox.Show(Convert.ToString(serviceManager.LastError));
                        break;

                }
            }
            dataGridView1.SelectedRows[0].Cells[2].Value = statusToString(status);
            updateButtons();

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
                try
                {
                    serviceManager.chkStatus(out status);
                }
                catch (COMException comEx)
                {
                    status = 100;
                }
                dataGridView1.Rows.Add(service.DisplayName, serviceManager.ServiceName, statusToString(status));
              
            }
       

        }

        private void dataGridView1_SelectionChanged(object sender, EventArgs e)
        {

            updateButtons();
        }

        private string statusToString(byte status)
        {
            switch (status)
            {

                case 0:
                    return "Остановлен";  

                case 2:
                    return "Выполняется";

            }

            return "Ошибка";
        }
        private void updateButtons()
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