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
using System.Windows.Navigation;
using System.Windows.Shapes;


namespace GraphSity {
	public partial class MainWindow : Window {
		CurrentMode currMode;
		NodesControl nodes;
		List<Grid> sities;
		List<Line> lines;

		bool moveNode;
		int moveNodeId;
		bool pathStart;
		int pathStartId, pathEndId;
		Point pathStartPoint, pathEndPoint;

		public MainWindow() {
			InitializeComponent();
			nodes = new NodesControl();
			currMode = CurrentMode.None;
			sities = new List<Grid>();
			lines = new List<Line>();

			//nodes.AddNode();
			//nodes.AddNode();
			//nodes.AddNode();
			//nodes.AddNode();
			//nodes.AddNode();
			//nodes.AddNode();
			//nodes.AddNode();

			//nodes.AddPath(0, 1, 10);
			//nodes.AddPath(0, 2, 30);
			//nodes.AddPath(0, 4, 40);
			//nodes.AddPath(1, 2, 20);
			//nodes.AddPath(1, 3, 20);
			//nodes.AddPath(3, 2, 5);
			//nodes.AddPath(4, 3, 10);

			//nodes.AddPath(0, 4, 40);
			//nodes.AddPath(0, 3, 80);
			//nodes.AddPath(0, 1, 10);
			//nodes.AddPath(1, 4, 20);
			//nodes.AddPath(1, 2, 20);
			//nodes.AddPath(2, 3, 14);
			//nodes.AddPath(4, 3, 30);

			//nodes.AddPath(0, 1, 10);
			//nodes.AddPath(0, 2, 20);
			//nodes.AddPath(0, 5, 100);
			//nodes.AddPath(1, 3, 80);
			//nodes.AddPath(1, 4, 60);
			//nodes.AddPath(2, 1, 70);
			//nodes.AddPath(2, 3, 70);
			//nodes.AddPath(3, 5, 75);
			//nodes.AddPath(4, 5, 60);
		}

		private void AddSityMode(object sender, RoutedEventArgs e) {
			if (currMode != CurrentMode.AddSity) {
				currMode = CurrentMode.AddSity;
				this.Cursor = Cursors.Hand;
			}
			else {
				currMode = CurrentMode.None;
				this.Cursor = Cursors.Arrow;
			}
		}

		private void RemoveSityMode(object sender, RoutedEventArgs e) {
			if (currMode != CurrentMode.RemoveSity) {
				currMode = CurrentMode.RemoveSity;
				this.Cursor = Cursors.No;
			}
			else {
				currMode = CurrentMode.None;
				this.Cursor = Cursors.Arrow;
			}
		}

		private void AddPathMode(object sender, RoutedEventArgs e) {
			if (currMode != CurrentMode.AddPath) {
				currMode = CurrentMode.AddPath;
				this.Cursor = Cursors.Cross;
				pathStart = true;
			}
			else {
				currMode = CurrentMode.None;
				this.Cursor = Cursors.Arrow;
			}
		}

		private void RemovePathMode(object sender, RoutedEventArgs e) {
			if (currMode != CurrentMode.RemovePath) {
				currMode = CurrentMode.RemovePath;
				this.Cursor = Cursors.Wait;
			}
			else {
				currMode = CurrentMode.None;
				this.Cursor = Cursors.Arrow;
			}
		}

		private void FindPathMode(object sender, RoutedEventArgs e) {
			if (currMode != CurrentMode.FindPath) {
				currMode = CurrentMode.FindPath;
				this.Cursor = Cursors.Help;
				pathStart = true;
			}
			else {
				currMode = CurrentMode.None;
				this.Cursor = Cursors.Arrow;
			}
		}

		private void ChangePathMode(object sender, RoutedEventArgs e) {
			if (currMode != CurrentMode.ChangePath) {
				currMode = CurrentMode.ChangePath;
				this.Cursor = Cursors.ArrowCD;
			}
			else {
				currMode = CurrentMode.None;
				this.Cursor = Cursors.Arrow;
			}
		}

