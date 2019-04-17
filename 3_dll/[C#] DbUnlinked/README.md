# DbUnlinked
 Eazy access to database using custom List implementition. Works with MS SQL Server

## Features
 * Work with DB like its List<T>
 * Create table based on user-defined classes
 
## API
 * **UlDb** - class for working with DB
	* **CreateOrLinkToDB(string connectionString, string dbName, bool alwaysRecreate = false)** - Create/link to DB
		* **connectionString** - Default connectionString, but without Initial Catalog
		* **dbName** - DB name
		* **alwaysRecreate** - always create DB(if its already exist, old DB will be drop)
	* Or you can invoke **bool CreateOrLinkToDB(string connectionString, string dbName, bool alwaysRecreate = false)**. It return bool IsDBWasCreated
	* **CreateOrLinkToTable<T>()** - pass your class with table data as T. Return **UlTable<T>**
   
 * **UlTable<T>** - class for working with table
	* inherit IEnumerable<T>, so it contain almost all IList<T> methods
	* **Fill()** - Read table from DB
	* **Update()** - Copy local changes to DB
	* **UlTableColumnAttribute[] GetColumnAttributes()** - Return array with columns attributes
	* Supported types for auto-define: 
		* System.Byte
		* System.Int16
		* System.Int32
		* System.Int64
		* System.Float
		* System.Double
		* System.Decimal
		* System.DateTime
		* System.String (will be nvarchar(100))
		* For any other type will be used nvarchar(100) and .ToString() for saving
	
 * **UlTable<T>** will be work with user-defined types T, only if:
	* Class contain attribute **UlTable**. But you can skip it, and attribute will add automatically
		* **string name** - table name
	* His public properties must have **UlTableColumn** attribute
		* **bool isPrimaryKey** - Is it primary key
		* **bool notNull** - is it can be NULL. Ignore if isPrimaryKey = true
		* **string dbType** - data type in table
		* **string name** - column name in table
		* Fields will fill automatically, if you left it empty

 
## Made with
 * С#
 * ADO.NET
