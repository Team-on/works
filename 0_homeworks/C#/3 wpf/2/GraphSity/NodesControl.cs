﻿using System;
using System.Collections;
using System.Collections.Generic;
using System.Windows;

namespace GraphSity {
	class NodesControl : IEnumerable {
		List<List<NodeInfo>> nodes;

		public NodesControl() {
			nodes = new List<List<NodeInfo>>();
		}

		public IEnumerator GetEnumerator() => ((IEnumerable)nodes).GetEnumerator();

		public int AddNode() {
			nodes.Add(new List<NodeInfo>());
			return nodes.Count - 1;
		}
		public void RemoveNode(int id) {
			foreach (var i in nodes) {
				var find = i.Find((a) => id == a.nodeId);
				while (find != null) {
					i.Remove(find);
					find = i.Find((a) => id == a.nodeId);
				}
			}
			nodes.RemoveAt(id);
		}

		public void AddPath(int from, int to, uint len) => nodes[from].Add(new NodeInfo() { nodeId = to, len = len });
		public void RemovePath(int from, int to) {
			var find = nodes[from].Find((a) => to == a.nodeId);
			if (find != null)
				nodes[from].Remove(find);
		}

		public uint ShortestPath(int from, int to) {
			List<int> visited = new List<int>();
			List<uint> ans = new List<uint>();
			List<PathInfo> mins = new List<PathInfo>();
			uint passed = 0;

			AddToMinsFromNode(from);
			Rec(from);

			//string str = "";
			//for(int i = 0; i < nodes.Count; ++i) {
			//	for (int j = 0; j < nodes[i].Count; ++j)
			//		str += nodes[i][j].len + " | ";
			//	str += "\n";
			//}

			//System.Windows.MessageBox.Show(str);
			System.Windows.MessageBox.Show("REZULT: " + passed.ToString());
			//foreach (var i in ans) 
				//MessageBox.Show("Ans: " + i.ToString());

			return passed;

			bool Rec(int currId) {
				if (currId == to) {
					ans.Add(passed);
					return true;
				}

				if (visited.Contains(currId))
					return false;
				visited.Add(currId);

				if(nodes[currId].Count != 0) {
					//string str1 = "";
					//foreach (var a in mins) 
					//	str1 += a.from + "-" + a.to + ": " + a.len + "\n";
					//MessageBox.Show(str1);

					uint min = mins[0].len;
					foreach (var i in mins)
						if (i.len < min) 
							min = i.len;

					//MessageBox.Show("Min: " + min.ToString());

					List<int> nextNodes = new List<int>();
					var find = mins.Find((a) => a.len == min);
					while (find != null) {
						nextNodes.Add(find.to);
						mins.Remove(find);
						find = mins.Find((a) => a.len == min);
					}

					//str1 = "";
					//foreach (var a in mins)
					//	str1 += a.from + "-" + a.to + ": " + a.len + "\n";
					//MessageBox.Show(str1);

					passed = min;

					foreach (var i in nextNodes) 
						AddToMinsFromNode(i);
					foreach (var i in nextNodes) 
						Rec(i);
				}

				return false;

				
			}

			void AddToMinsFromNode(int nodeId) {
				foreach (var i in nodes[nodeId]) {
					uint currLen = i.len + passed;
					var find = mins.Find((a)=>a.to == i.nodeId);
					if(find == null || (find != null && find.len == currLen))
						mins.Add(new PathInfo() { len = currLen, from = nodeId, to = i.nodeId });
					else if(find.len > currLen) {
						mins.RemoveAll((a) => a.to == i.nodeId);
						mins.Add(new PathInfo() { len = currLen, from = nodeId, to = i.nodeId });
					}
				}
			}
		}

		class NodeInfo {
			public uint len;
			public int nodeId;
		}

		class PathInfo {
			public uint len;
			public int from, to;
		}
	}

}