		void CreateNewNode(object sender, MouseButtonEventArgs e) {
			if (currMode == CurrentMode.AddSity && e.ClickCount == 1) {
				var pos = e.GetPosition(field);
				var rnd = new Random();
				sities.Add(new Grid() {
					Tag = new SityInfo(nodes.AddNode(), pos),
					Height = 30,
					Width = 30,
					Background = new SolidColorBrush(Color.FromRgb((byte)rnd.Next(0, 256), (byte)rnd.Next(0, 256), (byte)rnd.Next(0, 256)))
				});

				var elem = sities[sities.Count - 1];
				Canvas.SetLeft(elem, pos.X - elem.Width / 2);
				Canvas.SetTop(elem, pos.Y - elem.Height / 2);
				Canvas.SetZIndex(elem, 2);
				field.Children.Add(elem);

				elem.MouseLeftButtonDown += Elem_MouseLeftButtonDown;

				void Elem_MouseLeftButtonDown(object isender, MouseButtonEventArgs ie) {
					if (e.ClickCount == 1) {
						moveNode = false;
						if (currMode == CurrentMode.RemoveSity) {
							int id = (elem.Tag as SityInfo).nodeId;
							field.Children.Remove(elem);
							nodes.RemoveNode(id);
							sities.RemoveAt(id);
							for (int i = id; i < sities.Count; ++i)
								--(sities[i].Tag as SityInfo).nodeId;

							REPEATDELETE:
							foreach (var i in lines) {
								LineInfo lineInfo = i.Tag as LineInfo;
								if(lineInfo.id1 == id || lineInfo.id2 == id) {
									field.Children.Remove(i);
									field.Children.Remove((i.Tag as LineInfo).label);
									lines.Remove(i);
									goto REPEATDELETE;
								}
							}

							foreach (var i in lines) {
								LineInfo lineInfo = i.Tag as LineInfo;
								if (lineInfo.id1 >= id)
									--lineInfo.id1;
								if (lineInfo.id2 >= id)
									--lineInfo.id2;
							}
							}
						else if (currMode == CurrentMode.AddPath) {
							int id = (elem.Tag as SityInfo).nodeId;
							if (pathStart) {
								pathStartId = id;
								pathStartPoint = new Point( Canvas.GetLeft(elem) + elem.Width / 2, Canvas.GetTop(elem) + elem.Height / 2);
							}
							else {
								pathEndId = id;
								pathEndPoint = new Point(Canvas.GetLeft(elem) + elem.Width / 2, Canvas.GetTop(elem) + elem.Height / 2);
								if (pathEndId != pathStartId && !nodes.HavePath(pathStartId, pathEndId)) {
									InputLength len = new InputLength();
									len.ShowDialog();
									if (len.length != 0) {
										lines.Add(new Line() { X1 = pathStartPoint.X, Y1 = pathStartPoint.Y,
											X2 = pathEndPoint.X, Y2 = pathEndPoint.Y,
											
										StrokeEndLineCap = PenLineCap.Triangle,
											StrokeThickness = 3,
											Tag = new LineInfo() {id1 = pathStartId , id2 = pathEndId, len = len.length, label = new Label() { Content = len.length.ToString(), FontSize = 12, Background = Brushes.White} } }
										);

										Line line = lines[lines.Count - 1];

										if (pathStartPoint.X <= pathEndPoint.X && pathStartPoint.Y <= pathEndPoint.Y) {
											line.Stroke = new LinearGradientBrush(Colors.Black, Colors.Red,
											new Point(0.5, 0.5), new Point(1, 1));
										}
										else if (pathStartPoint.X >= pathEndPoint.X && pathStartPoint.Y >= pathEndPoint.Y) {
											line.Stroke = new LinearGradientBrush(Colors.Black, Colors.Red,
											new Point(0.5, 0.5), new Point(0, 0));
										}
										else if (pathStartPoint.X <= pathEndPoint.X && pathStartPoint.Y >= pathEndPoint.Y) {
											line.Stroke = new LinearGradientBrush(Colors.Black, Colors.Red,
											new Point(0.5, 0.5), new Point(1, 0));
										}
										else if (pathStartPoint.X >= pathEndPoint.X && pathStartPoint.Y <= pathEndPoint.Y) {
											line.Stroke = new LinearGradientBrush(Colors.Black, Colors.Red,
											new Point(0.5, 0.5), new Point(0, 1));
										}

										Canvas.SetZIndex(line, 1);
										field.Children.Add(line);
										Canvas.SetZIndex((line.Tag as LineInfo).label, 3);
										Canvas.SetTop((line.Tag as LineInfo).label, (line.Y1 + line.Y2) / 2 - (line.Tag as LineInfo).label.ActualHeight / 2);
										Canvas.SetLeft((line.Tag as LineInfo).label, (line.X1 + line.X2) / 2 - (line.Tag as LineInfo).label.ActualWidth / 2);
										field.Children.Add((line.Tag as LineInfo).label);

										nodes.AddPath(pathStartId, pathEndId, len.length);
										pathStartId = pathEndId = -1;

										bool firstRend = true;
										(line.Tag as LineInfo).label.LayoutUpdated += Label_Initialized;
										void Label_Initialized(object ssssender, EventArgs ssse) {
											if (firstRend) {
												Canvas.SetTop((line.Tag as LineInfo).label, (line.Y1 + line.Y2) / 2 - (line.Tag as LineInfo).label.ActualHeight / 2);
												Canvas.SetLeft((line.Tag as LineInfo).label, (line.X1 + line.X2) / 2 - (line.Tag as LineInfo).label.ActualWidth / 2);
												firstRend = !firstRend;
											}
										}

										line.MouseLeftButtonDown += Line_MouseLeftButtonDown;
										(line.Tag as LineInfo).label.MouseLeftButtonDown += Line_MouseLeftButtonDown;

										void Line_MouseLeftButtonDown(object iisender, MouseButtonEventArgs iie) {
											if (currMode == CurrentMode.RemovePath) {
												LineInfo info = line.Tag as LineInfo;
												nodes.RemovePath(info.id1, info.id2);
												field.Children.Remove(line);
												field.Children.Remove((line.Tag as LineInfo).label);
												lines.Remove(line);
											}
											else if (currMode == CurrentMode.ChangePath) {
												len = new InputLength();
												len.ShowDialog();
												if (len.length != 0) {
													(line.Tag as LineInfo).label.Content = len.length.ToString();
													(line.Tag as LineInfo).len = len.length;
													nodes.RemovePath((line.Tag as LineInfo).id1, (line.Tag as LineInfo).id2);
													nodes.AddPath((line.Tag as LineInfo).id1, (line.Tag as LineInfo).id2, (line.Tag as LineInfo).len);
												}
											}
										}
									}
								}
							}
							pathStart = !pathStart;
						}
						else if(currMode == CurrentMode.FindPath) {
							int id = (elem.Tag as SityInfo).nodeId;
							if (pathStart) {
								pathStartId = id;
								pathStartPoint = pos;
							}
							else {
								pathEndId = id;
								pathEndPoint = pos;
								if (pathEndId != pathStartId) {
									MessageBox.Show(nodes.ShortestPath(pathStartId, pathEndId).ToString());
								}
							}
							pathStart = !pathStart;
						}
						else if(currMode == CurrentMode.None) {
							moveNode = true;
							moveNodeId = (elem.Tag as SityInfo).nodeId;
						}
					}
				}
			}
		}

