namespace TeamCommander {
	namespace Elements {
		interface Element {
			ushort Id { get; }

			void SetElement(string ElementStr, Support.Coord StartPos, ushort NewId);
			void SetElement(Output.OutputObj[] Element, Support.Coord StartPos, ushort NewId);

			void OnPassIntoDirector(Output.Output Output);

			void AddElementToOutput();
			void Clear();
		}

		interface ActiveElement : Element {
			ushort ActiveId { get; set; }
		}

		interface InputElement : ActiveElement {
			void SetMask(string Mask);
			void SetStartInput(string startInput);

			void SetInput(string Input);
			void FlushInput();
			void AddToInput(char sym);
			string GetInput();
		}

		interface StaticElement : Element {

		}

		interface EternalElement : Element {

		}

		//Самий базовий клас для більшості елементів
		class ElementText : StaticElement {
			protected Output.OutputObj[] element;
			protected Support.Coord startPos;
			Output.Output output;

			public ushort Id { get; private set; }

			public ElementText() {
			}

			public ElementText(string ElementStr, Support.Coord StartPos, ushort NewId) {
				Output.OutputObj[] Element = new Output.OutputObj[ElementStr.Length];
				for (int i = 0; i < Element.Length; ++i)
					Element[i] = new Output.OutputObj(ElementStr[i]);
				SetElement(Element, StartPos, NewId);
			}

			public ElementText(Output.OutputObj[] Element, Support.Coord StartPos, ushort NewId) {
				SetElement(Element, StartPos, NewId);
			}

			public void SetElement(string ElementStr, Support.Coord StartPos, ushort NewId) {
				Output.OutputObj[] Element = new Output.OutputObj[ElementStr.Length];
				for (int i = 0; i < Element.Length; ++i)
					Element[i] = new Output.OutputObj(ElementStr[i]);
				Id = NewId;
				element = (Output.OutputObj[])Element.Clone();
				startPos = new Support.Coord(StartPos.x, StartPos.y);
			}

			public void SetElement(Output.OutputObj[] Element, Support.Coord StartPos, ushort NewId) {
				Id = NewId;
				element = (Output.OutputObj[])Element.Clone();
				startPos = new Support.Coord(StartPos.x, StartPos.y);
			}

			public void OnPassIntoDirector(Output.Output Output) {
				output = Output;
				//startPos.x += StartPosChange.x;
				//startPos.y += StartPosChange.y;
			}

			virtual public void AddElementToOutput() {
				output.AddOn(element, startPos);
			}

			public void Clear() {
				output.ClearOn(element, startPos);
			}
		}

		class ElementHLine : ElementText {
			public ElementHLine() {
			}
			public ElementHLine(short length, Output.OutputObj style, Support.Coord StartPos, ushort NewId) {
				Output.OutputObj[] element = new Output.OutputObj[length];
				for (short i = 0; i < length; ++i)
					element[i] = (Output.OutputObj)style.Clone();
				SetElement(element, StartPos, NewId);
			}
		}

		class ElementVLine : ElementText {
			public ElementVLine(short length, Output.OutputObj style, Support.Coord StartPos, ushort NewId) {
				Output.OutputObj[] element = new Output.OutputObj[length * 2];
				for (short i = 0; i < length * 2; ++i) {
					element[i] = (Output.OutputObj)style.Clone();
					element[++i] = new Output.OutputObj('\n');
				}
				SetElement(element, StartPos, NewId);
			}
		}

		//При кожному виклиці братиме нове значення для стрінгі із функції
		class ElementTextFromFunc : ElementText {
			public delegate string usedFunc();

			protected usedFunc func;

			public ElementTextFromFunc(Output.OutputObj[] Element, Support.Coord StartPos, ushort NewId, usedFunc Func)
				: base(Element, StartPos, NewId) {
				func = Func;
			}

			public override void AddElementToOutput() {
				ushort i = 0;
				foreach (char c in func.Invoke())
					base.element[i++].sym = c;
				base.AddElementToOutput();
			}
		}


		class ElemenEternaltHLine : ElementHLine, EternalElement {
			public ElemenEternaltHLine(short length, Output.OutputObj style, Support.Coord StartPos, ushort NewId) : base(length, style, StartPos, NewId) {
			}
		}

		class ElementEternalVLine : ElementVLine, EternalElement {
			public ElementEternalVLine(short length, Output.OutputObj style, Support.Coord StartPos, ushort NewId) : base(length, style, StartPos, NewId) {
			}
		}

		class ElementEternalText : ElementText, EternalElement {
			public ElementEternalText(Output.OutputObj[] Element, Support.Coord StartPos, ushort NewId) : base(Element, StartPos, NewId) {
			}
		}


		class ElementBtn : ElementText, ActiveElement {
			public  ushort ActiveId { get; set; }

			public ElementBtn(Output.OutputObj[] Element, Support.Coord StartPos, ushort NewId, ushort NewActiveId) : base(Element, StartPos, NewId) {
				ActiveId = NewActiveId;
			}


		}

		//class ElementBtnWithFrame : ElementBtn {

		//}
	}
}
