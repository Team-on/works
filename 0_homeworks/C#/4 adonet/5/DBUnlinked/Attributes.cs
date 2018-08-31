using System;

namespace DBUnlinked {
	/// <summary>
	/// Вказує що властивість буде колонкою таблиці.
	/// Властивість має мати публічні get i set. Інакше вона буде ігноруватися.
	/// Якщо властивість це struct(або примітивні типи як int, char...) то властивість має Nullable(int?, char?) 
	/// </summary>
	[AttributeUsage(AttributeTargets.Property)]
	public sealed class UlTableColumn : Attribute {
		bool isPrimaryKey;

		public UlTableColumn(bool IsPrimaryKey = false) {
			isPrimaryKey = IsPrimaryKey;
		}
	}
}