		void ClearMode(object sender, MouseButtonEventArgs e) {
			currMode = CurrentMode.None;
			this.Cursor = Cursors.Arrow;
		}

		private void Field_MouseLeftButtonDown() {
			switch (currMode) {
			case CurrentMode.RemoveSity:
			break;
			case CurrentMode.AddPath:
			break;
			case CurrentMode.RemovePath:
			break;
			case CurrentMode.None:
			break;
			}
		}

		private void EndMoveNode(object sender, MouseButtonEventArgs e) {
			EndMoveNodeBase(e.GetPosition(field));
		}

		private void field_MouseMove(object sender, MouseEventArgs e) {
			moveNode = EndMoveNodeBase(e.GetPosition(field));
		}

		bool EndMoveNodeBase(Point pos) {
			if (currMode == CurrentMode.None && moveNode) {
				moveNode = false;
				var elem = sities[moveNodeId];
				Canvas.SetLeft(elem, pos.X - elem.Width / 2);
				Canvas.SetTop(elem, pos.Y - elem.Height / 2);
				foreach (var line in lines) {
					var info = line.Tag as LineInfo;
					if (info.id1 == moveNodeId) {
						line.X1 = pos.X;
						line.Y1 = pos.Y;
					}
					else if (info.id2 == moveNodeId) {
						line.X2 = pos.X;
						line.Y2 = pos.Y;
					}
					pathStartPoint.X = line.X1;
					pathEndPoint.X = line.X2;
					pathStartPoint.Y = line.Y1;
					pathEndPoint.Y = line.Y2;
					if (info.id2 == moveNodeId || info.id1 == moveNodeId) {
						Canvas.SetTop((line.Tag as LineInfo).label, (line.Y1 + line.Y2) / 2 - (line.Tag as LineInfo).label.ActualHeight / 2);
						Canvas.SetLeft((line.Tag as LineInfo).label, (line.X1 + line.X2) / 2 - (line.Tag as LineInfo).label.ActualWidth / 2);
						if (pathStartPoint.X <= pathEndPoint.X && pathStartPoint.Y <= pathEndPoint.Y) {
							line.Stroke = new LinearGradientBrush(Colors.Black, Colors.Red,
							new Point(0.5, 0.5), new Point(1, 1));
						}
						else if (pathStartPoint.X >= pathEndPoint.X && pathStartPoint.Y >= pathEndPoint.Y) {
							line.Stroke = new LinearGradientBrush(Colors.Black, Colors.Red,
							new Point(0.5, 0.5), new Point(0, 0));
						}
						else if (pathStartPoint.X <= pathEndPoint.X && pathStartPoint.Y >= pathEndPoint.Y) {
							line.Stroke = new LinearGradientBrush(Colors.Black, Colors.Red,
							new Point(0.5, 0.5), new Point(1, 0));
						}
						else if (pathStartPoint.X >= pathEndPoint.X && pathStartPoint.Y <= pathEndPoint.Y) {
							line.Stroke = new LinearGradientBrush(Colors.Black, Colors.Red,
							new Point(0.5, 0.5), new Point(0, 1));
						}
					}
				}
				return true;
			}
			return false;
		}

		

		private void Window_SizeChanged(object sender, SizeChangedEventArgs e) {
			fieldBackground.Height = e.NewSize.Height - statusBar.ActualHeight - this.menuStrip.ActualHeight - 62;
			fieldBackground.Width = e.NewSize.Width - GridWithInfo.Width - 42;
		}

		class LineInfo {
			public int id1, id2;
			public uint len;
			public Label label;
		}
	}

}
