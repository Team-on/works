using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerController : MonoBehaviour {
	public float speed;
	Rigidbody rb;

	void Start() {
		rb = GetComponent<Rigidbody>();
	}

	void FixedUpdate() {
		float moveHorizontal = Input.GetAxis("Horizontal"),
			  moveVertical = Input.GetAxis("Vertical");
		Vector3 movement = new Vector3(moveHorizontal * speed, 0, moveVertical * speed);
			
		rb.AddForce(movement);
	}


}
