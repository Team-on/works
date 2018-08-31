using System;

namespace DBUnlinked {
	/// <summary>
	/// Вказує що властивість буде колонкою таблиці.
	/// Властивість має мати публічні get i set. Інакше вона буде ігноруватися.
	/// Якщо властивість це struct(або примітивні типи як int, char...) то властивість має Nullable(int?, char?) 
	/// </summary>
	[AttributeUsage(AttributeTargets.Property)]
	public sealed class UlTableColumnAttribute : Attribute {
		bool isPrimaryKey;
		bool canBeNull;
		string dbType;
		string name;

		public UlTableColumnAttribute(bool IsPrimaryKey = false, bool CanBeNull = false, string DBType = "", string Name = "") {
			isPrimaryKey = IsPrimaryKey;
			canBeNull = CanBeNull;
			dbType = DBType;
			name = Name;
		}
	}

	/// <summary>
	/// Вказує що клас буде таблицею
	/// </summary>
	[AttributeUsage(AttributeTargets.Class)]
	public sealed class UlTableAttribute : Attribute {
		string name;

		public UlTableAttribute(string Name = "") {
			name = Name;
		}
	}
}

