using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace GraphSity {
	class SityInfo {
		public int nodeId;
		Point pos;
		public Point Pos => pos;

		public SityInfo(int NodeId, Point point) {
			nodeId = NodeId;
			pos = point;
		}
	}
}
