using System;

namespace DBUnlinked {
	/// <summary>
	/// Вказує що властивість буде колонкою таблиці.
	/// Має бути вказаний обовязково
	/// Властивість має мати публічні get i set. Інакше вона буде ігноруватися.
	/// Якщо властивість це struct(або примітивні типи як int, char...) то властивість має Nullable(int?, char?) 
	/// </summary>
	[AttributeUsage(AttributeTargets.Property)]
	public sealed class UlTableColumnAttribute : Attribute {
		internal bool isPrimaryKey;
		internal bool notNull;
		internal string dbType;
		internal string name;

		public UlTableColumnAttribute(bool IsPrimaryKey = false, bool NotNull = true, string DBType = null, string Name = null) {
			isPrimaryKey = IsPrimaryKey;
			notNull = NotNull;
			dbType = DBType;
			name = Name;
		}

		public override bool Equals(object obj) {
			if(obj is UlTableColumnAttribute o)
				return isPrimaryKey == o.isPrimaryKey && notNull == o.notNull && dbType == o.dbType && name == o.name;
			return false;
		}
	}

	/// <summary>
	/// Вказує що клас буде таблицею
	/// Можна пропустити
	/// </summary>
	[AttributeUsage(AttributeTargets.Class)]
	public sealed class UlTableAttribute : Attribute {
		internal string name;

		public UlTableAttribute(string Name = null) {
			name = Name;
		}

		public override bool Equals(object obj) {
			if(obj is UlTableAttribute o)
				return name == o.name;
			return false;
		}
	}
}

