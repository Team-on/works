namespace MyProtocol {
	public enum CommandType : byte {
		None,
		Connect,
		Abort,
		Exit,
		String,
		RawData
	}
}
