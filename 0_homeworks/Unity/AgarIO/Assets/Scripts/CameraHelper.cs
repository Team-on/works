using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraHelper : MonoBehaviour {
	internal PlayerHelper playerHelper;

	void Start() {
		playerHelper = FindObjectOfType<PlayerHelper>();
	}

	void Update() {
		if (playerHelper == null) {
			playerHelper = FindObjectOfType<PlayerHelper>();
			return;
		}

		transform.position = Vector3.Lerp(
			transform.position,
			new Vector3(playerHelper.transform.position.x, playerHelper.transform.position.y, transform.position.z),
			Time.deltaTime
		);
	}
}
