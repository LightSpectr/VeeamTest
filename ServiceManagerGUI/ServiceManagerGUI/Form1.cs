using ServiceControlCOMLib;
using System.Runtime.InteropServices;

namespace ServiceManagerGUI
{
    public partial class MainForm : Form
    {
        ServiceManager serviceManager;
        public MainForm()
        {
            InitializeComponent();
            serviceManager = new ServiceManager(); // COM объект 
        }

        private void MainForm_Load(object sender, EventArgs e)
        {
            UpdateService(); // загрузка списка служб
        }

        // запуск выделенной службы
        private void StartButton_Click(object sender, EventArgs e)
        {
            StartButton.Enabled = false;
            byte status = 100;
            try
            {
                serviceManager.ServiceName = dataGridView1.SelectedRows[0].Cells[0].Value.ToString();
                serviceManager.startSvc();
                
                string msg = "Служба " + dataGridView1.SelectedRows[0].Cells[0].Value.ToString() + " запущена";
                MessageBox.Show(msg);
            }
            catch (COMException comEx)
            {
                errorToMessage(comEx);
            }
            try
            {
                serviceManager.chkStatus(out status);
            }
            catch (COMException comEx)
            {
                errorToMessage(comEx);
            }
            dataGridView1.SelectedRows[0].Cells[1].Value = statusToString(status);
            updateButtons();
            

        }

        // остановка службы
        private void StopButton_Click(object sender, EventArgs e)
        {

            StopButton.Enabled = false;
            ReloadButton.Enabled = false;
            byte status = 100;
            try
            {
                serviceManager.ServiceName = dataGridView1.SelectedRows[0].Cells[0].Value.ToString();
                serviceManager.stopSvc();
                
                string msg = "Служба " + dataGridView1.SelectedRows[0].Cells[0].Value.ToString() + " остановлена";
                MessageBox.Show(msg);
            }
            catch (COMException comEx)
            {
                errorToMessage(comEx);
            }
            try
            {
                serviceManager.chkStatus(out status);
            }
            catch (COMException comEx)
            {
                errorToMessage(comEx);
            }
            dataGridView1.SelectedRows[0].Cells[1].Value = statusToString(status);
            updateButtons();

        }

        //остановка и зупуск 
        private void ReloadButton_Click(object sender, EventArgs e)
        {
             StopButton.Enabled = false;
            ReloadButton.Enabled = false;
            byte status = 100;
            try
            {
                serviceManager.ServiceName = dataGridView1.SelectedRows[0].Cells[0].Value.ToString();
                serviceManager.stopSvc();
                serviceManager.startSvc();
                string msg = "Служба " + dataGridView1.SelectedRows[0].Cells[0].Value.ToString() + " перезапущена";
                MessageBox.Show(msg);
            }
            catch (COMException comEx)
            {
                errorToMessage(comEx);
            }
            try
            {
                serviceManager.chkStatus(out status);
            }
            catch (COMException comEx)
            {
                errorToMessage(comEx);
            }
            dataGridView1.SelectedRows[0].Cells[1].Value = statusToString(status);
            updateButtons();
        }

        // обновление списка служб
        private void UpdateButton_Click(object sender, EventArgs e)
        {
           
            dataGridView1.Rows.Clear();
            dataGridView1.Refresh();
            UpdateService();
        }

        private void UpdateService()
        {
            try
            {
                string[] services = serviceManager.AllSvcNames.Split('\n');
               
                foreach (string service in services)
                {
                    if (service != "")
                    {
                        serviceManager.ServiceName = service;
                        byte status = 100;
                        serviceManager.chkStatus(out status);
                        dataGridView1.Rows.Add(service, statusToString(status));
                    }
                   
                }
     
            }
            catch (COMException comEx)
            {
                errorToMessage(comEx);
            }
            serviceManager.clearMem();
        }

        
        private void dataGridView1_SelectionChanged(object sender, EventArgs e)
        {

            updateButtons();
        }

        // данные о службе 
        private void infoButton_Click(object sender, EventArgs e)
        {
            byte status;
            try
            {
                serviceManager.ServiceName = dataGridView1.SelectedRows[0].Cells[0].Value.ToString();
                serviceManager.chkStatus(out status);
                string msg = "Данные о службе:\nCurrentState: " + serviceManager.CurrentState + "\nExitCode: " + serviceManager.ExitCode +
                       "\nCheckPoint: " + serviceManager.CheckPoint + "\nWaitHint: " + serviceManager.WaitHint;
                MessageBox.Show(msg);
            }
            catch (COMException comEx)
            {
                errorToMessage(comEx);
            }

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

        // смена активных кнопок в зависимости от статуса службы
        private void updateButtons()
        {
            if (dataGridView1.SelectedRows.Count == 0)
            {
                StartButton.Enabled = false;
                StopButton.Enabled = false;
                ReloadButton.Enabled = false;
                infoButton.Enabled = false;
            }
            else
            {
                if (dataGridView1.SelectedRows[0].Cells[1].Value.ToString() == "Остановлен")
                {
                    StartButton.Enabled = true;
                    StopButton.Enabled = false;
                    ReloadButton.Enabled = false;
                    infoButton.Enabled = true;

                }
                else if (dataGridView1.SelectedRows[0].Cells[1].Value.ToString() == "Выполняется")
                {
                    StartButton.Enabled = false;
                    StopButton.Enabled = true;
                    ReloadButton.Enabled = true;
                    infoButton.Enabled = true;
                }
            }
        }

        // вывод окна с ошибкой при получении ошибки от COM объекта
        private void errorToMessage(COMException comEx)
        {
            string msg;
            switch ((uint)comEx.ErrorCode)
            {
                case 0x80004004: //E_ABORT
                    msg = "Не получилось запусть службу, данные службы:\nCurrentState: " + serviceManager.CurrentState + "\nExitCode: " + serviceManager.ExitCode +
                        "\nCheckPoint: " + serviceManager.CheckPoint + "\nWaitHint: " + serviceManager.WaitHint;
                    MessageBox.Show(msg, 
                        "Ошибка",
                        MessageBoxButtons.OK,
                        MessageBoxIcon.Error);
                    break;

                case 0x80004005: //E_FAIL
                    msg = "Код ошибки: " + serviceManager.LastError;
                    MessageBox.Show(msg,
                        "Ошибка",
                        MessageBoxButtons.OK,
                        MessageBoxIcon.Error);
                    break;

            }
        }

       
    }
}
