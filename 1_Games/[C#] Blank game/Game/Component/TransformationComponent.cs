using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Game.Common;
using Game.ComponentMessage;
using Game.GameObject;

namespace Game.Component {
	class TransformationComponent : BaseComponent {
		public Coord Pos { get; private set; }
		public Size Size { get; private set; }
		public short Angle { get; private set; }

		public TransformationComponent(BaseGameObject owner, Coord pos, Size size, short angle) : base(owner) {
			Pos = (Coord)pos.Clone();
			Size = (Size)size.Clone();
			Angle = angle;
		}

		public override void ProcessMessage(BaseComponentMessage msg) {

		}
	}
}
