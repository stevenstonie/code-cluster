using System;
using System.Collections.Generic;
using System.IO;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Threading;

namespace MemoryTilesGame {
	public partial class GameWindow : Window {
		DispatcherTimer _timer;
		TimeSpan _time;
		private int button1ListIndex;
		private int button1ImageId;
		private Button button1;
		List<KeyValuePair<int, ImageBrush>> imagesList; // param1 - id, param2 - image

		public GameWindow(int cols, int rows) {
			InitializeComponent();
			button1ListIndex = -1;
			button1ImageId = -1;
			button1 = null;
			imagesList = new List<KeyValuePair<int, ImageBrush>>();

			createGrid(cols, rows);

			addImagesToGrid(cols, rows);

			placeTimer();
		}

		private void createGrid(int cols, int rows) {
			// Create the rows of the grid
			for(int i = 0; i < rows; i++) {
				RowDefinition rowDef = new RowDefinition();
				GameGrid.RowDefinitions.Add(rowDef);
			}

			// Create the columns of the grid
			for(int i = 0; i < cols; i++) {
				ColumnDefinition colDef = new ColumnDefinition();
				GameGrid.ColumnDefinitions.Add(colDef);
			}

			// Create the buttons and add them to the grid
			for(int i = 0; i < rows; i++) {
				for(int j = 0; j < cols; j++) {
					Button button = new Button();
					button.MinHeight = 50;
					button.MinWidth = 50;
					button.Margin = new Thickness(3);

					button.Click += Button_Click; // add event handler

					Grid.SetRow(button, i);
					Grid.SetColumn(button, j);
					GameGrid.Children.Add(button);
				}
			}

			GameGrid.VerticalAlignment = VerticalAlignment.Top;
			GameGrid.HorizontalAlignment = HorizontalAlignment.Left;
			GameGrid.Margin = new Thickness(0, 40, 0, 50);

			// Add a SizeChanged event handler for the window
			this.SizeChanged += (sender, e) => {
				// Calculate the new button size based on the window size
				double size = Math.Min((this.ActualWidth - GameGrid.Margin.Right) / cols, this.ActualHeight / rows);

				// Update the button sizes
				foreach(var child in GameGrid.Children) {
					if(child is Button button) {
						button.Width = size;
						button.Height = size;
					}
				}
			};
		}

		private void addImagesToGrid(int cols, int rows) {
			// specify the folder path where your images are stored
			string folderPath = Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "Assets", "Images");

			// get the file names of all the images in the folder
			string[] images = Directory.GetFiles(folderPath, "*.png");

			// put images in a list
			for(int i = 0; i < cols * rows / 2; i++) {
				imagesList.Add(new KeyValuePair<int, ImageBrush>(i, new ImageBrush { ImageSource = new BitmapImage(new Uri(images[i], UriKind.Relative)) }));
				imagesList.Add(new KeyValuePair<int, ImageBrush>(i, new ImageBrush { ImageSource = new BitmapImage(new Uri(images[i], UriKind.Relative)) }));
			}

			//shuffle the list
			Random random = new Random();
			imagesList.Sort((a, b) => random.Next(2) == 0 ? -1 : 1);


			// Loop through each button and assign an image and a tag to it (the tag represents the index in the list)
			int index = 0;
			foreach(var child in GameGrid.Children) {
				if(child is Button button) {
					button.Tag = index++;
					button.Background = new ImageBrush(new BitmapImage(new Uri("Assets/greysquare.png", UriKind.Relative)));
				}
			}
		}

		private void placeTimer() {
			_time = TimeSpan.FromSeconds(10);
			tbTime.Margin = new Thickness(0, 0, GameGrid.ActualWidth - tbTime.ActualWidth, 0);

			_timer = new DispatcherTimer(new TimeSpan(0, 0, 1), DispatcherPriority.Normal, delegate {
				tbTime.Text = _time.ToString("c");
				if(_time == TimeSpan.Zero) {
					_timer.Stop();
					youLostMessage.Text = "the time is up. you lost..";
				}
				_time = _time.Add(TimeSpan.FromSeconds(-1));
			}, System.Windows.Application.Current.Dispatcher);


			_timer.Start();
		}

		private async void Button_Click(object sender, RoutedEventArgs e) {
			Console.WriteLine("tag: " + ((Button)sender).Tag);

			// disable the mouse for the entire grid
			IsHitTestVisible = false;

			// first flipped image
			if(button1ListIndex == -1) {
				button1ListIndex = (int)((Button)sender).Tag;
				button1ImageId = imagesList[button1ListIndex].Key;
				button1 = (Button)sender;
				button1.Background = imagesList[button1ListIndex].Value;

				await Task.Delay(700);
			}
			// second flipped image
			else {
				((Button)sender).Background = imagesList[(int)((Button)sender).Tag].Value;
				await Task.Delay(700);

				// have the same imageid but different button
				if(imagesList[(int)((Button)sender).Tag].Key == button1ImageId && ((Button)sender) != button1) {
					((Button)sender).Background = imagesList[(int)((Button)sender).Tag].Value;

					((Button)sender).IsEnabled = button1.IsEnabled = false;
				}
				else {
					((Button)sender).Background = button1.Background = new ImageBrush(new BitmapImage(new Uri("Assets/greysquare.png", UriKind.Relative)));
				}

				button1 = null;
				button1ImageId = -1;
				button1ListIndex = -1;
			}

			// reenable the mouse for the entire grid
			IsHitTestVisible = true;
		}
	}
}

// notes here:
// - change the datatype of the imagesList from <int, image> to <int, string> where string is the path of the images
// - add more images
// - get parameter of how many cols and rows should the grid have. (also limit the cols and rows to a maximum and also make sure one is even)
// - redo the timer and the lose case.
