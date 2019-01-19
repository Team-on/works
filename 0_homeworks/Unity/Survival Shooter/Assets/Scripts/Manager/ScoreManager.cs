using UnityEngine;
using UnityEngine.UI;
using System.Collections;

public class ScoreManager : MonoBehaviour {
	public static int score;        // The player's score.

	Text text;                      // Reference to the Text component.

	void Awake() {
		text = GetComponent<Text>();

		score = 0;
	}


	void Update() {
		text.text = "Score: " + score;
	}
}