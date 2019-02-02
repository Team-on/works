using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraHelper : MonoBehaviour {
	internal GameHelper gameHelper;

	void Start() {
		gameHelper = FindObjectOfType<GameHelper>();
	}

	void Update() {
		transform.position = Vector3.Lerp(
			transform.position,
			new Vector3(gameHelper.playerHelper.transform.position.x, gameHelper.playerHelper.transform.position.y, transform.position.z),
			Time.deltaTime
		);
	}
}
