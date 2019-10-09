using System;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.IO;
using System.Linq;
using System.Threading;
using System.Windows;
using CASCLibNET;


namespace CASCLib.NET.Example
{
	/// <summary>
	/// Interaction logic for MainWindow.xaml
	/// </summary>
	public partial class MainWindow : Window
	{
		public class CASCFile : INotifyPropertyChanged
		{
			private string _FileName { get; set; }

			public string FileName
			{
				get
				{
					return _FileName;
				}
				set
				{
					_FileName = value;
					OnPropertyChanged("FileName");
				}
			}

			private long _Size { get; set; }

			public long Size
			{
				get
				{
					return _Size;
				}
				set
				{
					_Size = value;
					OnPropertyChanged("Size");
				}
			}

			private string _IsLocal { get; set; }

			public string IsLocal
			{
				get
				{
					return _IsLocal;
				}
				set
				{
					_IsLocal = value;
					OnPropertyChanged("IsLocal");
				}
			}

			public CASCFile(string fileName, long fileSize, bool isLocal)
			{
				FileName = fileName;
				Size = fileSize;
				IsLocal = isLocal ? "Yes" : "No";
			}

			public event PropertyChangedEventHandler PropertyChanged;

			protected void OnPropertyChanged(string name)
			{
				PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(name));
			}
		}

		public ObservableCollection<CASCFile> CASCFiles { get; } = new ObservableCollection<CASCFile>();

		CASCStorage Storage { get; set; }

		public MainWindow()
		{
			DataContext = this;
			InitializeComponent();
		}

		private void OpenStorageClick(object sender, RoutedEventArgs e)
		{
			CASCFiles.Clear();
			Storage?.Dispose();

			using(var folderDialog = new System.Windows.Forms.FolderBrowserDialog()
			{
				Description = "Open CASC Storage",
				ShowNewFolderButton = false
			})
			{
				if(folderDialog.ShowDialog() == System.Windows.Forms.DialogResult.OK)
				{
					try
					{
						Storage = new CASCStorage(folderDialog.SelectedPath);

						foreach(var file in Storage.Files)
						{
							CASCFiles.Add(new CASCFile(file.FileName, file.FileSize, file.IsLocal));
						}
					}
					catch
					{
						Storage?.Dispose();
						MessageBox.Show(
							"Failed to open CASC Storage. Ensure that the storage is intact and exists at the given location.",
							"CASCLib.NET.Example | ERROR",
							MessageBoxButton.OK, MessageBoxImage.Error);
					}
				}
			}
		}

		private void ExtractFileClick(object sender, RoutedEventArgs e)
		{
			var files = FileList.SelectedItems.Cast<CASCFile>().ToList();

			if(files.Count == 0)
				files = FileList.Items.Cast<CASCFile>().ToList();

			if (files.Count == 0)
			{
				MessageBox.Show(
					"No files provided to extract.", 
					"CASCLib.NET.Example | ERROR", 
					MessageBoxButton.OK, 
					MessageBoxImage.Error);
				return;
			}

			var outputFolder = "";

			using (var folderDialog = new System.Windows.Forms.FolderBrowserDialog()
			{
				Description = "Select Output Folder",
			})
			{
				if (folderDialog.ShowDialog() == System.Windows.Forms.DialogResult.OK)
				{
					outputFolder = folderDialog.SelectedPath;
				}
				else
				{
					return;
				}
			}

			var progressWindow = new ProgressWindow()
			{
				Owner = this,
				Title = "CASCLib.NET.Example | Working"
			};

			Dispatcher.BeginInvoke(new Action(() => progressWindow.ShowDialog()));

			new Thread(() =>
			{
				var buffer = new byte[0x800000];

				progressWindow.SetTotalProgressCount(files.Count);

				foreach(var file in files)
				{
					if(file.IsLocal == "Yes")
					{
						progressWindow.SetProgressMessage(string.Format("Extracting {0}...", Path.GetFileName(file.FileName)));
						progressWindow.SetProgressCount(file.Size / 0x800000);

						var newPath = Path.Combine(outputFolder, file.FileName);
						Directory.CreateDirectory(Path.GetDirectoryName(newPath));

						try
						{
							using (var input = Storage.OpenFile(file.FileName))
							using (var output = File.Create(newPath))
							{
								while(true)
								{
									var bytesRead = input.Read(buffer, 0, 0x800000);
									output.Write(buffer, 0, bytesRead);

									if (progressWindow.IncrementProgress())
										break;

									if (bytesRead < 0x800000)
										break;
								}
							}
						}
						catch(Exception ex)
						{
							Console.WriteLine(ex);
						}
					}

					if (progressWindow.IncrementTotalProgress())
						break;
				}

				Dispatcher.BeginInvoke(new Action(() =>
				{
					progressWindow.Complete();
					GC.Collect();
				}));
			}).Start();
		}

		private void CloseStorageClick(object sender, RoutedEventArgs e)
		{
			CASCFiles.Clear();
			Storage?.Dispose();
			GC.Collect();
		}
	}
}
