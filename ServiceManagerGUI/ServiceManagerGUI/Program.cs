using Microsoft.Win32;
using System.Security.Principal;
namespace ServiceManagerGUI
{
    internal static class Program
    {
        /// <summary>
        ///  The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            // To customize application configuration such as set high DPI settings or default font,
            // see https://aka.ms/applicationconfiguration.

            //�������� ��� ������ COM ������ ���������������
            RegistryKey clsid = Registry.ClassesRoot.OpenSubKey("Interface");
            if (!clsid.GetSubKeyNames().Contains("{4557E734-2814-4B45-BFB7-D074C5219B78}"))
            {
                string message = "�������������������� ������ dll ����������.";
                MessageBox.Show(
                    message,
                    "������",
                    MessageBoxButtons.OK,    
                    MessageBoxIcon.Error 
                );

            }
            else
            {
                // �������� ��� � ��������� ���� ����� �������������� 
                bool isElevated;
                using (WindowsIdentity identity = WindowsIdentity.GetCurrent())
                {
                    WindowsPrincipal principal = new WindowsPrincipal(identity);
                    isElevated = principal.IsInRole(WindowsBuiltInRole.Administrator);
                }
                if (isElevated)
                {
                    // ������ �����
                    ApplicationConfiguration.Initialize();
                    Application.Run(new MainForm());
                }
                else
                {
                    string message = "� ��������� ��� ���� ��������������";
                    MessageBox.Show(
                        message,
                        "������",
                        MessageBoxButtons.OK,
                        MessageBoxIcon.Error
                    );
                }
                
            }
        }
    }
}
