using System;
using System.Collections.Generic;
using System.Linq;

using Game.GameObject;
using Game.ComponentMessage;

namespace Game.Component {
	abstract class BaseComponent {
		public BaseGameObject Owner { get; protected set; }

		protected BaseComponent(BaseGameObject owner) {
			Owner = owner;
			if (!CheckDependComponents())
				throw new ApplicationException("No linked component");
		}

		public abstract void ProcessMessage(BaseComponentMessage msg);

		public virtual bool CheckDependComponents() {
			return true;
		}
	}
}
