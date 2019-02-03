using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[RequireComponent(typeof(CharacterController))]
[AddComponentMenu("Control Script/FPS Input")]
public class KeyboardMove : MonoBehaviour {
	public float speed = 6f;
	public float gravity = -9.8f;

	CharacterController cc;

	void Start() {
		cc = GetComponent<CharacterController>();
	}

	void Update() {
		float deltaX = Input.GetAxis("Horizontal") * speed;
		float deltaZ = Input.GetAxis("Vertical") * speed;

		Vector3 movement = new Vector3(deltaX, 0, deltaZ);
		movement = Vector3.ClampMagnitude(movement, speed);
		movement.y = gravity;
		movement *= Time.deltaTime;
		movement = transform.TransformDirection(movement);
		cc.Move(movement);
	}
}
