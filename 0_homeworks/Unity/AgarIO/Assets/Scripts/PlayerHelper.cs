using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Networking;

public class PlayerHelper : NetworkBehaviour {
	public float speedMod = 1f;
	public Vector2 mapSize = new Vector2(20, 20);

	[SyncVar]
	public float size = 0.2f;
	[SyncVar]
	public Color color = Color.blue;
	[SyncVar]
	public float speed = 5;

	SpriteRenderer sr;

	void Start() {
		sr = GetComponent<SpriteRenderer>();
		
		ChangeSize(size);
	}

	void Update() {
		transform.localScale = new Vector3(size, size, size);
		sr.color = color;

		if (!isLocalPlayer || !Application.isFocused)
			return;

		MoveToMouse();
		CheckBounds();
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

	[Server]
	void ChangeSize(float newSize) {
		size = newSize;
		speed = 1 / size;
		transform.localScale = new Vector3(size, size, size);
	}

	void MoveToMouse() {
		Vector2 mousePos = Camera.main.ScreenToWorldPoint(Input.mousePosition);
		transform.position = Vector3.MoveTowards(transform.position, mousePos, speed * Time.deltaTime);
	}

	void CheckBounds() {
		if (transform.position.x >= mapSize.x)
			transform.position = new Vector3(mapSize.x - 0.01f, transform.position.y, 0);
		else if (transform.position.x <= -mapSize.x)
			transform.position = new Vector3(-mapSize.x + 0.01f, transform.position.y, 0);

		if (transform.position.y >= mapSize.y)
			transform.position = new Vector3(transform.position.x, mapSize.y - 0.01f, 0);
		else if (transform.position.y <= -mapSize.y)
			transform.position = new Vector3(transform.position.x, -mapSize.y + 0.01f, 0);
	}
}
