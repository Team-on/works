#pragma once

namespace CppCLR_WinformsProjekt {
	using namespace System;
	using namespace System::ServiceModel;

	[ServiceContract]
	interface class IServiseTest {
		[OperationContract]
		int GetNumber();
	};

	ref class ServiseTest : IServiseTest {
	public:
		virtual int GetNumber() {
			return 22;
		}
	};
}