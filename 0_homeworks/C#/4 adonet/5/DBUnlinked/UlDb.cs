using System;

namespace DBUnlinked {
	/// <summary>
	/// Працює лише з MS SQL Server
	/// </summary>
	public class UlDb {

		/// <summary>
		/// Викликає CreateOrLinkToDB всередині
		/// </summary>
		public UlDb(string connectionString, string initialCatalog) {
			CreateOrLinkToDB(connectionString, initialCatalog);
		}

		/// <summary>
		/// Створює чи привязуються до БД.
		/// </summary>
		/// <param name="connectionString">Стандартна connectionString, але без InitialCatalog(Database)</param>
		/// <param name="InitialCatalog">InitialCatalog = master якщо завжди створювати нову БД(перезаписувати).
		/// Інакше вказати бажане імя для БД і вона буде створена при потребі.
		/// </param>
		/// <returns>true якщо була створена нова БД</returns>
		public bool CreateOrLinkToDB(string connectionString, string initialCatalog) {
			return false;
		}

		public UlTable<T> CreateOrLinkToTable<T>() {
			return null;
		}
	}
}
