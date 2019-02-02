using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Networking;

public class PlayerHelper : NetworkBehaviour {
	public const float speedMod = 1f;
	
	[SyncVar]
	public float size = 0.2f;
	[SyncVar]
	public Color color = Color.blue;

	internal GameHelper gameHelper;

	[SyncVar]
	float speed;
	SpriteRenderer sr;

	void Start () {
		gameHelper = FindObjectOfType<GameHelper>();
		if (isLocalPlayer) {
			gameHelper.playerHelper = this;
			Camera.main.gameObject.GetComponent<CameraHelper>().enabled = true;
		}
		sr = GetComponent<SpriteRenderer>();
	}
	
	void Update () {
		ChangeSize(size);
		sr.color = color;

		if (!isLocalPlayer || !Application.isFocused)
			return;

		Vector2 mousePos = Camera.main.ScreenToWorldPoint(Input.mousePosition);
		transform.position = Vector3.MoveTowards(transform.position, mousePos, speed * Time.deltaTime);
	}

	[Server]
	void OnTriggerStay2D(Collider2D collider) {
		ChangeSize(size + collider.gameObject.GetComponent<PointHelper>().sizeFromFood);
		NetworkServer.Destroy(collider.gameObject);
	}

	[Server]
	void ChangeSize(float newSize){
		size = newSize;
		speed = speedMod / size;
		transform.localScale = new Vector3(size, size, size);
	}
}
