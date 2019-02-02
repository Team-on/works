using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraHelper : MonoBehaviour {
	internal GameHelper gameHelper;

	void Start() {
		gameHelper = FindObjectOfType<GameHelper>();
	}

	void Update() {
		if (gameHelper == null || gameHelper.playerHelper == null)
			return;

		transform.position = Vector3.Lerp(
			transform.position,
			new Vector3(gameHelper.playerHelper.transform.position.x, gameHelper.playerHelper.transform.position.y, transform.position.z),
			Time.deltaTime
		);
	}
}
