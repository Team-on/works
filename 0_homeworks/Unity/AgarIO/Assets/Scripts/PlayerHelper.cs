using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Networking;

public class PlayerHelper : NetworkBehaviour {
	public const float speedMod = 1f;
	
	[SyncVar]
	public float size = 0.2f;

	[SyncVar]
	float speed;

	void Start () {
		ChangeSize(size);
	}
	
	void Update () {

		if (!isLocalPlayer)
			return;

		Vector2 mousePos = Camera.main.ScreenToWorldPoint(Input.mousePosition);
		transform.position = Vector3.MoveTowards(transform.position, mousePos, speed * Time.deltaTime);
	}

	[Server]
	void ChangeSize(float newSize){
		size = newSize;
		speed = speedMod / size;
		transform.localScale = new Vector3(size, size, size);
	}
}
