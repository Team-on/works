using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Game.ComponentMessage;
using Game.GameObject;

namespace Game.Component {
	class TextureComponent : BaseComponent {
		public TextureId TextureId { get; private set; }

		TransformationComponent transformation;

		public TextureComponent(BaseGameObject owner, TextureId textureId) : base(owner) {
			TextureId = textureId;
		}

		public override void ProcessMessage(BaseComponentMessage msg) {
		}

		public override bool CheckDependComponents() {
			transformation = Owner.GetComponent<TransformationComponent>();
			return transformation != null;
		}
	}
}
