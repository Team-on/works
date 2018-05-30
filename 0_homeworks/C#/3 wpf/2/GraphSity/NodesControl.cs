using System;
using System.Collections;
using System.Collections.Generic;

namespace GraphSity {
	class NodesControl : IEnumerable {
		List<GraphNode> nodes;

		public NodesControl() {
			nodes = new List<GraphNode>();
		}

		public IEnumerator GetEnumerator() => ((IEnumerable)nodes).GetEnumerator();

		public void AddNode(GraphNode node) => nodes.Add(node);
		public void MakePath(GraphNode from, GraphNode to, uint len) => nodes.Find((a) => a == from)?.AddPath(to, len);
		public void RemovePath(GraphNode from, GraphNode to) => nodes.Find((a) => a == from)?.RemovePath(to);

		public uint FindShortestPath(GraphNode from, GraphNode to) {
			List<PATH> mins = new List<PATH>();
			uint passedLen = 0;

			Rec(from);

			return passedLen;

			bool Rec(GraphNode node) {
				if (node == to)
					return true;

				if (node.ContainPath()) {
					foreach (KeyValuePair<GraphNode, uint> i in node)
						mins.Add(new PATH() { from = node, to = i.Key, len = i.Value });

					uint min = mins[0].len;
					foreach (PATH i in mins) 
						if (i.len < min)
							min = i.len;

					List<GraphNode> nextNodes = new List<GraphNode>();
					while (mins.Find((a) => a.len == min) != null) {
						var find = mins.Find((a) => a.len == min);
						nextNodes.Add(find.to);
						mins.Remove(find);
					}

					passedLen += min;

					foreach (var i in nextNodes) {
						bool rez = Rec(i);
						if (rez)
							return rez;
					}

				}

				return false;
			}
		}

		class PATH {
			public GraphNode from, to;
			public uint len;
		}


	}
}
