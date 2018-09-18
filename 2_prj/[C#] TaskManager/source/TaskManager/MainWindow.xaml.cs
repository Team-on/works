using System;
using System.Management;
using System.Diagnostics;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace TaskManager {
    public partial class MainWindow : Window {
        List<MyProcess> pr;

        public MainWindow() {
            InitializeComponent();
            pr = new List<MyProcess>();
            dataGrid.ItemsSource = pr;

            dataGrid.Columns.Add(new DataGridTextColumn() {
                Header = "PID",
                Binding = new Binding("Id"),
            });

            dataGrid.Columns.Add(new DataGridTextColumn() {
                Header = "ProcessName",
                Binding = new Binding("ProcessName"),
            });

            dataGrid.Columns.Add(new DataGridTextColumn() {
                Header = "Owner",
                Binding = new Binding("GetProcessOwner"),
            });

            dataGrid.Columns.Add(new DataGridTextColumn() {
                Header = "TotalProcessorTime",
                Binding = new Binding("TotalProcessorTime"),
            });

            dataGrid.Columns.Add(new DataGridTextColumn() {
                Header = "UserProcessorTime",
                Binding = new Binding("UserProcessorTime"),
            });

            dataGrid.Columns.Add(new DataGridTextColumn() {
                Header = "Used memory",
                Binding = new Binding("PrivateMemorySize"),
            });
        }

        private void Window_Loaded(object sender, RoutedEventArgs e) {
            foreach (var p in Process.GetProcesses())
                pr.Add(p.ToMyPrcess());
            dataGrid.Items.Refresh();

            System.Timers.Timer t = new System.Timers.Timer() {
                AutoReset = true,
                Interval = 5000,
                Enabled = false,
            };
            t.Elapsed += T_Elapsed;
            //t.Start();
        }

        private void T_Elapsed(object sender, System.Timers.ElapsedEventArgs e) {
            RefreshTable(null, null);
        }

        void RefreshTable(object sender, EventArgs args) {
            //var proc = Process.GetProcesses();
            //MyProcess[] mproc = new MyProcess[proc.Length];
            //for (int i = 0; i < proc.Length; ++i) {
            //    mproc[i] = proc[i].ToMyPrcess();
            //}

            //foreach (var i in pr) {
            //    var f = mproc.First((a) => i.Id == a.Id);
            //    if (f)
            //        i.Update(f);
            //    else
            //        pr.Remove(i);
            //}
            var prr = Process.GetProcesses();

            pr.Clear();
            foreach (var i in prr) {
                pr.Add(i.ToMyPrcess());
            }
            dataGrid.Items.Refresh();
        }

        private void dataGrid_MouseDoubleClick(object sender, MouseButtonEventArgs e) {
            // Application.Current.Dispatcher.Invoke(() => {
            if (dataGrid.SelectedItem == null)
                return;

            try {
                MyProcess p = (MyProcess)dataGrid.SelectedItem;

                pr.Remove(p);
                dataGrid.Items.Refresh();
                //p.Kill();

                string arg = $@"/c taskkill /f /pid {p.Id}";
                ProcessStartInfo process = new ProcessStartInfo("cmd") {
                    UseShellExecute = true,
                    CreateNoWindow = true,
                    //Verb = "runas",
                    Arguments = arg,
                };
                Process.Start(process);
            }
            catch (Exception ex) {
                MessageBox.Show(ex.Message + '\n' + ex.StackTrace);
            }
            //});
        }

        private void Button_Click(object sender, RoutedEventArgs e) {

        }
    }

    class MyProcess //: Process 
        {
        Type type =typeof(MyProcess);

        public int Id { get; set; }
        public string ProcessName { get; set; }
        public int PrivateMemorySize { get; set; }

        public MyProcess() {

        }

        public static implicit operator bool(MyProcess b) {
            return b == null;
        }

        public MyProcess(Process pr) {
            //foreach (var prop in pr.GetType().GetProperties())
            //    type.GetProperty(prop.Name).SetValue(this, prop.GetValue(pr));
            //foreach (var field in pr.GetType().GetFields())
            //    type.GetField(field.Name).SetValue(this, field.GetValue(pr));

            Id = pr.Id;
            ProcessName = pr.ProcessName;
            PrivateMemorySize = pr.PrivateMemorySize;

            //foreach (var i in pr.GetType().GetProperties())
            //    type.GetProperty(i.Name)?.SetValue(this, i.GetValue(pr));
        }

        public void Update(Process pr) {
            Id = pr.Id;
            ProcessName = pr.ProcessName;
            PrivateMemorySize = pr.PrivateMemorySize;
            // foreach (var i in pr.GetType().GetProperties())
            //    type.GetProperty(i.Name)?.SetValue(this, i.GetValue(pr));
        }

        public void Update(MyProcess pr) {
            Id = pr.Id;
            ProcessName = pr.ProcessName;
            PrivateMemorySize = pr.PrivateMemorySize;
            // foreach (var i in pr.GetType().GetProperties())
            //     type.GetProperty(i.Name)?.SetValue(this, i.GetValue(pr));
        }

        public string GetProcessOwner {
            get {
                string query = $"Select * From Win32_Process Where ProcessID = {Id}";
                ManagementObjectSearcher searcher = new ManagementObjectSearcher(query);
                ManagementObjectCollection processList = searcher.Get();

                foreach (ManagementObject obj in processList) {
                    string[] argList = new string[] { string.Empty, string.Empty };
                    int returnVal = Convert.ToInt32(obj.InvokeMethod("GetOwner", argList));
                    if (returnVal == 0) {
                        // return DOMAIN\user
                        return argList[1] + "\\" + argList[0];
                    }
                }

                return "NO OWNER";
            }
        }
    }

    static class Ext {
        public static MyProcess ToMyPrcess(this Process pr) {
            return new MyProcess(pr);
        }
    }
}
