using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Compiler_UI_2018B
{
    public partial class Form1 : Form
    {
        Compiler_Project_2018B.Manager Compiler;
        public Form1()
        {
            InitializeComponent();
            Compiler = new Compiler_Project_2018B.Manager();
        }

        private void compileToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            String[] CompDetails = Compiler.Compile(UserInput.Text);
            Info.Lines = CompDetails;
        }

        private void Info_TextChanged(object sender, EventArgs e)
        {

        }

        private void ErrorSpace_TextChanged(object sender, EventArgs e)
        {

        }
    }
}