using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Linq;

using Game.Component;
using Game.ComponentMessage;

namespace Game.GameObject {
	abstract class BaseGameObject {
		static ulong lastId = 0;

		public GameObjectType GOType { get; protected set; }
		public BaseGameObject Parent { get; protected set; }
		public BaseComponent[] Components => components.ToArray();
		public ulong Id { get; private set; }
		public bool IsDisposed { get; protected set; }

		protected readonly List<BaseComponent> components;
		
		readonly ConcurrentQueue<BaseComponentMessage> messageQueue;

		protected BaseGameObject(GameObjectType goType, BaseGameObject parent) {
			components = new List<BaseComponent>();
			messageQueue = new ConcurrentQueue<BaseComponentMessage>();
			Id = ++lastId;
			IsDisposed = false;

			this.GOType = goType;
			this.Parent = parent;
		}

		public void Dispose() => IsDisposed = true;

		public T GetComponent<T>() where T : BaseComponent {
			foreach (var c in components)
				if (c.GetType() == typeof(T) || c.GetType().IsSubclassOf(typeof(T)))
					return c as T;
			return null;
		}

		public void SendMessage(BaseComponentMessage msg) => messageQueue.Enqueue(msg);
		bool TryReadMessage(out BaseComponentMessage msg) => messageQueue.TryDequeue(out msg);

		public void Process() {
			if (IsDisposed)
				return;

			SendMessage(new TickMessage());

			while (messageQueue.Count > 0) {
				if (messageQueue.TryDequeue(out BaseComponentMessage msg))
					foreach (var component in components)
						component.ProcessMessage(msg);
			}
		}
	}
}
