using System;
using System.Diagnostics;
using System.Windows.Forms;

namespace wsbToolSettings
{
    public partial class Credits: Form
    {
        public Credits()
        {
            InitializeComponent();
        }

        private void button5_Click(object sender, EventArgs e)
        {
            Process.Start("https://github.com/Maplespe/Tool");
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Process.Start("https://winmoes.com/tools/5249.html");
        }

        private void button2_Click(object sender, EventArgs e)
        {
         Process.Start("https://github.com/raytek-cafe/Wsbtool-EN");
        }

        private void button3_Click(object sender, EventArgs e)
        {
            Process.Start("https://www.vistastylebuilder.com/");
        }
    }
}
