using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class PlayerController : MonoBehaviour {
	public float speed;
	public Text scoreText;
	public Text winText;

	Rigidbody rb;
	int score;
	const int maxScore = 12;

	void Start() {
		rb = GetComponent<Rigidbody>();
		score = 0;
		scoreText.text = "Score: " + score.ToString();
		winText.text = "";
	}

	void FixedUpdate() {
		float moveHorizontal = Input.GetAxis("Horizontal"),
			  moveVertical = Input.GetAxis("Vertical");
		Vector3 movement = new Vector3(moveHorizontal * speed, 0, moveVertical * speed);

		rb.AddForce(movement);
	}

	void OnTriggerEnter(Collider other) {
		if (other.gameObject.CompareTag("pickup")) {
			other.gameObject.SetActive(false);
			scoreText.text = "Score: " + (++score).ToString();

			if(score == maxScore)
				winText.text = "You win!";
		}
	}
}
