using UnityEngine;

public class PlayerMovement : MonoBehaviour {
	public float speed = 6;

	Vector3 movement;
	Animator anim;
	Rigidbody rg;
	int floorMask;
	float camReyLength = 100;

	void Awake () {
		floorMask = LayerMask.GetMask("Floor");
		anim = GetComponent<Animator>();
		rg = GetComponent<Rigidbody>();
	}
	
	void FixedUpdate () {
		float h = Input.GetAxisRaw("Horizontal"),
			  v = Input.GetAxisRaw("Vertical");

		Move(h, v);
		Turning();
		Animating(h, v);
	}

	void Move(float h, float v) {
		movement.Set(h, 0, v);
		movement = movement.normalized * speed * Time.deltaTime;
		rg.MovePosition(transform.position + movement);
	}

	void Turning(){
		Ray camRay = Camera.main.ScreenPointToRay(Input.mousePosition);
		RaycastHit floorHit;

		if(Physics.Raycast(camRay, out floorHit, camReyLength, floorMask)){
			Vector3 playerToMouse = floorHit.point - transform.position;
			playerToMouse.y = 0;

			rg.MoveRotation(Quaternion.LookRotation(playerToMouse));
		}
	}

	void Animating(float h, float v) {
		anim.SetBool("IsWalking", h != 0 || v != 0);
	}
}
