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

	void Start() {
		gameHelper = FindObjectOfType<GameHelper>();
		if (isLocalPlayer) {
			gameHelper.playerHelper = this;
			Camera.main.gameObject.GetComponent<CameraHelper>().enabled = true;
		}
		sr = GetComponent<SpriteRenderer>();
	}

	void Update() {
		ChangeSize(size);
		sr.color = color;

		if (!isLocalPlayer || !Application.isFocused)
			return;

		MoveToMouse();
		CheckBounds();
	}

	public override void OnNetworkDestroy() {
		if (isLocalPlayer) 
			Camera.main.gameObject.GetComponent<CameraHelper>().enabled = false;
	}

	void OnTriggerStay2D(Collider2D collider) {
		if (collider.gameObject.tag == "Food") {
			ChangeSize(size + collider.gameObject.GetComponent<PointHelper>().sizeFromFood);
			NetworkServer.Destroy(collider.gameObject);
		}
		else if (collider.gameObject.tag == "Player") {
			PlayerHelper enemy = collider.gameObject.GetComponent<PlayerHelper>();
			if (enemy.size < this.size) {
				Collider2D currentCollider = GetComponent<Collider2D>();
				Vector2 centerEnemy = collider.bounds.center,
						centerCurrent = currentCollider.bounds.center;
				if (Vector2.Distance(centerCurrent, centerEnemy) < currentCollider.bounds.size.x) {
					ChangeSize(size + enemy.size);
					NetworkServer.Destroy(collider.gameObject);
				}
			}
		}
	}

	void MoveToMouse() {
		Vector2 mousePos = Camera.main.ScreenToWorldPoint(Input.mousePosition);
		transform.position = Vector3.MoveTowards(transform.position, mousePos, speed * Time.deltaTime);
	}

	void CheckBounds() {
		if (transform.position.x >= gameHelper.mapSize.x)
			transform.position = new Vector3(gameHelper.mapSize.x - 0.01f, transform.position.y, 0);
		else if (transform.position.x <= -gameHelper.mapSize.x)
			transform.position = new Vector3(-gameHelper.mapSize.x + 0.01f, transform.position.y, 0);

		if (transform.position.y >= gameHelper.mapSize.y)
			transform.position = new Vector3(transform.position.x, gameHelper.mapSize.y - 0.01f, 0);
		else if (transform.position.y <= -gameHelper.mapSize.y)
			transform.position = new Vector3(transform.position.x, -gameHelper.mapSize.y + 0.01f, 0);
	}

	void ChangeSize(float newSize) {
		size = newSize;
		speed = speedMod / size;
		transform.localScale = new Vector3(size, size, size);
	}
}
