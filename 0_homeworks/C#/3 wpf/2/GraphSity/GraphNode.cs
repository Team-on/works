using System;
using System.Collections;
using System.Collections.Generic;

namespace GraphSity {
	class GraphNode : System.Collections.IEnumerable {
		public object tag;

		Lazy<Dictionary<GraphNode, uint>> paths;

		public GraphNode() {
			paths = new Lazy<Dictionary<GraphNode, uint>>();
		}

		public void AddPath(GraphNode node, uint len) => paths.Value.Add(node, len);

		public bool ContainPath() => paths.IsValueCreated;

		public IEnumerator GetEnumerator() {
			return paths.Value.GetEnumerator();
		}

		public void RemovePath(GraphNode node) => paths.Value.Remove(node);
	}
}
