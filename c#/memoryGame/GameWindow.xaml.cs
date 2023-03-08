

using System;
using System.Windows;
using System.Windows.Threading;

namespace memoryGame {
	public partial class GameWindow : Window {
		DispatcherTimer _timer;
		TimeSpan _time;

		public GameWindow() {
			InitializeComponent();

			_time = TimeSpan.FromSeconds(4);

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

		private void loadPictures() {

		}


		/*
		// create a list of images
		List<string> images = new List<string>();
		for(int i = 0; i < 6; i++) {
			images.Add("Assets/GridImages/" + i + ".png");
		}

		// shuffle the list
		Random random = new Random();
		images = images.OrderBy(x => random.Next()).ToList();

		// load the images into the grid
		for(int i = 0; i < 6; i++) {
			Image image = new Image();
			image.Source = new BitmapImage(new Uri(images[i]));
			image.Stretch = Stretch.Fill;
			image.Margin = new Thickness(5);
			image.MouseDown += new MouseButtonEventHandler(image_MouseDown);
			grid.Children.Add(image);
		}
		*/


	}
}
