namespace TeamCommander {
	namespace Elements {
		interface Element {
			ushort Id { get; }

			void SetElement(Output.OutputObj[] Element, Support.Coord StartPos, ushort NewId);

			void OnPassIntoDirector(Output.Output Output);

			void Print();
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

		class ElementText : StaticElement {
			Output.OutputObj[] element;
			Support.Coord startPos;
			Output.Output output;

			public ushort Id { get; private set; }

			public ElementText() {
			}
			public ElementText(Output.OutputObj[] Element, Support.Coord StartPos, ushort NewId) {
				SetElement(Element, StartPos, NewId);
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

			public void Print() {
				short currYPos = startPos.y;
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
				Output.OutputObj[] element = new Output.OutputObj[length * 2];
				for (short i = 0; i < length * 2; ++i) {
					element[i] = (Output.OutputObj)style.Clone();
					element[++i] = new Output.OutputObj('\n');
				}
				SetElement(element, StartPos, NewId);
			}
		}

		class ElementVLine : ElementText {

		}

		//class ElemenEternaltHLine : EternalElement {

		//}

		//class ElementEternalVLine : EternalElement {

		//}

		//class ElementEternalText : EternalElement {

		//}

		//class ElementBtn : ActiveElement {

		//}

		//class ElementBtnWithFrame : ElementBtn {

		//}
	}
}
