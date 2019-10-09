using System;
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
using System.Windows.Shapes;

namespace CASCLib.NET.Example
{
	/// <summary>
	/// Interaction logic for ProgressWindow.xaml
	/// </summary>
	public partial class ProgressWindow : Window
	{
		public bool HasCancelled = false;

		public ProgressWindow()
		{
			InitializeComponent();
		}

		private void WindowClosing(object sender, System.ComponentModel.CancelEventArgs e)
		{
			e.Cancel = !HasCancelled;
		}

		public void Complete()
		{
			ProgressBar.Value = ProgressBar.Maximum;
			HasCancelled = true;
			Close();
		}

		private void CancelClick(object sender, RoutedEventArgs e)
		{
			HasCancelled = true;
		}

		public void SetProgressCount(double value)
		{
			// Invoke dispatcher to update UI
			Dispatcher.BeginInvoke(new Action(() =>
			{
				ProgressBar.Maximum = value;
				ProgressBar.Value = 0;
			}));
		}

		public void SetTotalProgressCount(double value)
		{
			// Invoke dispatcher to update UI
			Dispatcher.BeginInvoke(new Action(() =>
			{
				TotalProgressBar.Maximum = value;
				TotalProgressBar.Value = 0;
			}));
		}

		public void SetProgressMessage(string value)
		{
			// Invoke dispatcher to update UI
			Dispatcher.BeginInvoke(new Action(() =>
			{
				Message.Content = value;
			}));
		}

		public bool IncrementProgress()
		{
			// Invoke dispatcher to update UI
			Dispatcher.BeginInvoke(new Action(() =>
			{
				ProgressBar.Value++;
			}));

			// Return whether we've cancelled or not
			return HasCancelled;
		}

		public bool IncrementTotalProgress()
		{
			// Invoke dispatcher to update UI
			Dispatcher.BeginInvoke(new Action(() =>
			{
				TotalProgressBar.Value++;
			}));

			// Return whether we've cancelled or not
			return HasCancelled;
		}
	}
}
