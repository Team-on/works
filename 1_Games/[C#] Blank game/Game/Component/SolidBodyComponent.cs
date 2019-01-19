using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Game.ComponentMessage;
using Game.GameObject;

namespace Game.Component {
	class SolidBodyComponent : BaseComponent{
		public bool IsSemisolid { get; private set; }

		TransformationComponent transformation;

		public SolidBodyComponent(BaseGameObject owner, bool isSemisolid) : base(owner) {
			IsSemisolid = isSemisolid;
		}

		public override void ProcessMessage(BaseComponentMessage msg) {

		}

		public override bool CheckDependComponents() {
			transformation = Owner.GetComponent<TransformationComponent>();
			return transformation != null;
		}
	}
}
