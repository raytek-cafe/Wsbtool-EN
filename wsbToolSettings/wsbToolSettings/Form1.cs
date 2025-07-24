using Microsoft.Win32;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace wsbToolSettings
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Button1_Click(object sender, EventArgs e)
        {
            string Folder = Environment.GetEnvironmentVariable("ALLUSERSPROFILE");
            Folder += "\\Windows Style Builder\\Testing";
            Process.Start("explorer.exe", Folder);
        }

        private void Button2_Click(object sender, EventArgs e)
        {
            string Folder = Environment.GetEnvironmentVariable("WINDIR");
            Folder += "\\Resources\\Themes";
            Process.Start("explorer.exe", Folder);
        }

        /// <summary>
        /// 读取注册表字符串值
        /// </summary>
        /// <param name="path">路径</param>
        /// <param name="paramName">键名称</param>
        /// <returns></returns>
        public string GetRegistryValue(string path, string paramName)
        {
            string value = string.Empty;
            RegistryKey root = Registry.CurrentUser;
            RegistryKey rk = root.OpenSubKey(path);
            if (rk != null)
            {
                value = (string)rk.GetValue(paramName, null);
            }
            return value;
        }

        private void Button3_Click(object sender, EventArgs e)
        {
            string Folder = GetRegistryValue(@"Software\Ave Apps\Windows Style Builder\Recent Document List", "Document1");
            Process.Start("explorer.exe", "/select," + Folder);
        }

        private void Button4_Click(object sender, EventArgs e)
        {
            if(MessageBox.Show("Are you sure you want to disable the extension? Please save your theme first to avoid losing it! Click OK to disable it immediately and restart the program. (To restore the extension, delete the noLib file in the Data directory.)",
                "Are you sure?", MessageBoxButtons.YesNo, MessageBoxIcon.Question) == DialogResult.Yes)
            {
                //创建标识文件
                FileInfo f = new FileInfo("./Data/noLib");
                if (!f.Exists)
                    f.Create();
                //结束进程 & 重启程序
                Process mainp = Process.GetProcessById(Program.ProcessID);
                mainp.Kill();
                Process.Start(Application.StartupPath + "\\wsbTool.exe");
                Dispose();
                Application.Exit();
            }
        }

        private void button5_Click(object sender, EventArgs e)
        {
            Credits creditsForm = new Credits();
            creditsForm.Show();
            creditsForm.Focus();
        }
    }
}
