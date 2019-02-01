using UnityEngine;
using UnityEngine.UI;

public class GameHelper : MonoBehaviour {
	public InputField input;
	public Text text;

	internal PlayerHelper localPlayerHelper;

	void Start() {
	}


	void Update() {

	}

	public void Send(){
		if (localPlayerHelper != null)
		localPlayerHelper.Send(input.text);
	}
}
