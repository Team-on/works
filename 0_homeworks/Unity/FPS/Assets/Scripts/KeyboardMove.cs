using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class KeyboardMove : MonoBehaviour {
	public float speed = 6f;
	//public float airMovementMult = 0.3f;
	public float jumpForce = 9.8f;

	bool inAir = false;

	Rigidbody rb;

	void Start() {
		rb = GetComponent<Rigidbody>();
	}

	void Update() {
		float deltaX = Input.GetAxis("Horizontal") * speed;
		float deltaZ = Input.GetAxis("Vertical") * speed;

		Vector3 movement = new Vector3(deltaX, 0, deltaZ);
		movement = Vector3.ClampMagnitude(movement, speed);
		movement *= Time.deltaTime;

		//if (inAir)
		//	movement *= airMovementMult;

		movement = transform.TransformDirection(movement);

		rb.MovePosition(rb.position + movement);

		if (!inAir && Input.GetKeyDown(KeyCode.Space)) {
			inAir = true;
			rb.AddForce(transform.up * jumpForce, ForceMode.Impulse);
		}
	}

	void OnCollisionEnter(Collision collision) {
		inAir = false;
	}
}
