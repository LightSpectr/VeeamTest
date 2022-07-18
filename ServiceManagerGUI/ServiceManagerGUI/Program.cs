using Microsoft.Win32;
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
            RegistryKey clsid = Registry.ClassesRoot.OpenSubKey("Interface");
            if (!clsid.GetSubKeyNames().Contains("{4557E734-2814-4B45-BFB7-D074C5219B78}"))
            {
                string message = "Незарегистрированная нужная dll библиотека.";
                MessageBox.Show(
                    message,
                    "Ошибка",
                    MessageBoxButtons.OK,    
                    MessageBoxIcon.Error 
                );

            }
            else
            {
                ApplicationConfiguration.Initialize();

                Application.Run(new MainForm());
            }
        }
    }
}